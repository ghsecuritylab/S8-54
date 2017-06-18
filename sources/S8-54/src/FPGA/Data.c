// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#define _INCLUDE_DATA_
#include "Data.h"
#undef _INCLUDE_DATA_
#include "Globals.h"
#include "Hardware/FLASH.h"
#include "Hardware/FSMC.h"
#include "Settings/SettingsMemory.h"
#include "Utils/ProcessingSignal.h"


/** @addtogroup FPGA
 *  @{
 *  @addtogroup Data
 *  @{
 */


/** \todo ���� ��������� ����� ������, ��� ��� ��������������� ������ ����� pDSROM �� ��������� � EPROM  ���������� �����.
        ������� ��������� ������ ���������� � ��� ��������� � ������ ������� ������.
        ����������� � ������� ��� ���� - ��� ���� ���������. */
static DataSettings dataSettingsROM;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8 *dataDirA = 0;     ///< ��������� ��������� ������.
static uint8 *dataDirB = 0;

static uint8 *dataRAMA = 0;     ///< ������, ������� ������ ���������� � ������ "���������".
static uint8 *dataRAMB = 0;

static uint8 *dataROMA = 0;     ///< \brief ������, ������� ������ ���������� � ������ "����� ��" ��� ���������� ������ ��� �����. 
static uint8 *dataROMB = 0;     ///< ��������� "������-����� ��-���������� ������".

static DataSettings *pDSDir = 0;
static DataSettings *pDSRAM = 0;
static DataSettings *pDSROM = 0;

static ModeWork currentModeWork = ModeWork_Dir;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Clear(void);
/// ������� ������ 
static void GetDataFromStorage(void);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Data_GetFromIntMemory(void)
{
    if(FLASH_GetData(NUM_ROM_SIGNAL, &pDSROM, &dataROMA, &dataROMB))
    {
        memcpy(&dataSettingsROM, (void*)pDSROM, sizeof(DataSettings));
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void GetDataFromStorage(void)
{
    int fromEnd = 0;

    if (IN_P2P_MODE &&                              // ��������� � ������ ����������� ������
        START_MODE_WAIT &&                          // � ������ ������ �������������
        DS_NumElementsWithCurrentSettings() > 1)    // � � ��������� ��� ���� ��������� ������� � ������ �����������
    {
        fromEnd = 1;
    }

    DS_GetDataFromEnd_RAM(fromEnd, &pDSDir, (uint16**)&dataDirA, (uint16**)&dataDirB);

    if (sDisplay_NumAverage() != 1 || IN_RANDOM_MODE)
    {
        ModeFSMC mode = FSMC_GetMode();
        FSMC_SetMode(ModeFSMC_RAM);
        Data_GetAverageFromDataStorage();
        FSMC_SetMode(mode);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_GetAverageFromDataStorage(void)
{
    dataChan[A] = DS_GetAverageData(A);
    dataChan[B] = DS_GetAverageData(B);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_Load(void)
{
    Clear();

    if (DS_NumElementsInStorage() == 0)
    {
        return;
    }

    if (MODE_WORK_DIR)                              // ���� ��������� � �������� ������
    {   
        GetDataFromStorage();                       // ��������� ������ �� ���������

        if (ALWAYS_SHOW_ROM_SIGNAL)                 // �, ���� ����� ���������� ������ �� ���� � � �������� ������
        {
            Data_GetFromIntMemory();                // �� �� ��������
        }
    }
    else if (MODE_WORK_RAM)                         // ���� ��������� � ������ ����������� ���������
    {
        DS_GetDataFromEnd_RAM(NUM_RAM_SIGNAL, &pDSRAM, (uint16**)&dataRAMA, (uint16**)&dataRAMB);
    }
    else if (MODE_WORK_ROM)
    {
        if (!SHOW_IN_INT_DIRECT)                    // ���� ������������ �� ������ ���������������� ������
        {
            Data_GetFromIntMemory();                // �� ������ ���������� �� ����
        }

        if (SHOW_IN_INT_DIRECT || SHOW_IN_INT_BOTH) // �, ���� �����
        {
            GetDataFromStorage();                   // �� ���������
        }
    }
    
    Data_PrepareToUse(MODE_WORK);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Clear(void)
{
    pDS = pDSDir = pDSRAM = pDSROM = 0;
    dataChan[A] = dataChan[B] = 0;
    dataRAMA = dataRAMB = 0;
    dataROMA = dataROMB = 0;
    dataDirA = dataDirB = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_PrepareToUse(ModeWork mode)
{
    currentModeWork = mode;
    
    typedef DataSettings* pDataSettings;
    static const pDataSettings *ds[3] = {&pDSDir, &pDSRAM, &pDSROM};

    typedef uint8* pUINT8;
    static const pUINT8 *dA[3] = {&dataDirA, &dataRAMA, &dataROMA};
    static const pUINT8 *dB[3] = {&dataDirB, &dataRAMB, &dataROMB};
    
    DS = *ds[mode];
    if(mode == ModeWork_ROM)
    {
        DS = pDSROM ? &dataSettingsROM : 0;
    }
    DATA_A = *dA[mode];
    DATA_B = *dB[mode];

    int first = 0;
    int last = 0;
    sDisplay_PointsOnDisplay(&first, &last);

    Processing_SetSignal(DATA_A, DATA_B, DS, first, last);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_PrepareToDrawSettings(void)
{
    if (MODE_WORK_DIR)
    {

    }
    else if (MODE_WORK_RAM)
    {

    }
    else if (MODE_WORK_ROM)
    {
        if (SHOW_IN_INT_SAVED)                      // ���� ��������� ������ ���������� ������
        {
            Data_PrepareToUse(ModeWork_ROM);        // �� ��� � ������
        }
        else                                        // � ���� �� ������ ���� � ������ ������
        {
            if (EXIT_FROM_ROM_TO_RAM)               // ���� ������ �� ���
            {
                Data_PrepareToUse(ModeWork_RAM);    
            }
            else                                    // ���� ���������������� ������
            {
                Data_PrepareToUse(ModeWork_Dir);
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
ModeWork Data_GetUsedModeWork(void)
{
    return currentModeWork;
}


/** @}  @}
 */

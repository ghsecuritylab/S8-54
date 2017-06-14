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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8 *dataDir[2] = {0, 0};      ///< ��������� ��������� ������.
static uint8 *dataRAM[2] = {0, 0};     ///< ������, ������� ������ ���������� � ������ "���������".
static uint8 *dataROM[2] = {0, 0};      ///< \brief ������, ������� ������ ���������� � ������ "����� ��" ��� ���������� ������ ��� �����. 
                                            ///< ��������� "������-����� ��-���������� ������".

static DataSettings *pDSDir = 0;
static DataSettings *pDSRAM = 0;
static DataSettings *pDSROM = 0;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Clear(void);
/// ������� ������ 
static void GetDataFromStorage(void);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Data_GetFromIntMemory(void)
{
    FLASH_GetData(NUM_ROM_SIGNAL, &pDSROM, &dataROM[A], &dataROM[B]);
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

    DS_GetDataFromEnd_RAM(fromEnd, &pDS, (uint16**)&DATA_A, (uint16**)&DATA_B);

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

    if (WORK_DIRECT)                        // ���� ��������� � �������� ������
    {   
        GetDataFromStorage();               // ��������� ������ �� ���������

        if (ALWAYS_SHOW_ROM_SIGNAL)     // �, ���� ����� ���������� ������ �� ���� � � �������� ������
        {
            Data_GetFromIntMemory();        // �� �� ��������
        }
    }
    else if (WORK_LAST)                     // ���� ��������� � ������ ����������� ���������
    {

    }
    else if (WORK_EEPROM)
    {
        Data_GetFromIntMemory();            // ��������� ������ �� ����

        if (!SHOW_IN_INT_SAVED)             // �, ���� �����
        {
            GetDataFromStorage();           // �� ���������
        }
    }

    int first = 0;
    int last = 0;
    sDisplay_PointsOnDisplay(&first, &last);

    Processing_SetSignal(DATA_A, DATA_B, DS, first, last);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Clear(void)
{
    pDS = pDSDir = pDSRAM = pDSROM = 0;
    dataChan[A] = dataChan[B] = 0;
    dataRAM[A] = dataRAM[B] = 0;
    dataROM[A] = dataROM[B] = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_PrepareToUse(ModeWork mode)
{
    if (mode == ModeWork_Direct)
    {
        DS = pDSDir;
    }
    else if (mode == ModeWork_Latest)
    {
        DS = pDSRAM;
    }
    else if (mode == ModeWork_EEPROM)
    {
        DS = pDSROM;
    }
}

/** @}  @}
 */

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#define _INCLUDE_DATA_
#include "Data.h"
#undef _INCLUDE_DATA_
#include "DataBuffer.h"
#include "Globals.h"
#include "Log.h"
#include "FPGA/FPGA.h"
#include "Hardware/FLASH.h"
#include "Hardware/FSMC.h"
#include "Hardware/RAM.h"
#include "Settings/SettingsMemory.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/Math.h"
#include "Utils/ProcessingSignal.h"


/** @addtogroup FPGA
 *  @{
 *  @addtogroup Data
 *  @{
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Clear(void);
/// ��������� ��������� dataStruct ������� ��� ���������
static void PrepareDataForDraw(StructDataDrawing *dataStruct);
static void FillDataP2P(StructDataDrawing *dataStruct, Channel ch);
static void FillDataNormal(StructDataDrawing *dataStruct, Channel ch);
static void ReadMinMax(StructDataDrawing *dataStruct, int direction);


static DataSettings dataSettings;   ///< ����� �������� ��������� ��� �������� ��������� �������

static int numPointsP2P = 0;

/// ���� true, �� ��������� � ������ ������ ������������� � ����� �������� ����������� ������
#define STAND_P2P (IN_P2P_MODE && START_MODE_WAIT && DS_NumElementsWithCurrentSettings() > 0)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Clear(void)
{
    DS = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadFromRAM(int fromEnd, StructDataDrawing *dataStruct, bool forMemoryWindow)
{
    Clear();

    bool readed = false;      // ������� ����, ��� ������ �������

    dataStruct->posBreak = 0;

    if (RECORDER_MODE && FPGA_IN_STATE_STOP)
    {
        uint8 *dataA = 0;
        uint8 *dataB = 0;
        DataSettings *ds = 0;
        numPointsP2P = DS_GetFrameP2P_RAM(&ds, &dataA, &dataB);
        memcpy(&dataSettings, ds, sizeof(DataSettings));
        DS = &dataSettings;
        RAM_MemCpy16(dataA, IN_A, BYTES_IN_CHANNEL_DS);
        RAM_MemCpy16(dataB, IN_B, BYTES_IN_CHANNEL_DS);
        readed = true;
    }
    else if ((IN_AVERAGING_MODE || (IN_RANDOM_MODE && NRST_NUM_AVE_FOR_RAND))    // ���� �������� ����������
        && fromEnd == 0)                                                    // � ����������� ��������� ��������� ������
    {
        dataSettings = *DS_DataSettingsFromEnd(0);
        DS = &dataSettings;
        if (ENABLED_DS_A)
        {
            memcpy(IN_A, DS_GetAverageData(A), BytesInChannel(DS));
        }
        if (ENABLED_DS_B)
        {
            memcpy(IN_B, DS_GetAverageData(B), BytesInChannel(DS));
        }
        readed = true;
    }
    else if(!IN_P2P_MODE || (IN_P2P_MODE && STAND_P2P && !forMemoryWindow) || (IN_P2P_MODE && !FPGA_IS_RUNNING))
    {
        DS_GetDataFromEnd(fromEnd, &dataSettings, IN_A, IN_B);
        readed = true;
    }
    else
    {
        uint8 *dataA = 0;
        uint8 *dataB = 0;
        DataSettings *ds = 0;
        numPointsP2P = DS_GetFrameP2P_RAM(&ds, &dataA, &dataB);
        memcpy(&dataSettings, ds, sizeof(DataSettings));
        DS = &dataSettings;
        RAM_MemCpy16(dataA, IN_A, BYTES_IN_CHANNEL_DS);
        RAM_MemCpy16(dataB, IN_B, BYTES_IN_CHANNEL_DS);
        readed = true;
    }

    if (readed)
    {
        if (ENUM_POINTS(&dataSettings) == FPGA_ENUM_POINTS) /** \todo ��� ��������. ����� ������� �������� � ������������� ����� ������ �
                                                            � ProcessingSignal_SetData(), ����� �� �������� �� ������. */
        {
            DS = &dataSettings;

            Processing_SetData(true);

            PrepareDataForDraw(dataStruct);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadFromROM(StructDataDrawing *dataStruct)
{
    Clear();

    if (FLASH_GetData(NUM_ROM_SIGNAL, &dataSettings, IN_A, IN_B))
    {
        DS = &dataSettings;

        Processing_SetData(true);

        PrepareDataForDraw(dataStruct);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadMin(StructDataDrawing *dataStruct)
{
    ReadMinMax(dataStruct, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadMax(StructDataDrawing *dataStruct)
{
    ReadMinMax(dataStruct, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ReadMinMax(StructDataDrawing *dataStruct, int direction)
{
    Clear();

    dataSettings = *DS_DataSettingsFromEnd(0);
    
    dataStruct->needDraw[A] = dataStruct->needDraw[B] = false;

    if (DS_GetLimitation(A, IN_A, direction) && DS_GetLimitation(B, IN_B, direction))
    {
        DS = &dataSettings;

        Processing_SetData(false);

        PrepareDataForDraw(dataStruct);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void PrepareDataForDraw(StructDataDrawing *dataStruct)
{
    if (!dataStruct)
    {
        return;
    }

    if (!DS)
    {
        dataStruct->needDraw[A] = dataStruct->needDraw[B] = false;
        return;
    }

    dataStruct->needDraw[A] = ENABLED_DS_A && SET_ENABLED_A;
    dataStruct->needDraw[B] = ENABLED_DS_B && SET_ENABLED_B;

    if ((IN_P2P_MODE && numPointsP2P < 2) || (PEAKDET_DS != SET_PEAKDET))
    {
        dataStruct->needDraw[A] = dataStruct->needDraw[B] = false;
        return;
    }

    if ((IN_P2P_MODE && FPGA_IS_RUNNING && !STAND_P2P) || (FPGA_IN_STATE_STOP && RECORDER_MODE))   
                                                        // FPGA_IS_RUNNING - ������ ��� � �������������� ������ ��� ���������� ������� ��������� 
    {                                                   // ���������� ��������� ����� ���������� �� ��������� �����
        FillDataP2P(dataStruct, A);
        FillDataP2P(dataStruct, B);
    }
    else
    {
        FillDataNormal(dataStruct, A);
        FillDataNormal(dataStruct, B);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void FillDataP2P(StructDataDrawing *dataStruct, Channel ch)
{
    memset(dataStruct->data[ch], 0, 281 * 2);

    if (!dataStruct->needDraw[ch])
    {
        return;
    }

    int bytesInScreen = PEAKDET_DS ? 280 * 2 : 280;

    int allPoints = numPointsP2P;

    if (RECORDER_MODE)
    {
        int start = allPoints - bytesInScreen;  // ��������, ������� � �����, ����� ���������� � �������� �����.
        int end = allPoints - 1;                // ���� ��������� �������������� ����� �� �����
        LIMIT_BELOW(start, 0);

        if (end > BytesInChannel(DS) - 1)       // ���� ������� ������ �����, ��� ���������� � ������ ������
        {
            start = BytesInChannel(DS) - bytesInScreen;
            end = BytesInChannel(DS)  - 1;
        }

        int index = start;

        for (; index <= end; index++)
        {
            dataStruct->data[ch][index - start] = dataOUT[ch][index];
        }
        dataStruct->posBreak = PEAKDET_DS ? (index / 2) : (index - 1);
    }
    else
    {
        if (allPoints > 1)
        {
            int pointer = 0;                // ��������� �� ������ ������� ������
            int index = 0;                  // ��������� �� ������ ��������� ������, � ������� �� ������� 281 �����
            while (allPoints > BytesInChannel(DS))
            {
                ++index;
                SET_IF_LARGER(index, bytesInScreen, 0);
                --allPoints;
            }
            while (allPoints > 0)
            {
                dataStruct->data[ch][index++] = dataOUT[ch][pointer++];
                SET_IF_LARGER(index, bytesInScreen, 0);
                --allPoints;
            }
            dataStruct->posBreak = PEAKDET_DS ? (index / 2) : (index - 1);
        }

    }

    LIMITATION(dataStruct->posBreak, 0, 281);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void FillDataNormal(StructDataDrawing *dataStruct, Channel ch)
{
    if (!dataStruct->needDraw[ch])
    {
        return;
    }

    BitSet64 points = sDisplay_BytesOnDisplay();

    uint8 *dest = dataStruct->data[ch];
    uint8 *src = &dataOUT[ch][points.word0];

    int numBytes = PEAKDET_DS ? 281 * 2 : 281;

    for(int i = 0; i < numBytes; i++)
    {
        *dest++ = *src++;
    }
}


/** @}  @}
 */

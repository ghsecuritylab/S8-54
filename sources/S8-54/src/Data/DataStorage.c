// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "DataSettings.h"
#include "DataStorage.h"
#include "Log.h"
#include "FPGA/FPGAtypes.h"
#include "FPGA/FPGA.h"
#include "Hardware/Timer.h"
#include "Hardware/RTC.h"
#include "Hardware/FSMC.h"
#include "Hardware/RAM.h"
#include "Menu/Pages/PageMemory.h"
#include "Settings/Settings.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"
#include "Utils/Debug.h"
#include "Utils/GlobalFunctions.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� 0, ���� ����� ��������
static uint8 *AddressChannel(DataSettings *ds, Channel ch);
static bool DataSettingsIsEquals(const DataSettings *ds1, const DataSettings *ds2);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int SIZE_POOL = 0;

static uint *sumA_RAM = 0;        // ����� ������� ������
static uint *sumB_RAM = 0;

static uint16 *limitUpA_RAM = 0;
static uint16 *limitUpB_RAM = 0;
static uint16 *limitDownA_RAM = 0;
static uint16 *limitDownB_RAM = 0;

static int iFirst = 0;          // ����� � ������� datas ������� ����������� �������
static int iLast = 0;           // ����� � ������� datas ���������� ����������� �������

static float *aveDataA_RAM = 0; // � ���� �������� �������� ���������� ��������, ������������ �� ���������������� ���������.
static float *aveDataB_RAM = 0;

static bool newSumCalculated[NumChannels] = {true, true};   // ���� true, �� ����� ����� ����������, � ����� ��������� ������ ��������
static int numElementsInStorage = 0;


// ��� ����������� ������ ����� �������� �����
static uint8 *frameP2P = 0;
static int numPointsP2P = 0;            // ����� � ��������� ������ �������� ����� ��� ����������� ������, �� ����� �������� ���������� �����
static DataSettings dsP2P = {0};        // ��������� ����������� ������    
static bool inFrameP2Pmode = false;     // ���� true - ������ ���������� �����

#define NUM_DATAS 999
static DataSettings datas[NUM_DATAS];
static uint8 gDataAve[NumChannels][FPGA_MAX_POINTS];

#define ADDRESS_DATA(ds)        ((ds)->addr)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClearLimitsAndSums(void)
{
    int numBytesA = RequestBytesForChannel(A, 0);
    int numBytesB = RequestBytesForChannel(B, 0);

    RAM_MemClear(limitUpA_RAM, numBytesA);
    RAM_MemClear(limitUpB_RAM, numBytesB);
    RAM_MemClear(limitDownA_RAM, numBytesA);
    RAM_MemClear(limitDownB_RAM, numBytesB);
    RAM_MemClear(sumA_RAM, numBytesA * 4); //-V112
    RAM_MemClear(sumB_RAM, numBytesB * 4); //-V112
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void DS_Clear(void)
{
    SIZE_POOL = RAM8(DS_POOL_END) - RAM8(DS_POOL_BEGIN);

    sumA_RAM = (uint *)RAM8(DS_SUM_A); //-V206
    sumB_RAM = (uint *)RAM8(DS_SUM_B); //-V206

    limitUpA_RAM = RAM16(DS_LIMIT_UP_A);
    limitUpB_RAM = RAM16(DS_LIMIT_UP_B);
    limitDownA_RAM = RAM16(DS_LIMIT_DOWN_A);
    limitDownB_RAM = RAM16(DS_LIMIT_DOWN_B);
    frameP2P = RAM8(DS_P2P_FRAME);

    aveDataA_RAM = (float *)RAM8(DS_AVE_DATA_A);
    aveDataB_RAM = (float *)RAM8(DS_AVE_DATA_B);

    iFirst = 0;
    iLast = 0;
    ADDRESS_DATA(&datas[iFirst]) = ADDRESS_DATA(&datas[iLast]) = 0;

    for(int i = 0; i < NUM_DATAS; i++)
    {
        ADDRESS_DATA(&datas[i]) = 0;  // ����� ������� ����, ��� ������ ��������
    }

    numElementsInStorage = 0;

    ClearLimitsAndSums();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void CalculateAroundAverage(uint8 *dataA, uint8 *dataB, DataSettings *dss)
{
    if (!dataA && !dataB)
    {
        return;
    }

    int numAveData = DS_NumElementsWithCurrentSettings();

    int size = BytesInChannel(dss);

    if (numAveData <= 1)
    {
        for (int i = 0; i < size; i++)
        {
            aveDataA_RAM[i] = dataA[i]; //-V108
            aveDataB_RAM[i] = dataB[i]; //-V108
        }
    }
    else
    {
        if (numAveData > sDisplay_NumAverage())
        {
            numAveData = sDisplay_NumAverage();
        }

        float numAveDataF = (float)numAveData;
        float numAveDataFless = numAveDataF - 1.0f;
        float numAveDataInv = 1.0f / numAveDataF;
        float *aDataA = &aveDataA_RAM[0];
        float *aDataB = &aveDataB_RAM[0];
        uint8 *dA = &dataA[0];
        uint8 *dB = &dataB[0];
        float *endData = &aveDataA_RAM[size]; //-V108

        do 
        {
            *aDataA = ((*aDataA) * numAveDataFless + (float)(*dA++)) * numAveDataInv;
            aDataA++;
            *aDataB = ((*aDataB) * numAveDataFless + (float)(*dB++)) * numAveDataInv;
            aDataB++;
        } while (aDataA != endData && !NEED_FINISH_DRAW);
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
// ���������� ���������� ����, ��������� ��� ������ ������ � ����������� ds
static int SizeData(DataSettings *ds)
{
    /// \todo ������ ���� ���������� ������� ��� ������� ������� ������. ��������, ���-�� ��� ���� � �������� DataSettings.

    int size = 0;

    int numBytesInChannel = BytesInChannel(ds);

    if(ENABLED_A(ds))
    {
        size += numBytesInChannel;
        if(PEAKDET(ds) != PeakDet_Disable)
        {
            size += numBytesInChannel;
        }
    }

    if(ENABLED_B(ds))
    {
        size += numBytesInChannel;
        if(PEAKDET(ds) != PeakDet_Disable)
        {
            size += numBytesInChannel;
        }
    }
    return size;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DeleteFirst(void)
{
    ADDRESS_DATA(&datas[iFirst]) = 0;
    iFirst++;
    if(iFirst == NUM_DATAS)
    {
        iFirst = 0;
    }
    numElementsInStorage--;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
// ������� ����� ��� ������ ������ �� ������� ���.
// �� ������ �� ������� ������� datas[iLast] �������� ds, a ds �������� ����� ��� ������ �� ������� ���
// ��� ���� ������� ���� ������������ iFirst, iLast, addrData ��������� datas (0 ��������� �� ��, ��� ������� ��������)
static void PrepareLastElemForWrite(DataSettings *ds)
{
    // ���� ��������� ������
    if(ADDRESS_DATA(&datas[iFirst]) == 0)
    {
        iFirst = iLast = 0;
        ADDRESS_DATA(ds) = RAM8(DS_POOL_BEGIN);
        datas[iFirst] = *ds;
        return;
    }

    // ���� � ��������� ���� �������
    if(iFirst == iLast)
    {
        iLast = iFirst + 1;
        ADDRESS_DATA(ds) = ADDRESS_DATA(&datas[iFirst]) + SizeData(&datas[iFirst]);
        datas[iLast] = *ds;
        return;
    }

    // ���� � ��������� ����������� ��������� ����� ����������
    if(numElementsInStorage >= NUM_DATAS)
    {
        DeleteFirst();
    }

    uint8 *addrWrite = 0;

    int size = SizeData(ds);

    // ������� ����� ��������� ����� � ���

    volatile bool run = true;
    while(run)
    {
        uint8 *addrFirst = ADDRESS_DATA(&datas[iFirst]);
        uint8 *addrLast = ADDRESS_DATA(&datas[iLast]);

        if(addrLast > addrFirst)                                                   // ������ � ������ ��������� � ������� �����������
        {
            int memFree = RAM8(DS_POOL_END) - addrLast - SizeData(&datas[iLast]);     // ������� ������ �������� �� ��������� ���������

            if(memFree >= size)                                                    // ������ �� ��������� ��������� ����������
            {
                addrWrite = addrLast + SizeData(&datas[iLast]);
                break;
            }
            else                                                                    // ������ �� ��������� ��������� �� �������.
            {
                if(addrFirst - RAM8(DS_POOL_BEGIN) < size)                       // ���� � ������ ������ ������, ��� ����������
                {
                    DeleteFirst();                                              // ������� ���� ������� � ������
                }
                else
                {
                    addrWrite = RAM8(DS_POOL_BEGIN);
                    break;
                }
            }
        }
        else
        {
            int memFree = addrFirst - addrLast - SizeData(&datas[iFirst]);

            if(memFree >= size)
            {
                addrWrite = addrLast + SizeData(&datas[iLast]);
                break;
            }
            else
            {
                if(addrFirst - addrLast - SizeData(&datas[iLast]) < size)
                {
                    DeleteFirst();
                }
                else
                {
                    addrWrite = ADDRESS_DATA(&datas[iLast]) + SizeData(&datas[iLast]);
                    break;
                }
            }
        }
    }

    // ������ ����� ��������� �������
    iLast++;
    if(iLast == NUM_DATAS)
    {
        iLast = 0;
    }
    ADDRESS_DATA(ds) = addrWrite;
    datas[iLast] = *ds;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void PushData(DataSettings *ds, uint8 *dataA, uint8 *dataB)
{
    PrepareLastElemForWrite(ds);

    int numBytes = BytesInChannel(ds);

    if(dataA)
    {
        if (ENABLED_A(ds))
        {
            RAM_MemCpy16(dataA, AddressChannel(ds, A), numBytes);
        }
    }
    else
    {
        RAM_MemSet_Sinch(AddressChannel(ds, A), NONE_VALUE, numBytes);  // ��� ������ ����������� ������ - ��������� ����� ���������
    }

    if(dataB)
    {
        if (ENABLED_B(ds))
        {
            RAM_MemCpy16(dataB, AddressChannel(ds, B), numBytes);
        }
    }
    else
    {
        RAM_MemSet_Sinch(AddressChannel(ds, B), NONE_VALUE, numBytes);  // ��� ������ ����������� ������ - ��������� ����� ���������
    }

    numElementsInStorage++;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void BeginLimits(uint8 *dataA, uint8 *dataB, int numElements)
{
    for(int i = 0; i < numElements / 2; i++)
    {
        limitUpA_RAM[i] = limitDownA_RAM[i] = ((uint16 *)dataA)[i];
        limitUpB_RAM[i] = limitDownB_RAM[i] = ((uint16 *)dataB)[i];
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DataSettings* DS_DataSettingsFromEnd(int indexFromEnd)
{
    int index = 0;

    if(indexFromEnd <= iLast)
    {
        index = iLast - indexFromEnd;
    }
    else
    {
        indexFromEnd -= iLast;
        index = NUM_DATAS - indexFromEnd;
    }

    return &datas[index];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
DataSettings* GetSettingsDataFromEnd(int fromEnd)
{
    return DS_DataSettingsFromEnd(fromEnd);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void CalculateLimits(uint8 *dataA, uint8 *dataB, DataSettings *dss)
{
#define SET_LIMIT(d, up, down)          \
    data = RAM_ReadByte(d + i);         \
    limitUp = RAM_ReadByte(up + i);     \
    limitDown = RAM_ReadByte(down + i); \
    if(data > limitUp)                  \
    {                                   \
        RAM_WriteByte(up + i, data);    \
    }                                   \
    if(data < limitDown)                \
    {                                   \
        RAM_WriteByte(down + i, data);  \
    }

    int numBytes = BytesInChannel(dss);

    if(DS_NumElementsInStorage() == 0 || NUM_MIN_MAX == 1 || (!DataSettingsIsEquals(dss, GetSettingsDataFromEnd(0))))
    {
        BeginLimits(dataA, dataB, numBytes);
    }
    else
    {
        int allDatas = DS_NumElementsWithSameSettings();
        LIMITATION(allDatas, 1, NUM_MIN_MAX);

        if(DS_NumElementsWithSameSettings() >= NUM_MIN_MAX)
        {
            BeginLimits(dataA, dataB, numBytes);
            allDatas--;
        }

        for(int numData = 0; numData < allDatas; numData++)
        {
            const uint8 *dataA = DS_GetData_RAM(A, numData);
            const uint8 *dataB = DS_GetData_RAM(B, numData);

            uint8 data = 0;
            uint8 limitUp = 0;
            uint8 limitDown = 0;

            for(int i = 0; i < numBytes; i++)
            {
                SET_LIMIT((uint8 *)dataA, (uint8 *)limitUpA_RAM, (uint8 *)limitDownA_RAM);
                SET_LIMIT((uint8 *)dataB, (uint8 *)limitUpB_RAM, (uint8 *)limitDownB_RAM);
            }

            if (NEED_FINISH_DRAW)
            {
                break;
            }
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void CalculateSums(void)
{
    DataSettings *ds = 0;
    uint16 *dataA = 0;
    uint16 *dataB = 0;

    DS_GetDataFromEnd_RAM(0, &ds, &dataA, &dataB);

    int numPoints = BytesInChannel(ds);

    int numAveragings = sDisplay_NumAverage();

    uint16 *sumA16 = (uint16 *)sumA_RAM;
    uint16 *sumB16 = (uint16 *)sumB_RAM;

    int iMax = numPoints / 2;

    for(int i = 0; i < iMax; i++)
    {
        uint16 data16 = dataA[i]; //-V108
        *sumA16 = (uint8)data16;
        sumA16 += 2;
        *sumA16 = (uint8)(data16 >> 8);
        sumA16 += 2;

        data16 = dataB[i]; //-V108
        *sumB16 = (uint8)data16;
        sumB16 += 2;
        *sumB16 = (uint8)(data16 >> 8);
        sumB16 += 2;
    }

    if(numAveragings > 1)
    {
        int numSameSettins = DS_NumElementsWithSameSettings();
        if(numSameSettins < numAveragings)
        {
            numAveragings = numSameSettins;
        }

        for(int i = 1; i < numAveragings; i++)
        {
            DS_GetDataFromEnd_RAM(i, &ds, &dataA, &dataB);

            sumA16 = (uint16 *)sumA_RAM;
            uint16 *dA = dataA;

            sumB16 = (uint16 *)sumB_RAM;
            uint16 *dB = dataB;

/* ���������� � ������� 16 �������� ����� �������� ������� */
/* � ���������� ����� �� ����� 16 ������� �������� ����� */
/* ���� �������� ������� �� 16 �������� */
/* �� ���������� ������ ���������� ����� */
#define ALTERNATE_ADD(addr, shift)                                                                          \
    loSum = (*addr) + (uint8)(data16 >> shift);                                                             \
    *addr = (uint16)loSum;                                                                                  \
    if (loSum > 0xffff)                                                                                     \
    {                                                                                                       \
        sum = (uint)((int)loSum - (int)((uint8)(data16 >> shift))) + ((*(addr + 1)) >> 16) + (uint8)data16; \
        *addr = (uint16)sum;                                                                                \
        *(addr + 1) = (uint16)(sum >> 16);                                                                  \
    }                                                                                                       \
    addr += 2;

            for(int i = 0; i < iMax; i++)
            {
                uint sum = 0;
                uint loSum = 0;
                uint16 data16 = *dA++;     // ��������� ������ ��� ������� ������

                ALTERNATE_ADD(sumA16, 0);  /** \todo ������, sum ����������� �����������, ��-�� ���� �������� ��� ������� �����������. ����� 
                                           (loSum - data16) �������� �� ������ �������� (*data16) */

                ALTERNATE_ADD(sumA16, 8);

                data16 = *dB++;

                ALTERNATE_ADD(sumB16, 0);

                ALTERNATE_ADD(sumB16, 8);
            }
        }
    }
    newSumCalculated[A] = newSumCalculated[B] = true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DS_AddData(uint8 *dataA, uint8 *dataB, DataSettings dss)
{
    if (!ENABLED_A(&dss) && !ENABLED_B(&dss))
    {
        return;
    }

    inFrameP2Pmode = false;

    TIME_TIME(&dss) = RTC_GetPackedTime();

    CalculateLimits(dataA, dataB, &dss);

    PushData(&dss, dataA, dataB);

    CalculateSums();

    CalculateAroundAverage(dataA, dataB, &dss);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
// ���������� true, ���� ��������� ��������� � ��������� elemFromEnd0 � elemFromEnd1 ���������, � false � ���� ������.
static bool SettingsIsIdentical(int elemFromEnd0, int elemFromEnd1)
{
    DataSettings* dp0 = DS_DataSettingsFromEnd(elemFromEnd0);
    DataSettings* dp1 = DS_DataSettingsFromEnd(elemFromEnd1);
    return DataSettingsIsEquals(dp0, dp1);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int DS_NumElementsWithSameSettings(void)
{
    int retValue = 0;
    for(retValue = 1; retValue < numElementsInStorage; retValue++)
    {
        if(!SettingsIsIdentical(retValue, retValue - 1))
        {
            break;
        }
    }
    return retValue;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int DS_NumElementsWithCurrentSettings(void)
{
    DataSettings dp;
    DataSettings_Fill(&dp);
    int retValue = 0;
    int numElements = DS_NumElementsInStorage();

    for(retValue = 0; retValue < numElements; retValue++)
    {
        if(!DataSettingsIsEquals(&dp, DS_DataSettingsFromEnd(retValue)))
        {
            break;
        }
    }

    return retValue;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int DS_NumElementsInStorage(void)
{
    return numElementsInStorage;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
// �������� ������ ������ ch ��, ������������ ds, � ���� �� ���� ����� ������� dataImportRel. ������������ �������� false ��������, ��� ������ ����� 
// ��������.
static bool CopyData(DataSettings *ds, Channel ch, uint8 *dataImportRel)
{
    if((ch == A && !ENABLED_A(ds)) || (ch == B && !ENABLED_B(ds)))
    {
        return false;
    }

    uint8 *address = ADDRESS_DATA(ds);

    int length = BytesInChannel(ds);

    if(ch == B && ENABLED_B(ds) && ENABLED_A(ds))
    {
        address += length; //-V102
    }

    RAM_MemCpy16(address, dataImportRel, length);

    return true;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 *DS_GetData_RAM(Channel ch, int fromEnd)
{
    uint8 *dataImport = (ch == A) ? RAM8(DS_DATA_IMPORT_REL_A) : RAM8(DS_DATA_IMPORT_REL_B);

    DataSettings* dp = DS_DataSettingsFromEnd(fromEnd);

    if (dp == 0)
    {
        return 0;
    }

    if(CopyData(dp, ch, dataImport))
    {
        return dataImport;
    }

    return 0;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
bool DS_GetDataFromEnd(int fromEnd, DataSettings *ds, uint8 *dataA, uint8 *dataB)
{
    DataSettings *dataSettings = 0;
    uint16 *dA = 0;
    uint16 *dB = 0;
    
    if(DS_GetDataFromEnd_RAM(fromEnd, &dataSettings, &dA, &dB))
    {
        memcpy(ds, dataSettings, sizeof(DataSettings));
        if(dA)
        {
            RAM_MemCpy16(dA, dataA, BytesInChannel(ds));
        }
        if(dB)
        {
            RAM_MemCpy16(dB, dataB, BytesInChannel(ds));
        }

        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool DS_GetLimitation(Channel ch, uint8 *data, int direction)
{
    if (!MIN_MAX_ENABLED || DS_NumElementsWithSameSettings() < 2)
    {
        return false;
    }

    DataSettings *ds = DS_DataSettingsFromEnd(0);

    uint8 *limit = A == ch ? (uint8 *)limitDownA_RAM : (uint8 *)limitDownB_RAM;
    if (direction == 1)
    {
        limit = A == ch ? (uint8 *)limitUpA_RAM : (uint8 *)limitUpB_RAM;
    }
    RAM_MemCpy16(limit, data, BytesInChannel(ds));

    return true;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
bool DS_GetDataFromEnd_RAM(int fromEnd, DataSettings **ds, uint16 **dataA, uint16 **dataB)
{
    DataSettings *dp = DS_DataSettingsFromEnd(fromEnd);

    if(dp == 0)
    {
        return false;
    }
    
    uint8 *dataImportRelA = RAM8(DS_DATA_IMPORT_REL_A);
    uint8 *dataImportRelB = RAM8(DS_DATA_IMPORT_REL_B);

    if(dataA != 0)
    {
        *dataA = CopyData(dp, A, dataImportRelA) ? (uint16 *)dataImportRelA : 0;
    }
    if(dataB != 0)
    {
        *dataB = CopyData(dp, B, dataImportRelB) ? (uint16 *)dataImportRelB : 0;
    }

    *ds = dp;

    return true;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 *DS_GetAverageData(Channel ch)
{
    if (newSumCalculated[ch] == false)
    {
        return &gDataAve[ch][0];
    }

    newSumCalculated[ch] = false;

    DataSettings *ds = 0;
    uint16 *dA = 0;
    uint16 *dB = 0;
    DS_GetDataFromEnd_RAM(0, &ds, &dA, &dB);

    if (ds == 0)
    {
        return 0;
    }

    int numPoints = BytesInChannel(ds);

    if (sDisplay_GetModeAveraging() == Averaging_Around)
    {
        float *floatAveData = (ch == A) ? aveDataA_RAM : aveDataB_RAM;
        
        for (int i = 0; i < numPoints; i++)
        {
            gDataAve[ch][i] = (uint8)(floatAveData[i] + 0.5f); //-V108
        }
        return &gDataAve[ch][0];
    }

    int numAveraging = sDisplay_NumAverage();

    LIMIT_ABOVE(numAveraging, DS_NumElementsWithSameSettings());

    for(int i = 0; i < numPoints; i++)
    {
        gDataAve[A][i] = (uint8)((float)RAM_ReadWord(sumA_RAM + i) / numAveraging + 0.5f);
        gDataAve[B][i] = (uint8)((float)RAM_ReadWord(sumB_RAM + i) / numAveraging + 0.5f);
    }

    return &gDataAve[ch][0];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int DS_NumberAvailableEntries(void)
{
    if(ADDRESS_DATA(&datas[iFirst]) == 0)
    {
        return 0;
    }

    int numElems = 0;
    LIMITATION_ABOVE(numElems, SIZE_POOL / SizeData(&datas[iLast]), NUM_DATAS);

    return numElems;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void DS_NewFrameP2P(DataSettings *dss)
{
    if (!ENABLED_A(dss) && !ENABLED_B(dss))
    {
        return;
    }

    inFrameP2Pmode = true;
    dsP2P = *dss;
    dsP2P.addr = RAM8(DS_P2P_FRAME);
    RAM_MemClear(frameP2P, 2 * BytesInChannel(dss));
    numPointsP2P = 0;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void DS_AddPointsP2P(uint16 dataA, uint16 dataB)
{
    if (!ENABLED_A(&dsP2P) && !ENABLED_B(&dsP2P))
    {
        return;
    }

    FSMC_SET_MODE(ModeFSMC_RAM);

    int length = BytesInChannel(&dsP2P);

    if (numPointsP2P >= length)                         // ���� ����� �� ������ ��������� ���������
    {
        if (ENABLED_A(&dsP2P))                           // �� ������� ��� ����� �� ������ �����
        {
            RAM_MemShiftLeft(frameP2P + 2, length - 2, 2);
        }
        if (ENABLED_B(&dsP2P))
        {
            RAM_MemShiftLeft(frameP2P + 2 + length, length - 2, 2);
        }
    }

    int offsetWrite = (numPointsP2P >= length) ? length - 2 : numPointsP2P;

    if (ENABLED_A(&dsP2P))
    {
        uint16 *address = (uint16*)(frameP2P + offsetWrite);
        *address = dataA;
    }

    if (ENABLED_B(&dsP2P))
    {
        uint16 *address = (uint16 *)(frameP2P + length + offsetWrite);
        *address = dataB;
    }

    numPointsP2P += 2;

    FSMC_RESTORE_MODE();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int DS_GetFrameP2P_RAM(DataSettings **ds, uint8 **dataA, uint8 **dataB)
{
    if (!inFrameP2Pmode)
    {
        *ds = 0;
        *dataA = 0;
        *dataB = 0;
        return -1;
    }

    *ds = &dsP2P;
    *dataA = frameP2P;
    *dataB = frameP2P + BytesInChannel(&dsP2P);

    return numPointsP2P;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
uint8 *AddressChannel(DataSettings *ds, Channel ch)
{
    if (ch == A && ENABLED_A(ds))
    {
        return ADDRESS_DATA(ds);
    }

    if (ch == B && ENABLED_B(ds))
    {
        return ADDRESS_DATA(ds) + (ENABLED_A(ds) ? BytesInChannel(ds) : 0);
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool DataSettingsIsEquals(const DataSettings *ds1, const DataSettings *ds2)
{
    /** @todo �������������� ������� ��������� */
    bool equals = (ENABLED_A(ds1) == ENABLED_A(ds2)) &&
        (ENABLED_B(ds1) == ENABLED_B(ds2)) &&
        (INVERSE_A(ds1) == INVERSE_A(ds2)) &&
        (INVERSE_B(ds1) == INVERSE_B(ds2)) &&
        (RANGE_A(ds1) == RANGE_A(ds2)) &&
        (RANGE_B(ds1) == RANGE_B(ds2)) &&
        (RSHIFT_A(ds1) == RSHIFT_A(ds2)) &&
        (RSHIFT_B(ds1) == RSHIFT_B(ds2)) &&
        (TBASE(ds1) == TBASE(ds2)) &&
        (TSHIFT(ds1) == TSHIFT(ds2)) &&
        (COUPLE_A(ds1) == COUPLE_A(ds2)) &&
        (COUPLE_B(ds1) == COUPLE_B(ds2)) &&
        (TRIGLEV_A(ds1) == TRIGLEV_A(ds2)) &&
        (TRIGLEV_B(ds1) == TRIGLEV_B(ds2)) &&
        (DIVIDER_A(ds1) == DIVIDER_A(ds2)) &&
        (DIVIDER_B(ds1) == DIVIDER_B(ds2)) &&
        (PEAKDET(ds1) == PEAKDET(ds2));

    return equals;
}

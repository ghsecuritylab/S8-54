#include "FLASH.h"
#include "Log.h"
#include "Hardware/Hardware.h"
#include "Hardware/Sound.h"
#include "Hardware/Timer.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    ������� �������� ������.

    � ������� ADDR_SECTOR_DATA_DATA �������� ������� � �������� MAX_NUM_SAVED_WAVES ������ (���� ����� == -1, �� ������ �����). ��� ������ MAX_NUM_SAVED_WAVES + 1
    ��� ���� � �������� � �������� MAX_NUM_SAVED_WAVES �������� ������, ������������ �� ��, �������� �� ������� ������ ��������. ���� ��� -1, �� ���������� ��, ���� ��� - ��������� � ����������
    ��� �������� ���������� ������ ������������� ������� ADDR_SECTOR_DATA_0...6. ������ �������� ��� - ������� DataSettings, � ����� ������ � ������������ �������.\
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� � ����������� ������
#define ADDR_SECTOR_BOOT_0      ((uint)0x08000000)  // 16k ���������
#define ADDR_SECTOR_BOOT_1      ((uint)0x08004000)  // 16k ���������
#define ADDR_FLASH_SECTOR_2     ((uint)0x08008000)  // 16k
#define ADDR_FLASH_SECTOR_3     ((uint)0x0800C000)  // 16k
#define ADDR_FLASH_SECTOR_4     ((uint)0x08010000)  // 64k
#define ADDR_SECTOR_PROGRAM_0   ((uint)0x08020000)  // 128k �������� ���������
#define ADDR_SECTOR_PROGRAM_1   ((uint)0x08040000)  // 128k �������� ���������
#define ADDR_SECTOR_PROGRAM_2   ((uint)0x08060000)  // 128k �������� ���������
#define ADDR_SECTOR_TEMP_1      ((uint)0x08080000)  // 128k | ��� ������� ��� �������� ��������� �����. ��������, ��� ������������ ������ ���� ������ �����
#define ADDR_SECTOR_TEMP_2      ((uint)0x080A0000)  // 128k /
#define ADDR_SECTOR_RESOURCES   ((uint)0x080C0000)  // 128k ����������� � �������� �������
#define ADDR_SECTOR_SETTINGS    ((uint)0x080E0000)  // 128k ���������
#define ADDR_FLASH_SECTOR_12    ((uint)0x08100000)  // 16k
#define ADDR_FLASH_SECTOR_13    ((uint)0x08104000)  // 16k
#define ADDR_FLASH_SECTOR_14    ((uint)0x08108000)  // 16k
#define ADDR_FLASH_SECTOR_15    ((uint)0x0810C000)  // 16k
#define ADDR_SECTOR_DATA_DATA   ((uint)0x08110000)  // 64k  ����� ����� ��������� ������� ������� � ������ �������
#define ADDR_SECTOR_DATA_0      ((uint)0x08120000)  // 128k |
#define ADDR_SECTOR_DATA_1      ((uint)0x08140000)  // 128k |
#define ADDR_SECTOR_DATA_2      ((uint)0x08160000)  // 128k | ����� ����� ��������� ���������� ������
#define ADDR_SECTOR_DATA_3      ((uint)0x08180000)  // 128k |
#define ADDR_SECTOR_DATA_4      ((uint)0x081A0000)  // 128k |
#define ADDR_SECTOR_DATA_5      ((uint)0x081C0000)  // 128k |
#define ADDR_SECTOR_DATA_6      ((uint)0x081E0000)  // 128k /

#define SIZE_SECTOR_SETTINGS    (128 * 1024)        // ������ �������, ���� ����������� ���������, � ������

// ��������� ��� ������ ������� ���������� �� ������
typedef struct
{
    uint address[MAX_NUM_SAVED_WAVES + 1];
} ArrayDatas;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef CLEAR_FLASH_FLAGS
#define CLEAR_FLASH_FLAGS                                                                   \
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP     |  /* end of operation flag              */   \
                            FLASH_FLAG_OPERR  |  /* operation error flag               */   \
                            FLASH_FLAG_WRPERR |  /* write protected error flag         */   \
                            FLASH_FLAG_PGAERR |  /* programming alignment error flag   */   \
                            FLASH_FLAG_PGPERR |  /* programming parallelism error flag */   \
                            FLASH_FLAG_PGSERR);  /* programming sequence error flag    */

#undef FIRST_RECORD
#define FIRST_RECORD ((RecordConfig*)ADDR_ARRAY_RECORDS)

#undef READ_WORD
#define READ_WORD(address) (*((volatile uint*)address))

#undef RECORD_EXIST
#define RECORD_EXIST (READ_WORD(ADDR_ARRAY_RECORDS) != MAX_UINT)   // true, ���� ���� ���� ���� ����������� ������ (���������� ������)

#undef MEMORY_FOR_SETTINGS
#define MEMORY_FOR_SETTINGS ((ADDR_LAST_SET + 1) - ADDR_FIRST_SET)  // ��� ������ ������, ��������� ��� ���������� ��������. ��� ������ ������� �� ������� 4-� ���� ��� ������ ������� � ������ ��� �������� �������


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    uint addr;  // ������� � ����� ������ �������� ������. ���� addrData == MAX_UINT, �� ��� ������ ������, ���� ����� ������ ������
    int  size;  // ������ � ������ ���������� ������
} RecordConfig;


#define ADDR_ARRAY_RECORDS             ((ADDR_SECTOR_SETTINGS) + 4)
#define MAX_NUM_RECORDS 1024
#define SIZE_ARRAY_RECORDS_IN_BYTES    ((MAX_NUM_RECORDS) * sizeof(RecordConfig))
static const uint ADDR_FIRST_SET = ADDR_ARRAY_RECORDS + SIZE_ARRAY_RECORDS_IN_BYTES;    // ����� ������� ����� ������, ��� ��������� ���������
static const uint ADDR_LAST_SET = ((ADDR_SECTOR_SETTINGS + SIZE_SECTOR_SETTINGS) - 1);  // ����� ���������� ����� ������, ��� ��������� ���������


// ������� ����, ��� ������ � ���� ������� ���� ��� �������������. ���� ������� ����� ������� (������, �������� ��� ��������) ����� ��� ��������, ������ ��� ���� ����������� ��� ������� ���� ���
static const uint MARK_OF_FILLED = 0x123456;
static const uint startDataInfo = ADDR_SECTOR_DATA_0;


static RecordConfig *records = (RecordConfig *)ADDR_ARRAY_RECORDS;     // ��� ��������� �������� � ��������


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��� ��������
static int CalculateFreeMemory(void);
static RecordConfig* FindRecordConfigForWrite(void);
static void WriteWord(uint address, uint word);
static void WriteBuffer(uint address, uint *buffer, int size);
static void PrepareSectorForData(void);
static void ReadBuffer(uint addressSrc, uint *bufferDest, int size);
static void EraseSector(uint startAddress);
static uint GetSector(uint startAddress);
static RecordConfig* LastFilledRecord(void);    // ���������� ����� ��������� ������ � ����������� ����������� ��� 0, ���� ��� ���������� ��������

// ��� ������
static ArrayDatas* CurrentArray(void);          // ���������� ����� ����������� ������� � �������� ������


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FLASH_SaveSettings(void)
{
    if(gBF.alreadyLoadSettings == 0)
    {
        return;
    }

    CLEAR_FLASH_FLAGS
    
    RecordConfig *record = FindRecordConfigForWrite();
    if(record == 0)                                                 // ���� ��� ����� ��� ������ ��������
    {
        set.common.countErasedFlashSettings++;
        EraseSector(ADDR_SECTOR_SETTINGS);                          // ������� ������
        WriteWord(ADDR_SECTOR_SETTINGS, MARK_OF_FILLED);            // � ���������
        record = FIRST_RECORD;                                      // ������-�� �� ����� ����� ����� ��� ������
    }

    set.common.workingTimeInSecs += gTimerMS / 1000;

    WriteWord((uint)(&record->addr), (record == FIRST_RECORD) ? ADDR_FIRST_SET : (record - 1)->addr + (record - 1)->size);

    WriteWord((uint)(&record->size), sizeof(set));

    WriteBuffer(record->addr, (uint*)(&set), record->size / 4);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool FLASH_LoadSettings(void)
{
    CLEAR_FLASH_FLAGS;

    if(READ_WORD(ADDR_SECTOR_SETTINGS) != MARK_OF_FILLED)       // ���� ������ ���� ������� �� ������������ - ������ ��������� �������
    {
        set.common.countErasedFlashSettings = 0;
        set.common.countEnables = 0;
        set.common.countErasedFlashData = 0;
        set.common.workingTimeInSecs = 0;
        EraseSector(ADDR_SECTOR_SETTINGS);                      // �� ������ ������ ������� ������
        WriteWord(ADDR_SECTOR_SETTINGS, MARK_OF_FILLED);        // � ���������
        PrepareSectorForData();                                 // ����� ������� ������ ��� ���������� ������
        return false;
    }

    RecordConfig *record = LastFilledRecord();

    if(record == 0)                                             // �� �����-�� ������� ���������� �������� ����� �� ���������. ��������, ������ ��� ������������� ��� ���������� ���������,
    {                                                           // �� ������ ��������� ������������ �� ������ ������, � �� ������� �� �������� ������, ���������� ���� ��������� �� �����������
        return false;
    }

    int numWordsForCopy = record->size / 4;

    if(sizeof(set) != record->size)                         // ���� ����� ��������� �������� �� ������������� ����������
    {
        numWordsForCopy = SIZE_NONRESET_SETTINGS / 4;           // �� ����� ���������� ������ �������������� ��������� (� ��� ������ ���� ������ � ��� � ������ ���������)
    }

    ReadBuffer(record->addr, (uint*)(&set), numWordsForCopy);
    set.common.countEnables++;
    return true;
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static RecordConfig* LastFilledRecord(void)
{
    for(int i = MAX_NUM_RECORDS - 1; i >= 0; --i)           // ������������� ������ ������� �� ���������� �������� � �������
    {                                                       // ������� �������������� �������� �� ���������, ������ ��� ��� �������� ������� ��� �������� � �� ����� 0xffffffff
        if(records[i].addr != MAX_UINT)
        {
            return &records[i];
        }
    }

    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static RecordConfig* FindRecordConfigForWrite(void)
{
    RecordConfig *record = LastFilledRecord();
    if(record == &records[MAX_NUM_RECORDS - 1] ||   // ���� ��� ������ ������
       CalculateFreeMemory() < sizeof(set))         // ��� ������ �������� ������, ��� ����� ��� ���������� ��������
    {
        return 0;
    }
    
    if(record == 0)
    {
        return &records[0];
    }

    return ++record;                                // ���������� ����� ��������� �� ��������� ����������� ������
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteWord(uint address, uint word)
{
    CLEAR_FLASH_FLAGS

    HAL_FLASH_Unlock();
    if(HAL_FLASH_Program(TYPEPROGRAM_WORD, address, (uint64_t)word) != HAL_OK)
    {
        LOG_ERROR("�� ���� �������� � ������");
    }
    HAL_FLASH_Lock();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteBuffer(uint address, uint *buffer, int size)
{
    HAL_FLASH_Unlock();
    for(int i = 0; i < size; i++)
    {
        if(HAL_FLASH_Program(TYPEPROGRAM_WORD, address, (uint64_t)(buffer[i])) != HAL_OK)
        {
            LOG_ERROR("�� ���� �������� � ����-������");
        }
        address += sizeof(uint);
    }
    HAL_FLASH_Lock();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void PrepareSectorForData(void)
{
    EraseSector(ADDR_SECTOR_DATA_0);
    for(int i = 0; i < MAX_NUM_SAVED_WAVES; i++)
    {
        WriteWord(startDataInfo + i * 4, 0);
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void ReadBuffer(uint addressSrc, uint *bufferDest, int size)
{
    for(int i = 0; i < size; i++)
    {
        bufferDest[i] = *((uint*)addressSrc);
        addressSrc += 4;
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void EraseSector(uint startAddress)
{
    CLEAR_FLASH_FLAGS

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef flashITD;
    flashITD.TypeErase = TYPEERASE_SECTORS;
    flashITD.Sector = GetSector(startAddress);
    flashITD.NbSectors = 1;
    flashITD.VoltageRange = VOLTAGE_RANGE_3;

    uint32_t error = 0;

    while(gSoundIsBeep) // WARN ����� ���, ���� ������� �� ��������. �������, ���� �����������, ������ ��� �� ����� ������ ��������
    {
    };

    HAL_FLASHEx_Erase(&flashITD, &error);

    HAL_FLASH_Lock();
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static uint GetSector(uint startAddress)
{
    typedef struct
    {
        uint number;
        uint startAddress;
    } StructSector;

    static const StructSector sectors[24] =
    {
        {FLASH_SECTOR_0, ADDR_SECTOR_BOOT_0},
        {FLASH_SECTOR_1, ADDR_SECTOR_BOOT_1},
        {FLASH_SECTOR_2, ADDR_FLASH_SECTOR_2},
        {FLASH_SECTOR_3, ADDR_FLASH_SECTOR_3},
        {FLASH_SECTOR_4, ADDR_FLASH_SECTOR_4},
        {FLASH_SECTOR_5, ADDR_SECTOR_PROGRAM_0},
        {FLASH_SECTOR_6, ADDR_SECTOR_PROGRAM_1},
        {FLASH_SECTOR_7, ADDR_SECTOR_PROGRAM_2},
        {FLASH_SECTOR_8, ADDR_SECTOR_TEMP_1},
        {FLASH_SECTOR_9, ADDR_SECTOR_TEMP_2},
        {FLASH_SECTOR_10, ADDR_SECTOR_RESOURCES},
        {FLASH_SECTOR_11, ADDR_SECTOR_SETTINGS},
        {FLASH_SECTOR_12, ADDR_FLASH_SECTOR_12},
        {FLASH_SECTOR_13, ADDR_FLASH_SECTOR_13},
        {FLASH_SECTOR_14, ADDR_FLASH_SECTOR_14},
        {FLASH_SECTOR_15, ADDR_FLASH_SECTOR_15},
        {FLASH_SECTOR_16, ADDR_SECTOR_DATA_DATA},
        {FLASH_SECTOR_17, ADDR_SECTOR_DATA_0},
        {FLASH_SECTOR_18, ADDR_SECTOR_DATA_1},
        {FLASH_SECTOR_19, ADDR_SECTOR_DATA_2},
        {FLASH_SECTOR_20, ADDR_SECTOR_DATA_3},
        {FLASH_SECTOR_21, ADDR_SECTOR_DATA_4},
        {FLASH_SECTOR_22, ADDR_SECTOR_DATA_5},
        {FLASH_SECTOR_23, ADDR_SECTOR_DATA_6}
    };

    for(int i = 0; i < 24; i++)
    {
        if(sectors[i].startAddress == startAddress)
        {
            return sectors[i].number;
        }
    }

    LOG_ERROR("������������ ����� �������");

    return (uint)-1;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CalculateFreeMemory(void)
{
    RecordConfig *lastFilledRecord = LastFilledRecord();    // ������� ������ � ���������� ����������� �����������

    if(lastFilledRecord == 0)                               // ���� ��� ������ ��������
    {
        return MEMORY_FOR_SETTINGS;
    }

    if(lastFilledRecord == &records[MAX_NUM_RECORDS - 1])   // ���� ��� ������ ������
    {
        return 0;                                           // �� ��������� ������ ���
    }

    int retValue = ADDR_LAST_SET - (lastFilledRecord->addr + lastFilledRecord->size);

    return retValue < 0 ? 0 : retValue;     // ���������� 0, ���� ������ ��������� ������������� - �����-�� ������� ��������� ������ ��������� �� ��������� �������
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static uint FindAddressNextDataInfo(void)
{
    uint addressNextInfo = startDataInfo + MAX_NUM_SAVED_WAVES * 4;

    while (*((uint*)addressNextInfo) != MAX_UINT)
    {
        addressNextInfo = *((uint*)addressNextInfo) + MAX_NUM_SAVED_WAVES * 4;
    }

    return addressNextInfo;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static uint FindActualDataInfo(void)
{
    return FindAddressNextDataInfo() - MAX_NUM_SAVED_WAVES * 4;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void FLASH_GetDataInfo(bool existData[MAX_NUM_SAVED_WAVES])
{
    uint address = FindActualDataInfo();

    for (int i = 0; i < MAX_NUM_SAVED_WAVES; i++)
    {
        existData[i] = READ_WORD(address + i * 4) != 0;
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool FLASH_ExistData(int num)
{
    ArrayDatas *array = CurrentArray();
    return array->address[num] != MAX_UINT;     // ��������� ����, ��� ������ �� �������� � ���� �������, �������� ��������� ��� (-1)
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void FLASH_DeleteData(int num)
{
    /*
        ��� ����, ����� ������� ������, ����� ������� ���������:
        1. ���� � DATA_DATA ��� ����� ��� ������ ������ �������:
            1.1 ��������� ���������� �������� �������.
            1.2 C������ ������ DATA_DATA
            1.3 �������� � ������ ������� DATA_DATA ������, ������� ��� �������, �� ���������� �����������:
                - � MAX_NUM_SAVED_WAVES � array[num] ������ ���� (-1)
            1.4 �����
        2. 
    */

    uint address = FindActualDataInfo();
    WriteWord(address + num * 4, 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int CalculateSizeData(DataSettings *ds)
{
    int size = sizeof(DataSettings);

    int pointsInChannel = NumBytesInChannel(ds);

    if (ds->enableChA == 1)
    {
        size += pointsInChannel;
    }

    if (ds->enableChB == 1)
    {
        size += pointsInChannel;
    }

    return size;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static uint FreeMemory(void)
{
    return ADDR_SECTOR_DATA_0 + 128 * 1024 - FindAddressNextDataInfo() - 1 - 4 * MAX_NUM_SAVED_WAVES - 3000;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void WriteBufferBytes(uint address, uint8 *buffer, int size)
{
    HAL_FLASH_Unlock();
    for(int i = 0; i < size; i++)
    {
        HAL_FLASH_Program(TYPEPROGRAM_BYTE, address, (uint64_t)(buffer[i]));
        address++;
    }
    HAL_FLASH_Lock();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void CompactMemory(void)
{
    Display_ClearFromWarnings();
    Display_ShowWarning(MovingData);
    Display_Update();
    uint dataInfoRel = FindActualDataInfo() - ADDR_SECTOR_DATA_0;

    EraseSector(ADDR_SECTOR_DATA_1);
    WriteBufferBytes(ADDR_SECTOR_DATA_1, (uint8*)ADDR_SECTOR_DATA_0, 1024 * 128);
    PrepareSectorForData();

    uint addressDataInfo = ADDR_SECTOR_DATA_1 + dataInfoRel;

    for (int i = 0; i < MAX_NUM_SAVED_WAVES; i++)
    {
        uint addrDataOld = READ_WORD(addressDataInfo + i * 4);
        if (addrDataOld != 0)
        {
            uint addrDataNew = addrDataOld + 1024 * 128;
            DataSettings *ds = (DataSettings*)addrDataNew;
            addrDataNew += sizeof(DataSettings);
            uint8 *dataA = 0;
            uint8 *dataB = 0;
            if (ds->enableChA == 1)
            {
                dataA = (uint8*)addrDataNew;
                addrDataNew += NumBytesInChannel(ds);
            }
            if (ds->enableChB == 1)
            {
                dataB = (uint8*)addrDataNew;
            }
            FLASH_SaveData(i, ds, dataA, dataB);
        }
    }
    Display_ClearFromWarnings();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void FLASH_SaveData(int num, DataSettings *ds, uint8 *dataA, uint8 *dataB)
{
    /*
        0. ���� � num ��� �������� ������, �� ������� ��
        1. ����� ���������� ���������� ������
        2. ���� �� ������� ������ ��� ������ ������ - ��������� ������ (��� ���� ���� ���������� ��������������� ������� TEMP_1 � TEMP_2)
        4. ���������� � ������� ������ ������ � ������� DataSettings, dataChanA, dataChanB
        5. ���������� � ������ �� DATA_DATA ����� ����� ���������� ������
    */

// 0
    if (FLASH_ExistData(num))
    {
        FLASH_DeleteData(num);
    }





    int size = CalculateSizeData(ds);

// 2
    if (FreeMemory() < (uint)size)
    {
        CompactMemory();
    }

// 3
    uint addrDataInfo = FindActualDataInfo();          // ������� ������ ������������ ��������������� �������

// 4
    uint addrForWrite = addrDataInfo + MAX_NUM_SAVED_WAVES * 4;             // ��� - �����, �� �������� ����� ��������� ����� ���������� ��������������� �������
    uint valueForWrite = addrForWrite + 4 + size;                           // ��� - ����� ���������� ��������������� �������
    WriteWord(addrForWrite, valueForWrite);

// 5
    uint address = addrDataInfo + MAX_NUM_SAVED_WAVES * 4 + 4;              // �����, �� �������� ����� ������� ������ � �����������
    uint addressNewData = address;
    WriteBufferBytes(address, (uint8*)ds, sizeof(DataSettings));            // ��������� ��������� �������
    address += sizeof(DataSettings);
    
    int pointsInChannel = NumBytesInChannel(ds);

    if (ds->enableChA == 1)
    {
        WriteBufferBytes(address, (uint8*)dataA, pointsInChannel);       // ��������� ������ �����
        address += pointsInChannel;
    }

    if (ds->enableChB == 1)
    {
        WriteBufferBytes(address, (uint8*)dataB, pointsInChannel);       // ��������� ������ �����
        address += pointsInChannel;
    }

// 6
    for (int i = 0; i < MAX_NUM_SAVED_WAVES; i++)
    {
        uint addressForWrite = address + i * 4;
        if (i == num)
        {
            WriteWord(addressForWrite, addressNewData);
        }
        else
        {
            WriteWord(addressForWrite, READ_WORD(addrDataInfo + i * 4));
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static ArrayDatas* CurrentArray(void)
{
    ArrayDatas *array = (ArrayDatas*)ADDR_SECTOR_DATA_DATA;
    while (array->address[MAX_NUM_SAVED_WAVES] != MAX_UINT)
    {
        ++array;
    }
    return array;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool FLASH_GetData(int num, DataSettings **ds, uint8 **dataA, uint8 **dataB)
{
    *ds = 0;
    *dataA = 0;
    *dataB = 0;
    
    return false;

    uint addrDataInfo = FindActualDataInfo();
    if (READ_WORD(addrDataInfo + 4 * num) == 0)
    {
        return false;
    }

    uint addrDS = READ_WORD(addrDataInfo + 4 * num);

    uint addrData0 = 0;
    uint addrData1 = 0;

    *ds = (DataSettings*)addrDS;
    
    if ((*ds)->enableChA == 1)
    {
        addrData0 = addrDS + sizeof(DataSettings);
    }

    if ((*ds)->enableChB == 1)
    {
        if (addrData0 != 0)
        {
            addrData1 = addrData0 + NumBytesInChannel(*ds);
        }
        else
        {
            addrData1 = addrDS + sizeof(DataSettings);
        }
    }

    *dataA = (uint8*)addrData0;
    *dataB = (uint8*)addrData1;
    
    return true;
}

#undef CLEAR_FLASH_FLAGS
#undef FIRST_RECORD
#undef READ_WORD
#undef RECORD_EXIST
#undef MEMORY_FOR_SETTINGS

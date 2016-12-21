#pragma once


#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Display/Display.h"
#include "FPGA/DataStorage.h"


// ��������� � ����������� ������
#define ADDR_SECTOR_BOOT_0      ((uint)0x08000000)  // 16k ���������
#define ADDR_SECTOR_BOOT_1      ((uint)0x08004000)  // 16k ���������
#define ADDR_FLASH_SECTOR_2     ((uint)0x08008000)  // 16k
#define ADDR_FLASH_SECTOR_3     ((uint)0x0800C000)  // 16k
#define ADDR_FLASH_SECTOR_4     ((uint)0x08010000)  // 64k
#define ADDR_SECTOR_PROGRAM_0   ((uint)0x08020000)  // 128k �������� ���������
#define ADDR_SECTOR_PROGRAM_1   ((uint)0x08040000)  // 128k �������� ���������
#define ADDR_SECTOR_PROGRAM_2   ((uint)0x08060000)  // 128k �������� ���������
#define ADDR_SECTOR_DATA_MAIN   ((uint)0x08080000)  // 128k ���������� ������
#define ADDR_SECTOR_DATA_HELP   ((uint)0x080A0000)  // 128k ���������� ������
#define ADDR_SECTOR_RESOURCES   ((uint)0x080C0000)  // 128k ����������� � �������� �������
#define ADDR_SECTOR_SETTINGS    ((uint)0x080E0000)  // 128k ���������
#define ADDR_FLASH_SECTOR_12    ((uint)0x08100000)  // 16k
#define ADDR_FLASH_SECTOR_13    ((uint)0x08104000)  // 16k
#define ADDR_FLASH_SECTOR_14    ((uint)0x08108000)  // 16k
#define ADDR_FLASH_SECTOR_15    ((uint)0x0810C000)  // 16k
#define ADDR_FLASH_SECTOR_16    ((uint)0x08110000)  // 64k
#define ADDR_FLASH_SECTOR_17    ((uint)0x08120000)  // 128k
#define ADDR_FLASH_SECTOR_18    ((uint)0x08140000)  // 128k
#define ADDR_FLASH_SECTOR_19    ((uint)0x08160000)  // 128k
#define ADDR_FLASH_SECTOR_20    ((uint)0x08180000)  // 128k
#define ADDR_FLASH_SECTOR_21    ((uint)0x081A0000)  // 128k
#define ADDR_FLASH_SECTOR_22    ((uint)0x081C0000)  // 128k
#define ADDR_FLASH_SECTOR_23    ((uint)0x081E0000)  // 128k

#define SIZE_SECTOR_SETTINGS    (128 * 1024)        // ������ �������, ���� ����������� ���������, � ������

#define MAX_NUM_SAVED_WAVES 23  /* ���� ���������� ����������� �����������, ������� ����� ������� � ���� ����� ����� ����� */

bool    FLASH_LoadSettings(void);
void    FLASH_SaveSettings(void);

void    FLASH_GetDataInfo(bool existData[MAX_NUM_SAVED_WAVES]);                          // ���� ������� ����, ��������������� ������� ������� ����� true
bool    FLASH_ExistData(int num);
void    FLASH_SaveData(int num, DataSettings *ds, uint8 *dataA, uint8 *dataB);
bool    FLASH_GetData(int num, DataSettings **ds, uint8 **dataA, uint8 **dataB);
void    FLASH_DeleteData(int num);

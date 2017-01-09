#pragma once


#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Display/Display.h"
#include "FPGA/DataStorage.h"


#define MAX_NUM_SAVED_WAVES 23  /* ���� ���������� ����������� �����������, ������� ����� ������� � ���� ����� ����� ����� */


bool    FLASH_LoadSettings(void);
void    FLASH_SaveSettings(void);

void    FLASH_GetDataInfo(bool existData[MAX_NUM_SAVED_WAVES]);                          // ���� ������� ����, ��������������� ������� ������� ����� true
bool    FLASH_ExistData(int num);
void    FLASH_SaveData(int num, DataSettings *ds, uint8 *dataA, uint8 *dataB);
bool    FLASH_GetData(int num, DataSettings **ds, uint8 **dataA, uint8 **dataB);
void    FLASH_DeleteData(int num);

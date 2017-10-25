#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Display/Display.h"
#include "Data/DataStorage.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Hardware
 *  @{
 *  @defgroup FLASH
 *  @brief ������ � ���������� ����
 *  @{
 */

#define MAX_NUM_SAVED_WAVES 23  ///< \brief ����� ����������� �� ���������� ���� ���������. ���� ���������� ����������� �����������, ������� ����� 
                                ///< ������� � ���� ����� ����� �����.

void FLASH_LoadSettings(void);  ///< ���� onlyNonReset == true, ����������� ������ �������������� ���������.
void FLASH_SaveSettings(void);

void FLASH_GetDataInfo(bool existData[MAX_NUM_SAVED_WAVES]);    ///< ���� ������� ����, ��������������� ������� ������� ����� true.
bool FLASH_ExistData(int num);
void FLASH_SaveData(int num, DataSettings *ds, uint8 *dataA, uint8 *dataB);
bool FLASH_GetData(int num, DataSettings *ds, uint8 *dataA, uint8 *dataB);
void FLASH_DeleteData(int num);
void FLASH_DeleteAllData(void);

bool OTP_SaveSerialNumber(char *servialNumber);
int OTP_GetSerialNumber(char buffer[17]);   ///< ���������� ����� ��������� ���� ��� ������. ���� 0, �� ����� � OTP ��� �� ��������.

/** @} @}
 */

#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Hardware/RTC.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup FPGA
 *  @{
 *  @defgroup DataStorage Data Storage
 *  @{
 */

/// �������� ���� ���������� ���������.
void DS_Clear(void);
/// �������� ��������� ������. ��� ���� ����������� ��������� ������� ��������� �������.
void DS_AddData(uint8 *dataA, uint8 *dataB, DataSettings dss);
/// ���������� ����� ����������� ���������, ������� � ����������, � ������ �� �����������, ��� � ����������.
int DS_NumElementsWithSameSettings(void);
/// ���������� ����� ����������� ���������, ������� � ����������, � �������� ����������� �������.
int DS_NumElementsWithCurrentSettings(void);
/// ���������� ���������� ���������� ���������.
int DS_NumElementsInStorage(void);
/// �������� ������. ���� ��� � �����. ������� ����� ��������� �� ������� ds, dataA, dataB..
bool DS_GetDataFromEnd(int fromEnd, DataSettings *ds, uint8 *dataA, uint8 *dataB);
/// �������� ��������� �� ���������� ������. ������ �������� � ���.
bool DS_GetDataFromEnd_RAM(int fromEnd, DataSettings **ds, uint16 **dataA, uint16 **dataB);
/// ��������� ���������, ������� ��������� �� ������ � ������ �������� ���. ������ � ������ �������������� �� ����������
uint8 *DS_GetData_RAM(Channel ch, int fromEnd);
/// �������� ���������� ������ �� ���������� ����������
uint8 *DS_GetAverageData(Channel ch);
/// ���������� ��������� �� ������, ��������� �� indexFromEnd o� ���������� �����������
DataSettings *DS_DataSettingsFromEnd(int indexFromEnd);
/// �������� �������������� ����� ������� 0 - �����, 1 - ������
bool DS_GetLimitation(Channel ch, uint8 *data, int direction);
/// ������� ��������� ����� ���� ��������� ��� ����� �� ����� ������, ��� � ���������� �����������
int DS_NumberAvailableEntries(void);

//////////////////////////////// ������� ��� ����������� ������ ////////////////////////////////////////

/// ������ � ��������� ����� ��� ��������� ���� �����.������ ����� ������ ����� �������� DS_GetDataFromEnd_RAM(0...)
void DS_NewFrameP2P(DataSettings *dss);
/// ��������� ��������� ��������� ����� � ���������� ���������� ��� ��� �����
void DS_AddPointsP2P(uint16 dataA, uint16 dataB);
/// \brief �������� ������ ������ ����������� ������. ��������� ���������� ������ ����� �������� ������� DS_GetDataFromEnd_RAM(1...). 
/// ���������� ����� ���������� ����� (��� ����� ���� ������, ��� ���������� ����� � ������. � ���� ������ � ������ ��������� ��������� 
/// numPointsInChan �����.
int DS_GetFrameP2P_RAM(DataSettings **ds, uint8 **dataA, uint8 **dataB);

////////////////////////////// ������� ��� ��������� //////////////////////////////////////////////////

/** @}  @}
 */

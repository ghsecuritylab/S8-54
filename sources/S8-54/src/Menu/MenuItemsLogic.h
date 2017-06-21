#pragma once
#include "defines.h"
#include "MenuItems.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern int8 gCurDigit;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Menu
 *  @{
 *  @addtogroup MenuItems
 *  @{
 *  @defgroup MenuItmesLogic Menu Items Logic
 *  @{
 */

void Choice_StartChange(Choice *choice, int delta);
/// ������������ ��������� ���� ��������.
float Choice_Step(Choice *choice);
/// �������� �������� choice � ����������� �� �������� � ����� delta.
void Choice_ChangeIndex(Choice *choice, int delta);
/// ��������� �������� �������� ���������� ��� ���������� �������� ���� ���� Governor (� ����������� �� ����� delta).
void Governor_StartChange(Governor *governor, int detla);
/// ������������ ��������� ���� ��������.
float Governor_Step(Governor *governor);
/// �������� �������� � ������� ������� ��� ��������� ��������.
void Governor_ChangeValue(Governor *governor, int delta);
/// ���������� ��������� ������� ��������, ������� ����� ������� governor.
int16 Governor_NextValue(Governor *governor);
/// ���������� ��������� ������� ��������, ������� ����� ������� governor.
int16 Governor_PrevValue(Governor *governor);
/// ��� �������� �������� ������������ ������ �� ��������� �������.
void Governor_NextPosition(Governor *governor);
/// ���������� ����� ��������� � ���� ��� ����� �������� governor. ������� �� ������������� ��������, ������� ����� ��������� governor.
int  Governor_NumDigits(Governor *governor);
/// ��� �������� �������� ������������ ������ �� ��������� �������.
void IPaddress_NextPosition(IPaddress *ip);
/// �������� �������� � ������� ������� ��� �������� ��������.
void IPaddress_ChangeValue(IPaddress *ip, int delta);
/// ���������� ����� �������� ����� (4 - ����� �����) � ����� ������� ������� � �����.
void IPaddress_GetNumPosIPvalue(int *numIP, int *selPos);

void MACaddress_ChangeValue(MACaddress *mac, int delta);

void Time_SetOpened(Time *time);

void Time_SetNewTime(Time *time);

void Time_SelectNextPosition(Time *time);

void Time_IncCurrentPosition(Time *time);

void Time_DecCurrentPosition(Time *time);
/// �������� ������� ����� � governor.
void GovernorColor_ChangeValue(GovernorColor *governor, int delta);
/// ���������� ������� ������ �������� � ������ ��������.
void SBPage_SetCurrent(const Page *page);

/** @}  @}  @}
 */

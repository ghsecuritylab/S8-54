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



/// ��� �������� �������� ������������ ������ �� ��������� �������.
void IPaddress_NextPosition(IPaddress *ip);
/// �������� �������� � ������� ������� ��� �������� ��������.
void IPaddress_ChangeValue(IPaddress *ip, int delta);
/// ���������� ����� �������� ����� (4 - ����� �����) � ����� ������� ������� � �����.
void IPaddress_GetNumPosIPvalue(int *numIP, int *selPos);

void MACaddress_ChangeValue(MACaddress *mac, int delta);

void Time_SetNewTime(Time *time);

void Time_SelectNextPosition(Time *time);

void Time_DecCurrentPosition(Time *time);
/// �������� ������� ����� � governor.
void GovernorColor_ChangeValue(GovernorColor *governor, int delta);
/// ���������� ������� ������ �������� � ������ ��������.
void SBPage_SetCurrent(const Page *page);

/** @}  @}  @}
 */

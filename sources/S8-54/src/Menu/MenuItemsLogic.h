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



/// �������� �������� � ������� ������� ��� �������� ��������.
void IPaddress_ChangeValue(IPaddress *ip, int delta);
/// ���������� ����� �������� ����� (4 - ����� �����) � ����� ������� ������� � �����.
void IPaddress_GetNumPosIPvalue(int *numIP, int *selPos);


/** @}  @}  @}
 */

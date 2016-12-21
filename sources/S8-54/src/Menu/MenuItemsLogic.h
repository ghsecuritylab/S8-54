#pragma once


#include "defines.h"
#include "MenuItems.h"


void    Choice_StartChange(Choice *choice, int delta);
float   Choice_Step(Choice *choice);                            // ������������ ��������� ���� ��������.
void    Choice_ChangeIndex(Choice *choice, int delta);          // �������� �������� choice � ����������� �� �������� � ����� delta.

void    Governor_StartChange(Governor *governor, int detla);    // ��������� �������� �������� ���������� ��� ���������� �������� ���� ���� Governor (� ����������� �� ����� delta)
float   Governor_Step(Governor *governor);                      // ������������ ��������� ���� ��������.
void    Governor_ChangeValue(Governor *governor, int delta);    // �������� �������� � ������� ������� ��� ��������� ��������
int16   Governor_NextValue(Governor *governor);                 // ���������� ��������� ������� ��������, ������� ����� ������� governor.
int16   Governor_PrevValue(Governor *governor);                 // ���������� ��������� ������� ��������, ������� ����� ������� governor.
void    Governor_NextPosition(Governor *governor);              // ��� �������� �������� ������������ ������ �� ��������� �������
int     Governor_NumDigits(Governor *governor);                 // ���������� ����� ��������� � ���� ��� ����� �������� governor. ������� �� ������������� ��������, ������� ����� ��������� governor.

void    IPaddress_NextPosition(IPaddress *ip);                  // ��� �������� �������� ������������ ������ �� ��������� �������
void    IPaddress_ChangeValue(IPaddress *ip, int delta);        // �������� �������� � ������� ������� ��� �������� ��������
void    IPaddress_GetNumPosIPvalue(int *numIP, int *selPos);        // ���������� ����� �������� ����� (4 - ����� �����) � ����� ������� ������� � �����.

void    MACaddress_ChangeValue(MACaddress *mac, int delta);

void    Time_SetOpened(Time *time);
void    Time_SetNewTime(Time *time);
void    Time_SelectNextPosition(Time *time);
void    Time_IncCurrentPosition(Time *time);
void    Time_DecCurrentPosition(Time *time);

void    GovernorColor_ChangeValue(GovernorColor *governor, int delta);  // �������� ������� ����� � governor

extern int8 gCurDigit;

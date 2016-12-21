#pragma once


#include "SettingsTypes.h"
#include "defines.h"


#define TSHIFT  (set.time.tShiftRel)
#define TBASE   (set.time.tBase)
#define PEACKDET (set.time.peackDet)
#define PEACKDET_EN (set.time.peackDet == PeackDet_Enable)
#define PEACKDET_DIS (set.time.peackDet == PeackDet_Disable)


void    sTime_SetTBase(TBase tBase);        // ��������� ������� �� �������.
void    sTime_SetTShift(int16 shift);       // ��������� �������� �� ������� � ������������� ��������.
int     sTime_TPosInBytes(void);            // ������ �������� ���������� ������ ������������� � ������.
int16   sTime_TShiftMin(void);              // ����������� �������� �� �������, ������� ����� ���� �������� � ���������� �����.
int16   sTime_TShiftZero(void);             // �������� �� �������, ��������������� ������� TPos.
bool    sTime_RandomizeModeEnabled(void);   // ���� true, ������, �������� ������������.
bool    sTime_P2PModeEnabled(void);         // ���� true, �� �������� ���������� �����
int     sTime_TShiftInPoints(void);
int     sTime_TPosInPoints(void);

#pragma once


#include "SettingsTypes.h"
#include "defines.h"


#define TSHIFT          (set.time.tShiftRel)
#define TBASE           (set.time.tBase)
#define PEACKDET        (set.time.peackDet)
#define PEACKDET_EN     (PEACKDET == PeackDet_Enable)
#define PEACKDET_DIS    (PEACKDET == PeackDet_Disable)
#define IN_RANDOM_MODE  (TBASE < TBase_50ns)
#define IN_P2P_MODE     (TBASE >= MIN_TBASE_P2P)


void    sTime_SetTBase(TBase tBase);        // ��������� ������� �� �������.
void    sTime_SetTShift(int16 shift);       // ��������� �������� �� ������� � ������������� ��������.
int     sTime_TPosInBytes(void);            // ������ �������� ���������� ������ ������������� � ������.
int16   sTime_TShiftMin(void);              // ����������� �������� �� �������, ������� ����� ���� �������� � ���������� �����.
int16   sTime_TShiftZero(void);             // �������� �� �������, ��������������� ������� TPos.
int     sTime_TShiftInPoints(void);
int     sTime_TPosInPoints(void);

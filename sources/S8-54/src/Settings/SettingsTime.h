#pragma once


#include "SettingsTypes.h"
#include "defines.h"


#define TSHIFT          (set.time.tShiftRel)
#define TBASE           (set.time.tBase)
#define TIME_DIVXPOS    (set.time.timeDivXPos)

#define PEACKDET        (set.time.peackDet)
#define PEACKDET_EN     (PEACKDET == PeackDet_Enable)
#define PEACKDET_DIS    (PEACKDET == PeackDet_Disable)

#define IN_RANDOM_MODE  (TBASE < TBase_50ns)
#define IN_P2P_MODE     (TBASE >= MIN_TBASE_P2P)

#define TPOS            (set.time.tPos)
#define TPOS_RIGHT      (TPOS == TPos_Right)
#define TPOS_LEFT       (TPOS == TPos_Left)
#define TPOS_CENTER     (TPOS == TPos_Center)

#define SAMPLE          (set.time.sampleType)
#define SAMPLE_REAL     (SAMPLE == SampleType_Real)


void    sTime_SetTBase(TBase tBase);        // ��������� ������� �� �������.
void    sTime_SetTShift(int16 shift);       // ��������� �������� �� ������� � ������������� ��������.
int     sTime_TPosInBytes(void);            // ������ �������� ���������� ������ ������������� � ������.
int16   sTime_TShiftMin(void);              // ����������� �������� �� �������, ������� ����� ���� �������� � ���������� �����.
int16   sTime_TShiftZero(void);             // �������� �� �������, ��������������� ������� TPos.
int     sTime_TShiftInPoints(void);
int     sTime_TPosInPoints(void);

#pragma once


#include "defines.h"


typedef enum
{
    kPressKey,                  // ����� �������������, ����� �������� ������� �������.
    kShowLevelRShiftA,          // ����� �������������, ����� ���������� ��������� ����� �������� ������ 1.
    kShowLevelRShiftB,          // ����� �������������, ����� ���������� ��������� ����� �������� ������ 2.
    kShowLevelTrigLev,          // ����� �������������, ����� ���������� ��������� ����� ������ �������������
    kNumSignalsInSec,           // ��� ��������� ���������� ���������� ������� � �������.
    kFlashDisplay,              // ������ ��� ��������� �������� ������ �����-������ �������.
    kShowMessages,              // ������ ��� ��������� ����� ������ �������������� � ��������������� ���������.
    kMenuAutoHide,              // ������ ��� ������� ������� ��������� ����.
    kRShiftMarkersAutoHide,     // ������ ��� ������� ������� ��������� �������������� ������� �����.
    kTemp,                      // ���������������, ��� ����� ����.
    kStopSound,                 // ��������� ����
    kTemporaryPauseFPGA,        // ��������� ����� ��� �������� ������� �� ������ ����� �������� �����
    kTimerDrawHandFunction,     // ���� ������ ����� ������������ �������, ������������ ���� ��������� ���������
    kStrNaviAutoHide,           // ������� ������ ��������� ����
    kTimerStartP2P,             // ������ ��� ������� ���������� ����� ����������� ������
    kTimerMountFlash,           // ������ ��� ��������� ������� ��� ������������ ������
    kTimerBalanceChannel,       // ������ ��� ������� ��������� ������������
    NumTimers
} TypeTimer2;


void Timer_Init(void);
void Timer_Set(TypeTimer2 type, pFuncVV func, uint dTms);              // ��������� ������� timer ������� � ����� ������������
void Timer_SetAndStartOnce(TypeTimer2 type, pFuncVV func, uint dTms);
void Timer_SetAndEnable(TypeTimer2 type, pFuncVV func, uint dTms);
void Timer_StartOnce(TypeTimer2 type);
void Timer_Enable(TypeTimer2 type);
void Timer_Disable(TypeTimer2 type);
bool Timer_IsRun(TypeTimer2 type);

void Timer_PauseOnTime(uint timeMS);
void Timer_PauseOnTicks(uint numTicks);
void Timer_StartMultiMeasurement(void);      // ��������� ������� ��� ��������� ����� �������� �������.

void Timer_StartLogging(void);               // ������������� ��������� ����� ������������. ����� ������ Timer_LogPoint �������� ��������� ��������� �� ��� �����.
uint Timer_LogPointUS(char *name);
uint Timer_LogPointMS(char *name);

/**
  * gTimerTics - ���������� �����, ��������� � ������� ���������� ������ ������� Timer_StartMultiMeasurement(). �� ����� (1 << 32)
  * � ����� ������� 120.000.000 ����� ��� �8-53 � 90.000.000 ����� ��� �8-54.
  * ������������ ������� �������, ������� ����� ��������� � � ������� - 35 ���.
***/
#define gTimerTics (TIM2->CNT)
#define gTimerUS (TIM2->CNT / 90)
    
// �����, ��������� � ������� ������������� �������, � �������������
#define gTimerMS (TIM5->CNT / 2)   

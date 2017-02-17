#pragma once 


#include "defines.h"
#include "Utils/GlobalFunctions.h"


typedef enum
{
    kFlashDisplay,              // ������ ��� ��������� �������� ������ �����-������ �������.
    kTemp,                      // ���������������, ��� ����� ����.
    TypeTimerSize               // ����� ���������� ��������.
} TypeTimer;

typedef enum
{
    kDelayTrig                  // ��� ����� -> ���������
} TypePersonalTimer;

void    Timer_Init(void);
void    Timer_PauseOnTime(uint timeMS);
void    Timer_PauseOnTicks(uint numTicks);

void    Timer_Enable(TypeTimer type, int timeInMS, pFuncVV);
void    Timer_Disable(TypeTimer type);          // ���������� ������
void    Timer_Pause(TypeTimer type);            // ������������� ������. ��������� ����� ����� �������� Timer_Continue()
void    Timer_Continue(TypeTimer type);         // ���������� ������ �������, ����� ����������������� �������� Timer_Pause()
bool    Timer_IsRun(TypeTimer type);            // � ������� ���� ������� ����� ������, �������� �� ������

void    Timer_StartMultiMeasurement(void);      // ��������� ������� ��� ��������� ����� �������� �������.

void    Timer_StartLogging(void);               // ������������� ��������� ����� ������������. ����� ������ Timer_LogPoint �������� ��������� ��������� �� ��� �����.
uint    Timer_LogPointUS(char *name);
uint    Timer_LogPointMS(char *name);

void PersonalTimer_Start(TypePersonalTimer type, uint timeMS, bool repeat, pFuncVV func);
void PersonalTimer_Stop(TypePersonalTimer type);

//extern uint gTimerMS;

/**
  * gTimerTics - ���������� �����, ��������� � ������� ���������� ������ ������� Timer_StartMultiMeasurement(). �� ����� (1 << 32)
  * � ����� ������� 120.000.000 ����� ��� �8-53 � 90.000.000 ����� ��� �8-54.
  * ������������ ������� �������, ������� ����� ��������� � � ������� - 35 ���.
***/
#define gTimerTics (TIM2->CNT)
#define TICS_IN_US(x) ((x) / 90)

// �����, ��������� � ������� ������������� �������, � �������������
#define gTimerMS (TIM5->CNT / 10)                    

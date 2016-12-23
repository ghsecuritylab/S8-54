#pragma once 


#include "defines.h"
#include "Utils/GlobalFunctions.h"


void    Timer_PauseOnTime(uint timeMS);
void    Timer_PauseOnTicks(uint numTicks);

void    Timer_StartMultiMeasurement(void);      // ��������� ������� ��� ��������� ����� �������� �������.

void    Timer_StartLogging(void);               // ������������� ��������� ����� ������������. ����� ������ Timer_LogPoint �������� ��������� ��������� �� ��� �����.
uint    Timer_LogPointUS(char *name);
uint    Timer_LogPointMS(char *name);

//extern uint gTimerMS;

/**
  * gTimerTics - ���������� �����, ��������� � ������� ���������� ������ ������� Timer_StartMultiMeasurement(). �� ����� (1 << 32)
  * � ����� ������� 120.000.000 ����� ��� �8-53 � 90.000.000 ����� ��� �8-54.
  * ������������ ������� �������, ������� ����� ��������� � � ������� - 35 ���.
***/
#define gTimerTics (TIM2->CNT)
#define gTimerUS (TIM2->CNT / 90)
    
// �����, ��������� � ������� ������������� �������, � �������������
#define gTimerMS (TIM5->CNT / 2)                    

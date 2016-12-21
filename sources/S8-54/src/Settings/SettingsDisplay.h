#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "Display/Colors.h"


#define DISPLAY_NUM_ACCUM   (1 << (int)set.display.numAccumulation) /* ���������� ����� ���������� */
#define DISPLAY_NUM_MIN_MAX (1 << (int)set.display.numMinMax)       /* ���������� ���������� ��������� �������� ��� ������� ��������� � ����������. */


int     sDisplay_NumSignalsInS(void);                       // ���������� ����������� ������� ������.
void    sDisplay_SetNumSignalsInS(int maxFPS);              // ������������� ����������� ������� ������.
int     sDisplay_NumPointSmoothing(void);                   // ���������� ����� ����� ������������� ������� (����� ������� - �����������).
void    sDisplay_PointsOnDisplay(int *firstPoint, int *lastPoint); // ���������� ����� ������ � ��������� ����� �� ������.
int     sDisplay_TimeMenuAutoHide(void);                    // ���������� �����, ����� ������� ���� ������������� ����������, ���� �� ���� ������ �������.
bool    sDisplay_IsSeparate(void);                          // ���� ����� ������� �� ��� ����� � �������� ������ ��������� ������ - ��������, � ������ ������ �������
void    sDisplay_SetBrightness(int16 brightness);           // brightness = 1..100
ModeAveraging sDisplay_GetModeAveraging(void);              // ���������� ����� ����������
int     sDisplay_NumAverage(void);
int     sDisplay_ShiftInMemoryInPoints(void);               // ��� �������� ������ �� ������ � ������ �������� ��������� ��� ����� � ��� ���� ������, ��� ����, ������ ��� ������ ����� ������������ ����� �������


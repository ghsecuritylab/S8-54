#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "Display/Colors.h"


#define DISPLAY_NUM_ACCUM       (1 << (int)set.display.numAccumulation) /* ���������� ����� ���������� */
#define DISPLAY_NUM_MIN_MAX     (1 << (int)set.display.numMinMax)       /* ���������� ���������� ��������� �������� ��� ������� ��������� � ����������. */
#define SHOW_STRING_NAVI        (set.display.showStringNavigation)
#define SHOW_STRING_NAVI_TEMP   (set.display.showStringNavigation == ShowStrNavi_Temp)
#define SHOW_STRING_NAVI_ALL    (set.display.showStringNavigation == ShowStrNavi_All)
#define SHIFT_IN_MEMORY         (set.display.shiftInMemory)
#define TIME_MESSAGES           (set.display.timeMessages)
#define COLOR(x)                (set.display.colors[x])
#define MODE_DRAW_SIGNAL        (set.display.modeDrawSignal)
#define MODE_DRAW_SIGNAL_LINES  (MODE_DRAW_SIGNAL == ModeDrawSignal_Lines)
#define MODE_DRAW_SIGNAL_POINTS (MODE_DRAW_SIGNAL == ModeDrawSignal_Points)
#define TYPE_GRID               (set.display.typeGrid)
#define TYPE_GRID_1             (TYPE_GRID == TypeGrid_1)
#define TYPE_GRID_2             (TYPE_GRID == TypeGrid_2)
#define TYPE_GRID_3             (TYPE_GRID == TypeGrid_3)
#define TYPE_GRID_4             (TYPE_GRID == TypeGrid_4)


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


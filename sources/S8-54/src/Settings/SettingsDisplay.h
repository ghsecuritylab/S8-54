#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "Display/Colors.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsDisplay Settings Display
 *  @{
 */

#define SHIFT_IN_MEMORY         (set.display.shiftInMemory)
#define TIME_MESSAGES           (set.display.timeMessages)
#define COLOR(x)                (set.display.colors[x])
#define DISPLAY_NUM_MIN_MAX     (1 << (int)set.display.numMinMax)       /* ���������� ���������� ��������� �������� ��� ������� ��������� � ����������. */
#define NUM_SIGNALS_IN_SEC      (set.display.numSignalsInSec)
#define LAST_AFFECTED_CH        (set.display.lastAffectedChannel)
#define DISPLAY_ORIENTATION     (set.debug.orientation)


#define SHOW_STRING_NAVI        (set.display.showStringNavigation)
#define SHOW_STRING_NAVI_TEMP   (set.display.showStringNavigation == ShowStrNavi_Temp)
#define SHOW_STRING_NAVI_ALL    (set.display.showStringNavigation == ShowStrNavi_All)

#define MODE_DRAW_SIGNAL        (set.display.modeDrawSignal)
#define MODE_DRAW_SIGNAL_LINES  (MODE_DRAW_SIGNAL == ModeDrawSignal_Lines)
#define MODE_DRAW_SIGNAL_POINTS (MODE_DRAW_SIGNAL == ModeDrawSignal_Points)

#define TYPE_GRID               (set.display.typeGrid)
#define TYPE_GRID_1             (TYPE_GRID == TypeGrid_1)
#define TYPE_GRID_2             (TYPE_GRID == TypeGrid_2)
#define TYPE_GRID_3             (TYPE_GRID == TypeGrid_3)
#define TYPE_GRID_4             (TYPE_GRID == TypeGrid_4)

#define NUM_ACCUM               (set.display.numAccumulation)
#define NUM_ACCUM_INF           (NUM_ACCUM == NumAccumulation_Infinity)
#define DISPLAY_NUM_ACCUM       (1 << (int)NUM_ACCUM)                   /* ���������� ����� ���������� */

#define MODE_ACCUM              (set.display.modeAccumulation)
#define MODE_ACCUM_RESET        (MODE_ACCUM == ModeAccumulation_Reset)
#define MODE_ACCUM_NO_RESET     (MODE_ACCUM == ModeAccumulation_NoReset)

#define NUM_AVE                 (set.display.numAveraging)
#define DISPLAY_NUM_AVE         (1 << (int)NUM_AVE)

#define SMOOTHING               (set.display.smoothing)
#define SMOOTHING_ENABLED       (set.display.smoothing != NumSmooth_Disable)

#define ALT_MARKERS             (set.display.altMarkers)
#define ALT_MARKERS_SHOW        (ALT_MARKERS == AM_Show)
#define ALT_MARKERS_HIDE        (ALT_MARKERS == AM_Hide)
#define ALT_MARKERS_AUTO        (ALT_MARKERS == AM_AutoHide)

#define BACKGROUND              (set.display.background)
#define BACKGROUND_BLACK        (BACKGROUND == Background_Black)


/// ���������� ����������� ������� ������
int sDisplay_NumSignalsInS(void);
/// ������������� ����������� ������� ������
void sDisplay_SetNumSignalsInS(int maxFPS);
/// ���������� ����� ����� ������������� ������� (����� ������� - �����������)
int sDisplay_NumPointSmoothing(void);
/// ���������� ����� ������ � ��������� ����� �� ������
void sDisplay_PointsOnDisplay(int *firstPoint, int *lastPoint);
/// ���������� �����, ����� ������� ���� ������������� ����������, ���� �� ���� ������ �������
int sDisplay_TimeMenuAutoHide(void);
/// ���� ����� ������� �� ��� ����� � �������� ������ ��������� ������ - ��������, � ������ ������ �������
bool sDisplay_IsSeparate(void);
/// brightness = 1..100
void sDisplay_SetBrightness(int16 brightness);
/// ���������� ����� ����������
ModeAveraging sDisplay_GetModeAveraging(void);

int sDisplay_NumAverage(void);
/// ��� �������� ������ �� ������ � ������ �������� ��������� ��� ����� � ��� ���� ������, ��� ����, ������ ��� ������ ����� ������������ ����� �������
int sDisplay_ShiftInMemoryInPoints(void);

/** @}  @}
 */

#pragma once
#include "defines.h"
#include "SettingsTypes.h"
#include "SettingsTime.h"
#include "Display/Colors.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsDisplay Settings Display
 *  @{
 */

#define SHIFT_IN_MEMORY         (set.disp_ShiftInMemory)
#define TIME_MESSAGES           (set.disp_TimeMessages)
#define COLOR(x)                (set.disp_Colors[x])
#define ENUM_SIGNALS_IN_SEC     (set.disp_ENumSignalsInSec)
#define NUM_SIGNALS_IN_SEC      (sDisplay_NumSignalsInS())
#define LAST_AFFECTED_CH        (set.disp_LastAffectedChannel)
#define LAST_AFFECTED_CH_IS_A   (LAST_AFFECTED_CH == A)
#define DISPLAY_ORIENTATION     (set.dbg_Orientation)

#define SHOW_STRING_NAVI        (set.disp_ShowStringNavigation)
#define SHOW_STRING_NAVI_TEMP   (SHOW_STRING_NAVI == ShowStrNavi_Temp)
#define SHOW_STRING_NAVI_ALL    (SHOW_STRING_NAVI == ShowStrNavi_All)

#define MODE_DRAW_SIGNAL        (set.disp_ModeDrawSignal)
#define MODE_DRAW_SIGNAL_LINES  (MODE_DRAW_SIGNAL == ModeDrawSignal_Lines)
#define MODE_DRAW_SIGNAL_POINTS (MODE_DRAW_SIGNAL == ModeDrawSignal_Points)

#define TYPE_GRID               (set.disp_TypeGrid)
#define TYPE_GRID_1             (TYPE_GRID == TypeGrid_1)
#define TYPE_GRID_2             (TYPE_GRID == TypeGrid_2)
#define TYPE_GRID_3             (TYPE_GRID == TypeGrid_3)
#define TYPE_GRID_4             (TYPE_GRID == TypeGrid_4)

#define ENUM_ACCUM              (set.disp_ENumAccum)
#define ENUM_ACCUM_INF          (ENUM_ACCUM == ENumAccum_Infinity)
#define NUM_ACCUM               (1 << (int)ENUM_ACCUM)                   /* ���������� ����� ���������� */
#define IN_ACCUM_MODE           (ENUM_ACCUM > ENumAccum_1)

#define MODE_ACCUM              (set.disp_ModeAccumulation)
#define MODE_ACCUM_RESET        (MODE_ACCUM == ModeAccumulation_Reset)
#define MODE_ACCUM_NO_RESET     (MODE_ACCUM == ModeAccumulation_NoReset)

#define ENUM_MIN_MAX            (set.disp_ENumMinMax)
#define MIN_MAX_ENABLED         (ENUM_MIN_MAX != ENumMinMax_1)
#define NUM_MIN_MAX             (1 << (int)ENUM_MIN_MAX)                /* ���������� ���������� ��������� �������� ��� ������� ��������� � ����������. */

#define MODE_AVERAGING          (set.disp_ModeAveraging)
#define ENUM_AVE                (set.disp_ENumAverages)
#define NUM_AVE                 (1 << (int)ENUM_AVE)
#define IN_AVERAGING_MODE       (ENUM_AVE > ENumAverages_1 && (!IN_P2P_MODE))

#define ENUM_SMOOTHING          (set.disp_ENumSmoothing)
#define NUM_SMOOTHING          (sDisplay_NumPointSmoothing())
#define SMOOTHING_ENABLED       (ENUM_SMOOTHING != ENumSmooth_Disable)

#define ALT_MARKERS             (set.disp_AltMarkers)
#define ALT_MARKERS_SHOW        (ALT_MARKERS == AM_Show)
#define ALT_MARKERS_HIDE        (ALT_MARKERS == AM_Hide)
#define ALT_MARKERS_AUTO        (ALT_MARKERS == AM_AutoHide)

#define BACKGROUND              (set.disp_Background)
#define BACKGROUND_BLACK        (BACKGROUND == Background_Black)

#define LINKING_RSHIFT          (set.disp_LinkingRShift)

#define MENU_AUTO_HIDE          (set.disp_MenuAutoHide)

#define BRIGHTNESS_DISPLAY      (set.disp_Brightness)

#define BRIGHTNESS_GRID         (set.disp_BrightnessGrid)

#define SET_NUM_BYTES_ON_DISPLAY   (SET_PEAKDET_EN ? 281 * 2 : 281)


/// ���������� ����������� ������� ������
int sDisplay_NumSignalsInS(void);
/// ������������� ����������� ������� ������
void sDisplay_SetNumSignalsInS(int maxFPS);
/// ���������� ����� ����� ������������� ������� (����� ������� - �����������)
int sDisplay_NumPointSmoothing(void);
/// ���������� ����� ������ � ��������� ����� �� ������ � ����������� ������
BitSet64 sDisplay_PointsOnDisplay(void);
/// \brief ��������� ����� ������ � ��������� ����� � ����������� ������
BitSet64 sDisplay_BytesOnDisplay(void);
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

#define SHIFT_IN_MEMORY_IN_POINTS sDisplay_ShiftInMemoryInPoints()

/** @}  @}
 */

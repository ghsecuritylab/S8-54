#pragma once
#include "DisplayTypes.h"
#include "Settings/SettingsTypes.h"
#include "Tables.h"
#include "Painter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup Display
 *  @brief ������ � ��������
 *  @details ��� ���������� ������ ������ ������� ����� ������� �� DS_GetData(0), � ��������� ������ ������ �� DS_GetData(1).
 *  @{
 */

/// �������������
void Display_Init(void);
/// ��� ������� ����� �������� ������ ���� - ���������
void Display_Update(void);
/// ��� ������� ����� �������� ��� �������� ����� �������� �� ��������� ��� ��������� ��������� ��������������� ��������
void Display_RotateRShift(Channel ch);
/// ��� ������� ����� �������� ��� �������� ����� ������ ������������� ��� ��������� ��������� ��������������� ��������
void Display_RotateTrigLev(void);

void Display_EnableTrigLabel(bool enable);

void Display_SetAddDrawFunction(pFuncVV func);

pFuncVV Display_GetAddDrawFunction(void);

void Display_RemoveAddDrawFunction(void);

void Display_Clear(void);

void Display_ShiftScreen(int delta);

void Display_ChangedRShiftMarkers(bool active);

void Display_AddStringToIndicating(const char *string);

void Display_OneStringUp(void);

void Display_OneStringDown(void);

void Display_SetPauseForConsole(bool pause);

void Display_SetOrientation(DisplayOrientation orientation);
/// ������� ��������� ���������� �������
void Display_DrawConsole(void);
/// @brief ���������� ������� � ����� ��������� ������.
/// @details �������� ��� ��������.
/// 1. DrawMode_Hand - � ���� ������ ����� ���������� ������� func(), ������������ �������������, � �������� 25 ��� � �������.
/// ������������ � �������, ����� �� ����������� ������� ����.
/// 2. DrawMode_Auto � func == 0 - � ���� ������ ����� ����������� ������� Display_Update() � ������� �����.
/// 3. DrawMode_Auto � func != 0 - � ���� ������ ����� ����������� ������� func(), ������������ �������������, �� � ����
/// �������� �����, ������ ���������� �� Display_Update() ������ Display_Update().
void Display_SetDrawMode(DrawMode mode, pFuncVV func); 


/// C��������, ��������� �� �����
typedef enum
{
    LimitChan1_Volts,               ///< ������ �������� �� ����������� ������� ������.
    LimitChan2_Volts,               ///< ������ �������� �� ���������� ������� ������.
    LimitSweep_Time,                ///< ������ �������� �� �������.
    EnabledPeakDet,                 ///< ������� ������� ��������.
    LimitChan1_RShift,              ///< ������ �������� �� ���������� ������� ������.
    LimitChan2_RShift,              ///< ������ �������� �� ���������� ������� ������.
    LimitSweep_Level,               ///< ������ ������ �������������.
    LimitSweep_TShift,              ///< ������ �������� �� �������.
    TooSmallSweepForPeakDet,        ///< ������� ������� �������� ��� �������� ���������.
    TooFastScanForRecorder,         ///< ������� ������� �������� ��� ����������� ������.
    FileIsSaved,                    ///< ���� ������� �� ������.
    SignalIsSaved,                  ///< ������ ������� � ���.
    SignalIsDeleted,                ///< �� ���� ����� ������.
    MenuDebugEnabled,               ///< �������� ���� �������.
    TimeNotSet,                     ///< ����� �� �����������.
    SignalNotFound,                 ///< ������ �� ������ (���������).
    SetTPosToLeft,                  ///< ������������.
    NeedRebootDevice,               ///< ��������� ������������.
    ImpossibleEnableMathFunction,   ///< ���������� �������� �������������� �������.
    ImpossibleEnableFFT,            ///< ���������� �������� ���������� ���.
    WrongFileSystem,                ///< ���������� ���������� ������.
    WrongModePeackDet,              ///< ���������� �������� ������� ��������.
    DisableChannel2,                ///< ��������� ��������� ����� 2.
    TooLongMemory,                  ///< ��������� � ������������� ��������� ������ 32�.
    NoPeakDet32k,                   ///< ������� �������� �� �������� ��� ����� ������ 32�.
    NoPeakDet16k,                   ///< ������� �������� �� �������� ��� ����� ������ 16�.
    Warn50Ohms,                     ///< �������������� �� ����������� �������� ������ �� 50 ����.
    WarnNeedForFlashDrive,          ///< ��������� ������������ ������.
    FirmwareSaved,                  ///< �������� ��������� �� ������.
    FullyCompletedOTP,              ///< 
    Warning_Count
} Warning;

void Display_ClearFromWarnings(void);

void Display_ShowWarning(Warning warning);

// ������ ������� ��� ������ ��������� � ������� �������
void Display_FuncOnWaitStart(const char *text, bool eraseBackground);

void Display_FuncOnWaitStop(void);

/** @}
 */

#pragma once
#include "DisplayTypes.h"
#include "Settings/SettingsTypes.h"
#include "Tables.h"
#include "Painter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup Display
 *  @brief ������ � ��������
 *  @details ��� ���������� ������ ������ ������� ����� ������� �� DS_GetData(0), � ��������� ������ ������ �� DS_GetData(1).
 *  @{
 */

class Display
{
public:
    /// �������������
    void Init(void);
    /// ��� ������� ����� �������� ������ ���� - ���������
    void Update(void);
    /// ��� ������� ����� �������� ��� �������� ����� �������� �� ��������� ��� ��������� ��������� ��������������� ��������
    void RotateRShift(Channel ch);
    /// ��� ������� ����� �������� ��� �������� ����� ������ ������������� ��� ��������� ��������� ��������������� ��������
    void RotateTrigLev(void);

    void EnableTrigLabel(bool enable);

    void SetAddDrawFunction(pFuncVV func);

    pFuncVV GetAddDrawFunction(void);

    void RemoveAddDrawFunction(void);

    void Clear(void);

    void ShiftScreen(int delta);

    void ChangedRShiftMarkers(bool active);

    void AddStringToIndicating(const char *string);

    void OneStringUp(void);

    void OneStringDown(void);

    void SetPauseForConsole(bool pause);

    void SetOrientation(DisplayOrientation orientation);
    /// ������� ��������� ���������� �������
    void DrawConsole(void);
    /// @brief ���������� ������� � ����� ��������� ������.
    /// @details �������� ��� ��������.
    /// 1. DrawMode_Hand - � ���� ������ ����� ���������� ������� func(), ������������ �������������, � �������� 25 ��� � �������.
    /// ������������ � �������, ����� �� ����������� ������� ����.
    /// 2. DrawMode_Auto � func == 0 - � ���� ������ ����� ����������� ������� Update() � ������� �����.
    /// 3. DrawMode_Auto � func != 0 - � ���� ������ ����� ����������� ������� func(), ������������ �������������, �� � ����
    /// �������� �����, ������ ���������� �� Update() ������ Update().
    void SetDrawMode(DrawMode mode, pFuncVV func);

    void ClearFromWarnings(void);

    void ShowWarning(Warning warning);

    // ������ ������� ��� ������ ��������� � ������� �������
    void FuncOnWaitStart(const char *text, bool eraseBackground);

    void FuncOnWaitStop(void);
};

extern Display display;

/** @}
 */

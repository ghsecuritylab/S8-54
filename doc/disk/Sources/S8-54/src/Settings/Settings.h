#pragma once
#include "SettingsTypes.h"
#include "Utils/Measures.h"
#include "Menu/MenuItems.h"
#include "Panel/Controls.h"
#include "SettingsChannel.h"
#include "SettingsDisplay.h"
#include "SettingsMemory.h"
#include "SettingsTime.h"
#include "SettingsTrig.h"
#include "SettingsService.h"
#include "SettingsCursors.h"
#include "SettingsDebug.h"
#include "SettingsMeasures.h"
#include "SettingsMath.h"
#include "SettingsNRST.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup Settings
 *  @{
 */


#define ETH_ENABLED         (set.eth_enable)
#define ETH_PORT            (set.eth_port)


#define SIZE_NONRESET_SETTINGS 200


// �������� ������������, ����� ���������� ����������� ����������� ����� ������ ��������� Settings

#pragma pack(push, 1)

typedef struct
{
    uint16              size;                       ///< \brief � ������ ����� ������ ������ ���������, ����� ��� �������� ����� ���� ���������� 
                                                    /// ��������� ��������� Settings.
    // SettingsDisplay
    int16               disp_TimeShowLevels;        ///< �����, � ������� �������� ����� ���������� ������ ��������.
    int16               disp_ShiftInMemory;         ///< \brief ���������� �������� ������ ���� ����� ������������ �������� ����� ������ � ������
                                                    ///< �.�. ��� �������� ��������� ����� � ��� ���� ������ ���������� ����� �� ������.
    int16               disp_TimeMessages;          ///< ����� � ��������, �� ������� ��������� ������� �� �����.
    int16               disp_Brightness;            ///< ������� �������.
    int16               disp_BrightnessGrid;        ///< ������� ����� �� 0 �� 100.
    uint16              disp_Colors[16];
    ModeDrawSignal      disp_ModeDrawSignal;        ///< ����� ��������� �������.
    TypeGrid            disp_TypeGrid;              ///< ��� �����
    ENumAccum           disp_ENumAccum;             ///< ����� ���������� ������� �� ������.
    ENumAverages        disp_ENumAverages;          ///< ����� ���������� �������.
    ModeAveraging       disp_ModeAveraging;         ///< ��� ���������� �� ����������.
    ENumMinMax          disp_ENumMinMax;            ///< ������������ ���������� ��������� ��� ����������� ��������� � ���������.
    ENumSmoothing       disp_ENumSmoothing;         ///< ������������ ���������� ����� ��� ����������� �������.
    ENumSignalsInSec    disp_ENumSignalsInSec;      ///< ������������ ����� ���������� ������� � �������.
    Channel             disp_LastAffectedChannel;   ///< \brief ����� �������� ����� ���������� ������, ������� ��������� �������. ����� ��� ����, 
                                                    /// ����� �����, ����� ������ �������� �������.
    ModeAccumulation    disp_ModeAccumulation;      ///< ����� ���������� ��������.
    AltMarkers          disp_AltMarkers;            ///< ����� ����������� �������������� ������� �������� ��������.
    MenuAutoHide        disp_MenuAutoHide;          ///< ����� ������� ������� ����� ���������� ������� ������� ������� ����.
    ShowStrNavi         disp_ShowStringNavigation;  ///< ����� ������ ������ ��������� ����.
    LinkingRShift       disp_LinkingRShift;         ///< ��� �������� � �������� �� ���������.
    Background          disp_Background;            ///< ���� ����.
    // Channels
    uint16          chan_RShiftRel[2];
    ModeCouple      chan_ModeCouple[2];             ///< ����� �� �����.
    Divider         chan_Divider[2];                ///< ���������.
    Range           chan_Range[2];                  ///< ������� �� ����������.
    bool            chan_Enable[2];
    bool            chan_Inverse[2];
    int8            chan_BalanceShiftADC[2];        ///< ���������� �������� ��� ������������ ���.
    Bandwidth       chan_Bandwidth[2];              ///< ����������� ������.
    Resistance      chan_Resistance[2];             ///< ������������� �����.
    CalibrationMode chan_CalibrationMode[2];        ///< ����� ����������.
    // Trig
    uint16          trig_LevelRel[3];               ///< ������� ������������� ��� ��� �������.
    uint16          trig_TimeDelay;
    StartMode       trig_StartMode;                 ///< ����� �������.
    TrigSource      trig_Source;                    ///< ��������.
    TrigPolarity    trig_Polarity;                  ///< ��� �������������.
    TrigInput       trig_Input;                     ///< ���� �������������.
    TrigModeFind    trig_ModeFind;                  ///< ����� ������������� - ������� ��� �������������.
    // TBase
    TBase           time_TBase;                     ///< ������� �� �������.
    int16           time_TShiftRel;                 ///< �������� �� �������.
    FunctionTime    time_TimeDivXPos;
    TPos            time_TPos;
    SampleType      time_SampleType;
    SampleType      time_SampleTypeOld;
    PeakDetMode    time_PeakDet;
    // �������
    CursCntrl       curs_CntrlU[NumChannels];       ///< �������� ������� ����������.
    CursCntrl       curs_CntrlT[NumChannels];       ///< �������� ������� �������.
    Channel         curs_Source;                    ///< �������� - � ������ ������ ��������� �������.
    float           curs_PosCurU[NumChannels][2];   ///< ������� ������� �������� ���������� ����� �������.
    float           curs_PosCurT[NumChannels][2];   ///< ������� ������� �������� ������� ����� �������.
    float           curs_DeltaU100percents[2];      ///< ���������� ����� ��������� ���������� ��� 100%, ��� ����� �������.
    float           curs_DeltaT100percents[2];      ///< ���������� ����� ��������� ������� ��� 100%, ��� ����� �������.
    CursMovement    curs_Movement;                  ///< ��� ������������ �������� - �� ������ ��� ���������.
    CursActive      curs_Active;                    ///< ����� ������� ����� �������.
    CursLookMode    curs_LookMode[2];               ///< ������ �������� �� ��������� ��� ���� ��� ��������.
    bool            curs_ShowFreq;                  ///< ������������� � true ��������, ��� ����� ���������� �� ������ 1/dT ����� ���������.
    bool            curs_ShowCursors;               ///< ���������� �� �������.
    // Memory
#define MAX_SYMBOLS_IN_FILE_NAME 35
    ENumPointsFPGA  mem_ENumPointsFPGA;             ///< ����� �����.
    ModeWork        mem_ModeWork;                   ///< ����� ������.
    FileNamingMode  mem_FileNamingMode;             ///< ����� ���������� ������.
    char            mem_FileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; ///< \brief ����� ����� ��� ��������������� ���������� ������.
                ///< \details ������� ����������.\n
                /// \code
                /// %y('\x42') - ���, %m('\x43') - �����, %d('\x44') - ����, %H('\x45') - ����, %M('\x46') - ������, %S('\x47') - �������
                /// %Nn('\x48''n') - ���������� �����, ������ �������� �� ����� n ���������, ��������, 7 � %3N ����� ������������� � 007
                /// �������
                /// name_%4N_%y_%m_%d_%H_%M_%S ����� ������������ ����� ���� name_0043_2014_04_25_14_45_32
                /// ��� ���� �������� ��������, ��� ���� ������������ %4N ����� ����� ��������� ����������, ��, ������ �����, ���� �������� 
                /// ����� ������ ����� 0001, �.�. ��� ����������� ������ ���������������.
                /// \endcode
    char            mem_FileName[MAX_SYMBOLS_IN_FILE_NAME]; ///< ��� ����� ��� ������ ������� �������.
    int8            mem_IndexCurSymbolNameMask; ///< ������ �������� ������� � ������ ������� ����� ��� ������ �����.
    ModeShowIntMem  mem_ModeShowIntMem;         ///< ��� ���������� � ������ ����� �� - ��������� ��� ���������� ������.
    bool            mem_FlashAutoConnect;       ///< ���� true, ��� ����������� ������ ������������� ��������� ����-��������.
    ModeBtnMemory   mem_ModeBtnMemory;
    ModeSaveSignal  mem_ModeSaveSignal;         ///< � ����� ���� ��������� ������.
    // ���������
    MeasuresNumber  meas_Number;                ///< ������� ��������� ��������.
    Channel         meas_Source;                ///< ��� ����� ������� �������� ���������.
    ModeViewSignals meas_ModeViewSignals;       ///< ������� �� ������� ��� ������ ���������.
    Measure         meas_Measures[15];          ///< ��������� ��� ��������� ���������.
    bool            meas_Show;                  ///< ���������� �� ���������.
    MeasuresZone    meas_Zone;                  ///< ����� �������, �� ������� ������� �������� ��� ������� ���������.
    int16           meas_PosCurU[2];            ///< \brief ������� ��������, ������� ������ �������, �� ������� ������� �������� ��� ������� 
                                                ///< ��������� ��� field == MeasuresField_Hand.
    int16           meas_PosCurT[2];            ///< \brief ������� ��������, ������� ������ �������, �� ������� ������� �������� ��� �������
                                                ///< ��������� ��� field == MeasuresField_Hand.
    CursCntrl       meas_CntrlU;                ///< �������� ������� ����������.
    CursCntrl       meas_CntrlT;                ///< �������� ������� �������.
    CursActive      meas_CursActive;            ///< ����� ������� ������� - �� ������� ��� ����������.
    Measure         meas_Marked;                ///< ���������, �� ������� ����� �������� �������.
    // SettingsMath
    ScaleFFT        math_ScaleFFT;
    SourceFFT       math_SourceFFT;
    WindowFFT       math_WindowFFT;
    FFTmaxDB        math_FFTmaxDB;
    Function        math_Function;
    uint8           math_CurrentCursor;         ///< ����������, ����� �������� ������� ��������� ����� ���������.
    uint8           math_PosCur[2];             ///< ������� ������� �������. ���������� 0...256.
    int8            math_koeff1add;             ///< ����������� ��� ������ ��������� ��� ��������.
    int8            math_koeff2add;
    int8            math_koeff1mul;
    int8            math_koeff2mul;
    bool            math_EnableFFT;
    ModeDrawMath    math_ModeDraw;              ///< ���������� ��� ����� ������� � ������ �������������� �������.
    ModeRegSet      math_ModeRegSet;            ///< ������� ����� ��������� - ������� �� ������� ��� �������� �� ���������.
    Range           math_Range;
    Divider         math_Divider;
    uint16          math_RShift;
    // ����������
    bool            freq_Enable;
    TimeCounting    freq_TimeCounting;          ///< ����� ����� �������.
    FreqClc         freq_FreqClc;               ///< ������� ����������.
    NumberPeriods   freq_NumberPeriods;         ///< ���������� ��������.
    // ������
    int16               serv_SoundVolume;       ///< ��������� ����� [0...100].
    int16               serv_SpeedRShift;       ///< ������������� �������� �������� �� �������� ����� RShift.
    bool                serv_SoundEnable;       ///< �������� �� �����.
    bool                serv_Recorder;          ///< ������� �� ����� ������������.
    CalibratorMode      serv_CalibratorMode;    ///< ����� ������ �����������.
    ColorScheme         serv_ColorScheme;
    FunctionPressRShift serv_FuncRShift;        ///< �������, ����������� �� ������� �� ����� RShift.
    // Ethernet
    uint8       eth_mac0;
    uint8       eth_mac1;
    uint8       eth_mac2;
    uint8       eth_mac3;
    uint8       eth_mac4;
    uint8       eth_mac5;
    uint8       eth_ip0;
    uint8       eth_ip1;
    uint8       eth_ip2;
    uint8       eth_ip3;
    uint16      eth_port;
    uint8       eth_mask0;
    uint8       eth_mask1;
    uint8       eth_mask2;
    uint8       eth_mask3;
    uint8       eth_gw0;
    uint8       eth_gw1;
    uint8       eth_gw2;
    uint8       eth_gw3;
    bool        eth_enable;
    // Common
    int         com_CountEnables;                   ///< ���������� ���������. ���������������� ��� ������ ���������.
    int         com_CountErasedFlashData;           ///< ������� ��� �������� ������ ������ � ���������.
    int         com_CountErasedFlashSettings;       ///< ������� ��� �������� ������ � �����������.
    int         com_WorkingTimeInSecs;              ///< ����� ������ � ��������.
    Language    com_Lang;                           ///< ���� ����.
    // Debug
    bool                dbg_ShowRandInfo;           ///< �������� ���������� �� ������������� - ������ � ��������� ��������.
    bool                dbg_ShowRandStat;           ///< �������� ������ ����������.
    bool                dbg_ModeEMS;                ///< \brief ��� ��������� ����� ������ ������������� ���������� ������ 20���, ���������� �� 
                                                    /// 8-�� ������, ����������� �� 4-�.
    bool                dbg_ShowStats;              ///< ���������� ���������� �� ������ (fps, ��������).
    bool                dbg_ModePauseConsole;       ///< ���� true, �� ����� � ������� ��������������� �������� ������ ����/����.
    int8                dbg_SizeFont;               ///< ������ ������ ������� - 0 - 5, 1 - 8.
    DisplayOrientation  dbg_Orientation;
    int16               dbg_NumStrings;             ///< ����� ����� � �������.
    int16               dbg_NumMeasuresForGates;    ///< ����� ��������� ��� �����.
    int16               dbg_TimeCompensation;       ///< �������������� �������� �� ������� ��� ������ �������� ������ �������������.
    int16               dbg_AltShift;               ///< ���������� �������� ��� ���������� ������� �������������� ������ �������������.
    int16               dbg_Pretriggered;           ///< ������������ �������� ����������� ��� ������������ �������������.
    Bandwidth           dbg_Bandwidth[2];           ///< \brief ����� ������� ������, ������� ����� ���������� ��� ������ � "�����-������" 
                                                    ///< �������� "������".
    bool                dbg_ShowAll;
    bool                dbg_ShowFlag;
    bool                dbg_ShowRShift[2];
    bool                dbg_ShowTrigLev;
    bool                dbg_ShowRange[2];
    bool                dbg_ShowChanParam[2];
    bool                dbg_ShowTrigParam;
    bool                dbg_ShowTShift;
    bool                dbg_ShowTBase;
    // SettingsMenu
    int8                menu_PosActItem[Page_NumPages];             ///< \brief ������� ��������� ������. bit7 == 1 - item is opened, 0x7f - ��� 
                                                                    ///< ��������� ������.
    int8                menu_CurrentSubPage[Page_NumPages];         ///< ����� ������� �����������.
    bool                menu_PageDebugActive;                       ///< ������� �� ������ ������� � ����.
    int8                menu_IsShown;                               ///< \brief ���� ��������. ���� == false, � ��� ���� �����-���� ������� ���� �������,
                                                                    ///< �� �� ����� ������� �� ������.
    // ���������, ������� �������� �������� ��� ������� �� ������
    int16               nrst_RShiftAdd[NumChannels][RangeSize][2];  ///< ���������� ��������, ������� ������� ���� ��� ���������� � ������������
    int16               nrst_CorrectionTime;                        ///< ����������� ��������� �������.
    int16               nrst_BalanceADC[NumChannels];               ///< �������� ��������������� �������� ��� ��� ������ ������������.
    int16               nrst_NumAveForRand;                         ///< �� �������� ���������� ��������� ������ � ������ �������������.
    BalanceADCtype      nrst_BalanceADCtype;                        ///< ��� ������������.
    StretchADCtype      nrst_StretchADCtype;                        ///< ��� �������� ������.
    int16               nrst_StretchADC[NumChannels][3];            ///< \brief ����������� ����������� ��� �������, �������������� �
                        ///< ������������ �������. ����� �������� � ����� ����, ����� �������� �������� �����������, ����� ��������� �� 1000 �
                        ///< ��������� �������.
    int16               nrst_AddStretch20mV[NumChannels];
    int16               nrst_AddStretch50mV[NumChannels];
    int16               nrst_AddStretch100mV[NumChannels];
    int16               nrst_AddStretch2V[NumChannels];
    int16               nrst_NumSmoothForRand;                      ///< ����� ����� ��� ����������� ������ � �������������.
    MemDataScale        mem_DataScale;                              ///< \brief ���������� ��������� ����������� ������� ��� ������������ �����
                                                                    ///< ���������� ��������.
    PlaceOfSaving       rec_PlaceOfSaving;                          ///< ���� ����� ����������� ������ ������������
    int8                rec_NumCursor;                              ///< ����� ��������� �������
    int16               nrst_RShiftAddStable[NumChannels][3];       ///< ���������� �������� ��� ��� ����� �������������� ����������. ������� �������� ��� ���������
} Settings;

#pragma pack(pop)

extern Settings set;

/// ���������� ������� ��������� ������ �� �������� namePage.
void SetMenuPosActItem(NamePage namePage, int8 pos);
/// ���������� ����� ������� ����������� �������� namePage.
int8 MenuCurrentSubPage(NamePage namePage);
/// ������������� ����� ������� ����������� � �������� namePage.
void SetMenuCurrentSubPage(NamePage namePage, int8 posSubPage);
/// ���� true - ���� ��������� � �������������� ������.
bool MenuIsMinimize(void);
/// ������� �� �������� �������.
bool MenuPageDebugIsActive(void);
/// �������/��������� �������� �������� �������.
void SetMenuPageDebugActive(bool active);
/// ��������� ����� ��������� �� ������� �������� ����� ������.
void CurrentPageSBregSet(int angle);
/// ������� ��������� �� ����� ������, ��������������� ������ ������ ������.
const SButton*  GetSmallButton(PanelButton button);

/// ���������� ������� ��������� ������ �� �������� namePage.
#define MENU_POS_ACT_ITEM(namePage) (set.menu_PosActItem[namePage])

/// \brief ��������� ���������. ���� default == true, ����������� ��������� �� ���������, ����� �������� ��������� ��������� �� ���, � � ������ 
/// ������� - ���� ��������� �� ���������.
void Settings_Load(bool _default);
/// ��������� ��������� �� ����-������.
void Settings_Save(void);
/// ���������� true, ���� ������� ����� �������.
bool Settings_DebugModeEnable(void);
/// ��������� ������� ��������� � set_.
void Settings_SaveState(Settings *set_);
/// ��������������� ����� ���������� ��������� � set_.
void Settings_RestoreState(const Settings *set_);

/** @}
 */

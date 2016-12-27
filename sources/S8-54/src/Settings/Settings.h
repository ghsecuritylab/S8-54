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

#ifndef _MS_VS
#pragma anon_unions     // ��������� ���������� �����������
#endif


#define SIZE_NONRESET_SETTINGS 200


// ��������� �����������
typedef struct
{
    int16               timeShowLevels;             // �����, � ������� �������� ����� ���������� ������ ��������
    int16               shiftInMemory;              // ���������� �������� ������ ���� ����� ������������ �������� ����� ������. ����� ��� ����������� ����������� ������� � ����. ��� �������� ��������� ���������� ���������� ����, � �� �����.
    int16               timeMessages;               // ����� � ��������, �� ������� ��������� ������� �� ������
    int16               brightness;                 // ������� ������� (������ ��� ��������)
    int16               brightnessGrid;             // ������� ����� �� 0 �� 100
    uint16              colors[16];
    ModeDrawSignal      modeDrawSignal;             // ����� ��������� �������
    TypeGrid            typeGrid;                   // ��� �����
    NumAccumulation     numAccumulation;            // ����� ���������� ������� �� ������
    NumAveraging        numAveraging;               // ����� ���������� �������
    ModeAveraging       modeAveraging;              // ��� ���������� �� ����������
    NumMinMax           numMinMax;                  // ����� ��������� ��� ����������� ��������� � ����������
    NumSmoothing        smoothing;                  // ����� ����� ��� ����������� �������
    NumSignalsInSec     numSignalsInSec;            // ����� ���������� ������� � �������
    Channel             lastAffectedChannel;        // ����� �������� ����� ���������� ������, ������� ��������� �������. ����� ��� ����, ����� �����, ����� ������ �������� �������.
    ModeAccumulation    modeAccumulation;           // ����� ����� ���������� ��������
    AltMarkers          altMarkers;                 // ����� ����������� �������������� ������� �������� ��������
    MenuAutoHide        menuAutoHide;               // ����� ������� ������� ����� ���������� ������� ������� ������� ���� 
    ShowStrNavi         showStringNavigation;       // ����� ������ ������ ��������� ����
    LinkingRShift       linkingRShift;              // ��� �������� � �������� �� ���������
    Background          background;                 // ���� ����
} SettingsDisplay;


// ��������� �������
typedef struct
{
    uint16          rShiftRel;
    ModeCouple      modeCouple;         	    // ����� �� �����.
    Divider         divider;                    // ���������.
    Range           range;              	    // ������� �� ����������.
    bool            enable;
    bool            inverse;
    int8            balanceShiftADC;    	    // ���������� �������� ��� ������������ ���.
    Bandwidth       bandwidth;                  // ����������� ������
    Resistance      resistance;                 // ������������� �����
    CalibrationMode calibrationMode;            // ����� ����������
    // ��������� ��������� �������� � SettingsNonReset
} SettingsChannel;


// ��������� �������������
typedef struct
{
    StartMode           startMode;          // ����� �������.
    TrigSource          source;             // ��������.
    TrigPolarity        polarity;           // ��� �������������.
    TrigInput           input;              // ���� �������������.
    uint16              levelRel[3];        // ������� ������������� ��� ��� ����������.
    TrigModeFind        modeFind;           // ����� ������������� - ������� ��� �������������.
    uint16              timeDelay;
} SettingsTrig;


// ��������� ���������
typedef struct
{
    TBase           tBase;                  // ������� �� �������.
    int16           tShiftRel;              // �������� �� �������
    FunctionTime    timeDivXPos;
    TPos            tPos;
    SampleType      sampleType;
    SampleType      sampleTypeOld;
    PeackDetMode    peackDet;
} SettingsTime;


// ��������� ��������
typedef struct
{
    CursCntrl           cntrlU[NumChannels];                    // �������� ������� ����������.
    CursCntrl           cntrlT[NumChannels];                    // �������� ������� ����������.
    Channel             source;                                 // �������� - � ������ ������ ��������� �������.
    float               posCurU[NumChannels][2];                // ������� ������� �������� ���������� ����� �������.
    float               posCurT[NumChannels][2];                // ������� ������� �������� ������� ����� �������.
    float               deltaU100percents[2];                   // ���������� ����� ��������� ���������� ��� 100%, ��� ����� �������.
    float               deltaT100percents[2];                   // ���������� ����� ��������� ������� ��� 100%, ��� ����� �������.
    CursMovement        movement;                               // ��� ������������ �������� - �� ������ ��� �� ���������.
    CursActive          active;                                 // ����� ������� ������ �������.
    CursLookMode        lookMode[2];                            // ������ �������� �� ��������� ��� ���� ��� ��������.
    bool                showFreq;                               // ������������� � true ��������, ��� ����� ���������� �� ������ �������� 1/dT ����� ���������.
    bool                showCursors;                            // ���������� �� �������
} SettingsCursors;


typedef  struct
{
    bool isActiveModeSelect;
} StructMemoryLast;


// ��������� ����->������
typedef struct
{
#define MAX_SYMBOLS_IN_FILE_NAME 35
    NumPoinstFPGA   fpgaNumPoints;              // ����� �����.
    ModeWork        modeWork;                   // ����� ������.
    FileNamingMode  fileNamingMode;             // ����� ���������� ������.
    char            fileNameMask[MAX_SYMBOLS_IN_FILE_NAME]; // ����� ����� ��� ��������������� ���������� ������\n
         // ������� ����������.\n
         // %y('\x42') - ���, %m('\x43') - �����, %d('\x44') - ����, %H('\x45') - ����, %M('\x46') - ������, %S('\x47') - �������\n
         // %Nn('\x48''n') - ���������� �����, ������ �������� �� ����� n ���������, ��������, 7 � %3N ����� ������������� � 007\n
         // �������\n
         // name_%4N_%y_%m_%d_%H_%M_%S ����� ������������ ����� ���� name_0043_2014_04_25_14_45_32\n
         // ��� ���� �������� ��������, ��� ���� ������������ %4N ����� ����� ��������� ����������, ��, ������ �����, ���� �������� ����� ������ ����� 0001, �.�. ��� ����������� ������ ��������������� ������ ������� �� ����.
    char            fileName[MAX_SYMBOLS_IN_FILE_NAME];     // ��� ����� ��� ������ ������� �������
    int8                indexCurSymbolNameMask; // ������ �������� ������� � ������ ������� ����� ��� ������ �����.
    StructMemoryLast    strMemoryLast;
    ModeShowIntMem      modeShowIntMem;
    bool                flashAutoConnect;       // ���� true, ��� ���������� ���� ������������� ��������� NC (������ ���������)
    ModeBtnMemory       modeBtnMemory;     
    ModeSaveSignal      modeSaveSignal;         // � ����� ���� ��������� ������.
} SettingsMemory;


typedef struct
{
    MeasuresNumber  number;             // ������� ��������� ��������.
    Channel         source;             // ��� ����� ������� �������� ���������.
    ModeViewSignals modeViewSignals;    // ������� �� ������� ��� ������ ���������.
    Measure         measures[15];       // ��������� ��� ��������� ���������.
    bool            show;               // ���������� �� ���������.
    MeasuresZone    zone;               // ����� �������, �� ������� ������� �������� ��� ������� ���������.
    int16           posCurU[2];         // ������� ��������, ������� ������ �������, �� ������� ������� �������� ��� ������� ��������� ��� field == MeasuresField_Hand.
    int16           posCurT[2];         // ������� ��������, ������� ������ �������, �� ������� ������� �������� ��� ������� ��������� ��� field == MeasuresField_Hand.
    CursCntrl       cntrlU;             // �������� ������� ����������.
    CursCntrl       cntrlT;             // �������� ������� �������.
    CursActive      cursActive;         // ����� ������� ������� - �� ������� ��� ����������.
    Measure         markedMeasure;      // ���������, �� ������� ����� �������� �������.
} SettingsMeasures;


typedef struct
{
    ScaleFFT        scaleFFT;
    SourceFFT       sourceFFT;
    WindowFFT       windowFFT;
    FFTmaxDB        fftMaxDB;
    Function        mathFunc;
    uint8           currentCursor;          // ����������, ����� �������� ������� ��������� ����� ���������
    uint8           posCur[2];              // ������� ������� �������. ���������� 0...256.
    int8            koeff1add;              // ����������� ��� ������ ��������� ��� ��������.
    int8            koeff2add;
    int8            koeff1mul;
    int8            koeff2mul;
    bool            enableFFT;
    ModeDrawMath    modeDraw;               // ���������� ��� ����� ������� � ������ �������������� �������
    ModeRegSet      modeRegSet;             // ������� ����� ��������� - ������� �� ������� ��� �������� �� ���������
    Range           range;
    Divider         divider;
    uint16          rShift;
} SettingsMath;


// ��������� �����������
typedef struct
{
    bool            enable;
    TimeCounting    timeCounting;       // ����� ����� �������
    FreqClc         freqClc;            // ������� ���������
    NumberPeriods   numberPeriods;      // ���������� ��������
} SettingsFreqMeter;


// ��� ��������� �������� ����� ���� -> ������
typedef struct
{
    bool                screenWelcomeEnable;    // ����� �� ������������ ����� ����������� ��� ��������� �������.
    bool                soundEnable;            // �������� �� �����.
    int16               soundVolume;            // ��������� ����� [0...100]
    CalibratorMode      calibrator;             // ����� ������ �����������.
    int8                IPaddress;              // IP-����� (��������)
    ColorScheme         colorScheme;            //
    SettingsFreqMeter   freqMeter;              // ��������� �����������
    bool                recorder;               // ������� �� ����� ������������.
    FunctionPressRShift funcRShift;             // �������, ����������� �� ������� �� ����� RShift
    int16               speedRShift;            // ������������� �������� �������� �� �������� ����� RShift
} SettingsService;


typedef struct
{
    uint8 mac0;
    uint8 mac1;
    uint8 mac2;
    uint8 mac3;
    uint8 mac4;
    uint8 mac5;

    uint8 ip0;
    uint8 ip1;
    uint8 ip2;
    uint8 ip3;

    uint16 port;

    uint8 mask0;
    uint8 mask1;
    uint8 mask2;
    uint8 mask3;

    uint8 gw0;
    uint8 gw1;
    uint8 gw2;
    uint8 gw3;

    bool enable;
} SettingsEthernet; 


typedef struct
{
    int     countEnables;               // ���������� ���������. ������������� ��� ������ ���������
    int     countErasedFlashData;       // ������� ��� �������� ������ ������ � ���������
    int     countErasedFlashSettings;   // ������� ��� �������� ������ � ����������
    int     workingTimeInSecs;          // ����� ������ � ��������
    Language lang;                      // ���� ����
} SettingsCommon;


// ��������� ���������
typedef  struct
{
    // ��������� ��������� �������� � SettingsNonReset

    int16   numStrings;                 // ����� ����� � �������.
    int8    sizeFont;                   // ������ ������ ������� - 0 - 5, 1 - 8,
    bool    consoleInPause;             // ������� ����, ��� ������� ��������� � ������ �����. ����� ����� ��������, ��� ����� ��������� ��� �� ���������� � �� ���������.
    int16   numMeasuresForGates;        // ����� ��������� ��� �����.
    int16   timeCompensation;           // �������������� �������� �� ������� ��� ������ �������� ������ �������������.
    bool    viewAlteraWrittingData;     // ���������� �� ������, ������ � �������.
    bool    viewAllAlteraWrittingData;  // ���������� �� ��� ������, ������ � ������� (���� false, �� ��������� ������ ������� ����� START, STOP �� ������������).
    int16   altShift;                   // ���������� �������� ��� ���������� ������� �������������� ������ �������������.
    bool    showRandInfo;               // �������� ���������� �� ������������� - ������ � ���������� ��������
    bool    showRandStat;               // ������� ������ ����������
    bool    modeEMS;                    // ��� ��������� ����� ������ ������������� ���������� ������ 20���, ���������� �� 8-�� ������, ����������� �� 4-�
    bool    showStats;                  // ���������� ���������� �� ������ (fps, ��������).
    int16   pretriggered;               // ������������ �������� ����������� ��� ������������ �������������
    Bandwidth bandwidth[2];             // ����� ������� ������, ������� ����� ��������� ��� ������ � �����-������ �������� "������"
    struct Show
    {
        bool all;
        bool flag;
        bool rShift[NumChannels];
        bool trigLev;
        bool range[NumChannels];
        bool chanParam[NumChannels];
        bool trigParam;
        bool tShift;
        bool tBase;
    } show;
    DisplayOrientation orientation;
} SettingsDebug;


typedef struct
{
    int8            posActItem[Page_NumPages];      // ������� �������� ������. bit7 == 1 - item is opened, 0x7f - ��� ��������� ������
    int8            currentSubPage[Page_NumPages];  // ����� ������� �����������.
    bool            pageDebugActive;                    // ������� �� ������ ������� � ����.
    int8            isShown;                            // ���� ��������. ���� == false, � ��� ���� �����-���� ������� ���� ������, �� �� ����� ������� �� ������
} SettingsMenu;


typedef struct
{
    /*
    ******************************************************************************************************************************
    !!!!!!!!!!!!!!!!!!!!!!! �������� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    �� ������� ������� ���������� � �� �������� ������.
    ������ � ���� ������ ������������� ����������� �������� ��� ��������� ������� ��������� �������� � ���������� ��������� � ����
    ******************************************************************************************************************************
    */

    // channel
    int16           rShiftAdd[NumChannels][RangeSize][2];    // ���������� �������� ��� ��������� (0) � ��������� (1) ������.

    // service
    int16           correctionTime;             // ����������� ��������� �������

    // debug
    int16           balanceADC[NumChannels];    // �������� ��������������� �������� ��� ��� ������ ������������.
    int16           numAveForRand;              // �� �������� ���������� ��������� ������ � ������ �������������.
    BalanceADCtype  balanceADCtype;             // ��� ������������.
    StretchADCtype  stretchADCtype;             // ��� �������� ������.

    // channels
    int16           stretchADC[NumChannels][3]; // ����������� ����������� ��� �������, �������������� � ����������� �������
                                                // ����� �������� � ������ ����, ����� �������� ������� �����������, ����� ��������� �� 1000 � ��������� �������.

    int16           addStretch20mV[NumChannels];
    int16           addStretch50mV[NumChannels];
    int16           addStretch100mV[NumChannels];
    int16           addStretch2V[NumChannels];

    // debug
    int16           numSmoothForRand;           // ����� ����� ��� ����������� ������� � �������������
} SettingsNonReset; // ����� ����� ��������� �������������� ���������


void    SetMenuPosActItem(NamePage namePage, int8 pos);             // ���������� ������� ��������� ������ �� �������� namePage.
int8    MenuCurrentSubPage(NamePage namePage);                      // ���������� ����� ������� ����������� �������� namePage.
void    SetMenuCurrentSubPage(NamePage namePage, int8 posSubPage);  // ������������� ����� ������� ����������� � �������� namePage.
bool    MenuIsMinimize(void);                                       // ���� true - ���� ��������� � �������������� ������.
bool    MenuPageDebugIsActive(void);                                // ������� �� �������� �������.
void    SetMenuPageDebugActive(bool active);                        // �������/��������� �������� �������� �������.
void    CurrentPageSBregSet(int angle);                             // ��������� ����� ��������� �� ������� �������� ����� ������.
bool    PressSmallButton(PanelButton button);                       // ������ ����� ������, ��������������� ������ ������ ������.
const SmallButton*  GetSmallButton(PanelButton button);             // ������� ��������� �� ����� ������, ��������������� ������ ������ ������.

// ���������� ������� ��������� ������ �� �������� namePage.
#define MENU_POS_ACT_ITEM(namePage) (set.menu.posActItem[namePage])

// �������� ������ ��� ��������� �������.
typedef struct
{
    union
    {
        SettingsNonReset nr;                    // ����� �������� ���������, ������� �� ������������ ��� ������ - ����� ��������
        uint8 buf[SIZE_NONRESET_SETTINGS];
    };
    SettingsDisplay     display;                // ��������� �����������          (���� �������)
    SettingsChannel     chan[NumChannels];      // ��������� �������              (���� ����� 1 � ����� 2)
    SettingsTrig        trig;                   // ��������� �������������        (���� �����)
    SettingsTime        time;                   // ��������� ���������            (���� ���¨����)
    SettingsCursors     cursors;                // ��������� ��������� ���������  (���� �������)
    SettingsMemory      memory;                 // ��������� ������� ������       (���� ������)
    SettingsMeasures    measures;               // ��������� ���������            (���� ���������)
    SettingsMath        math;                   // ��������� ������ �������������� ���������
    SettingsService     service;                // �������������� ���������       (���� ������)
    SettingsEthernet    eth;
    SettingsCommon      common;                 // ��������� ���������
    SettingsMenu        menu;                   // ��������� ����
    SettingsDebug       debug;
    //int temp[4];
} Settings;


extern Settings set;


void Settings_Load(bool _default);          // ��������� ���������. ���� default == true, ����������� ��������� �� ���������, ����� �������� ��������� ��������� �� ���, � � ������ ������� - ���� ��������� �� ���������.
void Settings_Save(void);                   // ��������� ��������� �� ����-������.
bool Settings_DebugModeEnable(void);        // ���������� true, ���� ������� ����� �������.
void Settings_SaveState(Settings *set_);    // ��������� ������� ��������� � set_.
void Settings_RestoreState(Settings *set_); // ��������������� ����� ���������� ��������� � set_.

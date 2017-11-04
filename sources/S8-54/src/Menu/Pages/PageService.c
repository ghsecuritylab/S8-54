#include "Definition.h"
#include "main.h"
#include "Display/Display.h"
#include "Display/Symbols.h"
#include "FlashDrive/FlashDrive.h"
#include "FPGA/FPGA.h"
#include "Hardware/FLASH.h"
#include "Hardware/Hardware.h"
#include "Hardware/RTC.h"
#include "Hardware/Sound.h"
#include "Menu/MenuDrawing.h"
#include "Menu/MenuFunctions.h"
#include "Panel/Panel.h"
#include "Utils/Dictionary.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/Math.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void Func_Start(int key);          // 1 - �������, 1 - ����������

extern const         Page pService;
extern const       Button bResetSettings;                           ///< ������ - ����� ��������
        void       OnPress_ResetSettings(void);
static void           Draw_ResetSettings(void);
extern const       Button bAutoSearch;                              ///< ������ - ����� �������
static void        OnPress_AutoSearch(void);
extern const        Page ppCalibrator;                              ///< ������ - ����������
extern const       Choice cCalibrator_Calibrator;                   ///< ������ - ���������� - ����������
static void      OnChanged_Calibrator_Calibrator(bool active);
extern const       Button bCalibrator_Calibrate;                    ///< ������ - ���������� - �����������
static bool       IsActive_Calibrator_Calibrate(void);
static void        OnPress_Calibrator_Calibrate(void);
#ifdef OLD_RECORDER
extern const       Choice cRecorder;
static void      OnChanged_Recorder(bool active);
#else
static const       Page ppRecorder;                                 ///< ������ - �����������
static const     SButton bRecorder_Exit;                            ///< ������ - ����������� - �����
static const     SButton bRecorder_SaveTo;                          ///< ������ - ����������� - ��������� �...
static bool      IsActive_Recorder_SaveTo(void);
static void       OnPress_Recorder_SaveTo(void);
static void          Draw_Recorder_SaveTo(int, int);
static void          Draw_Recorder_SaveTo_RAM(int, int);
static void          Draw_Recorder_SaveTo_EXT(int, int);
static const     SButton bRecorder_Choice;                          ///< ������ - ����������� - �����
static void       OnPress_Recorder_Choice(void);
static void          Draw_Recorder_Choice(int x, int y);
static const     SButton bRecorder_Cursor;                          ///< ������ - ����������� - ������
static void       OnPress_Recorder_Cursor(void);
static void          Draw_Recorder_Cursor(int x, int y);
#endif
extern const        Page ppFFT;                                     ///< ������ - ������
static bool       IsActive_FFT(void);
static void        OnPress_FFT(void);
extern const       Choice cFFT_View;                                ///< ������ - ������ - �����������
extern const       Choice cFFT_Scale;                               ///< ������ - ������ - �����
extern const       Choice cFFT_Source;                              ///< ������ - ������ - ��������
extern const       Choice cFFT_Window;                              ///< ������ - ������ - ����
extern const       Page pppFFT_Cursors;                             ///< ������ - ������ - �������
static bool       IsActive_FFT_Cursors(void);
static void       OnRegSet_FFT_Cursors(int angle);
extern const      SButton bFFT_Cursors_Exit;                        ///< ������ - ������ - ������� - �����
extern const      SButton bFFT_Cursors_Source;                      ///< ������ - ������ - ������� - ��������
static void        OnPress_FFT_Cursors_Source(void);
static void           Draw_FFT_Cursors_Source(int x, int y);
extern const       Choice cFFT_Range;                               ///< ������ - ������ - ��������
static bool       IsActive_FFT_Range(void);
extern const        Page ppFunction;                                ///< ������ - �������
static bool       IsActive_Function(void);
static void        OnPress_Function(void);
static void       OnRegSet_Function(int delta);
extern const      SButton bFunction_Exit;                           ///< ������ - ������� - �����
extern const      SButton bFunction_Screen;                         ///< ������ - ������� - �����
static void        OnPress_Function_Screen(void);
static void           Draw_Function_Screen(int x, int y);
static void           Draw_Function_Screen_Disable(int x, int y);
static void           Draw_Function_Screen_Separate(int x, int y);
static void           Draw_Function_Screen_Together(int x, int y);
extern const      SButton bFunction_Type;                           ///< ������ - ������� - ���
static void        OnPress_Function_Type(void);
static void           Draw_Function_Type(int x, int y);
static void           Draw_Function_Type_Sum(int x, int y);
static void           Draw_Function_Type_Mul(int x, int y);
extern const      SButton bFunction_ModeRegSet;                     ///< ������ - ������� - ����� ����� ���������
static void        OnPress_Function_ModeRegSet(void);
static void           Draw_Function_ModeRegSet(int x, int y);
static void           Draw_Function_ModeRegSet_Range(int x, int y);
static void           Draw_Function_ModeRegSet_RShift(int x, int y);
extern const      SButton bFunction_RangeA;                         ///< ������ - ������� - ������� 1-�� ������
static void        OnPress_Function_RangeA(void);
static void           Draw_Function_RangeA(int x, int y);
extern const      SButton bFunction_RangeB;                         ///< ������ - ������� - ������� 2-�� ������
static void        OnPress_Function_RangeB(void);
static void           Draw_Function_RangeB(int x, int y);
extern const        Page ppEthernet;                                ///< ������ - ETHERNET
extern const      Choice cEthernet_Ethernet;                        ///< ������ - ETHERNET - Ethernet
static void     OnChanged_Ethernet_Settings(bool active);
extern const  IPaddress ipEthernet_IP;                              ///< ������ - ETHERNET - IP �����
extern const  IPaddress ipEthernet_NetMask;                         ///< ������ - ETHERNET - ����� �������
extern const  IPaddress ipEthernet_Gateway;                         ///< ������ - ETHERNET - ����
extern const MACaddress ipEthernet_MAC;                             ///< ������ - ETHERNET - MAC �����
extern const       Page ppSound;                                    ///< ������ - ����
extern const      Choice cSound_Enable;                             ///< ������ - ���� - ����
extern const    Governor gSound_Volume;                             ///< ������ - ���� - ���������
extern const       Page ppRTC;                                     ///< ������ - �����
extern const        Time tRTC_Time;                                ///< ������ - ����� - �����
extern const    Governor tRTC_Correction;                          ///< ������ - ����� - ���������
static void     OnChanged_Time_Correction(void);
extern const      Choice cLanguage;                                 ///< ������ - ����
extern const       Page ppInformation;                              ///< ������ - ����������
static void       OnPress_Information(void);
static void   Information_Draw(void);
extern const     SButton bInformation_Exit;                         ///< ������ - ���������� - �����
static void       OnPress_Information_Exit(void);

extern Page mainPage;

// ������ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pService =
{
    Item_Page, &mainPage, 0,
    {
        "������", "SERVICE",
        "�������������� ���������, ����������, ����� �������, �������������� �������",
        "Additional settings, calibration, signal search, mathematical functions"
    },
    Page_Service,
    {
        (void *)&bResetSettings,    // ������ - ����� ��������
        (void *)&bAutoSearch,       // ������ - ����� �������
        (void *)&ppCalibrator,      // ������ - ����������
#ifdef OLD_RECORDER
        (void *)&cRecorder,         // ������ - �����������
#else
        (void *)&ppRecorder,        // ������ - �����������
#endif
        (void *)&ppFFT,             // ������ - ������
        (void *)&ppFunction,        // ������ - �������
        (void *)&ppEthernet,        // ������ - ETHERNET
        (void *)&ppSound,           // ������ - ����
        (void *)&ppRTC,             // ������ - �����
        (void *)&cLanguage,         // ������ - ����
        (void *)&ppInformation      // ������ - ����������
    }
};

static const char * const titlesResetSettings[] =
{
    "����� ��������", "Reset settings",
    "����� �������� �� ��������� �� ���������",
    "Reset to default settings"    
};

// ������ - ����� �������� ---------------------------------------------------------------------------------------------------------------------------
static const Button bResetSettings
(
    titlesResetSettings, &pService, OnPress_ResetSettings
);

void OnPress_ResetSettings(void)
{
    panel.Disable();
    display.SetDrawMode(DrawMode_Hand, Draw_ResetSettings);

    if (panel.WaitPressingButton() == B_Start)
    {
        Settings_Load(true);
    }

    display.SetDrawMode(DrawMode_Auto, 0);
    panel.Enable();
    //Func_Start(1);
}

static void Draw_ResetSettings(void)
{
    painter.BeginScene(gColorBack);

    painter.DrawTextInRectWithTransfersC(30, 110, 300, 200, "����������� ����� �������� �������� ������ ����/����.\n"
                                                         "������� ����� ������ ������, ���� ����� �� �����.", gColorFill);

    painter.EndScene();
}

static const char * const titlesAutoSearch[] =
{
    "����� �������", "Find signal",
    "������������� ����������� ��������� ������������ ��� ������� � ������ 1",
    "Sets optimal settings for the oscilloscope signal on channel 1"
};

// ������ - ����� ������� ----------------------------------------------------------------------------------------------------------------------------
static const Button bAutoSearch
(
    titlesAutoSearch, &pService, OnPress_AutoSearch
);

static void OnPress_AutoSearch(void)
{
    FPGA_NEED_AUTO_FIND = 1;
};


// ������ - ���������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppCalibrator =
{
    Item_Page, &pService, 0,
    {
        "����������", "CALIBRATOR",
        "����������� ������������ � ���������� ������������",
        "Control of the calibrator and calibration of an oscillograph"
    },
    Page_Service_Calibrator,
    {
        (void *)&cCalibrator_Calibrator,    // ������ - ���������� - ����������
        (void *)&bCalibrator_Calibrate      // ������ - ���������� - �����������
    }
};


// ������ - ���������� - ���������� ------------------------------------------------------------------------------------------------------------------
static const Choice cCalibrator_Calibrator =
{
    Item_Choice, &ppCalibrator, 0,
    {
        "����������",   "Calibrator",
        "����� ������ �����������",
        "Mode of operation of the calibrator"
    },
    {
        {"�����",       "DC"},
        {"+4V",         "+4V"},
        {"0V",          "0V"}
    },
    (int8 *)&CALIBRATOR_MODE, OnChanged_Calibrator_Calibrator
};

static void OnChanged_Calibrator_Calibrator(bool active)
{
    FPGA_SetCalibratorMode(CALIBRATOR_MODE);
}

static const char * const titlesCalibrator_Calibrate[] =
{
    "�����������", "Calibrate",
    "������ ��������� ����������",
    "Running the calibration procedure"
};

// ������ - ���������� - ����������� -----------------------------------------------------------------------------------------------------------------
static const Button bCalibrator_Calibrate
(
    titlesCalibrator_Calibrate, &ppCalibrator, OnPress_Calibrator_Calibrate, IsActive_Calibrator_Calibrate
);

static bool IsActive_Calibrator_Calibrate(void)
{
    return !(SET_CALIBR_MODE_A == CalibrationMode_Disable && CALIBR_MODE_B == CalibrationMode_Disable);
}

static void OnPress_Calibrator_Calibrate(void)
{
    gStateFPGA.needCalibration = true;
}

#ifdef OLD_RECORDER

// ������ - ����������� ------------------------------------------------------------------------------------------------------------------------------
static const Choice cRecorder =
{
    Item_Choice, &pService, 0,
    {
        "�����������", "Recorder",
        "��������/��������� ����� ������������. ���� ����� �������� �� ��������� 50 ��/��� � ����� ���������.",
        "Turn on/off recorder mode. This mode is available for scanning 20ms/div and slower."
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&RECORDER_MODE, OnChanged_Recorder
};

static void OnChanged_Recorder(bool active)
{
    FPGA_EnableRecorderMode(RECORDER_MODE);
}

#else

// C����� - ����������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppRecorder =
{
    Item_Page, &pService, 0,
    {
        "�����������", "RECORDER",
        "������ � ��������������� ������� ��������",
        "Recording and playback of input signals"
    },
    PageSB_Service_Recorder,
    {
        (void *)&bRecorder_Exit,
        (void *)&bRecorder_SaveTo,
        (void *)&bRecorder_Choice,
        (void *)&bRecorder_Cursor
    },
    true
};

// ������ - ����������� - ����� ----------------------------------------------------------------------------------------------------------------------
static const SButton bRecorder_Exit =
{
    Item_SmallButton, &ppRecorder, 0,
    {
        "�����", "Exit",
        "����� �� ������ ������������",
        "Exit registrator mode"
    },
    OnPressSB_Exit,
    DrawSB_Exit
};

// ������ - ����������� - ��������� � ... ------------------------------------------------------------------------------------------------------------
static const SButton bRecorder_SaveTo =
{
    Item_SmallButton, &ppRecorder, IsActive_Recorder_SaveTo,
    {
        "��������� � ...", "Save in ...",
        "����� ����� �������� ������",
        "Selecting a storage location"
    },
    OnPress_Recorder_SaveTo,
    Draw_Recorder_SaveTo,
    {
        {Draw_Recorder_SaveTo_RAM, "������ ����������� �� ���������� ������", "data is stored in the internal memory"},
        {Draw_Recorder_SaveTo_EXT, "������ ����������� �� ������� ��", "data is stored in the data storage"}
    }
};

static bool IsActive_Recorder_SaveTo(void)
{
    return FDRIVE_IS_CONNECTED;
}

static void OnPress_Recorder_SaveTo(void)
{
    CircleIncreaseInt8((int8*)(&REC_PLACE_OF_SAVING), 0, PlaceOfSaving_Number - 1);
}

static void Draw_Recorder_SaveTo(int x, int y)
{
    static const pFuncVII funcs[PlaceOfSaving_Number] =
    {
        Draw_Recorder_SaveTo_RAM, Draw_Recorder_SaveTo_EXT
    };

    funcs[REC_PLACE_OF_SAVING](x, y);
}

static void Draw_Recorder_SaveTo_RAM(int x, int y)
{
    painter.SetFont(TypeFont_UGO2);
    painter.Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_ROM);
    painter.SetFont(TypeFont_8);
}

static void Draw_Recorder_SaveTo_EXT(int x, int y)
{
    painter.SetFont(TypeFont_UGO2);
    painter.Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_FLASH_DRIVE_BIG);
    painter.SetFont(TypeFont_8);
}

// ������ - ����������� - ����� ----------------------------------------------------------------------------------------------------------------------
static const SButton bRecorder_Choice =
{
    Item_SmallButton, &ppRecorder, 0,
    {
        "�����", "Choice",
        "����� ������� ��� ���������",
        "Select signal to view"
    },
    OnPress_Recorder_Choice,
    Draw_Recorder_Choice
};

static void OnPress_Recorder_Choice(void)
{

}

static void Draw_Recorder_Choice(int x, int y)
{
    painter.SetFont(TypeFont_UGO2);
    painter.Draw4SymbolsInRect(x + 1, y, SYMBOL_FOLDER);
    painter.SetFont(TypeFont_8);
}

// ������ - ����������� - ������ ---------------------------------------------------------------------------------------------------------------------
static const SButton bRecorder_Cursor =
{
    Item_SmallButton, &ppRecorder, 0,
    {
        "������", "Cursors",
        "����� �������",
        "Cursor selection"
    },
    OnPress_Recorder_Cursor,
    Draw_Recorder_Cursor
};

static void OnPress_Recorder_Cursor(void)
{
    CircleIncreaseInt8(&REC_NUM_CURSOR, 0, 1);
}

static void Draw_Recorder_Cursor(int x, int y)
{
    painter.DrawText(x + 8, y + 5, REC_NUM_CURSOR ? "2" : "1");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------



#endif


// ������ - ������ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppFFT =
{
    Item_Page, &pService, IsActive_FFT,
    {
        "������", "SPECTRUM",
        "����������� ������� �������� �������",
        "Mapping the input signal spectrum"
    },
    Page_Service_FFT,
    {
        (void *)&cFFT_View,         // ������ - ������ - �����������
        (void *)&cFFT_Scale,        // ������ - ������ - �����
        (void *)&cFFT_Source,       // ������ - ������ - ��������
        (void *)&cFFT_Window,       // ������ - ������ - ���� 
        (void *)&pppFFT_Cursors,    // ������ - ������ - �������
        (void *)&cFFT_Range         // ������ - ������ - ��������
    },
    false, OnPress_FFT
};

static bool IsActive_FFT(void)
{
    return !FUNC_ENABLED;
}

static void OnPress_FFT(void)
{
    if (!IsActive_FFT())
    {
        display.ShowWarning(ImpossibleEnableFFT);
    }
}

// ������ - ������ - ����������� ---------------------------------------------------------------------------------------------------------------------
static const Choice cFFT_View =
{
    Item_Choice, &ppFFT, 0,
    {
        "�����������", "Display",
        "�������� � ��������� ����������� �������",
        "Enables or disables the display of the spectrum"
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8 *)&FFT_ENABLED
};


// ������ - ������ - ����� ---------------------------------------------------------------------------------------------------------------------------
static const Choice cFFT_Scale =
{
    Item_Choice, &ppFFT, 0,
    {
        "�����",        "Scale",
        "����� ������� ������ ������� - �������� ��� ���������������",
        "Sets the scale of the output spectrum - linear or logarithmic"
    },
    {
        {"��������",    "Log"},
        {"��������",    "Linear"}
    },
    (int8 *)&SCALE_FFT
};

// ������ - ������ - �������� ------------------------------------------------------------------------------------------------------------------------
static const Choice cFFT_Source =
{
    Item_Choice, &ppFFT, 0,
    {
        "��������",     "Source",
        "����� ��������� ��� ������� �������",
        "Selecting the source for the calculation of the spectrum"
    },
    {
        {"����� 1",     "Channel 1"},
        {"����� 2",     "Channel 2"},
        {"����� 1 + 2", "Channel 1 + 2"}
    },
    (int8 *)&SOURCE_FFT
};

// ������ - ������ - ���� ----------------------------------------------------------------------------------------------------------------------------
static const Choice cFFT_Window =
{
    Item_Choice, &ppFFT, 0,
    {
        "����",         "Window",
        "����� ���� ��� ������� �������",
        "Sets the window to calculate the spectrum"
    },
    {
        {"�����������", "Rectangle"},
        {"��������",    "Hamming"},
        {"��������",    "Blackman"},
        {"�����",       "Hann"}
    },
    (int8 *)&WINDOW_FFT
};

// ������ - ������ - ������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page pppFFT_Cursors =
{
    Item_Page, &ppFFT, IsActive_FFT_Cursors,
    {
        "�������", "CURSORS",
        "�������� ������� ��� ��������� ���������� �������",
        "Includes cursors to measure the parameters of the spectrum"
    },
    PageSB_Service_FFT_Cursors,
    {
        (void *)&bFFT_Cursors_Exit,     // ������ - ������ - ������� - �����
        (void *)&bFFT_Cursors_Source,   // ������ - ������ - ������� - ��������
        (void *)0,
        (void *)0,
        (void *)0,
        (void *)0
    },
    true, 0, 0, OnRegSet_FFT_Cursors
};

static bool IsActive_FFT_Cursors(void)
{
    return FFT_ENABLED;
}

static void OnRegSet_FFT_Cursors(int angle)
{
    POS_MATH_CUR(MATH_CURRENT_CUR) += (uint8)angle;
    Sound_RegulatorShiftRotate();
}


// ������ - ������ - ������� - ����� -----------------------------------------------------------------------------------------------------------------
static const SButton bFFT_Cursors_Exit
(
    COMMON_BEGIN_SB_EXIT,
    &pppFFT_Cursors, OnPressSB_Exit, DrawSB_Exit
);

// ������ - ������ - ������� - �������� --------------------------------------------------------------------------------------------------------------
static const SButton bFFT_Cursors_Source
(
     "��������", "Source",
     "����� ��������� ��� ������� �������",
     "Source choice for calculation of a range",
    &pppFFT_Cursors, OnPress_FFT_Cursors_Source, Draw_FFT_Cursors_Source
);

static void OnPress_FFT_Cursors_Source(void)
{
    MATH_CURRENT_CUR = (MATH_CURRENT_CUR + 1) % 2;
}

static void Draw_FFT_Cursors_Source(int x, int y)
{
    painter.DrawText(x + 7, y + 5, MATH_CURRENT_CUR_IS_0 ? "1" : "2");
}

// ������ - ������ - �������� ------------------------------------------------------------------------------------------------------------------------
static const Choice cFFT_Range =
{
    Item_Choice, &ppFFT, IsActive_FFT_Range,
    {
        "��������", "Range",
        "����� ����� ������ ������ ���������� �� ��������� �������",
        "Here you can set the limit of monitoring the power spectrum"
    },

    {
        {"-40��",   "-40dB"},
        {"-60��",   "-60dB"},
        {"-80��",   "-80dB"}
    },
    (int8 *)&MAX_DB_FFT
};

static bool IsActive_FFT_Range(void)
{
    return SCALE_FFT_LOG;
}

// ������ - ������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppFunction =
{
    Item_Page, &pService, IsActive_Function,
    {
        "�������", "FUNCTION",
        "��������� � ����� �������������� ������� - �������� ��� ���������",
        "Installation and selection of mathematical functions - addition or multiplication"
    },
    PageSB_Service_Function,
    {
        (void *)&bFunction_Exit,        // ������ - ������� - �����
        (void *)&bFunction_Screen,      // ������ - ������� - �����
        (void *)&bFunction_Type,        // ������ - ������� - ���
        (void *)&bFunction_ModeRegSet,  // ������ - ������� - ����� ����� ���������
        (void *)&bFunction_RangeA,      // ������ - ������� - ������� 1-�� ������
        (void *)&bFunction_RangeB
    },
    true, OnPress_Function, 0, OnRegSet_Function
};

static bool IsActive_Function(void)
{
    return !FFT_ENABLED;
}

static void OnPress_Function(void)
{
    if (FFT_ENABLED)
    {
        display.ShowWarning(ImpossibleEnableMathFunction);
    }
}

static void OnRegSet_Function(int delta)
{
    if (!FUNC_ENABLED)
    {
        return;
    }

    if (MATH_MODE_REG_SET_IS_RSHIFT)
    {
        uint16 prevRShift = SET_RSHIFT_MATH;
        uint16 rShift = prevRShift;
        if (delta > 0)
        {
            if (rShift < RShiftMax)
            {
                rShift += 4 * STEP_RSHIFT;
                LIMIT_ABOVE(rShift, RShiftMax);
                if (prevRShift < RShiftZero && rShift > RShiftZero)
                {
                    rShift = RShiftZero;
                }
                Sound_RegulatorShiftRotate();
                SET_RSHIFT_MATH = rShift;
            }
        }
        else if (delta < 0)
        {
            if (rShift > RShiftMin)
            {
                rShift -= 4 * STEP_RSHIFT;
                LIMIT_BELOW(rShift, RShiftMin);
                if (prevRShift > RShiftZero && rShift < RShiftZero)
                {
                    rShift = RShiftZero;
                }
                Sound_RegulatorShiftRotate();
                SET_RSHIFT_MATH = rShift;
            }
        }
    }
    if (MATH_MODE_REG_SET_IS_RANGE)
    {
        static int sum = 0;
        sum -= delta;

        float rShiftAbs = RSHIFT_2_ABS(SET_RSHIFT_MATH, SET_RANGE_MATH);

        if (sum > 2)
        {
            if (SET_RANGE_MATH < RangeSize - 1)
            {
                SET_RANGE_MATH = (Range)((int)SET_RANGE_MATH + 1);  // SET_RANGE_MATH++;
                SET_RSHIFT_MATH = (int16)math.RShift2Rel(rShiftAbs, SET_RANGE_MATH);
                Sound_RegulatorSwitchRotate();
            }
            sum = 0;
        }
        else if (sum < -2)
        {
            if (SET_RANGE_MATH > 0)
            {
                SET_RANGE_MATH = (Range)((int)SET_RANGE_MATH - 1);  // SET_RANGE_MATH--;
                SET_RSHIFT_MATH = (int16)math.RShift2Rel(rShiftAbs, SET_RANGE_MATH);
                Sound_RegulatorSwitchRotate();
            }
            sum = 0;
        }
    }
}

// ������ - ������� - ����� --------------------------------------------------------------------------------------------------------------------------
static const SButton bFunction_Exit
(
    "�����", "Exit",
    "������ ��� ������ � ���������� ����",
    "Button to return to the previous menu",
    &ppFunction, 0, DrawSB_Exit
);

static const StructHelpSmallButton hintsScreen[] =
{
    {Draw_Function_Screen_Disable,  "����� �������������� ������� ��������",     
                                    "The conclusion of mathematical function is disconnected"},
    {Draw_Function_Screen_Separate, "������� � �������������� ������� ��������� � ������ �����",
                                    "Signals and mathematical function are removed in different windows"},
    {Draw_Function_Screen_Together, "������� � �������������� ������� ��������� � ����� ����",
                                    "Signals and mathematical function are removed in one window"}
};

// ������ - ������� - ����� --------------------------------------------------------------------------------------------------------------------------
static const SButton bFunction_Screen
(
    "�����", "Display",
    "�������� ����� ����������� ��������������� �������",
    "Chooses the mode of display of a mathematical signal",
    &ppFunction, OnPress_Function_Screen, Draw_Function_Screen, 0,
    hintsScreen, 3
);

static void OnPress_Function_Screen(void)
{
    if (FFT_ENABLED)
    {
        display.ShowWarning(ImpossibleEnableMathFunction);
    }
    else
    {
        CircleIncreaseInt8((int8 *)&FUNC_MODE_DRAW, 0, 2);
    }
}

static void Draw_Function_Screen(int x, int y)
{
    const pFuncVII funcs[3] =
    {
        Draw_Function_Screen_Disable,
        Draw_Function_Screen_Separate,
        Draw_Function_Screen_Together
    };
    funcs[FUNC_MODE_DRAW](x, y);
}

static void Draw_Function_Screen_Disable(int x, int y)
{
    painter.DrawText(x + 2 + (LANG_EN ? 2 : 0), y + 5, DICT(DDis));
}

static void Draw_Function_Screen_Separate(int x, int y)
{
    painter.DrawRectangle(x + 3, y + 5, 13, 9);
    painter.DrawHLine(y + 9, x + 3, x + 16);
    painter.DrawHLine(y + 10, x + 3, x + 16);
}

static void Draw_Function_Screen_Together(int x, int y)
{
    painter.DrawRectangle(x + 3, y + 5, 13, 9);
}

static const StructHelpSmallButton hintsType[] =
{
    { Draw_Function_Type_Sum,      "��������",     "Addition"       },
    { Draw_Function_Type_Mul,      "���������",    "Multiplication" }    
};

// ������ - ������� - ��� ----------------------------------------------------------------------------------------------------------------------------
static const SButton bFunction_Type
(
    "���", "Type",
    "����� �������������� �������",
    "Choice of mathematical function",
    &ppFunction, OnPress_Function_Type, Draw_Function_Type, 0,
    hintsType, 2
);

static void OnPress_Function_Type(void)
{
    CircleIncreaseInt8((int8 *)&MATH_FUNC, 0, 1);
}

static void Draw_Function_Type(int x, int y)
{
    const pFuncVII funcs[2] = {Draw_Function_Type_Sum, Draw_Function_Type_Mul};
    funcs[MATH_FUNC](x, y);
}

static void Draw_Function_Type_Sum(int x, int y)
{
    painter.DrawHLine(y + 9, x + 4, x + 14);
    painter.DrawVLine(x + 9, y + 4, y + 14);
}

static void Draw_Function_Type_Mul(int x, int y)
{
    painter.SetFont(TypeFont_UGO2);
    painter.Draw4SymbolsInRect(x + 4, y + 3, SYMBOL_MATH_FUNC_MUL);
    painter.SetFont(TypeFont_8);
}

static const StructHelpSmallButton hintsModeRegSet[] =
{
    {Draw_Function_ModeRegSet_Range,  "���������� ���������", "Management of scale"},
    {Draw_Function_ModeRegSet_RShift, "���������� ���������", "Management of shift"}    
};

// ������ - ������� - ����� ����� ��������� ----------------------------------------------------------------------------------------------------------
static const SButton bFunction_ModeRegSet
(
    "����� ����� ���������", "Mode regulator SET",
    "����� ������ ����� ��������� - ���������� ��������� ��� ���������",
    "Choice mode regulcator ��������� - management of scale or shift",
    &ppFunction, OnPress_Function_ModeRegSet, Draw_Function_ModeRegSet, 0, hintsModeRegSet, 2
);

static void OnPress_Function_ModeRegSet(void)
{
    CircleIncreaseInt8((int8 *)&MATH_MODE_REG_SET, 0, 1);
}

static void Draw_Function_ModeRegSet(int x, int y)
{
    static const pFuncVII funcs[2] = {Draw_Function_ModeRegSet_Range, Draw_Function_ModeRegSet_RShift};
    funcs[MATH_MODE_REG_SET](x, y);
}

static void Draw_Function_ModeRegSet_Range(int x, int y)
{
    painter.DrawChar(x + 7, y + 5, LANG_RU ? 'M' : 'S');
}

static void Draw_Function_ModeRegSet_RShift(int x, int y)
{
    painter.DrawText(x + 5 - (LANG_EN ? 3 : 0), y + 5, DICT(DShift));
}

// ������ - ������� - ������� 1-�� ������ ------------------------------------------------------------------------------------------------------------
static const SButton bFunction_RangeA
(
    "������� 1-�� ������", "Scale of the 1st channel",
    "���������� ������� ������� ������ ��� ����������� ����������",
    "Takes scale for a mathematical signal from the first channel",
    &ppFunction, OnPress_Function_RangeA, Draw_Function_RangeA
);

static void OnPress_Function_RangeA(void)
{
    SET_RANGE_MATH = SET_RANGE_A;
    MATH_DIVIDER = SET_DIVIDER_A;
}

static void Draw_Function_RangeA(int x, int y)
{
    painter.DrawChar(x + 8, y + 5, '1');
}

// ������ - ������� - ������� 2-�� ������ ------------------------------------------------------------------------------------------------------------
static const SButton bFunction_RangeB
(
    "������� 2-�� ������", "Scale of the 2nd channel",
    "���������� ������� ������� ������ ��� ����������� ����������",
    "Takes scale for a mathematical signal from the second channel",
    &ppFunction, OnPress_Function_RangeB, Draw_Function_RangeB
);

static void OnPress_Function_RangeB(void)
{
    SET_RANGE_MATH = SET_RANGE_B;
    MATH_DIVIDER = SET_DIVIDER_B;
}

static void Draw_Function_RangeB(int x, int y)
{
    painter.DrawChar(x + 8, y + 5, '2');
}

// ������ - ETHERNET /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppEthernet =
{
    Item_Page, &pService, 0,
    {
        "ETHERNET", "ETHERNET",
        "��������� ethernet",
        "Settings of ethernet"
    },
    Page_Service_Ethernet,
    {
        (void *)&cEthernet_Ethernet,    // ������ - ETHERNET - Ethernet
        (void *)&ipEthernet_IP,         // ������ - ETHERNET - IP �����
        (void *)&ipEthernet_NetMask,    // ������ - ETHERNET - ����� �������
        (void *)&ipEthernet_Gateway,    // ������ - ETHERNET - ����
        (void *)&ipEthernet_MAC         // ������ - ETHERNET - MAC �����
    }
};

// ������ - ETHERNET - Ethernet ----------------------------------------------------------------------------------------------------------------------
static const Choice cEthernet_Ethernet =
{
    Item_Choice, &ppEthernet, 0,
    {
        "Ethernet",    "Ethernet"
        ,
    "����� ������������� ethernet, �������� \"��������\" � ��������� ������.\n"
    "����� ��������� ethernet, �������� \"���������\" � ��������� ������."
    ,
    "To involve ethernet, choose \"Included\" and switch off the device.\n"
    "To disconnect ethernet, choose \"Disconnected\" and switch off the device."
    },
    {
        {"��������",    "Included"},
        {"���������",   "Disconnected"}
    },
    (int8 *)&ETH_ENABLED, OnChanged_Ethernet_Settings
};

static void OnChanged_Ethernet_Settings(bool active)
{
    display.ShowWarning(NeedRebootDevice);
}

// ������ - ETHERNET - IP ����� ----------------------------------------------------------------------------------------------------------------------
static const IPaddress ipEthernet_IP =
{
    Item_IP, &ppEthernet, 0,
    {
        "IP �����", "IP-address",
        "��������� IP ������",
        "Set of IP-address"
    },
    &IP_ADDR0, &IP_ADDR1, &IP_ADDR2, &IP_ADDR3,
    OnChanged_Ethernet_Settings,
    &ETH_PORT
};

// ������ - ETHERNET - ����� ������� -----------------------------------------------------------------------------------------------------------------
static const IPaddress ipEthernet_NetMask =
{
    Item_IP, &ppEthernet, 0,
    {
        "����� �������", "Network mask",
        "��������� ����� �������",
        "Set of network mask"
    },
    &NETMASK_ADDR0, &NETMASK_ADDR1, &NETMASK_ADDR2, &NETMASK_ADDR3,
    OnChanged_Ethernet_Settings
};

// ������ - ETHERNET - ���� --------------------------------------------------------------------------------------------------------------------------
static const IPaddress ipEthernet_Gateway =
{
    Item_IP, &ppEthernet, 0,
    {
        "����", "Gateway",
        "��������� ������ ��������� �����",
        "Set of gateway address"
    },
    &GW_ADDR0, &GW_ADDR1, &GW_ADDR2, &GW_ADDR3,
    OnChanged_Ethernet_Settings
};

// ������ - ETHERNET - MAC ����� ---------------------------------------------------------------------------------------------------------------------
static const MACaddress ipEthernet_MAC =
{
    Item_MAC, &ppEthernet, 0,
    {
        "MAC �����", "MAC-address",
        "��������� ����������� ������",
        "Set of MAC-address"
    },
    &set.eth_mac0, &set.eth_mac1, &set.eth_mac2, &set.eth_mac3, &set.eth_mac4, &set.eth_mac5,
    OnChanged_Ethernet_Settings
};

// ������ - ���� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppSound =
{
    Item_Page, &pService, 0,
    {
        "����", "SOUND",
        "� ���� ���� ����� ��������� ��������� �����",
        "In this menu, you can adjust the volume"
    },
    Page_Service_Sound,
    {
        (void *)&cSound_Enable, // ������ - ���� - ����
        (void *)&gSound_Volume  // ������ - ���� - ���������
    }

};

// ������ - ���� - ���� ------------------------------------------------------------------------------------------------------------------------------
static const Choice cSound_Enable =
{
    Item_Choice, &ppSound, 0,
    {
        "����", "Sound",
        "���������/���������� �����",
        "Inclusion/switching off of a sound"
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&SOUND_ENABLED
};

// ������ - ���� - ��������� -------------------------------------------------------------------------------------------------------------------------
static const Governor gSound_Volume =
{
    Item_Governor, &ppSound, 0,
    {
        "���������", "Volume",
        "��������� ��������� �����",
        "Set the volume"
    },
    &SOUND_VOLUME, 0, 100
};


// ������ - ����� ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppRTC =
{
    Item_Page, &pService, 0,
    {
        "�����", "TIME",
        "��������� � ��������� �������",
        "Set and setup time"
    },
    Page_Service_RTC,
    {
        (void *)&tRTC_Time,         // ������ - ����� - �����
        (void *)&tRTC_Correction    // C����� - ����� - ���������
    }
};

// ������ - ����� - ����� ----------------------------------------------------------------------------------------------------------------------------
static int8 dServicetime = 0;
static int8 hours = 0, minutes = 0, secondes = 0, year = 0, month = 0, day = 0;
static const Time tRTC_Time
(
    "�����", "Time",
    "��������� �������� �������.\n������� ������:\n"
    "������ �� ������� ���� \"�����\". ��������� ���� ��������� �������� �������. ��������� ��������� ������ �� �������� ����������, �������������� "
    "�������� ���������� \"�����\", �������� ����, ������, �������, ���, �����, ��� �����. ���������� ������� ������������ �������� ��������. "
    "��������� ����� ��������� ���������� ����������� ��������. ����� �������� ����� \"���������\", ������ � ���������� ����� 0.5 ��� ������ �� ������ "
    "����������. ���� ��������� �������� ������� ��������� � ����������� ������ �������� �������. ������� ���������� ��������� ������ �� ����� ������ �������� "
    "������� � �������� ���� ��������� �������� ���    ���� ��� ���������� ������ �������� �������"
    ,
    "Setting the current time. \nPoryadok work:\n"
    "Click on the menu item \"Time\".The menu set the current time.By briefly pressing the button on the numeric keypad of conformity "
    "Control \"Time\", highlight the hours, minutes, seconds, year, month, or a number.The selected item is indicated by a flashing area. "
    "Turn the setting knob to set the desired value. Then highlight \"Save\", press and udrezhivat more than 0.5 seconds, the button on the panel "
    "Control. Menu Setting the current time will be closed to the conservation of the new current time. Pressing a button on the prolonged retention of any other element "
    "will lead to the closure of the current time setting menu without saving the new current time",
    &ppRTC, 0, &dServicetime, &hours, &minutes, &secondes, &month, &day, &year
);

// ������ - ����� - ��������� ------------------------------------------------------------------------------------------------------------------------
static const Governor tRTC_Correction =
{
    Item_Governor, &ppRTC, 0,
    {
        "���������", "Correction",
        "��������� ��������������� ������������ ��� ����������� ���� �������",
        "Setting correction factor to compensate for time travel"
    },
    &NRST_CORRECTION_TIME, -63, 63, OnChanged_Time_Correction
};

static void OnChanged_Time_Correction(void)
{
    RTC_SetCorrection((int8)NRST_CORRECTION_TIME);
}

// ������ - ���� -------------------------------------------------------------------------------------------------------------------------------------
static const Choice cLanguage =
{
    Item_Choice, &pService, 0,
    {
        "����",         "Language",
        "��������� ������� ���� ����",
        "Allows you to select the menu language"
    },
    {
        {"�������",     "Russian"},
        {"����������",  "English"}
    },
    (int8 *)&LANG
};


// ������ - ���������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppInformation =
{
    Item_Page, &pService, 0,
    {
        "����������", "INFORMATION",
        "���������� ���������� � �������",
        "Displays information about the device"
    },
    PageSB_Service_Information,
    {
        (void *)&bInformation_Exit, // ������ - ���������� - �����
        (void *)0,
        (void *)0,
        (void *)0,
        (void *)0,
        (void *)0
    },
    true, OnPress_Information
};

static void OnPress_Information(void)
{
    display.SetDrawMode(DrawMode_Auto, Information_Draw);
}

static void Information_Draw(void)
{
    painter.BeginScene(gColorBack);
    int x = 100;
    int dY = 20;
    int y = 20;
    painter.DrawRectangle(0, 0, 319, 239, gColorFill);
    y += dY;
    painter.DrawText(x, y, DICT(DInformation));
    y += dY;
    
    char buffer[100];

    sprintf(buffer, "%s : %s", DICT(DModel), LANG_RU ? MODEL_RU : MODEL_EN);
    painter.DrawText(x, y, buffer);

    y += 2 * dY;

    painter.DrawText(x, y, DICT(DSoftware));
    y += dY;
    sprintf(buffer, (const char *)DICT(DVersion), NUM_VER);
    painter.DrawText(x, y, buffer);
    y += dY;

    painter.DrawFormText(x, y, gColorFill, "CRC32 : %X", Hardware_CalculateCRC32());

    dY = -10;
    painter.DrawStringInCenterRect(0, 190 + dY, 320, 20, "��� ��������� ������ ������� � ����������� ������ ������");
#ifdef S8_54
    painter.DrawStringInCenterRect(0, 205 + dY, 320, 20, "����� ����������: ���./����. 8-017-262-57-50");
    painter.DrawStringInCenterRect(0, 220 + dY, 320, 20, "������������: e-mail: mnipi-24(@)tut.by, ���. 8-017-262-57-51");
#endif

    Menu_Draw();
    painter.EndScene();
}

// ������ - ���������� - ����� -----------------------------------------------------------------------------------------------------------------------
static const SButton bInformation_Exit
(
    COMMON_BEGIN_SB_EXIT,
    &ppInformation, OnPress_Information_Exit, DrawSB_Exit
);

static void OnPress_Information_Exit(void)
{
    display.SetDrawMode(DrawMode_Auto, 0);
}







































/*
//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnPressPrevSettings(void)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnChangedColorMenuTitle(void)
{
    uint16 newColor1 = painter.ReduceBrightness(COLOR(COLOR_MENU_TITLE), 0.50f);
    uint16 newColor2 = painter.ReduceBrightness(COLOR(COLOR_MENU_TITLE), 1.50f);
    COLOR(Color::MENU_TITLE_DARK) = newColor1;
    COLOR(COLOR_MENU_TITLE_BRIGHT) = newColor2;
    Color_Log(COLOR_MENU_TITLE);
    Color_Log(Color::MENU_TITLE_DARK);
    Color_Log(COLOR_MENU_TITLE_BRIGHT);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnChangedColorMenu2Item(void)
{
    uint16 newColor1 = painter.ReduceBrightness(COLOR(COLOR_MENU_ITEM), 0.50f);
    uint16 newColor2 = painter.ReduceBrightness(COLOR(COLOR_MENU_ITEM), 1.50f);
    COLOR(COLOR_MENU_ITEM_DARK) = newColor1;
    COLOR(COLOR_MENU_ITEM_BRIGHT) = newColor2;
    Color_Log(COLOR_MENU_ITEM);
    Color_Log(COLOR_MENU_ITEM_DARK);
    Color_Log(COLOR_MENU_ITEM_BRIGHT);
}


// ������ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Page pService;

// ������ - ����� ��������
const Button mbServicePreviousSettings =
{
    Item_Button, &pService, 0,
    {
        "����� ��������", "Return settings",
        "���������� ��������� ������������, ������� ���� � ������ ������� \"����� �������\"",
        "Returns the oscilloscope settings that were in when you press \"Searching for signal\""
    },
    OnPressPrevSettings
};

static bool ActiveF_MathFormula(void)
{
    return MATH_FUNC_MUL || MATH_FUNC_SUM;
}

static void ChangeF_MathFormula(void)
{

}

static int8 curDigit = 0;
const Formula mfMathFormula =
{
    Item_Formula, &ppFunction, ActiveF_MathFormula,
    {
        "�������", "Formulf",
        "����� �������� ������������ � ����� � �������������� �������",
        "Here you can set the coefficients and signs in a mathematical formula"
    },
    (int8 *)&MATH_FUNC, (int8 *)&set.math_koeff1add, (int8 *)&set.math_koeff2add, (int8 *)&set.math_koeff1mul, (int8 *)&set.math_koeff2mul, &curDigit, ChangeF_MathFormula
};
*/

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "PageServiceMath.h"
#include "ServiceEthernet.h"
#include "ServiceInformation.h"
#include "ServiceTime.h"
#include "ServiceSound.h"
#include "Display/Display.h"
#include "FPGA/FPGA.h"
#include "Panel/Panel.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Page mainPage;
extern void Func_Start(int key);          // 1 - �������, 1 - ����������


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const  Button bResetSettings;                        ///< ������ - ����� ��������
        void  OnPress_ResetSettings(void);
static void      Draw_ResetSettings(void);
static const  Button bAutoSearch;                           ///< ������ - ����� �������
static void   OnPress_AutoSearch(void);
static const   Page ppCalibrator;                           ///< ������ - ����������
static const  Choice cCalibrator_Calibrator;                ///< ������ - ���������� - ����������
static void OnChanged_Calibrator_Calibrator(bool active);
static const  Button bCalibrator_Calibrate;                 ///< ������ - ���������� - �����������
static bool  IsActive_Calibrator_Calibrate(void);
static void   OnPress_Calibrator_Calibrate(void);


static const  Choice cRecorder;
static void OnChanged_Recorder(bool active);
static const  Choice cLanguage;


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
        (void*)&bResetSettings,     // ������ - ����� ��������
        (void*)&bAutoSearch,        // ������ - ����� �������
        (void*)&ppCalibrator,       // ������ - ����������
        (void*)&cRecorder,          // ������ - �����������
        (void*)&ppFFT,              // ������ - ������
        (void*)&mspMathFunction,    // ������ - �������
        (void*)&mspEthernet,        // ������ - ETHERNET
        (void*)&mspSound,           // ������ - ����
        (void*)&mspTime,            // ������ - �����
        (void*)&cLanguage,          // ������ - ����
        (void*)&mspInformation      // ������ - ����������
    }
};

// ������ - ����� �������� ---------------------------------------------------------------------------------------------------------------------------
static const Button bResetSettings =
{
    Item_Button, &pService, 0,
    {
        "����� ��������", "Reset settings",
        "����� �������� �� ��������� �� ���������",
        "Reset to default settings"
    },
    OnPress_ResetSettings
};

void OnPress_ResetSettings(void)
{
    Panel_Disable();
    Display_SetDrawMode(DrawMode_Hand, Draw_ResetSettings);

    if (Panel_WaitPressingButton() == B_Start)
    {
        Settings_Load(true);
    }

    Display_SetDrawMode(DrawMode_Auto, 0);
    Panel_Enable();
    Func_Start(1);
}

static void Draw_ResetSettings(void)
{
    Painter_BeginScene(gColorBack);

    Painter_DrawTextInRectWithTransfersC(30, 110, 300, 200, "����������� ����� �������� �������� ������ ����/����.\n"
                                                         "������� ����� ������ ������, ���� ����� �� �����.", gColorFill);

    Painter_EndScene();
}

// ������ - ����� ������� ----------------------------------------------------------------------------------------------------------------------------
static const Button bAutoSearch =
{
    Item_Button, &pService, 0,
    {
        "����� �������", "Find signal",
        "������������� ����������� ��������� ������������ ��� ������� � ������ 1",
        "Sets optimal settings for the oscilloscope signal on channel 1"
    },
    OnPress_AutoSearch
};

static void OnPress_AutoSearch(void)
{
    gBF.FPGAneedAutoFind = 1;
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
    Page_ServiceCalibrator,
    {
        (void*)&cCalibrator_Calibrator,     // ������ - ���������� - ����������
        (void*)&bCalibrator_Calibrate       // ������ - ���������� - �����������
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
    (int8*)&CALIBRATOR_MODE, OnChanged_Calibrator_Calibrator
};

static void OnChanged_Calibrator_Calibrator(bool active)
{
    FPGA_SetCalibratorMode(CALIBRATOR_MODE);
}

// ������ - ���������� - ����������� -----------------------------------------------------------------------------------------------------------------
static const Button bCalibrator_Calibrate =
{
    Item_Button, &ppCalibrator, IsActive_Calibrator_Calibrate,
    {
        "�����������", "Calibrate",
        "������ ��������� ����������",
        "Running the calibration procedure"
    },
    OnPress_Calibrator_Calibrate, EmptyFuncVII
};

static bool IsActive_Calibrator_Calibrate(void)
{
    return !(SET_CALIBR_MODE_A == CalibrationMode_Disable && CALIBR_MODE_B == CalibrationMode_Disable);
}

static void OnPress_Calibrator_Calibrate(void)
{
    gStateFPGA.needCalibration = true;
}


























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
    (int8*)&RECORDER_MODE, OnChanged_Recorder
};

static void OnChanged_Recorder(bool active)
{
    FPGA_EnableRecorderMode(RECORDER_MODE);
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
    (int8*)&LANG
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnPressPrevSettings(void)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnChangedColorMenuTitle(void)
{
    uint16 newColor1 = Painter_ReduceBrightness(COLOR(COLOR_MENU_TITLE), 0.50f);
    uint16 newColor2 = Painter_ReduceBrightness(COLOR(COLOR_MENU_TITLE), 1.50f);
    COLOR(COLOR_MENU_TITLE_DARK) = newColor1;
    COLOR(COLOR_MENU_TITLE_BRIGHT) = newColor2;
    Color_Log(COLOR_MENU_TITLE);
    Color_Log(COLOR_MENU_TITLE_DARK);
    Color_Log(COLOR_MENU_TITLE_BRIGHT);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnChangedColorMenu2Item(void)
{
    uint16 newColor1 = Painter_ReduceBrightness(COLOR(COLOR_MENU_ITEM), 0.50f);
    uint16 newColor2 = Painter_ReduceBrightness(COLOR(COLOR_MENU_ITEM), 1.50f);
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

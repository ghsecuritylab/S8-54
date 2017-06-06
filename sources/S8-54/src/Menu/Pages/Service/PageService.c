// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "Display/Display.h"
#include "Display/Painter.h"
#include "Display/Colors.h"
#include "FPGA/FPGA.h"
#include "Hardware/Timer.h"
#include "Menu/Menu.h"
#include "Menu/MenuDrawing.h"
#include "Menu/MenuFunctions.h"
#include "PageServiceMath.h"
#include "Panel/Panel.h"
#include "Settings/Settings.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"
#include "ServiceInformation.h"
#include "ServiceTime.h"
#include "ServiceCalibrator.h"
#include "ServiceSound.h"
#include "ServiceEthernet.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Page mainPage;
extern void FuncBtnStart(int key);          // 1 - �������, -1 - ����������


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Button mbResetSettings;
        void OnPress_ResetSettings(void);
static void  FuncDraw_ResetSettings(void);
static const Choice mcRecorder;
static void  OnChange_Recorder(bool active);
static const Choice mcLanguage;


// ������ - ����� ������� ----------------------------------------------------------------------------------------------------------------------------
static void OnPress_AutoSearch(void)
{
    gBF.FPGAneedAutoFind = 1;
};

static const Button mbAutoSearch =
{
    Item_Button, &mpService, 0,
    {
        "����� �������", "Find signal",
        "������������� ����������� ��������� ������������ ��� ������� � ������ 1",
        "Sets optimal settings for the oscilloscope signal on channel 1"
    },
    OnPress_AutoSearch
};

// ������ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mpService =
{
    Item_Page, &mainPage, 0,
    {
        "������", "SERVICE",
        "�������������� ���������, ����������, ����� �������, �������������� �������",
        "Additional settings, calibration, signal search, mathematical functions"
    },
    Page_Service,
    {
        (void*)&mbResetSettings,    // ������ - ����� ��������
        (void*)&mbAutoSearch,       // ������ - ����� �������
        (void*)&mspCalibrator,      // ������ - ����������
        (void*)&mcRecorder,         // ������ - �����������
        (void*)&mspFFT,             // ������ - ������
        (void*)&mspMathFunction,    // ������ - �������
        (void*)&mspEthernet,        // ������ - ETHERNET
        (void*)&mspSound,           // ������ - ����
        (void*)&mspTime,            // ������ - �����
        (void*)&mcLanguage,         // ������ - ����
        (void*)&mspInformation      // ������ - ����������
    }
};

// ������ - ����� �������� ---------------------------------------------------------------------------------------------------------------------------
static const Button mbResetSettings =
{
    Item_Button, &mpService, 0,
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
    Display_SetDrawMode(DrawMode_Hand, FuncDraw_ResetSettings);

    if (Panel_WaitPressingButton() == B_Start)
    {
        Settings_Load(true);
    }

    Display_SetDrawMode(DrawMode_Auto, 0);
    Panel_Enable();
    FuncBtnStart(1);
}

static void FuncDraw_ResetSettings(void)
{
    Painter_BeginScene(gColorBack);

    Painter_DrawTextInRectWithTransfersC(30, 110, 300, 200, "����������� ����� �������� �������� ������ ����/����.\n"
                                         "������� ����� ������ ������, ���� ����� �� �����.", gColorFill);

    Painter_EndScene();
}

// ������ - ����������� ------------------------------------------------------------------------------------------------------------------------------
static const Choice mcRecorder =
{
    Item_Choice, &mpService, 0,
    {
        "�����������", "Recorder",
        "��������/��������� ����� ������������. ���� ����� �������� �� ��������� 50 ��/��� � ����� ���������.",
        "Turn on/off recorder mode. This mode is available for scanning 20ms/div and slower."
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&RECORDER_MODE, OnChange_Recorder
};

static void OnChange_Recorder(bool active)
{
    FPGA_EnableRecorderMode(RECORDER_MODE);
}

// ������ - ���� -------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcLanguage =
{
    Item_Choice, &mpService, 0,
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
extern const Page mpService;

// ������ - ����� ��������
const Button mbServicePreviousSettings =
{
    Item_Button, &mpService, 0,
    {
        "����� ��������", "Return settings",
        "���������� ��������� ������������, ������� ���� � ������ ������� \"����� �������\"",
        "Returns the oscilloscope settings that were in when you press \"Searching for signal\""
    },
    OnPressPrevSettings
};

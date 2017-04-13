// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "Menu/Menu.h"
#include "Menu/MenuItems.h"
#include "FPGA/FPGA.h"
#include "Settings/SettingsDisplay.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"
#include "PageDisplay.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern ColorType colorTypeGrid;

extern Page mainPage;

       const Page mpDisplay;
static const Choice mcViewMode;
static const Choice mcMinMax;
static const Choice mcSmoothing;
static const Choice mcRefreshFPS;
static const Choice mcScaleYtype;

static const Page mspAccum;
static const Choice mcAccum_Num;
static const Choice mcAccum_Mode;
static const Button mbAccum_Crear;

static const Page mspAverage;
static const Choice mcAverage_Num;
static const Choice mcAverage_Mode;

static const Page mspGrid;
static const Choice mcGrid_Type;
static const Governor mgGrid_Brightness;

static const Page mspSettings;
static const Choice mcSettings_Colors_Background;
static void OnChange_Settings_Colors_Background(bool active);
static const Choice mcSettings_Colors_Scheme;
static const GovernorColor mgcSettings_Colors_ChannelA;
static const GovernorColor mgcSettings_Colors_ChannelB;
static const GovernorColor mgcSettings_Colors_Grid;
static const Page mspSettings_Colors;
static const Governor mgSettings_Brightness;
static const Governor mgSettings_Levels;
static const Governor mgSettings_Time;
static const Choice mcSettings_StringNavigation;
static const Choice mcSettings_AltMarkers;
static const Choice mcSettings_AutoHide;
static void OnChange_Settings_Brightness(void);

static bool IsActive_MinMax(void);
static void OnChange_MinMax(bool active);
static void OnChange_RefreshFPS(bool active);
static bool IsActive_Accum(void);
static bool IsActive_Accum_Clear(void);
       void OnPress_Accum_Clear(void);
static bool IsActive_Average(void);
       void OnChange_Grid_Brightness(void);
static void BeforeDraw_Grid_Brightness(void);


// ������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PageDisplay_Init(void)
{
    OnChange_Settings_Colors_Background(true);   // ������� �������� � �������� ������
}

const Page mpDisplay =
{
    Item_Page, &mainPage, 0,
    {
        "�������", "DISPLAY",
        "�������� ��������� ����������� �������.",
        "Contains settings of display of the display."
    },
    Page_Display,
    {
        (void*)&mcViewMode,     // ������� - �����������
        (void*)&mspAccum,       // ������� - ����������
        (void*)&mspAverage,     // ������� - ����������
        (void*)&mcMinMax,       // ������� - ��� ����
        (void*)&mcSmoothing,    // ������� - �����������
        (void*)&mcRefreshFPS,   // ������� - ���������� - �������
        (void*)&mspGrid,        // ������� - �����
        (void*)&mcScaleYtype,   // ������� - ��������
        (void*)&mspSettings     // ������� - ���������
    }
};

// ������� - ����������� -----------------------------------------------------------------------------------------------------------------------------
static const Choice mcViewMode =
{
    Item_Choice, &mpDisplay, 0,
    {
        "�����������", "View",
        "����� ����� ����������� �������.",
        "Sets the display mode signal."
    },
    {
        {"������",  "Vector"},
        {"�����",   "Points"}
    },
    (int8*)&MODE_DRAW_SIGNAL
};

// ������� - ��� ���� --------------------------------------------------------------------------------------------------------------------------------
static const Choice mcMinMax =
{
    Item_ChoiceReg, &mpDisplay, IsActive_MinMax,
    {
        "��� ����", "Min Max",
        "����� ���������� ��������� ���������, �� ������� �������� ��������������� �����, ��������� �������� � ��������� ���������.",
        "Sets number of the last measurements on which the limiting lines which are bending around minima and maxima of measurements are under construction."
    },
    {
        {DISABLE_RU,DISABLE_EN},
        {"2",   "2"},
        {"4",   "4"},
        {"8",   "8"},
        {"16",  "16"},
        {"32",  "32"},
        {"64",  "64"},
        {"128", "128"}
    },
    (int8*)&set.display.numMinMax, OnChange_MinMax
};

static bool IsActive_MinMax(void)
{
    return SET_TBASE > TBase_20ns;
}

static void OnChange_MinMax(bool active)
{
    /*
    int maxMeasures = DS_NumberAvailableEntries();  
    int numMinMax = sDisplay_NumberMinMax();

    if (maxMeasures < numMinMax)
    {
        Display_ShowWarningWithNumber(ExcessValues, maxMeasures);
    }
    */
}

// ������� - ����������� ----------------------------------------------------------------------------------------------------------------------------
static const Choice mcSmoothing =
{
    Item_ChoiceReg, &mpDisplay, 0,
    {
        "�����������", "Smoothing",
        "������������� ���������� ����� ��� ������� ����������� �� �������� ������ �������.",
        "Establishes quantity of points for calculation of the signal smoothed on the next points."
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {"2 �����", "2 points"},
        {"3 �����", "3 points"},
        {"4 �����", "4 points"},
        {"5 �����", "5 points"},
        {"6 �����", "6 points"},
        {"7 �����", "7 points"},
        {"8 �����", "8 points"},
        {"9 �����", "9 points"},
        {"10 �����", "10 points"}
    },
    (int8*)&SMOOTHING
};

// ������� - ���������� - ������� ------------------------------------------------------------------------------------------------------------------
static const Choice mcRefreshFPS =
{
    Item_Choice, &mpDisplay, 0,
    {
        "������� ������", "Refresh rate",
        "����� ������������ ����� ��������� � ������� ������.",
        "Sets the maximum number of the shots removed in a second."
    },
    {
        {"25",  "25"},
        {"10",  "10"},
        {"5",   "5"},
        {"2",   "2"},
        {"1",   "1"}
    },
    (int8*)&NUM_SIGNALS_IN_SEC, OnChange_RefreshFPS
};

static void OnChange_RefreshFPS(bool active)
{
    FPGA_SetNumSignalsInSec(sDisplay_NumSignalsInS());
}

// ������� - �������� -------------------------------------------------------------------------------------------------------------------------------
static const Choice mcScaleYtype =
{
    Item_Choice, &mpDisplay, 0,
    {
        "��������", "�ffset",
        "����� ����� ��������� �������� �� ���������\n1. \"����������\" - ����������� ��������� ��������.\n2. \"�������\" - ����������� ��������� �������� �� ������.",
        "Sets the mode of retaining the vertical displacement\n1. \"Voltage\" - saved dressing bias.\n2. \"Divisions\" - retained the position of the offset on the screen."
    },
    {
        {"����������", "Voltage"},
        {"�������", "Divisions"}
    },
    (int8*)&set.display.linkingRShift
};

// ������� - ���������� -----------------------------------------------------------------------------------------------------------------------------
static const Page mspAccum =
{
    Item_Page, &mpDisplay, IsActive_Accum,
    {
        "����������", "ACCUMULATION",
        "��������� ������ ����������� ��������� �������� �� ������.",
        "Mode setting signals to display the last screen."
    },
    Page_DisplayAccumulation,
    {
        (void*)&mcAccum_Num,    // ������� - ���������� - ����������
        (void*)&mcAccum_Mode,   // ������� - ���������� - ���
        (void*)&mbAccum_Crear   // ������� - ���������� - ��������
    }
};

static bool IsActive_Accum(void)
{
    return SET_TBASE > TBase_20ns;
}

// ������� - ���������� - ���������� ---------------------------------------------------------------------------------------------------------------
static const Choice mcAccum_Num =
{
    Item_ChoiceReg, &mspAccum, 0,
    {
        "����������", "Number"
        ,
        "����� ������������ ���������� ��������� �������� �� ������. ���� � ��������� \"�����\" ������� \"�������������\", ����� ��������� ������ �������� ������ \"��������\"."
        "\"�������������\" - ������ ��������� ������� �� ������� �� ��� ���, ���� �� ����� ������ ������ \"��������\"."
        ,
        "Sets the maximum quantity of the last signals on the screen. If in control \"Mode\" it is chosen \"Infinity\", the screen is cleared only by pressing of the button \"Clear\"."
        "\"Infinity\" - each measurement remains on the display until the button \"Clear\" is pressed."
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {"2",   "2"},
        {"4",   "4"},
        {"8",   "8"},
        {"16",  "16"},
        {"32",  "32"},
        {"64",  "64"},
        {"128", "128"},
        {"�������������", "Infinity"}
    },
    (int8*)&NUM_ACCUM
};

// ������� - ���������� - ��� ----------------------------------------------------------------------------------------------------------------------
static const Choice mcAccum_Mode =
{
    Item_Choice, &mspAccum, 0,
    {
        "�����", "Mode"
        ,
        "1. \"����������\" - ����� ���������� ��������� ���������� ��������� ���������� ������� �������. ���� ����� ������, ����� ������ �� ������� ��� ���������� ������� ���������� ���������.\n"
        "2. \"�� ����������\" - �� ������� ������ ��������� �������� ��� ������� (� ������ �������� ������) ���������� ���������. ����������� �������� ������� �������������� � ������������� ���������� ��������� ���������� ��������� ��� ���������� ������."
        ,
        "1. \"Dump\" - after accumulation of the set number of measurement there is a cleaning of the display. This mode is convenient when memory isn't enough for preservation of the necessary number of measurements.\n"
        "2. \"Not to dump\" - the number of measurements is always output to the display set or smaller (in case of shortage of memory). Shortcoming is smaller speed and impossibility of accumulation of the set number of measurements at a lack of memory."
    },
    {
        {"�� ����������",   "Not to dump"},
        {"����������",      "Dump"}
    },
    (int8*)&MODE_ACCUM
};

// ������� - ���������� - �������� -----------------------------------------------------------------------------------------------------------------
static const Button mbAccum_Crear =
{
    Item_Button, &mspAccum, IsActive_Accum_Clear,
    {
        "��������", "Clear",
        "������� ����� �� ����������� ��������.",
        "Clears the screen of the saved-up signals."
    },
    OnPress_Accum_Clear, EmptyFuncVII
};

static bool IsActive_Accum_Clear(void)
{
    return NUM_ACCUM_INF;
}

void OnPress_Accum_Clear(void)
{
    Display_Redraw();
}

// ������� - ���������� -----------------------------------------------------------------------------------------------------------------------------
static const Page mspAverage =
{
    Item_Page, &mpDisplay, IsActive_Average,
    {
        "����������", "AVERAGE",
        "��������� ������ ���������� �� ��������� ����������.",
        "Settings of the mode of averaging on the last measurements."
    },
    Page_DisplayAverage,
    {
        (void*)&mcAverage_Num,  // ������� - ���������� - ����������
        (void*)&mcAverage_Mode  // ������� - ���������� - �����
    }
};

static bool IsActive_Average(void)
{
    return true;
}

// ������� - ���������� - ���������� ---------------------------------------------------------------------------------------------------------------
static const Choice mcAverage_Num =
{
    Item_ChoiceReg, &mspAverage, 0,
    {
        "����������", "Number",
        "����� ���������� ��������� ���������, �� ������� ������������ ����������.",
        "Sets number of the last measurements on which averaging is made."
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {"2",   "2"},
        {"4",   "4"},
        {"8",   "8"},
        {"16",  "16"},
        {"32",  "32"},
        {"64",  "64"},
        {"128", "128"},
        {"256", "256"},
        {"512", "512"}
    },
    (int8*)&NUM_AVE
};

// ������� - ���������� - ����� --------------------------------------------------------------------------------------------------------------------
static const Choice mcAverage_Mode =
{
    Item_Choice, &mspAverage, 0,
    {
        "�����", "Mode"
        ,
        "1. \"�����\" - ������ ����� ����������, ����� � ������� ��������� ������ ��������� �������.\n"
        "2. \"��������������\" - ��������������� ����� ����������. ����� ����� ������������, ����� ������ ���������� ��������� �������, ��� ����� ����������� � ������."
        ,
        "1. \"Accurately\" - the exact mode of averaging when only the last signals participate in calculation.\n"
        "2. \"Around\" - approximate mode of averaging. It makes sense to use when the number of measurements bigger is set, than can be located in memory."
    },
    {
        {"�����",           "Accurately"},
        {"��������������",  "Around"}
    },
    (int8*)&set.display.modeAveraging
};

// ������� - ����� ----------------------------------------------------------------------------------------------------------------------------------
static const Page mspGrid =
{
    Item_Page, &mpDisplay, 0,
    {
        "�����", "GRID",
        "�������� ��������� ����������� ������������ �����.",
        "Contains settings of display of a coordinate grid."
    },
    Page_DisplayGrid,
    {
        (void*)&mcGrid_Type,        // ������� - ����� - ���
        (void*)&mgGrid_Brightness   // ������� - ����� - �������
    }
};

// ������� - ����� - ��� ---------------------------------------------------------------------------------------------------------------------------
static const Choice mcGrid_Type =
{
    Item_Choice, &mspGrid, 0,
    {
        "���", "Type",
        "����� ���� �����.",
        "Choice like grid."
    },
    {
        {"��� 1", "Type 1"},
        {"��� 2", "Type 2"},
        {"��� 3", "Type 3"},
        {"��� 4", "Type 4"}
    },
    (int8*)&TYPE_GRID
};

// ������� - ����� - ������� -----------------------------------------------------------------------------------------------------------------------
static const Governor mgGrid_Brightness =
{
    Item_Governor, &mspGrid, 0,
    {
        "�������", "Brightness",
        "������������� ������� �����.",
        "Adjust the brightness of the grid."
    },
    &set.display.brightnessGrid, 0, 100, OnChange_Grid_Brightness, BeforeDraw_Grid_Brightness
};

void OnChange_Grid_Brightness(void)
{
    Color_SetBrightness(&colorTypeGrid, set.display.brightnessGrid / 1e2f);
}


static void BeforeDraw_Grid_Brightness(void)
{
    Color_Init(&colorTypeGrid, false);
    set.display.brightnessGrid = (int16)(colorTypeGrid.brightness * 100.0f);
}

// ������� - ��������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mspSettings =
{
    Item_Page, &mpDisplay, 0,
    {
        "���������", "SETTINGS",
        "�������������� ��������� �������",
        "Additional display settings"
    },
    Page_DisplaySettings,
    {
        (void*)&mspSettings_Colors,
        (void*)&mgSettings_Brightness,
        (void*)&mgSettings_Levels,
        (void*)&mgSettings_Time,
        (void*)&mcSettings_StringNavigation,
        (void*)&mcSettings_AltMarkers,
        (void*)&mcSettings_AutoHide
    }
};

// ������� - ��������� - �������� ------------------------------------------------------------------------------------------------------------------
static void Menu_AutoHide(bool autoHide)
{
    Menu_SetAutoHide(autoHide);
}

static const Choice mcSettings_AutoHide =
{
    Item_Choice, &mspSettings, 0,
    {
        "��������", "Hide",
        "��������� ����� ���������� ������� ������ ��� �������� �����, �� ��������� �������� ���� ������������� ��������� � ������",
        "Installation after the last keystroke or turning the handle, after which the menu will automatically disappear"
    },
    {
        { "�������", "Never" },
        { "����� 5 ���", "Through 5 s" },
        { "����� 10 ���", "Through 10 s" },
        { "����� 15 ���", "Through 15 s" },
        { "����� 30 ���", "Through 30 s" },
        { "����� 60 ���", "Through 60 s" }
    },
    (int8*)&set.display.menuAutoHide, Menu_AutoHide
};

// ������ - ������� - ���. ������� -----------------------------------------------------------------------------------------------------------------
static const Choice mcSettings_AltMarkers =
{
    Item_Choice, &mspSettings, 0,
    {
        "���. �������", "Alt. markers"
        ,
        "������������� ����� ����������� �������������� �������� ������� �������� � �������������:\n"
        "\"��������\" - �������������� ������� �� ������������,\n"
        "\"����������\" - �������������� ������� ������������ ������,\n"
        "\"����\" - �������������� ������� ������������ � ������� 5 ��� ����� �������� ����� �������� ������ �� ���������� ��� ������ �������������"
        ,
        "Sets the display mode of additional markers levels of displacement and synchronization:\n"
        "\"Hide\" - additional markers are not shown,\n"
        "\"Show\" - additional markers are shown always,\n"
        "\"Auto\" - additional markers are displayed for 5 seconds after turning the handle channel offset voltage or trigger level"
    },
    {
        { "��������", "Hide" },
        { "����������", "Show" },
        { "����", "Auto" }
    },
    (int8*)&ALT_MARKERS, Display_ChangedRShiftMarkers
};

// ������� - ��������� - ������ ���� -----------------------------------------------------------------------------------------------------------------
static const Choice mcSettings_StringNavigation =
{
    Item_Choice, &mspSettings, 0,
    {
        "������ ����", "Path menu",
        "��� ������ \n����������\n ����� ������ ������ ��������� ������ ���� �� ������� �������� ����",                         // WARN ��������� �������
        "When choosing \nDisplay\n at the top left of the screen displays the full path to the current page menu"
    },
    {
        { "��������", "Temporary" },                    // WARN ��������� �������
        { "������", "All" },
        { "�������", "None" }
    },
    (int8*)&SHOW_STRING_NAVI
};

// ������� - ��������� - ����� ---------------------------------------------------------------------------------------------------------------------
/** @todo �������� �������������� ����� 1-�� � 2-�� ������� */
static const Page mspSettings_Colors =
{
    Item_Page, &mspSettings, 0,
    {
        "�����", "COLORS",
        "����� ������ �������",
        "The choice of colors display"
    },
    Page_ServiceDisplayColors,
    {
        (void*)&mcSettings_Colors_Scheme,
        (void*)&mgcSettings_Colors_ChannelA,
        (void*)&mgcSettings_Colors_ChannelB,
        (void*)&mgcSettings_Colors_Grid,
        (void*)&mcSettings_Colors_Background
        //(void*)&mgcColorChannel0alt,
        //(void*)&mgcColorChannel1alt,
        //(void*)&mgcColorMenu1,
        //(void*)&mgcColorMenu2,
        //(void*)&mgcColorMenu3
        //,(void*)&mgcColorMathem,
        //(void*)&mgcColorFFT,
        //(void*)&mcServDisplInverse
    }
};

// ������� - ��������� - ������� -------------------------------------------------------------------------------------------------------------------
static const Governor mgSettings_Brightness =
{
    Item_Governor, &mspSettings, 0,
    {
        "�������", "Brightness",
        "��������� ������� �������� �������",
        "Setting the brightness of the display"
    },
    &set.display.brightness, 0, 100, OnChange_Settings_Brightness
};

static void OnChange_Settings_Brightness(void)
{
    Painter_SetBrightnessDisplay(set.display.brightness);
}

// ������� - ��������� - ������ --------------------------------------------------------------------------------------------------------------------
static const Governor mgSettings_Levels =
{
    Item_Governor, &mspSettings, 0,
    {
        "������", "Levels",
        "����� �����, � ������� �������� ����� �������� ����� ������� ���������� �� ������ ������� ��������������� ����� ������ ��������",
        "Defines the time during which, after turning the handle visits to the voltage on the screen remains auxiliary label offset level"
    },
    &TIME_SHOW_LEVELS, 0, 125
};

// ������� - ��������� - ����� ---------------------------------------------------------------------------------------------------------------------
static const Governor mgSettings_Time =
{
    Item_Governor, &mspSettings, 0,
    {
        "�����", "Time",
        "��������� �������, � ������� �������� ��������� ����� ���������� �� ������",
        "Set the time during which the message will be on the screen"
    },
    &TIME_MESSAGES, 1, 99
};


static const Choice mcSettings_Colors_Background =
{
    Item_Choice, &mspSettings_Colors, 0,
    {
        "���", "Background",
        "����� ����� ����",
        "Choice of color of a background"
    },
    {
        { "׸����", "Black" },
        { "�����", "White" }
    },
    (int8*)&BACKGROUND, OnChange_Settings_Colors_Background
};

// ������� - ��������� - ����� - �������� ����� ---------------------------------------------------------------------------------------------------
static const Choice mcSettings_Colors_Scheme =
{
    Item_Choice, &mspSettings_Colors, 0,
    {
        "�������� �����", "Color scheme",
        "����� ������ �����������",
        "Mode of operation of the calibrator"
    },
    {
        { "����� 1", "Scheme 1" },
        { "����� 2", "Scheme 2" }
    },
    (int8*)&set.service.colorScheme
};

static void OnChange_Settings_Colors_Background(bool active)
{
    PageService_InitGlobalColors();

    mgcSettings_Colors_ChannelA.colorType->color = gColorChan[A];
    mgcSettings_Colors_ChannelB.colorType->color = gColorChan[B];
    mgcSettings_Colors_Grid.colorType->color = gColorGrid;

    Color_Init((ColorType*)&mgcSettings_Colors_ChannelA, true);
    Color_Init((ColorType*)&mgcSettings_Colors_ChannelB, true);
    Color_Init((ColorType*)&mgcSettings_Colors_Grid, true);
}

// ������� - ��������� - ����� - ����� 1 ----------------------------------------------------------------------------------------------------------
static ColorType colorT1 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_DATA_1 };
static const GovernorColor mgcSettings_Colors_ChannelA =
{
    Item_GovernorColor, &mspSettings_Colors, 0,
    {
        "����� 1", "Channel 1",
        "",
        ""
    },
    &colorT1
};

// ������� - ��������� - ����� - ����� 2 ----------------------------------------------------------------------------------------------------------
static ColorType colorT2 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_DATA_2 };
static const GovernorColor mgcSettings_Colors_ChannelB =
{
    Item_GovernorColor, &mspSettings_Colors, 0,
    {
        "����� 2", "Channel 2",
        "",
        ""
    },
    &colorT2
};

// ������� - ��������� - ����� - ����� ------------------------------------------------------------------------------------------------------------
ColorType colorTypeGrid = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_GRID };
static const GovernorColor mgcSettings_Colors_Grid = 
{ 
    Item_GovernorColor, &mspSettings_Colors, 0,
    { 
        "�����", "Grid",
        "������������� ���� �����",
        "Sets the grid color"
    },
    &colorTypeGrid
};

//------------------------------------------------------------------------------------------------------------------------------------------------------
void PageService_InitGlobalColors(void)
{
    gColorBack = BACKGROUND_BLACK ? COLOR_BLACK : COLOR_WHITE;
    gColorFill = BACKGROUND_BLACK ? COLOR_WHITE : COLOR_BLACK;
    gColorGrid = BACKGROUND_BLACK ? COLOR_GRID : COLOR_GRID_WHITE;
    gColorChan[A] = BACKGROUND_BLACK ? COLOR_DATA_1 : COLOR_DATA_A_WHITE;
    gColorChan[B] = BACKGROUND_BLACK ? COLOR_DATA_2 : COLOR_DATA_B_WHITE;
    gColorChan[A_B] = gColorChan[Math] = BACKGROUND_BLACK ? COLOR_WHITE : COLOR_BLACK;
}

/*
//------------------------------------------------------------------------------------------------------------------------------------------------------
// ������ - ������� - ����� - ���� �������
static ColorType colorT6 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_MENU_FIELD };
const GovernorColor mgcColorMenu3 = { Item_GovernorColor, &mspSettings_Colors, { "���� �������", "Menu Field" },
{
    "",
    "",
},
0, &colorT6
};


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ������ - ������� - ����� - ���� ���������
static ColorType colorT7 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_MENU_TITLE };
const GovernorColor mgcColorMenu1 = { Item_GovernorColor, &mspSettings_Colors, { "M��� ���������", "Menu Title" },
{
    "",
    ""
},
0, &colorT7, OnChangedColorMenuTitle
};


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ������ - ������� - ����� - ���� �����
static ColorType colorT8 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_MENU_ITEM };
const GovernorColor mgcColorMenu2 = { Item_GovernorColor, &mspSettings_Colors, { "���� �����", "Menu Item" },
{
    "",
    ""
},
0, &colorT8, OnChangedColorMenu2Item
};


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ������ - ������� - ����� - ��������
const Choice mcServDisplInverse =
{
    Item_Choice, &mspSettings_Colors, { "��������", "Inverse" },
    {
        "",
        ""
    },
    0,
    { { DISABLE_RU, DISABLE_EN },
    { ENABLE_RU, ENABLE_EN },
    },
    0
};
*/

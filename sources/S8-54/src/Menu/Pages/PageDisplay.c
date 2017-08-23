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

       const Page pDisplay;
static const         Choice cViewMode;                          ///< ������� - �����������
static const          Page ppAccum;                             ///< ������� - ����������
static bool         IsActive_Accum(void);
static const         Choice cAccum_Num;                         ///< ������� - ���������� - ����������
static const         Choice cAccum_Mode;                        ///< ������� - ���������� - �����
static const         Button bAccum_Clear;                       ///< ������� - ���������� - ��������
static bool         IsActive_Accum_Clear(void);
       void          OnPress_Accum_Clear(void);
static const          Page ppAverage;                           ///< ������� - ����������
static bool         IsActive_Average(void);
static const         Choice cAverage_Num;                       ///< ������� - ���������� - ����������
static const         Choice cAverage_Mode;                      ///< ������� - ���������� - �����
static const         Choice cMinMax;                            ///< ������� - ��� ����
static bool         IsActive_MinMax(void);
static void        OnChanged_MinMax(bool active);
static const         Choice cSmoothing;                         ///< ������� - �����������
static const         Choice cRefreshFPS;                        ///< ������� - ������� ������
static void        OnChanged_RefreshFPS(bool active);
static const          Page ppGrid;                              ///< ������� - �����
static const         Choice cGrid_Type;                         ///< ������� - ����� - ���
static const       Governor gGrid_Brightness;                   ///< ������� - ����� - �������
       void        OnChanged_Grid_Brightness(void);
static void       BeforeDraw_Grid_Brightness(void);
static const         Choice cScaleYtype;                        ///< ������� - ��������
static const          Page ppSettings;                          ///< ������� - ���������
static const         Page pppSettings_Colors;                   ///< ������� - ��������� - �����
static const         Choice cSettings_Colors_Scheme;            ///< ������� - ��������� - ����� - �������� �����
static const GovernorColor gcSettings_Colors_ChannelA;          ///< ������� - ��������� - ����� - ����� 1
static const GovernorColor gcSettings_Colors_ChannelB;          ///< ������� - ��������� - ����� - ����� 2
static const GovernorColor gcSettings_Colors_Grid;              ///< ������� - ��������� - ����� - �����
static const         Choice cSettings_Colors_Background;        ///< ������� - ��������� - ����� - ���
static void        OnChanged_Settings_Colors_Background(bool active);
       void PageService_InitGlobalColors(void);
static const       Governor gSettings_Brightness;               ///< ������� - ��������� - �������
static void        OnChanged_Settings_Brightness(void);
static const       Governor gSettings_Levels;                   ///< ������� - ��������� - ������
static const       Governor gSettings_Time;                     ///< ������� - ��������� - �����
static const         Choice cSettings_StringNavigation;         ///< ������� - ��������� - ������ ����
static const         Choice cSettings_AltMarkers;               ///< ������� - ��������� - ���. �������
static const         Choice cSettings_AutoHide;                 ///< ������� - ��������� - ��������
static void        OnChanged_Settings_AutoHide(bool active);


extern Page mainPage;

// ������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PageDisplay_Init(void)
{
    OnChanged_Settings_Colors_Background(true);   // ������� �������� � �������� ������
}

const Page pDisplay =
{
    Item_Page, &mainPage, 0,
    {
        "�������", "DISPLAY",
        "�������� ��������� ����������� �������.",
        "Contains settings of display of the display."
    },
    Page_Display,
    {
        (void *)&cViewMode,     // ������� - �����������
        (void *)&ppAccum,       // ������� - ����������
        (void *)&ppAverage,     // ������� - ����������
        (void *)&cMinMax,       // ������� - ��� ����
        (void *)&cSmoothing,    // ������� - �����������
        (void *)&cRefreshFPS,   // ������� - ������� ������
        (void *)&ppGrid,        // ������� - �����
        (void *)&cScaleYtype,   // ������� - ��������
        (void *)&ppSettings     // ������� - ���������
    }
};

// ������� - ����������� -----------------------------------------------------------------------------------------------------------------------------
static const Choice cViewMode =
{
    Item_Choice, &pDisplay, 0,
    {
        "�����������", "View",
        "����� ����� ����������� �������.",
        "Sets the display mode signal."
    },
    {
        {"������",  "Vector"},
        {"�����",   "Points"}
    },
    (int8 *)&MODE_DRAW_SIGNAL
};

// ������� - ���������� ------------------------------------------------------------------------------------------------------------------------------
static const Page ppAccum =
{
    Item_Page, &pDisplay, IsActive_Accum,
    {
        "����������", "ACCUMULATION",
        "��������� ������ ����������� ��������� �������� �� ������.",
        "Mode setting signals to display the last screen."
    },
    Page_Display_Accum,
    {
        (void *)&cAccum_Num,    // ������� - ���������� - ����������
        (void *)&cAccum_Mode,   // ������� - ���������� - �����
        (void *)&bAccum_Clear   // ������� - ���������� - ��������
    }
};

static bool IsActive_Accum(void)
{
    return SET_TBASE > TBase_20ns;
}

// ������� - ���������� - ���������� -----------------------------------------------------------------------------------------------------------------
static const Choice cAccum_Num =
{
    Item_ChoiceReg, &ppAccum, 0,
    {
        "����������", "Number"
        ,
        "����� ������������ ���������� ��������� �������� �� ������. ���� � ��������� \"�����\" ������� \"�������������\", ����� ��������� ������ "
        "�������� ������ \"��������\"."
        "\"�������������\" - ������ ��������� ������� �� ������� �� ��� ���, ���� �� ����� ������ ������ \"��������\"."
        ,
        "Sets the maximum quantity of the last signals on the screen. If in control \"Mode\" it is chosen \"Infinity\", the screen is cleared only "
        "by pressing of the button \"Clear\"."
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
    (int8 *)&ENUM_ACCUM
};

// ������� - ���������� - ����� ----------------------------------------------------------------------------------------------------------------------
static const Choice cAccum_Mode =
{
    Item_Choice, &ppAccum, 0,
    {
        "�����", "Mode"
        ,
        "1. \"����������\" - ����� ���������� ��������� ���������� ��������� ���������� ������� �������. ���� ����� ������, ����� ������ �� ������� "
        "��� ���������� ������� ���������� ���������.\n"
        "2. \"�� ����������\" - �� ������� ������ ��������� �������� ��� ������� (� ������ �������� ������) ���������� ���������. ����������� �������� "
        "������� �������������� � ������������� ���������� ��������� ���������� ��������� ��� ���������� ������."
        ,
        "1. \"Dump\" - after accumulation of the set number of measurement there is a cleaning of the display. This mode is convenient when memory "
        "isn't enough for preservation of the necessary number of measurements.\n"
        "2. \"Not to dump\" - the number of measurements is always output to the display set or smaller (in case of shortage of memory). Shortcoming "
        "is smaller speed and impossibility of accumulation of the set number of measurements at a lack of memory."
    },
    {
        {"�� ����������",   "Not to dump"},
        {"����������",      "Dump"}
    },
    (int8 *)&MODE_ACCUM
};

// ������� - ���������� - �������� -------------------------------------------------------------------------------------------------------------------
static const Button bAccum_Clear =
{
    Item_Button, &ppAccum, IsActive_Accum_Clear,
    {
        "��������", "Clear",
        "������� ����� �� ����������� ��������.",
        "Clears the screen of the saved-up signals."
    },
    OnPress_Accum_Clear, EmptyFuncVII
};

static bool IsActive_Accum_Clear(void)
{
    return ENUM_ACCUM != ENumAccum_1 && !MODE_ACCUM_NO_RESET;
}

void OnPress_Accum_Clear(void)
{
    NEED_FINISH_DRAW = 1;
}

// ������� - ���������� ------------------------------------------------------------------------------------------------------------------------------
static const Page ppAverage =
{
    Item_Page, &pDisplay, IsActive_Average,
    {
        "����������", "AVERAGE",
        "��������� ������ ���������� �� ��������� ����������.",
        "Settings of the mode of averaging on the last measurements."
    },
    Page_Display_Average,
    {
        (void *)&cAverage_Num,  // ������� - ���������� - ����������
        (void *)&cAverage_Mode  // ������� - ���������� - �����
    }
};

static bool IsActive_Average(void)
{
    return true;
}

// ������� - ���������� - ���������� -----------------------------------------------------------------------------------------------------------------
static const Choice cAverage_Num =
{
    Item_ChoiceReg, &ppAverage, 0,
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
    (int8 *)&ENUM_AVE
};

// ������� - ���������� - ����� ----------------------------------------------------------------------------------------------------------------------
static const Choice cAverage_Mode =
{
    Item_Choice, &ppAverage, 0,
    {
        "�����", "Mode"
        ,
        "1. \"�����\" - ������ ����� ����������, ����� � ������� ��������� ������ ��������� �������.\n"
        "2. \"��������������\" - ��������������� ����� ����������. ����� ����� ������������, ����� ������ ���������� ��������� �������, ��� ����� "
        "����������� � ������."
        ,
        "1. \"Accurately\" - the exact mode of averaging when only the last signals participate in calculation.\n"
        "2. \"Around\" - approximate mode of averaging. It makes sense to use when the number of measurements bigger is set, than can be located in "
        "memory."
    },
    {
        {"�����",           "Accurately"},
        {"��������������",  "Around"}
    },
    (int8 *)&MODE_AVERAGING
};

// ������� - ��� ����--------------------------------------------------------------------------------------------------------------------------------
static const Choice cMinMax =
{
    Item_ChoiceReg, &pDisplay, IsActive_MinMax,
    {
        "��� ����", "Min Max",
        "����� ���������� ��������� ���������, �� ������� �������� ��������������� �����, ��������� �������� � ��������� ���������.",
        "Sets number of the last measurements on which the limiting lines which are bending around minima and maxima of measurements are under "
        "construction."
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
    (int8 *)&ENUM_MIN_MAX, OnChanged_MinMax
};

static bool IsActive_MinMax(void)
{
    return !IN_RANDOM_MODE && !IN_P2P_MODE;
}

static void OnChanged_MinMax(bool active)
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

// ������� - ����������� -----------------------------------------------------------------------------------------------------------------------------
static const Choice cSmoothing =
{
    Item_ChoiceReg, &pDisplay, 0,
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
    (int8 *)&ENUM_SMOOTHING
};

// ������� - ������� ������ --------------------------------------------------------------------------------------------------------------------------
static const Choice cRefreshFPS =
{
    Item_Choice, &pDisplay, 0,
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
    (int8 *)&ENUM_SIGNALS_IN_SEC, OnChanged_RefreshFPS
};

static void OnChanged_RefreshFPS(bool active)
{
    FPGA_SetENumSignalsInSec(NUM_SIGNALS_IN_SEC);
}

// ������� - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Page ppGrid =
{
    Item_Page, &pDisplay, 0,
    {
        "�����", "GRID",
        "�������� ��������� ����������� ������������ �����.",
        "Contains settings of display of a coordinate grid."
    },
    Page_Display_Grid,
    {
        (void *)&cGrid_Type,        // ������� - ����� - ���
        (void *)&gGrid_Brightness   // ������� - ����� - �������
    }
};

// ������� - ����� - ��� -----------------------------------------------------------------------------------------------------------------------------
static const Choice cGrid_Type =
{
    Item_Choice, &ppGrid, 0,
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
    (int8 *)&TYPE_GRID
};

// ������� - ����� - ������� -------------------------------------------------------------------------------------------------------------------------
static const Governor gGrid_Brightness =
{
    Item_Governor, &ppGrid, 0,
    {
        "�������", "Brightness",
        "������������� ������� �����.",
        "Adjust the brightness of the grid."
    },
    &BRIGHTNESS_GRID, 0, 100, OnChanged_Grid_Brightness, BeforeDraw_Grid_Brightness
};

void OnChanged_Grid_Brightness(void)
{
    Color_SetBrightness(&colorTypeGrid, BRIGHTNESS_GRID / 1e2f);
}


static void BeforeDraw_Grid_Brightness(void)
{
    Color_Init(&colorTypeGrid, false);
    BRIGHTNESS_GRID = (int16)(colorTypeGrid.brightness * 100.0f);
}

// ������� - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice cScaleYtype =
{
    Item_Choice, &pDisplay, 0,
    {
        "��������", "�ffset",
        "����� ����� ��������� �������� �� ���������\n1. \"����������\" - ����������� ��������� ��������.\n2. \"�������\" - ����������� ��������� "
        "�������� �� ������.",
        "Sets the mode of retaining the vertical displacement\n1. \"Voltage\" - saved dressing bias.\n2. \"Divisions\" - retained the position of "
        "the offset on the screen."
    },
    {
        {"����������", "Voltage"},
        {"�������", "Divisions"}
    },
    (int8 *)&LINKING_RSHIFT
};

// ������� - ��������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page ppSettings =
{
    Item_Page, &pDisplay, 0,
    {
        "���������", "SETTINGS",
        "�������������� ��������� �������",
        "Additional display settings"
    },
    Page_Display_Settings,
    {
        (void *)&pppSettings_Colors,            // ������� - ��������� - �����
        (void *)&gSettings_Brightness,          // ������� - ��������� - �������
        (void *)&gSettings_Levels,              // ������� - ��������� - ������
        (void *)&gSettings_Time,                // ������� - ��������� - �����
        (void *)&cSettings_StringNavigation,    // ������� - ��������� - ������ ����
        (void *)&cSettings_AltMarkers,          // ������� - ��������� - ���. �������
        (void *)&cSettings_AutoHide             // ������� - ��������� - ��������
    }
};

// ������� - ��������� - ����� -----------------------------------------------------------------------------------------------------------------------
/// \todo �������� �������������� ����� 1-�� � 2-�� �������
static const Page pppSettings_Colors =
{
    Item_Page, &ppSettings, 0,
    {
        "�����", "COLORS",
        "����� ������ �������",
        "The choice of colors display"
    },
    Page_Display_Settings_Colors,
    {
        (void *)&cSettings_Colors_Scheme,       // ������� - ��������� - ����� - �������� �����
        (void *)&gcSettings_Colors_ChannelA,    // ������� - ��������� - ����� - ����� 1
        (void *)&gcSettings_Colors_ChannelB,    // ������� - ��������� - ����� - ����� 2
        (void *)&gcSettings_Colors_Grid,        // ������� - ��������� - ����� - �����
        (void *)&cSettings_Colors_Background    // ������� - ��������� - ����� - ���
        //(void *)&mgcColorChannel0alt,
        //(void *)&mgcColorChannel1alt,
        //(void *)&mgcColorMenu1,
        //(void *)&mgcColorMenu2,
        //(void *)&mgcColorMenu3
        //,(void *)&mgcColorMathem,
        //(void *)&mgcColorFFT,
        //(void *)&mcServDisplInverse
    }
};

// ������� - ��������� - ����� - �������� ����� ------------------------------------------------------------------------------------------------------
static const Choice cSettings_Colors_Scheme =
{
    Item_Choice, &pppSettings_Colors, 0,
    {
        "�������� �����", "Color scheme",
        "����� ������ �����������",
        "Mode of operation of the calibrator"
    },
    {
        { "����� 1", "Scheme 1" },
        { "����� 2", "Scheme 2" }
    },
    (int8 *)&set.serv_ColorScheme
};

// ������� - ��������� - ����� - ����� 1 -------------------------------------------------------------------------------------------------------------
static ColorType colorT1 = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_DATA_1};
static const GovernorColor gcSettings_Colors_ChannelA =
{
    Item_GovernorColor, &pppSettings_Colors, 0,
    {
        "����� 1", "Channel 1",
        "",
        ""
    },
    &colorT1
};

// ������� - ��������� - ����� - ����� 2 -------------------------------------------------------------------------------------------------------------
static ColorType colorT2 = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_DATA_2};
static const GovernorColor gcSettings_Colors_ChannelB =
{
    Item_GovernorColor, &pppSettings_Colors, 0,
    {
        "����� 2", "Channel 2",
        "",
        ""
    },
    &colorT2
};

// ������� - ��������� - ����� - ����� ---------------------------------------------------------------------------------------------------------------
ColorType colorTypeGrid = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_GRID};
static const GovernorColor gcSettings_Colors_Grid =
{
    Item_GovernorColor, &pppSettings_Colors, 0,
    {
        "�����", "Grid",
        "������������� ���� �����",
        "Sets the grid color"
    },
    &colorTypeGrid
};

// ������� - ��������� - ����� - ��� -----------------------------------------------------------------------------------------------------------------
static const Choice cSettings_Colors_Background =
{
    Item_Choice, &pppSettings_Colors, 0,
    {
        "���", "Background",
        "����� ����� ����",
        "Choice of color of a background"
    },
    {
        { "׸����", "Black" },
        { "�����", "White" }
    },
    (int8 *)&BACKGROUND, OnChanged_Settings_Colors_Background
};

static void OnChanged_Settings_Colors_Background(bool active)
{
    PageService_InitGlobalColors();

    gcSettings_Colors_ChannelA.colorType->color = gColorChan[A];
    gcSettings_Colors_ChannelB.colorType->color = gColorChan[B];
    gcSettings_Colors_Grid.colorType->color = gColorGrid;

    Color_Init((ColorType*)&gcSettings_Colors_ChannelA, true);
    Color_Init((ColorType*)&gcSettings_Colors_ChannelB, true);
    Color_Init((ColorType*)&gcSettings_Colors_Grid, true);
}

void PageService_InitGlobalColors(void)
{
    gColorBack = BACKGROUND_BLACK ? COLOR_BLACK : COLOR_WHITE;
    gColorFill = BACKGROUND_BLACK ? COLOR_WHITE : COLOR_BLACK;
    gColorGrid = BACKGROUND_BLACK ? COLOR_GRID : COLOR_GRID_WHITE;
    gColorChan[A] = BACKGROUND_BLACK ? COLOR_DATA_1 : COLOR_DATA_A_WHITE_ACCUM;
    gColorChan[B] = BACKGROUND_BLACK ? COLOR_DATA_2 : COLOR_DATA_B_WHITE_ACCUM;
    gColorChan[A_B] = gColorChan[Math] = BACKGROUND_BLACK ? COLOR_WHITE : COLOR_BLACK;
}

// ������� - ��������� - ������� ---------------------------------------------------------------------------------------------------------------------
static const Governor gSettings_Brightness =
{
    Item_Governor, &ppSettings, 0,
    {
        "�������", "Brightness",
        "��������� ������� �������� �������",
        "Setting the brightness of the display"
    },
    &BRIGHTNESS_DISPLAY, 0, 100, OnChanged_Settings_Brightness
};

static void OnChanged_Settings_Brightness(void)
{
    Painter_SetBrightnessDisplay(BRIGHTNESS_DISPLAY);
}

// ������� - ��������� - ������ ----------------------------------------------------------------------------------------------------------------------
static const Governor gSettings_Levels =
{
    Item_Governor, &ppSettings, 0,
    {
        "������", "Levels",
        "����� �����, � ������� �������� ����� �������� ����� ������� ���������� �� ������ ������� ��������������� ����� ������ ��������",
        "Defines the time during which, after turning the handle visits to the voltage on the screen remains auxiliary label offset level"
    },
    &TIME_SHOW_LEVELS, 0, 125
};

// ������� - ��������� - ����� -----------------------------------------------------------------------------------------------------------------------
static const Governor gSettings_Time =
{
    Item_Governor, &ppSettings, 0,
    {
        "�����", "Time",
        "��������� �������, � ������� �������� ��������� ����� ���������� �� ������",
        "Set the time during which the message will be on the screen"
    },
    &TIME_MESSAGES, 1, 99
};

// ������� - ��������� - ������ ���� -----------------------------------------------------------------------------------------------------------------
static const Choice cSettings_StringNavigation =
{
    Item_Choice, &ppSettings, 0,
    {
        "������ ����", "Path menu",
        "��� ������ \n����������\n ����� ������ ������ ��������� ������ ���� �� ������� �������� ����", /// \todo ��������� �������
        "When choosing \nDisplay\n at the top left of the screen displays the full path to the current page menu"
    },
    {
        { "��������", "Temporary" },    /// \todo ��������� �������
        { "������", "All" },
        { "�������", "None" }
    },
    (int8 *)&SHOW_STRING_NAVI
};

// ������� - ��������� - ���. ������� ----------------------------------------------------------------------------------------------------------------
static const Choice cSettings_AltMarkers =
{
    Item_Choice, &ppSettings, 0,
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
    (int8 *)&ALT_MARKERS, Display_ChangedRShiftMarkers
};

// ������� - ��������� - �������� --------------------------------------------------------------------------------------------------------------------
static const Choice cSettings_AutoHide =
{
    Item_Choice, &ppSettings, 0,
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
    (int8 *)&MENU_AUTO_HIDE, OnChanged_Settings_AutoHide
};

static void OnChanged_Settings_AutoHide(bool autoHide)
{
    Menu_SetAutoHide(autoHide);
}



/*
//----------------------------------------------------------------------------------------------------------------------------------------------------
// ������ - ������� - ����� - ���� �������
static ColorType colorT6 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_MENU_FIELD };
const GovernorColor mgcColorMenu3 = { Item_GovernorColor, &pppSettings_Colors, { "���� �������", "Menu Field" },
{
    "",
    "",
},
0, &colorT6
};


//----------------------------------------------------------------------------------------------------------------------------------------------------
// ������ - ������� - ����� - ���� ���������
static ColorType colorT7 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_MENU_TITLE };
const GovernorColor mgcColorMenu1 = { Item_GovernorColor, &pppSettings_Colors, { "M��� ���������", "Menu Title" },
{
    "",
    ""
},
0, &colorT7, OnChangedColorMenuTitle
};


//----------------------------------------------------------------------------------------------------------------------------------------------------
// ������ - ������� - ����� - ���� �����
static ColorType colorT8 = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, COLOR_MENU_ITEM };
const GovernorColor mgcColorMenu2 = { Item_GovernorColor, &pppSettings_Colors, { "���� �����", "Menu Item" },
{
    "",
    ""
},
0, &colorT8, OnChangedColorMenu2Item
};


//----------------------------------------------------------------------------------------------------------------------------------------------------
// ������ - ������� - ����� - ��������
const Choice mcServDisplInverse =
{
    Item_Choice, &pppSettings_Colors, { "��������", "Inverse" },
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

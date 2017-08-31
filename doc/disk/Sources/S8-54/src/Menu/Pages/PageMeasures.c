// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Utils/Measures.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"
#include "Utils/GlobalFunctions.h"
#include "Menu/Pages/Definition.h"
#include "Hardware/Sound.h"
#include "FPGA/fpgaExtensions.h  "


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const    Page ppFreqMeter;                       ///< ��������� - ����������
static const   Choice cFreqMeter_Enable;                ///< ��������� - ���������� - ����������
static void  OnChanged_FreqMeter_Enable(bool param);    
static const   Choice cFreqMeter_TimeF;                 ///< ��������� - ���������� - ����� ����� F
static const   Choice cFreqMeter_FreqClc;               ///< ��������� - ���������� - ����� �������
static const   Choice cFreqMeter_NumPeriods;            ///< ��������� - ���������� - ���-�� ��������
static const   Choice cIsShow;                          ///< ��������� - ����������
static const   Choice cNumber;                          ///< ��������� - ����������
static bool   IsActive_Number(void);
static const   Choice cChannels;                        ///< ��������� - ������
static bool   IsActive_Channels(void);
static const    Page ppTune;                            ///< ��������� - ���������
static bool   IsActive_Tune(void);
static void   OnRegSet_Tune(int angle);
static const  SButton bTune_Exit;                       ///< ��������� - ��������� - �����
static const  SButton bTune_Markers;                    ///< ��������� - ��������� - �������
static void    OnPress_Tune_Markers(void);
static void       Draw_Tune_Markers(int x, int y);
static const  SButton bTune_Settings;                   ///< ��������� - ��������� - ���������
static void    OnPress_Tune_Settings(void);
static void  Draw_Tune_Settings(int x, int y);
static const   Choice cMode;                            ///< ��������� - ���
static bool   IsActive_Mode(void);

int8 posActive = 0;                 ///< ������� ��������� ��������� (�� ������� ������)
bool pageChoiceIsActive = false;    ///< ���� true - �������� �������� ������ ���������
int8 posOnPageChoice = 0;           ///< ������� ������� �� �������� ������ ���������

extern const Page mainPage;


// ��������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pMeasures =
{
    Item_Page, &mainPage, 0,
    {
        "���������", "MEASURES",
        "�������������� ���������",
        "Automatic measurements"
    },
    Page_Measures,
    {
        (void *)&ppFreqMeter,   // ��������� - ����������
        (void *)&cIsShow,       // ��������� - ����������
        (void *)&cNumber,       // ��������� - ����������
        (void *)&cChannels,     // ��������� - ������
        (void *)&ppTune,        // ��������� - ���������
        (void *)&cMode          // ��������� - ���
    }
};

// ��������� - ���������� ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page ppFreqMeter =
{
    Item_Page, &pMeasures, 0,
    {
        "����������", "FREQ METER",
        "",
        ""
    },
    Page_Service_FreqMeter,
    {
        (void *)&cFreqMeter_Enable,     // ��������� - ���������� - ����������
        (void *)&cFreqMeter_TimeF,      // ��������� - ���������� - ����� ����� F
        (void *)&cFreqMeter_FreqClc,    // ��������� - ���������� - ����� �������
        (void *)&cFreqMeter_NumPeriods  // ��������� - ���������� - ���-�� ��������
    }
};

// ��������� - ���������� - ���������� ---------------------------------------------------------------------------------------------------------------
static const Choice cFreqMeter_Enable =
{
    Item_Choice, &ppFreqMeter, 0,
    {
        "����������", "Freq meter",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&FREQ_METER_ENABLED, OnChanged_FreqMeter_Enable
};

static void OnChanged_FreqMeter_Enable(bool param)
{
    FreqMeter_Init();
}

// ��������� - ���������� - ����� ����� F ------------------------------------------------------------------------------------------------------------
static const Choice cFreqMeter_TimeF =
{
    Item_Choice, &ppFreqMeter, 0,
    {
        "����� ����� F", "Time calc F",
        "��������� ������� �������� ��������� ������� - ��� ������ �����, ��� ������ �������� � ������ ����� ���������",
        "Allows to choose the accuracy of measurement of frequency - the more time, the accuracy more time of measurement is more"
    },
    {
        {"100��", "100ms"},
        {"1�", "1s"},
        {"10�", "10ms"}
    },
    (int8 *)&FREQ_METER_TIMECOUNTING, OnChanged_FreqMeter_Enable
};

// ��������� - ���������� - ����� ������� ------------------------------------------------------------------------------------------------------------
static const Choice cFreqMeter_FreqClc =
{
    Item_Choice, &ppFreqMeter, 0,
    {
        "����� �������", "Timestamps",
        "����� ������� ���������� ������� ���������",
        "Choice of frequency of following of calculating impulses"
    },
    {
        {"100���", "10MHz"},
        {"1���", "200MHz"},
        {"10���", "10MHz"},
        {"100���", "100MHz"}
    },
    (int8 *)&FREQ_METER_FREQ_CLC, OnChanged_FreqMeter_Enable
};

// ��������� - ���������� - ���-�� �������� ----------------------------------------------------------------------------------------------------------
static const Choice cFreqMeter_NumPeriods =
{
    Item_Choice, &ppFreqMeter, 0,
    {
        "���-�� ��������", "Num periods",
        "��������� ������� �������� ��������� ������� - ��� ������ �����, ��� ������ �������� � ������ ����� ���������",
        "Allows to choose the accuracy of measurement of period - the more time, the accuracy more time of measurement is more"
    },
    {
        {"1", "1"},
        {"10", "10"},
        {"100", "100"}
    },
    (int8 *)&FREQ_METER_NUM_PERIODS, OnChanged_FreqMeter_Enable
};

// ��������� - ���������� ----------------------------------------------------------------------------------------------------------------------------
static const Choice cIsShow =
{
    Item_Choice, &pMeasures, 0,
    {
        "����������", "Show",
        "�������� ��� �� �������� ��������� �� �����",
        "Output or output measurements on screen"
    },
    {
        {"���", "No"},
        {"��", "Yes"}
    },
    (int8 *)&SHOW_MEASURES
};

// ��������� - ���������� ----------------------------------------------------------------------------------------------------------------------------
static const Choice cNumber =
{
    Item_Choice, &pMeasures, IsActive_Number,
    {
        "����������", "Number"
        ,
        "������������� ������������ ���������� ��������� ���������:\n"
        "\"1\" - ���� ���������\n"
        "\"2\" - ��� ���������\n"
        "\"1�5\" - 1 ������ � ����� �����������\n"
        "\"2�5\" - 2 ������ � ����� ����������� � ������\n"
        "\"3�5\" - 3 ������ � ����� ����������� � ������\n"
        "\"6x1\" - 6 ����� �� ������ ��������� � ������\n"
        "\"6�2\" - 6 ����� �� ��� ��������� � ������"
        ,
        "Sets the maximum number of output measurements:\n"
        "\"1\" - one measurement\n"
        "\"2\" - two measurements\n"
        "\"1x5\" - 1 line with the five dimensions\n"
        "\"2x5\" - two rows with five measurements in each\n"
        "\"3x5\" - 3 lines with five measurements in each"
        "\"6x1\" - 6 lines, one in each dimension\n"
        "\"6x2\" - 6 lines of two dimensions in each\n"
    },
    {
        {"1", "1"},
        {"2", "2"},
        {"1x5", "1x5"},
        {"2x5", "2x5"},
        {"3x5", "3x5"},
        {"6x1", "6x1"},
        {"6x2", "6x2"}
    },
    (int8 *)&NUM_MEASURES
};

static bool IsActive_Number(void)
{
    return SHOW_MEASURES;
}

// ��������� - ������ --------------------------------------------------------------------------------------------------------------------------------
static const Choice cChannels =
{
    Item_Choice, &pMeasures, IsActive_Channels,
    {
        "������", "Channels",
        "�� ����� ������� �������� ���������",
        "Which channels to output measurement"
    },
    {
        {"1", "1"},
        {"2", "2"},
        {"1 � 2", "1 and 2"}
    },
    (int8 *)&SOURCE_MEASURE
};

static bool IsActive_Channels(void)
{
    return SHOW_MEASURES;
}

// ��������� - ��� -----------------------------------------------------------------------------------------------------------------------------------
static const Choice cMode =
{
    Item_Choice, &pMeasures, IsActive_Mode,
    {
        "���", "View",
        "��������� ��� ��� ���� ������ ������� ��� ���������� ���������� ��� ���������� ���������",
        "Decrease or no zone output signal to avoid overlapping of its measurement results"
    },
    {
        {"��� ����",    "As is"},
        {"���������",   "Reduce"}
    },
    (int8 *)&set.meas_ModeViewSignals
};

static bool IsActive_Mode(void)
{
    return SHOW_MEASURES;
}


// ��������� - ��������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppTune =
{
    Item_Page, &pMeasures, IsActive_Tune,
    {
        "���������", "CONFIGURE",
        "������� � ����� ������ ��������� ���������� � ����� ���������",
        "Transition to rezhm of exact control of quantity and types of measurements"
    },
    PageSB_Measures_Tune,
    {
        (void *)&bTune_Exit,    // ��������� - ��������� - �����
        (void *)0,
        (void *)0,
        (void *)0,
        (void *)&bTune_Markers, // ��������� - ��������� - �������
        (void *)&bTune_Settings // ��������� - ��������� - ���������
    },
    true, 0, 0, OnRegSet_Tune
};

static bool IsActive_Tune(void)
{
    return SHOW_MEASURES;
}

static void OnRegSet_Tune(int angle)
{
    static const int8 step = 3;
    static int8 currentAngle = 0;
    currentAngle += (int8)angle;
    if (currentAngle < step && currentAngle > -step)
    {
        return;
    }
    if (pageChoiceIsActive)
    {
        posOnPageChoice += (int8)Math_Sign(currentAngle);
        Sound_RegulatorSwitchRotate();
        if (posOnPageChoice < 0)
        {
            posOnPageChoice = Measure_NumMeasures - 1;
        }
        else if (posOnPageChoice == Measure_NumMeasures)
        {
            posOnPageChoice = 0;
        }
        MEASURE(posActive) = (Measure)posOnPageChoice;
        Painter_ResetFlash();
    }
    else
    {
        int row = 0;
        int col = 0;
        Measure_GetActive(&row, &col);
        col += Math_Sign(currentAngle);
        if (col < 0)
        {
            col = Measure_NumCols() - 1;
            row--;
            if (row < 0)
            {
                row = Measure_NumRows() - 1;
            }
        }
        else if (col == Measure_NumCols())
        {
            col = 0;
            row++;
            if (row >= Measure_NumRows())
            {
                row = 0;
            }
        }
        Measure_SetActive(row, col);
        Sound_RegulatorSwitchRotate();
    }
    currentAngle = 0;
}

// ��������� - ��������� - ����� ---------------------------------------------------------------------------------------------------------------------
static const SButton bTune_Exit =
{
    Item_SmallButton, &ppTune,
    COMMON_BEGIN_SB_EXIT,
    OnPressSB_Exit,
    DrawSB_Exit
};

// ��������� - ��������� - ������� -------------------------------------------------------------------------------------------------------------------
static const SButton bTune_Markers =
{
    Item_SmallButton, &ppTune, 0,
    {
        "������", "Marker",
        "��������� ���������� ������� ��� ����������� �������� ���������",
        "Allows to establish markers for visual control of measurements"
    },
    OnPress_Tune_Markers,
    Draw_Tune_Markers
};

static void OnPress_Tune_Markers(void)
{
    Measure_ShortPressOnSmallButonMarker();
}

static void Draw_Tune_Markers(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x60');
    Painter_SetFont(TypeFont_8);
}

// ��������� - ��������� - ��������� -----------------------------------------------------------------------------------------------------------------
static const SButton bTune_Settings =
{
    Item_SmallButton, &ppTune, 0,
    {
        "���������", "Setup",
        "��������� ������� ����������� ���������",
        "Allows to choose necessary measurements"
    },
    OnPress_Tune_Settings,
    Draw_Tune_Settings
};

static void OnPress_Tune_Settings(void)
{
    pageChoiceIsActive = !pageChoiceIsActive;
    if (pageChoiceIsActive)
    {
        posOnPageChoice = MEASURE(posActive); //-V2006
    }
}

static void Draw_Tune_Settings(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x62');
    Painter_SetFont(TypeFont_8);
}

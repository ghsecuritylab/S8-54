// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Log.h"
#include "Data/DataBuffer.h"
#include "Display/Grid.h"
#include "Display/Symbols.h"
#include "FlashDrive/FlashDrive.h"
#include "FPGA/FPGA.h"
#include "Hardware/FLASH.h"
#include "Hardware/Sound.h"
#include "Menu/MenuDrawing.h"
#include "Menu/MenuFunctions.h"
#include "Menu/Pages/Definition.h"
#include "Settings/SettingsDebug.h"
#include "Utils/Debug.h"
#include "Utils/Dictionary.h"
#include "Utils/GlobalFunctions.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Page mainPage;
extern void LoadTShift(void);

static const     Page ppConsole;                            ///< ������� - �������
static const  Governor gConsole_NumStrings;                 ///< ������� - ������� - ������ ������
static const    Choice cConsole_SizeFont;                   ///< ������� - ������� - ������ ������
static const    Choice cConsole_ModeStop;                   ///< ������� - ������� - ���. ��������
static const    Page pppConsole_Registers;                  ///< ������� - ������� - ��������
static const    Choice cConsole_Registers_ShowAll;          ///< ������� - ������� - �������� - ���������� ���
static const    Choice cConsole_Registers_RD_FL;            ///< ������� - ������� - �������� - RD_FL
static bool    IsActive_Console_Registers(void);
static const    Choice cConsole_Registers_RShiftA;          ///< ������� - ������� - �������� - U ��. 1�
static const    Choice cConsole_Registers_RShiftB;          ///< ������� - ������� - �������� - U ��. 2�
static const    Choice cConsole_Registers_TrigLev;          ///< ������� - ������� - �������� - U �����.
static const    Choice cConsole_Registers_RangeA;           ///< ������� - ������� - �������� - �����/��� 1
static const    Choice cConsole_Registers_RangeB;           ///< ������� - ������� - �������� - �����/��� 2
static const    Choice cConsole_Registers_TrigParam;        ///< ������� - ������� - �������� - �����. �����.
static const    Choice cConsole_Registers_ChanParamA;       ///< ������� - ������� - �������� - �����. ���. 2
static const    Choice cConsole_Registers_ChanParamB;       ///< ������� - ������� - �������� - �����. ���. 2
static const    Choice cConsole_Registers_TBase;            ///< ������� - ������� - �������� - �����/���
static const    Choice cConsole_Registers_TShift;           ///< ������� - ������� - �������� - � ��.
static const    Button bConsole_SizeSettings;               ///< ������� - ������� - ������ ��������
static void        Draw_Console_SizeSettings(int x, int y); 
static const     Page ppADC;                                ///< ������� - ���
static const    Page pppADC_Balance;                        ///< ������� - ��� - ������
static const    Choice cADC_Balance_Mode;                   ///< ������� - ��� - ������ - �����
static void   OnChanged_ADC_Balance_Mode(bool active);
static void        Draw_ADC_Balance_Mode(int x, int y);
static const  Governor gADC_Balance_ShiftA;                 ///< ������� - ��� - ������ - �������� 1
static bool    IsActive_ADC_Balance_ShiftAB(void);
static void   OnChanged_ADC_Balance_ShiftA(void);
static const  Governor gADC_Balance_ShiftB;                 ///< ������� - ��� - ������ - �������� 2 
static void   OnChanged_ADC_Balance_ShiftB(void);
static const    Page pppADC_Stretch;                        ///< ������� - ��� - ��������
static const    Choice cADC_Stretch_Mode;                   ///< ������� - ��� - �������� - �����
       void   OnChanged_ADC_Stretch_Mode(bool active);
static const  Governor gADC_Stretch_A;                      ///< ������� - ��� - �������� - �������� 1�
static bool    IsActive_ADC_StretchAB(void);
static void   OnChanged_ADC_Stretch_A(void);
static const  Governor gADC_Stretch_B;                      ///< ������� - ��� - �������� - �������� 2�
static void   OnChanged_ADC_Stretch_B(void);
static const  Governor gADC_Stretch_Ak20mV;                 ///< ������� - ��� - �������� - 20��/1� 1�
static const  Governor gADC_Stretch_Ak50mV;                 ///< ������� - ��� - �������� - 50�� 1� 
static const  Governor gADC_Stretch_Ak100mV;                ///< ������� - ��� - �������� - 100��/5� 1�
static const  Governor gADC_Stretch_Ak2V;                   ///< ������� - A�� - �������� - 2� 1�
static const  Governor gADC_Stretch_Bk20mV;                 ///< ������� - ��� - �������� - 20��/1� 2�
static const  Governor gADC_Stretch_Bk50mV;                 ///< ������� - ��� - �������� - 50�� 2� 
static const  Governor gADC_Stretch_Bk100mV;                ///< ������� - ��� - �������� - 100��/5� 2�
static const  Governor gADC_Stretch_Bk2V;                   ///< ������� - ��� - �������� - 2� 2�
static const    Page pppADC_Shift;                          ///< ������� - ��� - ��� ����
static const    Button bADC_Shift_Reset;                    ///< ������� - ��� - ��� ���� - �����
static void     OnPress_ADC_Shift_Reset(void);
static const  Governor gADC_Shift_A2mV;                     ///< ������� - ��� - ��� ���� - �� 1� 2�� ����
static void   OnChanged_ADC_Shift_A(void);
static const  Governor gADC_Shift_B2mV;                     ///< ������� - ��� - ��� ���� - �� 2� 2�� ����
static void   OnChanged_ADC_Shift_B(void);
static const  Governor gADC_Shift_A5mV;                     ///< ������� - ��� - ��� ���� - �� 1� 5�� ����
static const  Governor gADC_Shift_B5mV;                     ///< ������� - ��� - ��� ���� - �� 2� 5�� ����
static const  Governor gADC_Shift_A10mV;                    ///< ������� - ��� - ��� ���� - �� 1� 10�� ����
static const  Governor gADC_Shift_B10mV;                    ///< ������� - ��� - ��� ���� - �� 2� 10�� ����
static const     Page ppRand;                               ///< ������� - ����-���
static const  Governor gRand_NumMeasures;                   ///< ������� - ����-��� - ���-�/������
static void   OnChanged_Rand_NumMeasures(void);
static const  Governor gRand_NumAverage;                    ///< ������� - ����-��� - ������.
static const  Governor gRand_NumSmooth;                     ///< ������� - ����-��� - �����������
static const    Choice cRand_ShowInfo;                      ///< ������� - ����-��� - ����������
static const    Choice gRand_ShowStat;                      ///< ������� - ����-��� - ����������
static const  Governor gRand_TimeCompensation;              ///< ������� - ����-��� - ����������� ��������
static void   OnChanged_Rand_TimeCompensation(void);
static const  Governor gRand_AddTimeShift;                  ///< ������� - ����-��� - ��������
static void   OnChanged_Rand_AddTimeShift(void);
static const  Governor gRand_Pretriggered;                  ///< ������� - ����-��� - ����������
static void   OnChanged_Rand_Pretriggered(void);
static const     Page ppChannels;                           ///< ������� - ������
static const    Choice cChannels_BandwidthA;                ///< ������� - ������ - ������ 1
static void   OnChanged_Channels_BandwidthA(bool active);
static const    Choice cChannels_BandwidthB;                ///< ������� - ������ - ������ 2
static void   OnChanged_Channels_BandwidthB(bool active);
static const    Choice cStats;                              ///< ������� - ����������
static const    Choice cDisplayOrientation;                 ///< ������� - ����������
       void   OnChanged_DisplayOrientation(bool);
static const    Choice cEMS;                                ///< ������� - ����� ���
static void   OnChanged_EMS(bool);
static const Governor mgPred;                               ///< ������� - ����������
static void   OnChanged_Pred(void);
static const Governor mgPost;                               ///< ������� - �����������
static void   OnChanged_Post(void);
static const     Page ppSettings;                           ///< ������� - ���������
static void     OnPress_Settings(void);
static const   SButton bSettings_Exit;                      ///< ������� - ��������� - �����
static void     OnPress_Settings_Exit(void);
static const    Button bSaveFirmware;                       ///< ������� - ����. ��������
static bool    IsActive_SaveFirmware(void);
static void     OnPress_SaveFirmware(void);
static const     Page ppSerialNumber;                       ///< ������� - �/�
static void     OnPress_SerialNumber(void);
static void        Draw_EnterSerialNumber(void);
static void    OnRegSet_SerialNumber(int);
static const   SButton bSerialNumber_Exit;                  ///< ������� - �/� - �����
static void     OnPress_SerialNumber_Exit(void);
static const   SButton bSerialNumber_Change;                ///< ������� - �/� - �������
static void     OnPress_SerialNumber_Change(void);
static void        Draw_SerialNumber_Change(int, int);
static const   SButton bSerialNumber_Save;                  ///< ������� - �/� - ���������
static void     OnPress_SerialNumber_Save(void);
static void        Draw_SerialNumber_Save(int, int);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// � ���� ��������� ����� ��������� ������ ��������� ������ ��� �������� �������� ppSerialNumer
typedef struct
{
    int number;     ///< ��������������, ���������� �����.
    int year;       ///< ��������������, ���.
    int curDigt;    ///< ��������������, ������� (0) ��� ����� (1) ��������� ����� ���������.
} StructForSN;


// ������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pDebug =
{
    Item_Page, &mainPage, 0,
    {
        "�������", "DEBUG",
        "", ""
    },
    Page_Debug,
    {
        (void *)&ppConsole,             // ������� - �������
        (void *)&ppADC,                 // ������� - ���
        (void *)&ppRand,			    // ������� - ����-���
        (void *)&ppChannels,		    // ������� - ������
        (void *)&cStats,			    // ������� - ����������
        (void *)&cDisplayOrientation,   // ������� - ����������
        (void *)&cEMS,                  // ������� - ����� ���
        (void *)&mgPred,			    // ������� - ����������
        (void *)&mgPost,			    // ������� - �����������
        (void *)&ppSettings,		    // ������� - ���������
        (void *)&bSaveFirmware,         // ������� - ����. ��������
        (void *)&ppSerialNumber         // ������� - �/�
    }
};

// ������� - ������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppConsole =
{
    Item_Page, &pDebug, 0,
    {
        "�������", "CONSOLE",
        "",
        ""
    },
    Page_Debug_Console,
    {
        (void *)&gConsole_NumStrings,   // ������� - ������� - ����� �����
        (void *)&cConsole_SizeFont,     // ������� - ������� - ������ ������
        (void *)&cConsole_ModeStop,     // ������� - ������� - ���. ��������
        (void *)&pppConsole_Registers,  // ������� - ������� - ��������
        (void *)&bConsole_SizeSettings  // ������� - ������� - ������ ��������

    }
};

// ������� - ������� - ����� ����� -------------------------------------------------------------------------------------------------------------------
static const Governor gConsole_NumStrings =
{
    Item_Governor, &ppConsole, 0,
    {
        "����� �����", "Number strings",
        "",
        ""
    },
    &CONSOLE_NUM_STRINGS, 0, 33
};

// ������� - ������� - ������ ������ -----------------------------------------------------------------------------------------------------------------
static const Choice cConsole_SizeFont =
{
    Item_Choice, &ppConsole, 0,
    {
        "������ ������", "Size font",
        "",
        ""
    },
    {
        {"5", "5"},
        {"8", "8"}
    },
    &set.dbg_SizeFont
};

// ������� - ������� - ���. �������� -----------------------------------------------------------------------------------------------------------------
static const Choice cConsole_ModeStop =
{
    Item_Choice, &ppConsole, 0,
    {
        "���. ��������", "Mode stop",
        "������������� ����������� ������������ ������ � ������� ���� ������� �� ������ ����/����",
        "It provides the ability to pause the output to the console by pressing the ����/���� button"
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&MODE_PAUSE_CONSOLE
};

// ������� - ������� - �������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page pppConsole_Registers =
{
    Item_Page, &ppConsole, 0,
    {
        "��������", "REGISTERS",
        "",
        ""
    },
    Page_Debug_Console_Registers,
    {
        (void *)&cConsole_Registers_ShowAll,    // ������� - ������� - �������� - ���������� ���
        (void *)&cConsole_Registers_RD_FL,      // ������� - ������� - �������� - RD_FL
        (void *)&cConsole_Registers_RShiftA,    // ������� - ������� - �������� - U ��. 1�
        (void *)&cConsole_Registers_RShiftB,    // ������� - ������� - �������� - U ��. 2�
        (void *)&cConsole_Registers_TrigLev,    // ������� - ������� - �������� - U �����
        (void *)&cConsole_Registers_RangeA,     // ������� - ������� - �������� - �����/��� 1
        (void *)&cConsole_Registers_RangeB,     // ������� - ������� - �������� - �����/��� 2
        (void *)&cConsole_Registers_TrigParam,  // ������� - ������� - �������� - �����. �����.
        (void *)&cConsole_Registers_ChanParamA, // ������� - ������� - �������� - �����. ���. 1
        (void *)&cConsole_Registers_ChanParamB, // ������� - ������� - �������� - �����. ���. 2
        (void *)&cConsole_Registers_TBase,      // ������� - ������� - �������� - �����/���
        (void *)&cConsole_Registers_TShift      // ������� - ������� - �������� - � ��.
    }
};

// ������� - ������� - �������� - ���������� ��� -----------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_ShowAll =
{
    Item_Choice, &pppConsole_Registers, 0,
    {
        "���������� ���", "Show all",
        "���������� ��� ��������, ���������� � ��������",
        "To show all values transferred in registers"
    },
    {
        {"���", "No"},
        {"��", "Yes"}
    },
    (int8 *)&DBG_SHOW_ALL
};

// ������� - ������� - �������� - RD_FL --------------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_RD_FL =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "RD_FL", "RD_FL",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&DBG_SHOW_FLAG
};

static bool IsActive_Console_Registers(void)
{
    return DBG_SHOW_ALL;
}

// ������� - ������� - �������� - U ��. 1� -----------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_RShiftA =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "U ��. 1�", "U shift 1ch",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowRShift[A]
};

// ������� - ������� - �������� - U ��. 2� -----------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_RShiftB =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "U ��. 2�", "U shift 2ch",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowRShift[B]
};

// ������� - ������� - �������� - U �����. -----------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_TrigLev =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "U �����.", "U trig.",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowTrigLev
};

// ������� - ������� - �������� - �����/��� 1 --------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_RangeA =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "�����/��� 1", "Range 1",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowRange[A]
};

// ������� - ������� - �������� - �����/��� 2 --------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_RangeB =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "�����/��� 2", "Range 2",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowRange[B]
};

// ������� - ������� - �������� - �����. �����. ------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_TrigParam =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "�����. �����.", "Trig param",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowTrigParam
};

// ������� - ������� - �������� - �����. ���. 2 ------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_ChanParamA =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "�����. ���. 1", "Chan 1 param",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowChanParam[A]
};

// ������� - ������� - �������� - �����. ���. 2 ------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_ChanParamB =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "�����. ���. 2", "Chan 2 param",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowChanParam[B]
};

// ������� - ������� - �������� - �����/��� ----------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_TBase =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "�����/���", "TBase",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowTBase
};

// ������� - ������� - �������� - � ��. --------------------------------------------------------------------------------------------------------------
static const Choice cConsole_Registers_TShift =
{
    Item_Choice, &pppConsole_Registers, IsActive_Console_Registers,
    {
        "� ��.", "tShift",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&set.dbg_ShowTShift
};

// ������� - ������� - ������ �������� ---------------------------------------------------------------------------------------------------------------
static const Button bConsole_SizeSettings =
{
    Item_Button, &ppConsole, 0,
    {
        "", "",
        "���������� ������� ������ ��������� ��� ���������� ��������",
        "Displays the current size of the structure to save settings"
    },
    0, Draw_Console_SizeSettings
};

static void Draw_Console_SizeSettings(int x, int y)
{
    char buffer[30];
    sprintf(buffer, "����.�����. %d", sizeof(Settings));
    Painter_DrawTextC(x + 6, y + 13, buffer, gColorBack);
}

// ������� - ��� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppADC =
{
    Item_Page, &pDebug, 0,
    {
        "���", "ADC",
        "",
        ""
    },
    Page_Debug_ADC,
    {
        (void *)&pppADC_Balance,    // ������� - ��� - ������
        (void *)&pppADC_Stretch,    // ������� - ��� - ��������
        (void *)&pppADC_Shift       // ������� - ��� - ��� ����
    }
};

// ������� - ��� - ������ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page pppADC_Balance =
{
    Item_Page, &ppADC, 0,
    {
        "������", "BALANCE",
        "",
        ""
    },
    Page_Debug_ADC_Balance,
    {
        (void *)&cADC_Balance_Mode,     // ������� - ��� - ������ - �����
        (void *)&gADC_Balance_ShiftA,   // ������� - ��� - ������ - �������� 1
        (void *)&gADC_Balance_ShiftB    // ������� - ��� - ������ - �������� 2
    }
};

// ������� - ��� - ������ - ����� --------------------------------------------------------------------------------------------------------------------
static const Choice cADC_Balance_Mode =
{
    Item_Choice, &pppADC_Balance, 0,
    {
        "�����", "Mode",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {"��������", "Real"},
        {"������", "Manual"}
    },
    (int8 *)&NRST_BALANCE_ADC_TYPE, OnChanged_ADC_Balance_Mode, Draw_ADC_Balance_Mode
};

static void OnChanged_ADC_Balance_Mode(bool active)
{
    Draw_ADC_Balance_Mode(0, 0);
}

static int16 shiftADCA;
static int16 shiftADCB;

static void Draw_ADC_Balance_Mode(int x, int y)
{
    int8 shift[2][3] =
    {
        {0, SET_BALANCE_ADC_A, (int8)NRST_BALANCE_ADC_A},
        {0, SET_BALANCE_ADC_B, (int8)NRST_BALANCE_ADC_B}
    };

    shiftADCA = shift[A][NRST_BALANCE_ADC_TYPE];
    shiftADCB = shift[B][NRST_BALANCE_ADC_TYPE];
}

// ������� - ��� - ������ - �������� 1 ---------------------------------------------------------------------------------------------------------------
static const Governor gADC_Balance_ShiftA =
{
    Item_Governor, &pppADC_Balance, IsActive_ADC_Balance_ShiftAB,
    {
        "�������� 1", "Offset 1",
        "",
        ""
    },
    &shiftADCA, -125, 125, OnChanged_ADC_Balance_ShiftA
};

static bool IsActive_ADC_Balance_ShiftAB(void)
{
    return NRST_BALANCE_ADC_TYPE_IS_HAND;
}

static void OnChanged_ADC_Balance_ShiftA(void)
{
    NRST_BALANCE_ADC_A = shiftADCA;
}

// ������� - ��� - ������ - �������� 2 ---------------------------------------------------------------------------------------------------------------
static const Governor gADC_Balance_ShiftB =
{
    Item_Governor, &pppADC_Balance, IsActive_ADC_Balance_ShiftAB,
    {
        "�������� 2", "Offset 2",
        "",
        ""
    },
    &shiftADCB, -125, 125, OnChanged_ADC_Balance_ShiftB
};

static void OnChanged_ADC_Balance_ShiftB(void)
{
    NRST_BALANCE_ADC_B = shiftADCB;
}

static const Choice emptyChoice;

// ������� - ��� - �������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page pppADC_Stretch =
{
    Item_Page, &ppADC, 0,
    {
        "��������", "STRETCH",
        "������������� ����� � �������� �������� (��� ������� ������)",
        "Sets mode and the value of stretching (manual mode)"
    },
    Page_Debug_ADC_Stretch,
    {
        (void *)&cADC_Stretch_Mode,     // ������� - ��� - �������� - �����
        (void *)&gADC_Stretch_A,        // ������� - ��� - �������� - �������� 1�
        (void *)&gADC_Stretch_B,        // ������� - ��� - �������� - �������� 2�
        (void *)&emptyChoice,
        (void *)&emptyChoice,
        (void *)&gADC_Stretch_Ak20mV,   // ������� - ��� - �������� - 20��/1� 1�
        (void *)&gADC_Stretch_Ak50mV,   // ������� - ��� - �������� - 50�� 1� 
        (void *)&gADC_Stretch_Ak100mV,  // ������� - ��� - �������� - 100��/5� 1�
        (void *)&gADC_Stretch_Ak2V,     // ������� - A�� - �������� - 2� 1�
        (void *)&emptyChoice,
        (void *)&gADC_Stretch_Bk20mV,   // ������� - ��� - �������� - 20��/1� 2�
        (void *)&gADC_Stretch_Bk50mV,   // ������� - ��� - �������� - 50�� 2� 
        (void *)&gADC_Stretch_Bk100mV,  // ������� - ��� - �������� - 100��/5� 2�
        (void *)&gADC_Stretch_Bk2V,     // ������� - ��� - �������� - 2� 2�
        (void *)&emptyChoice
    }
};


// ������� - ��� - �������� - ����� ------------------------------------------------------------------------------------------------------------------
static const Choice cADC_Stretch_Mode =
{
    Item_Choice, &pppADC_Stretch, 0,
    {
        "�����", "Mode",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {"��������", "Real"},
        {"������", "Manual"}
    },
    (int8 *)&NRST_STRETCH_ADC_TYPE, OnChanged_ADC_Stretch_Mode
};

static int16 stretchA;
static int16 stretchB;  

void OnChanged_ADC_Stretch_Mode(bool active)
{
    if (NRST_STRETCH_ADC_TYPE_IS_DISABLE)
    {
        stretchA = NRST_STRETCH_ADC_A(StretchADC_Disable) = 0;
        stretchB = NRST_STRETCH_ADC_B(StretchADC_Disable) = 0;
    }
    else
    {
        stretchA = NRST_STRETCH_ADC_A(NRST_STRETCH_ADC_TYPE);
        stretchB = NRST_STRETCH_ADC_B(NRST_STRETCH_ADC_TYPE);
    }
}

// ������� - ��� - �������� - �������� 1� ------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_A =
{
    Item_Governor, &pppADC_Stretch, IsActive_ADC_StretchAB,
    {
        "�������� 1�", "Stretch 1ch"
        ,
        "����� ������ �������� ������� ������.\n"
        "1 ������� = 0.0001"
        ,
        "Sets the manual stretching of the first channel.\n"
        "1 = 0.0001"
    },
    &stretchA, -10000, 10000, OnChanged_ADC_Stretch_A
};

static bool IsActive_ADC_StretchAB(void)
{
    return NRST_STRETCH_ADC_TYPE_IS_HAND;
}

static void OnChanged_ADC_Stretch_A(void)
{
    NRST_STRETCH_ADC_A(NRST_STRETCH_ADC_TYPE) = stretchA;
}

// ������� - ��� - �������� - �������� 2� ------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_B =
{
    Item_Governor, &pppADC_Stretch, IsActive_ADC_StretchAB,
    {
        "�������� 2�", "Stretch 2ch"
        ,
        "����� ������ �������� ������� ������.\n"
        "1 ������� = 0.0001"
        ,
        "Sets the manual stretching of the second channel.\n"
        "1 = 0.0001"
    },
    &stretchB, -10000, 10000, OnChanged_ADC_Stretch_B
};

static void OnChanged_ADC_Stretch_B(void)
{
    NRST_STRETCH_ADC_B(NRST_STRETCH_ADC_TYPE) = stretchB;
}

// ������� - ��� - �������� - 20��/1� 1� -------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_Ak20mV =
{
    Item_Governor, &pppADC_Stretch, 0,
    {
        "20��/1� 1�", "20mV/1V 1k",
        "",
        ""
    },
    &NRST_ADD_STRETCH_20mV_A, -10000, 10000
};

// ������� - ��� - �������� - 50�� 1� ----------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_Ak50mV =
{
    Item_Governor, &pppADC_Stretch, 0,
    {
        "50�� 1�", "50mV 1k",
        "",
        ""
    },
    &NRST_ADD_STRETCH_50mV_A, -10000, 10000
};

// ������� - ��� - �������� - 100��/5� 1� ------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_Ak100mV =
{
    Item_Governor, &pppADC_Stretch, 0,
    {
        "100��/5� 1�", "100mV/5V 1ch",
        "",
        ""
    },
    &NRST_ADD_STRETCH_100mV_A, -10000, 10000
};

// ������� - ��� - �������� - 2� 1� ------------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_Ak2V =
{
    Item_Governor, &pppADC_Stretch, 0,
    {
        "2� 1�", "2V 1ch",
        "",
        ""
    },
    &NRST_ADD_STRETCH_2V_A, -10000, 10000
};

// ������� - ��� - �������� - 20��/1� 2� -------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_Bk20mV =
{
    Item_Governor, &pppADC_Stretch, 0,
    {
        "20��/1� 2�", "20mV/1V 2k",
        "",
        ""
    },
    &NRST_ADD_STRETCH_20mV_B, -10000, 10000
};

// ������� - ��� - �������� - ��� ���� 50�� 2� -------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_Bk50mV =
{
    Item_Governor, &pppADC_Stretch, 0,
    {
        "50�� 2�", "50mV 2k",
        "",
        ""
    },
    &NRST_ADD_STRETCH_50mV_B, -10000, 10000
};

// ������� - ��� - �������� - 100��/5� 2� ------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_Bk100mV =
{
    Item_Governor, &pppADC_Stretch, 0,
    {
        "100��/5� 2�", "100mV/5V 2k",
        "",
        ""
    },
    &NRST_ADD_STRETCH_100mV_B, -10000, 10000
};

// ������� - ��� - �������� - 2� 2� ------------------------------------------------------------------------------------------------------------------
static const Governor gADC_Stretch_Bk2V =
{
    Item_Governor, &pppADC_Stretch, 0,
    {
        "2� 2�", "2V 2ch",
        "",
        ""
    },
    &NRST_ADD_STRETCH_2V_B, -10000, 10000
};

// ������� - ��� - ��� ���� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page pppADC_Shift =
{
    Item_Page, &ppADC, 0,
    {
        "��� ����", "ADD RSHFIT",
        "",
        ""
    },
    Page_Debug_ADC_Shift,
    {
        (void *)&bADC_Shift_Reset,  // ������� - ��� - ��� ���� - �����
        (void *)&gADC_Shift_A2mV,   // ������� - ��� - ��� ���� - �� 1� 2�� ����
        (void *)&gADC_Shift_B2mV,   // ������� - ��� - ��� ���� - �� 2� 2�� ����
        (void *)&gADC_Shift_A5mV,   // ������� - ��� - ��� ���� - �� 1� 5�� ����
        (void *)&gADC_Shift_B5mV,   // ������� - ��� - ��� ���� - �� 2� 5�� ����
        (void *)&gADC_Shift_A10mV,  // ������� - ��� - ��� ���� - �� 1� 10�� ����
        (void *)&gADC_Shift_B10mV   // ������� - ��� - ��� ���� - �� 2� 10�� ����
    }
};

// ������� - ��� - ��� ���� - ����� ------------------------------------------------------------------------------------------------------------------
static const Button bADC_Shift_Reset =
{
    Item_Button, &pppADC_Shift, 0,
    {
        "�����", "Reset",
        "",
        ""
    },
    OnPress_ADC_Shift_Reset
};

static void OnPress_ADC_Shift_Reset(void)
{
    for (int ch = 0; ch < 2; ch++)
    {
        for (int range = 0; range < 3; range++)
        {
            RSHIFT_ADD_STABLE(ch, range) = 0;
        }
    }
    FPGA_SetRShift(A, SET_RSHIFT_A);
    FPGA_SetRShift(B, SET_RSHIFT_B);
}

// ������� - ��� - ��� ���� - �� 1� 2�� ���� ---------------------------------------------------------------------------------------------------------
static const Governor gADC_Shift_A2mV =
{
    Item_Governor, &pppADC_Shift, 0,
    {
        "�� 1� 2�� ����", "Shift 1ch 2mV DC",
        "",
        ""
    },
    (int16 *)(&RSHIFT_ADD_STABLE_A(Range_2mV)), -100, 100, OnChanged_ADC_Shift_A
};

static void OnChanged_ADC_Shift_A(void)
{
    FPGA_SetRShift(A, SET_RSHIFT_A);

    //LOG_WRITE("2mv = %d, 5mV = %d, 10mV = %d", RSHIFT_ADD_STABLE(A, Range_2mV), RSHIFT_ADD_STABLE(A, Range_5mV), RSHIFT_ADD_STABLE(A, Range_10mV));
}

// ������� - ��� - ��� ���� - �� 2� 2�� ���� ---------------------------------------------------------------------------------------------------------
static const Governor gADC_Shift_B2mV =
{
    Item_Governor, &pppADC_Shift, 0,
    {
        "�� 2� 2�� ����", "Shift 2ch 2mV DC",
        "",
        ""
    },
    (int16 *)(&RSHIFT_ADD_STABLE_B(Range_2mV)), -100, 100, OnChanged_ADC_Shift_B
};

static void OnChanged_ADC_Shift_B(void)
{
    FPGA_SetRShift(B, SET_RSHIFT_B);
}

// ������� - ��� - ��� ���� - �� 1� 5�� ���� ---------------------------------------------------------------------------------------------------------
static const Governor gADC_Shift_A5mV =
{
    Item_Governor, &pppADC_Shift, 0,
    {
        "�� 1� 5�� ����", "Shift 1ch 5mV DC",
        "",
        ""
    },
    (int16 *)(&RSHIFT_ADD_STABLE_A(Range_5mV)), -100, 100, OnChanged_ADC_Shift_A
};

// ������� - ��� - ��� ���� - �� 2� 5�� ���� ---------------------------------------------------------------------------------------------------------
static const Governor gADC_Shift_B5mV =
{
    Item_Governor, &pppADC_Shift, 0,
    {
        "�� 2� 5�� ����", "Shift 2ch 5mV DC",
        "",
        ""
    },
    (int16 *)(&RSHIFT_ADD_STABLE_B(Range_5mV)), -100, 100, OnChanged_ADC_Shift_B
};

// ������� - ��� - ��� ���� - �� 1� 10�� ���� --------------------------------------------------------------------------------------------------------
static const Governor gADC_Shift_A10mV =
{
    Item_Governor, &pppADC_Shift, 0,
    {
        "�� 1� 10�� ����", "Shift 1ch 10mV DC",
        "",
        ""
    },
    (int16 *)(&RSHIFT_ADD_STABLE_A(Range_10mV)), -100, 100, OnChanged_ADC_Shift_A
};

// ������� - ��� - ��� ���� - �� 2� 10�� ���� --------------------------------------------------------------------------------------------------------
static const Governor gADC_Shift_B10mV =
{
    Item_Governor, &pppADC_Shift, 0,
    {
        "�� 2� 10�� ����", "Shift 2ch 10mV DC",
        "",
        ""
    },
    (int16 *)(&RSHIFT_ADD_STABLE_B(Range_10mV)), -100, 100, OnChanged_ADC_Shift_B
};

// ������� - ����-��� ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppRand =
{
    Item_Page, &pDebug, 0,
    {
        "����-���", "RANDOMIZER",
        "",
        ""
    },
    Page_Debug_Rand,
    {
        (void *)&gRand_NumAverage,          // ������� - ����-��� - ������.
        (void *)&gRand_NumSmooth,           // ������� - ����-��� - �����������
        (void *)&gRand_NumMeasures,         // ������� - ����-��� - ���-�/������
        (void *)&cRand_ShowInfo,            // ������� - ����-��� - ����������
        (void *)&gRand_ShowStat,            // ������� - ����-��� - ����������
        (void *)&gRand_TimeCompensation,    // ������� - ����-��� - ����������� ��������
        (void *)&gRand_AddTimeShift,        // ������� - ����-��� - ��������
        (void *)&gRand_Pretriggered         // ������� - �A��-��� - ����������
    }
};

// ������� - ������ //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppChannels =
{
    Item_Page, &pDebug, 0,
    {
        "������", "CHANNELS",
        "",
        ""
    },
    Page_Debug_Channels,
    {
        (void *)&cChannels_BandwidthA,  // ������� - ������ - ������ 1
        (void *)&cChannels_BandwidthB   // ������� - ������ - ������ 2
    }
};

// ������� - ������ - ������ 1 -----------------------------------------------------------------------------------------------------------------------
static const Choice cChannels_BandwidthA =
{
    Item_Choice, &ppChannels, 0,
    {
        "������ 1", "Bandwidth 1",
        "����� ����� ������� ������, ������� ����� ����������� � �����1-������ ��� ������ �������� ������",
        "Here you can select the bandwidth, which will operate in CHANNEL1-Bandwidth when set to Full"
    },
    {
        {"������", "Full"},
        {"20���", "20MHz"},
        {"100���", "100MHz"},
        {"200���", "200MHz"},
        {"350���", "350MHz"},
        {"650���", "650MHz"},
        {"750���", "750MHz"}
    },
    (int8 *)&BANDWIDTH_DEBUG(A), OnChanged_Channels_BandwidthA
};

static void OnChanged_Channels_BandwidthA(bool active)
{
    FPGA_SetBandwidth(A);
}

// ������� - ������ - ������ 1 -----------------------------------------------------------------------------------------------------------------------
static const Choice cChannels_BandwidthB =
{
    Item_Choice, &ppChannels, 0,
    {
        "������ 2", "Bandwidth 2",
        "����� ����� ������� ������, ������� ����� ����������� � �����2-������ ��� ������ �������� ������",
        "Here you can select the bandwidth, which will operate in CHANNEL2-Bandwidth when set to Full"
    },
    {
        {"������", "Full"},
        {"20���", "20MHz"},
        {"100���", "100MHz"},
        {"200���", "200MHz"},
        {"350���", "350MHz"},
        {"650���", "650MHz"},
        {"750���", "750MHz"}
    },
    (int8 *)&BANDWIDTH_DEBUG(B), OnChanged_Channels_BandwidthB
};

static void OnChanged_Channels_BandwidthB(bool active)
{
    FPGA_SetBandwidth(B);
}

// ������� - ����-��� - ���-�/������ -----------------------------------------------------------------------------------------------------------------
static const Governor gRand_NumMeasures =
{
    Item_Governor, &ppRand, 0,
    {
        "���-�/������", "Samples/gates",
        "",
        ""
    },
    &NUM_MEASURES_FOR_GATES, 1, 2500, OnChanged_Rand_NumMeasures
};

static void OnChanged_Rand_NumMeasures(void)
{
    FPGA_SetNumberMeasuresForGates(NUM_MEASURES_FOR_GATES);
}

// ������� - ����-��� - ����������� �������� ---------------------------------------------------------------------------------------------------------
static const Governor gRand_TimeCompensation =
{
    Item_Governor, &ppRand, 0,
    {
        "����������� ��������", "Compenstaion time",
        "���������� ����������� �������� ��� 40 ��",
        ""
    },
    &TIME_COMPENSATION, 0, 510, OnChanged_Rand_TimeCompensation
};

static void OnChanged_Rand_TimeCompensation(void)
{
    FPGA_SetDeltaTShift(TIME_COMPENSATION);
}

// ������� - ����-��� - �������� ---------------------------------------------------------------------------------------------------------------------
int16 addShift = 0;

static const Governor gRand_AddTimeShift =
{
    Item_Governor, &ppRand, 0,
    {
        "��� ��������", "Add shift",
        "���������� ������� ��� �������� tShift",
        ""
    },
    &addShift, -100, 100, OnChanged_Rand_AddTimeShift
};

static void OnChanged_Rand_AddTimeShift(void)
{
    FPGA_SetTShift(SET_TSHIFT);
}

// ������� - ����-��� - ���������� -------------------------------------------------------------------------------------------------------------------
static const Governor gRand_Pretriggered =
{
    Item_Governor, &ppRand, 0,
    {
        "����������", "Pretiggered",
        "�������� �����������, ������� ������� � ������������",
        ""
    },
    &PRETRIGGERED, 0, 30000, OnChanged_Rand_Pretriggered
};

static void OnChanged_Rand_Pretriggered(void)
{
    LoadTShift();
}

// ������� - ����-��� - ������. ----------------------------------------------------------------------------------------------------------------------
static const Governor gRand_NumAverage =
{
    Item_Governor, &ppRand, 0,
    {
        "������.", "Average",
        "",
        ""
    },
    &NRST_NUM_AVE_FOR_RAND, 1, 32
};

// ������� - ����-��� - ����������� ------------------------------------------------------------------------------------------------------------------
static const Governor gRand_NumSmooth =
{
    Item_Governor, &ppRand, 0,
    {
        "�����������", "Smoothing",
        "",
        ""
    },
    &NRST_NUM_SMOOTH_FOR_RAND, 1, 10
};

static int16 pred;
static int16 post;

// ������� - ���������� ------------------------------------------------------------------------------------------------------------------------------
static const Governor mgPred =
{
    Item_Governor, &pDebug, 0,
    {
        "����������", "",
        "", ""
    },
    &pred, 0, 15000, OnChanged_Pred
};

// ������� - ����������� -----------------------------------------------------------------------------------------------------------------------------
static const Governor mgPost =
{
    Item_Governor, &pDebug, 0,
    {
        "�����������", "",
        "", ""
    },
    &post, 0, 15000, OnChanged_Post
};


// ������� - ��������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppSettings =
{
    Item_Page, &pDebug, 0,
    {
        "���������", "SETTINGS",
        "�������� ���������� � ����������",
        "Show settings information"
    },
    PageSB_Debug_Settings,
    {
        (void *)&bSettings_Exit     // ������� - ��������� - �����
    },
    true, OnPress_Settings
};

// ������� - ��������� - ����� -----------------------------------------------------------------------------------------------------------------------
static const SButton bSettings_Exit =
{
    Item_SmallButton, &ppSettings,
    COMMON_BEGIN_SB_EXIT,
    OnPress_Settings_Exit,
    DrawSB_Exit
};

static void OnPress_Settings_Exit(void)
{
    Display_SetDrawMode(DrawMode_Auto, 0);
}

static void DebugShowSetInfo_Draw(void)
{
    Painter_BeginScene(gColorBack);
    Painter_DrawRectangleC(0, 0, 319, 239, gColorFill);

    int x0 = 30;
    int y0 = 25;
    int dY = 10;
    int y = y0 - dY;

#define Y_AND_INCREASE (y += dY, y)
#define DRAW_TEXT(str)                  Painter_DrawText(x0, Y_AND_INCREASE, str);
#define DRAW_FORMAT(str, value)         Painter_DrawFormatText(x0, Y_AND_INCREASE, str, value)
#define DRAW_FORMAT2(str, val1, val2)   Painter_DrawFormatText(x0, Y_AND_INCREASE, str, val1, val2);

    //Painter_DrawFormatText(x0, Y_AND_INCREASE, "������ �������� ��������� %d", sizeof(set));
    DRAW_FORMAT("������ �������� ��������� : %d", sizeof(set));
    Painter_DrawText(x0, Y_AND_INCREASE, "�������������� ���������:");
    int x = Painter_DrawText(x0, Y_AND_INCREASE, "rShiftAdd :") + 5;

    int ddY = 0;

    for (int type = 0; type < 2; type++)
    {
        for (int ch = 0; ch < 2; ch++)
        {
            for (int range = 0; range < RangeSize; range++)
            {
                Painter_DrawFormatText(x + range * 20, y + dY * ddY, "%d", NRST_RSHIFT_ADD(ch, range, type));
            }
            ddY++;
        }
    }

    y += dY * 3;

    DRAW_FORMAT("correctionTime : %d", NRST_CORRECTION_TIME);
    DRAW_FORMAT2("balanceADC : %d %d", NRST_BALANCE_ADC_A, NRST_BALANCE_ADC_B);
    DRAW_FORMAT("numAveForRand : %d", NRST_NUM_AVE_FOR_RAND);

    const char * const s[3] = {"���������", "��������� �������������", "������ �������"};
    DRAW_FORMAT("balanceADCtype : %s", (NRST_BALANCE_ADC_TYPE < 3 ? s[NRST_BALANCE_ADC_TYPE] : "!!! ������������ �������� !!!"));
    DRAW_FORMAT("stretchADCtype : %s", (NRST_STRETCH_ADC_TYPE < 3 ? s[NRST_STRETCH_ADC_TYPE] : "!!! ������������ �������� !!!"));
  
    x = Painter_DrawText(x0, Y_AND_INCREASE, "stretchADC :") + 5;

    for (int ch = 0; ch < 2; ch++)
    {
        for (int num = 0; num < 3; num++)
        {
            Painter_DrawFormatText(x + num * 20, y + dY * ch, "%d", NRST_STRETCH_ADC(ch, num));
        }
    }

    y += dY;

#define DRAW_STRETCH(name) DRAW_FORMAT2(#name " : %d %d", set.nrst_##name[0], set.nrst_##name[1])

    DRAW_STRETCH(AddStretch20mV);
    DRAW_STRETCH(AddStretch50mV);
    DRAW_STRETCH(AddStretch100mV);
    DRAW_STRETCH(AddStretch2V);

    DRAW_FORMAT("numSmoothForRand : %d", NRST_NUM_SMOOTH_FOR_RAND);

    Menu_Draw();
    Painter_EndScene();
}

static void OnPress_Settings(void)
{
    Display_SetDrawMode(DrawMode_Auto, DebugShowSetInfo_Draw);
}

static void OnChanged_Pred(void)
{
    gPred = ~pred;
    static char buffer[30];
    LOG_WRITE("pred %d %s", pred, Hex16toString(gPred, buffer, true));
}

static void OnChanged_Post(void)
{
    gPost = ~post;
    static char buffer[30];
    LOG_WRITE("post %d %s", post, Hex16toString(gPost, buffer, true));
}

// ������� - ����-��� - ���������� -------------------------------------------------------------------------------------------------------------------
static const Choice cRand_ShowInfo =
{
    Item_Choice, &ppRand, 0,
    {
        "����������", "Information",
        "���������� ���������� � ������� �������������",
        "To show information on randomizer gate"
    },
    {
        {"�� ����������", "Hide"},
        {"����������", "Show"}
    },
    (int8 *)&SHOW_RAND_INFO
};

// ������� - ����-��� - ���������� -------------------------------------------------------------------------------------------------------------------
static const Choice gRand_ShowStat =
{
    Item_Choice, &ppRand, 0,
    {
        "����������", "Statistics",
        "���������� ������ ����������",
        "Statistics show schedule"
    },
    {
        {"�� ����������",   "Hide"},
        {"����������",      "Show"}
    },
    (int8 *)&SHOW_RAND_STAT
};

// ������� - ����� ��� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Choice cEMS =
{
    Item_Choice, &pDebug, 0,
    {
        "����� ���", "EMS mode",
        "������������� �������� ������ 20���, ����������� �� 4-� ������, ���������� �� 8-�� ������",
        ""
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8 *)&MODE_EMS, OnChanged_EMS
};

static void OnChanged_EMS(bool active)
{
    FPGA_SetBandwidth(A);
    FPGA_SetBandwidth(B);
}

// ������� - ���������� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Choice cDisplayOrientation =
{
    Item_Choice, &pDebug, 0,
    {
        "����������", "DisplayOrientation",
        "������������� ���������� �������",
        "Sets display orientation"
    },
    {
        { "������", "Direct" },
        { "��������", "Back" }
    },
    (int8 *)&DISPLAY_ORIENTATION, OnChanged_DisplayOrientation
};

void OnChanged_DisplayOrientation(bool active)
{
    Display_SetOrientation(DISPLAY_ORIENTATION);
}

// ������� - ���������� ------------------------------------------------------------------------------------------------------------------------------
static const Choice cStats =
{
    Item_Choice, &pDebug, 0,
    {
        "����������", "Statistics",
        "����������/�� ���������� �����/����, ������ � �������, ���������� �������� � ���������� ����������� � ������/���������� ����������� � ������ ��������",
        "To show/not to show a time/shot, frames per second, quantity of signals with the last settings in memory/quantity of the signals kept in memory"
    },
    {
        {"�� ����������",   "Hide"},
        {"����������",      "Show"}
    },
    (int8 *)&SHOW_STAT
};

// ������� - ����. �������� --------------------------------------------------------------------------------------------------------------------------
static const Button bSaveFirmware =
{
    Item_Button, &pDebug, IsActive_SaveFirmware,
    {
        "����. ��������", "Save firmware",
        "���������� �������� - �������� 5, 6, 7 ����� ������� 3 � 128 ��, ��� �������� ���������",
        "Saving firmware - sectors 5, 6, 7 with a total size of 3 x 128 kB, where the program is stored"
    },
    OnPress_SaveFirmware
};

static bool IsActive_SaveFirmware(void)
{
    return FDRIVE_IS_CONNECTED;
}

static void OnPress_SaveFirmware(void)
{
    Display_FuncOnWaitStart(DICT(DSaveFirmware), false);

    StructForWrite structForWrite;

    FDrive_OpenNewFileForWrite("S8-54.bin", &structForWrite);

    uint8 *address = (uint8 *)0x08020000;
    uint8 *endAddress = address + 128 * 1024 * 3;

    int sizeBlock = 512;

    while (address < endAddress)
    {
        FDrive_WriteToFile(address, sizeBlock, &structForWrite);
        address += sizeBlock;
    }

    FDrive_CloseFile(&structForWrite);

    Display_FuncOnWaitStop();

    Display_ShowWarning(FirmwareSaved);
}

// ������� - �/� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppSerialNumber =
{
    Item_Page, &pDebug, 0,
    {
        "�/�", "S/N",
        "������ ��������� ������ � OTP-������. ��������!!! ��P-������ - ������ � ����������� �������.",
        "Serial number recording in OTP-memory. ATTENTION!!! OTP memory is a one-time programming memory."
    },
    PageSB_Debug_SerialNumber,
    {
        (void *)&bSerialNumber_Exit,    // ������� - �/� - �����
        (void *)&bSerialNumber_Change,  // ������� - �/� - �������
        (void *)0,
        (void *)0,
        (void *)0,
        (void *)&bSerialNumber_Save     // ������� - �/� - ���������
    },
    true, OnPress_SerialNumber, 0, OnRegSet_SerialNumber
};

static void OnPress_SerialNumber(void)
{
    Display_SetAddDrawFunction(Draw_EnterSerialNumber);
    MALLOC_EXTRAMEM(StructForSN, s);
    s->number = 01;
    s->year = 2017;
    s->curDigt = 0;
}

static void Draw_EnterSerialNumber(void)
{
    int x0 = GridLeft() + 40;
    int y0 = GRID_TOP + 20;
    int width = GridWidth() - 80;
    int height = 160;

    Painter_DrawRectangleC(x0, y0, width, height, gColorFill);
    Painter_FillRegionC(x0 + 1, y0 + 1, width - 2, height - 2, gColorBack);

    int deltaX = 10;

    ACCESS_EXTRAMEM(StructForSN, s);
    
    bool selNumber = s->curDigt == 0;

    char buffer[20];
    snprintf(buffer, 19, "%02d", s->number);

    Color colorText = gColorFill;
    Color colorBackground = gColorBack;

    if (selNumber)
    {
        colorText = COLOR_FLASH_01;
        colorBackground = COLOR_FLASH_10;
    }

    int y = y0 + 50;

    Painter_SetColor(colorText);
    int x = Painter_DrawTextOnBackground(x0 + deltaX, y, buffer, colorBackground);

    colorText = COLOR_FLASH_01;
    colorBackground = COLOR_FLASH_10;

    if (selNumber)
    {
        colorText = gColorFill;
        colorBackground = gColorBack;
    }

    snprintf(buffer, 19, "%04d", s->year);

    Painter_SetColor(colorText);
    Painter_DrawTextOnBackground(x + 5, y, buffer, colorBackground);

    // ������ ������� ���������� �� ���������� ����� � OTP-������ ��� ������

    int allShots = OTP_GetSerialNumber(buffer);

    Painter_DrawFormText(x0 + deltaX, y0 + 130, gColorFill, "������� ���������� ����� %s", buffer[0] == 0 ? "-- ----" : buffer);

    Painter_DrawFormText(x0 + deltaX, y0 + 100, gColorFill, "�������� ����� ��� %d �������", allShots);
}

static void OnRegSet_SerialNumber(int angle)
{
    typedef int (*pFunc)(int *, int, int);

    pFunc p = angle > 0 ? CircleIncreaseInt : CircleDecreaseInt;

    ACCESS_EXTRAMEM(StructForSN, s);

    if (s->curDigt == 0)
    {
        p(&s->number, 1, 99);
    }
    else
    {
        p(&s->year, 2016, 2050);
    }
    Sound_GovernorChangedValue();
}

// ������� - �/� - ����� -----------------------------------------------------------------------------------------------------------------------------
static const SButton bSerialNumber_Exit =
{
    Item_SmallButton, &ppSerialNumber,
    COMMON_BEGIN_SB_EXIT,
    OnPress_SerialNumber_Exit,
    DrawSB_Exit
};

static void OnPress_SerialNumber_Exit(void)
{
    OnPressSB_Exit();
    FREE_EXTRAMEM();
}

// ������� - �/� - �������� --------------------------------------------------------------------------------------------------------------------------
static const SButton bSerialNumber_Change =
{
    Item_SmallButton, &ppSerialNumber, 0,
    {
        "��������", "Insert",
        "��������� �������� ������",
        "Inserts the chosen symbol"
    },
    OnPress_SerialNumber_Change,
    Draw_SerialNumber_Change
};

static void OnPress_SerialNumber_Change(void)
{
    ACCESS_EXTRAMEM(StructForSN, s);
    ++s->curDigt;
    s->curDigt %= 2;
    Painter_ResetFlash();
}

static void Draw_SerialNumber_Change(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, SYMBOL_TAB);
    Painter_SetFont(TypeFont_8);
}

// ������� - �/� - ��������� -------------------------------------------------------------------------------------------------------------------------
static const SButton bSerialNumber_Save =
{
    Item_SmallButton, &ppSerialNumber, 0,
    {
        "���������", "Save",
        "���������� �������� ����� � OTP",
        "Records the serial number in OTP"
    },
    OnPress_SerialNumber_Save,
    Draw_SerialNumber_Save
};

static void OnPress_SerialNumber_Save(void)
{
    ACCESS_EXTRAMEM(StructForSN, s);

    char stringSN[20];

    snprintf(stringSN, 19, "%02d %04d", s->number, s->year);

    if (!OTP_SaveSerialNumber(stringSN))
    {
        Display_ShowWarning(FullyCompletedOTP);
    }
}

static void Draw_SerialNumber_Save(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_SAVE_TO_MEM);
    Painter_SetFont(TypeFont_8);
}


































/*
void OnPressDebugDisable(void)
{
    ShowMenu(false);
    SetMenuPageDebugActive(false);
    SetMenuPosActItem(Page_Main, 0);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void OnDegubConsoleViewChanged(bool active)
{
    Display_SetPauseForConsole(CONSOLE_IN_PAUSE);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void OnPressDebugConsoleUp(void)
{
    Display_OneStringUp();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void OnPressDebugConsoleDown(void)
{
    Display_OneStringDown();
}

        /// ������� - ��� - ���. ����. ���. - ��������
        const Governor mgDebugADCaltShift =
        {
            Item_Governor, &mspDebugADCaltShift,
            {
                "��������", "Value"
            },
            {
                "",
                ""
            },
            0,
            &set.debug.altShift, -2, 2, 0
        };

bool sIsShowReg_RShift1(void)
{
    return set.debug.showRegisters.rShiftB || set.debug.showRegisters.all;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sIsShowReg_TrigLev(void)
{
    return set.debug.showRegisters.trigLev || set.debug.showRegisters.all;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sIsShowReg_Range(Channel ch)
{
    return set.debug.showRegisters.range[ch] || set.debug.showRegisters.all;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sIsShowReg_TrigParam(void)
{
    return set.debug.showRegisters.trigParam || set.debug.showRegisters.all;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sIsShowReg_ChanParam(Channel ch)
{
    return set.debug.showRegisters.chanParam[ch] || set.debug.showRegisters.all;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sIsShowReg_TShift(void)
{
    return set.debug.showRegisters.tShift || set.debug.showRegisters.all;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sIsShowReg_TBase(void)
{
    return set.debug.showRegisters.tBase || set.debug.showRegisters.all;
}


const Page mspDebugADCaltShift =    // ������� - ��� - ��� ���� ���
{
    Item_Page, &ppADC,
    {
        "��� ���� ���", "ALT SHIFT MEM"
    },
    {
        "",
        ""
    },
    0, Page_Debug_ADC_AltShift,
    {
        (void *)&mgDebugADCaltShift
    }
};
*/

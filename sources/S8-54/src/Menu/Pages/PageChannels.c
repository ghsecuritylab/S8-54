// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "Display/Display.h"
#include "FPGA/fpga.h"
#include "FPGA/fpgaExtensions.h"
#include "Log.h"
#include "Menu/MenuItems.h"
#include "Panel/Panel.h"
#include "Settings/Settings.h"
#include "Settings/SettingsTypes.h"
#include "Utils/GlobalFunctions.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const  Choice cChanA_Input;                      ///< ����� 1 - ����
       void OnChanged_ChanA_Input(bool active);
static const  Choice cChanA_Couple;                     ///< ����� 1 - �����
static void OnChanged_ChanA_Couple(bool active);
static const  Choice cChanA_Bandwidth;                  ///< ����� 1 - ������
static void OnChanged_ChanA_Bandwidth(bool active);
static const  Choice cChanA_Resistance;                 ///< ����� 1 - �� ����
static void OnChanged_ChanA_Resistance(bool active);
static const  Choice cChanA_Inverse;                    ///< ����� 1 - ��������
static void OnChanged_ChanA_Inverse(bool active);
static const Choice cChanA_Divider;                     ///< ����� 1 - ��������
static const Button bChanA_Balance;                     ///< ����� 1 - �������������
static void OnPress_ChanA_Balance(void);
static const Choice cChanB_Input;
static bool IsActive_ChanB_Input(void);
      void OnChanged_ChanB_Input(bool active);
static const Choice cChanB_Couple;
static void OnChanged_ChanB_Couple(bool active);
static const Choice cChanB_Bandwidth;
static void OnChanged_ChanB_Bandwidth(bool active);
static const Choice cChanB_Resistance;
static void OnChanged_ChanB_Resistance(bool active);
static const Choice cChanB_Inverse;
static void OnChanged_ChanB_Inverse(bool active);
static const Choice cChanB_Divider;
static const Button bChanB_Balance;
static void OnPress_ChanB_Balance(void);


//----------------------------------------------------------------------------------------------------------------------------------------------------
static const char chanInputRu[] =   "1. \"���\" - �������� ������ �� �����.\n"
                                    "2. \"����\" - �� �������� ������ �� �����.";
static const char chanInputEn[] =   "1. \"Enable\" - signal output to the screen.\n"
                                    "2. \"Disable\" - no output to the screen.";

static const char chanCoupleRu[] =  "����� ��� ����� � ���������� �������.\n"
                                    "1. \"����\" - �������� ����.\n"
                                    "2. \"�����\" - �������� ����.\n"
                                    "3. \"�����\" - ���� ������� � �����.";
static const char chanCoupleEn[] =  "Sets a type of communication with a signal source.\n"
                                    "1. \"AC\" - open input.\n"
                                    "2. \"DC\" - closed input.\n"
                                    "3. \"Ground\" - input is connected to the ground.";

static const char chanInverseRu[] = "��� \"���\" ������ �� ������ ����� ����������� ������ ������������ U = 0�.";
static const char chanInverseEn[] = "When \"Enable\" signal on the screen will be reflected symmetrically with respect to U = 0V.";

static const char chanDividerRu[] = "���������� �������:\n\"����\" - ������ �� �����������.\n\"x10\" - ������ ����������� � 10 ���";
static const char chanDividerEn[] = "Attenuation: \n\"Off\" - the signal is not attenuated.\n\"x10\" - the signal is attenuated by 10 times";

extern const Page mainPage;

// ����� 1 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pChanA =
{
    Item_Page, &mainPage, 0,
    {
        "����� 1", "CHANNEL 1",
        "�������� ��������� ������ 1.",
        "Contains settings of the channel 1."
    },
    Page_ChannelA,
    {
        (void *)&cChanA_Input,      // ����� 1 - ����
        (void *)&cChanA_Couple,     // ����� 1 - �����
        (void *)&cChanA_Bandwidth,  // ����� 1 - ������
        (void *)&cChanA_Resistance, // ����� 1 - �� ����
        (void *)&cChanA_Inverse,    // ����� 1 - ��������
        (void *)&cChanA_Divider,    // ����� 1 - ��������
        (void *)&bChanA_Balance     // ����� 1 - �������������
    }
};

// ����� 1 - ���� ------------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanA_Input =
{
    Item_Choice, &pChanA, 0,
    {
        "����", "Input",
        chanInputRu,
        chanInputEn
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&SET_ENABLED_A, OnChanged_ChanA_Input
};

void OnChanged_ChanA_Input(bool active)
{
    Panel_EnableLEDChannel(A, SET_ENABLED_A);
}

// ����� 1 - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanA_Couple =
{
    Item_Choice, &pChanA, 0,
    {
        "�����", "Couple",
        chanCoupleRu,
        chanCoupleEn
    },
    {
        {"����", "AC"},
        {"�����", "DC"},
        {"�����", "Ground"}
    },
    (int8 *)&SET_COUPLE_A, OnChanged_ChanA_Couple
};

static void OnChanged_ChanA_Couple(bool active)
{
    FPGA_SetModeCouple(A, SET_COUPLE_A);
}

// ����� 1 - ������ ----------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanA_Bandwidth =
{
    Item_Choice, &pChanA, 0,
    {
        "������", "Bandwidth",
        "����� ������ ����������� ������", "Sets the channel bandwidth"
    },
    {
        {"������", "Full"},
        {"20���", "20MHz"}
    },
    (int8 *)&SET_BANDWIDTH_A, OnChanged_ChanA_Bandwidth
};

static void OnChanged_ChanA_Bandwidth(bool active)
{
    FPGA_SetBandwidth(A);
}

// ����� 1 - ������������� ---------------------------------------------------------------------------------------------------------------------------
static const Choice cChanA_Resistance =
{
    Item_Choice, &pChanA, 0,
    {
        "�� ����", "Resistance",
        "", ""
    },
    {
        {"1 ���", "1 Mohm"},
        {"50 ��", "50 Ohm"}
    },
    (int8 *)&SET_RESISTANCE_A, OnChanged_ChanA_Resistance
};

static void OnChanged_ChanA_Resistance(bool active)
{
    FPGA_SetResistance(A, SET_RESISTANCE_A);
    if (SET_RESISTANCE_A == Resistance_50Om)
    {
        Display_ShowWarning(Warn50Ohms);
    }
}

// ����� 1 - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanA_Inverse =
{
    Item_Choice, &pChanA, 0,
    {
        "��������", "Inverse",
        chanInverseRu,
        chanInverseEn
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&SET_INVERSE_A, OnChanged_ChanA_Inverse
};

static void OnChanged_ChanA_Inverse(bool active)
{
    FPGA_SetRShift(A, SET_RSHIFT_A);
}

// ����� 1 - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanA_Divider =
{
    Item_Choice, &pChanA, 0,
    {
        "��������", "Divider",
        chanDividerRu,
        chanDividerEn
    },
    {
        {"����", "Off"},
        {"1/10", "1/10"}
    },
    (int8 *)&SET_DIVIDER_A
};

// ����� 1 - ������������� ---------------------------------------------------------------------------------------------------------------------------
static const Button bChanA_Balance =
{
    Item_Button, &pChanA, 0,
    {
        "�������������", "Balance",
        "������������� �����",
        "Balancing channel"
    },
    OnPress_ChanA_Balance
};

static void OnPress_ChanA_Balance(void)
{
    FPGA_BalanceChannel(A);
}

// ����� 2 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pChanB =
{
    Item_Page, &mainPage, 0,
    {
        "����� 2", "CHANNEL 2",
        "�������� ��������� ������ 2.",
        "Contains settings of the channel 2."
    },
    Page_ChannelB,
    {
        (void *)&cChanB_Input,      // ����� 2 - ����
        (void *)&cChanB_Couple,     // ����� 2 - �����
        (void *)&cChanB_Bandwidth,  // ����� 2 - ������
        (void *)&cChanB_Resistance, // ����� 2 - �������������
        (void *)&cChanB_Inverse,    // ����� 2 - ��������
        (void *)&cChanB_Divider,    // ����� 2 - ��������
        (void *)&bChanB_Balance     // ����� 2 - �������������
    }
};

// ����� 2 - ���� ------------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanB_Input =
{
    Item_Choice, &pChanB, IsActive_ChanB_Input,
    {
        "����", "Input",
        chanInputRu,
        chanInputEn
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&SET_ENABLED_B, OnChanged_ChanB_Input
};

static bool IsActive_ChanB_Input(void)
{
    return !FPGA_POINTS_32k;
}

void OnChanged_ChanB_Input(bool active)
{
    if (!active)
    {
        Display_ShowWarning(TooLongMemory);
        return;
    }

    if (FPGA_POINTS_32k && SET_ENABLED_B)
    {
        SET_ENABLED_B = false;
    }
    Panel_EnableLEDChannel(B, SET_ENABLED_B);
}

// ����� 2 - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanB_Couple =
{
    Item_Choice, &pChanB, 0,
    {
        "�����", "Couple",
        chanCoupleRu,
        chanCoupleEn
    },
    {
        {"����", "AC"},
        {"�����", "DC"},
        {"�����", "Ground"}
    },
    (int8 *)&SET_COUPLE_B, OnChanged_ChanB_Couple
};

static void OnChanged_ChanB_Couple(bool active)
{
    FPGA_SetModeCouple(B, SET_COUPLE_B);
}

// ����� 2 - ������ ----------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanB_Bandwidth =
{
    Item_Choice, &pChanB, 0,
    {
        "������", "Bandwidth",
        "",
        ""
    },
    {
        {"������", "Full"}, 
        {"20���", "20MHz"}
    },
    (int8 *)&SET_BANDWIDTH_B, OnChanged_ChanB_Bandwidth
};

static void OnChanged_ChanB_Bandwidth(bool active)
{
    FPGA_SetBandwidth(B);
}

// ����� 2 - ������������� ---------------------------------------------------------------------------------------------------------------------------
static const Choice cChanB_Resistance =
{
    Item_Choice, &pChanB, 0,
    {
        "�� ����", "Resistance",
        "", ""
    },
    {
        {"1 ���", "1 Mohm"},
        {"50 ��", "50 Ohm"}
    },
    (int8 *)&SET_RESISTANCE_B, OnChanged_ChanB_Resistance
};

static void OnChanged_ChanB_Resistance(bool active)
{
    FPGA_SetResistance(B, SET_RESISTANCE_B);
    if (SET_RESISTANCE_B == Resistance_50Om)
    {
        Display_ShowWarning(Warn50Ohms);
    }
}

// ����� 2 - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanB_Inverse =
{
    Item_Choice, &pChanB, 0,
    {
        "��������", "Inverse",
        chanInverseRu,
        chanInverseEn
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8 *)&SET_INVERSE_B, OnChanged_ChanB_Inverse
};

static void OnChanged_ChanB_Inverse(bool active)
{
    FPGA_SetRShift(B, SET_RSHIFT_B);
}

// ����� 2 - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice cChanB_Divider =
{
    Item_Choice, &pChanB, 0,
    {
        "��������", "Divider",
        chanDividerRu,
        chanDividerEn
    },
    {
        {"����", "Jff"},
        {"1/10", "1/10"}
    },
    (int8 *)&SET_DIVIDER_B
};

// ����� 2 - ������������� ---------------------------------------------------------------------------------------------------------------------------
static const Button bChanB_Balance =
{
    Item_Button, &pChanB, 0,
    {
        "�������������", "Balance",
        "������������� �����",
        "Balancing channel"
    },
    OnPress_ChanB_Balance
};

static void OnPress_ChanB_Balance(void)
{
    FPGA_BalanceChannel(B);
}

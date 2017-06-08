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
extern const Page mainPage;

static const Choice mcChanA_Input;
static const Choice mcChanA_Couple;
static const Choice mcChanA_Bandwidth;
static const Choice mcChanA_Resistance;
static const Choice mcChanA_Inverse;
static const Choice mcChanA_Divider;
static const Button mbChanA_Balance;

static const Choice mcChanB_Input;
static const Choice mcChanB_Couple;
static const Choice mcChanB_Bandwidth;
static const Choice mcChanB_Resistance;
static const Choice mcChanB_Inverse;
static const Choice mcChanB_Divider;
static const Button mbChanB_Balance;

       void OnChange_ChanA_Input(bool active);
static void OnChange_ChanA_Couple(bool active);
static void OnChange_ChanA_Bandwidth(bool active);
static void OnChange_ChanA_Resistance(bool active);
static void OnChange_ChanA_Inverse(bool active);
static void OnPress_ChanA_Balance(void);

static bool IsActive_ChanB_Input(void);
       void OnChange_ChanB_Input(bool active);
static void OnChange_ChanB_Couple(bool active);
static void OnChange_ChanB_Bandwidth(bool active);
static void OnChange_ChanB_Resistance(bool active);
static void OnChange_ChanB_Inverse(bool active);
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


// ����� 1 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mpChanA =
{
    Item_Page, &mainPage, 0,
    {
        "����� 1", "CHANNEL 1",
        "�������� ��������� ������ 1.",
        "Contains settings of the channel 1."
    },
    Page_ChannelA,
    {
        (void*)&mcChanA_Input,      // ����� 1 - ����
        (void*)&mcChanA_Couple,     // ����� 1 - �����
        (void*)&mcChanA_Bandwidth,  // ����� 1 - ������
        (void*)&mcChanA_Resistance, // ����� 1 - �� ����
        (void*)&mcChanA_Inverse,    // ����� 1 - ��������
        (void*)&mcChanA_Divider,    // ����� 1 - ��������
        (void*)&mbChanA_Balance     // ����� 1 - �������������
    }
};

// ����� 1 - ���� ------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Input =
{
    Item_Choice, &mpChanA, 0,
    {
        "����", "Input",
        chanInputRu,
        chanInputEn
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&SET_ENABLED_A, OnChange_ChanA_Input
};

void OnChange_ChanA_Input(bool active)
{
    Panel_EnableLEDChannelA(sChannel_Enabled(A));
}

// ����� 1 - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Couple =
{
    Item_Choice, &mpChanA, 0,
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
    (int8*)&SET_COUPLE_A, OnChange_ChanA_Couple
};

static void OnChange_ChanA_Couple(bool active)
{
    FPGA_SetModeCouple(A, SET_COUPLE_A);
}

// ����� 1 - ������ ----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Bandwidth =
{
    Item_Choice, &mpChanA, 0,
    {
        "������", "Bandwidth",
        "����� ������ ����������� ������", "Sets the channel bandwidth"
    },
    {
        {"������", "Full"},
        {"20���", "20MHz"}
    },
    (int8*)&SET_BANDWIDTH_A, OnChange_ChanA_Bandwidth
};

static void OnChange_ChanA_Bandwidth(bool active)
{
    FPGA_SetBandwidth(A);
}

// ����� 1 - ������������� ---------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Resistance =
{
    Item_Choice, &mpChanA, 0,
    {
        "�� ����", "Resistance",
        "", ""
    },
    {
        {"1 ���", "1 Mohm"},
        {"50 ��", "50 Ohm"}
    },
    (int8*)&SET_RESISTANCE_A, OnChange_ChanA_Resistance
};

static void OnChange_ChanA_Resistance(bool active)
{
    FPGA_SetResistance(A, SET_RESISTANCE_A);
    if (SET_RESISTANCE_A == Resistance_50Om)
    {
        Display_ShowWarning(Warn50Ohms);
    }
}

// ����� 1 - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Inverse =
{
    Item_Choice, &mpChanA, 0,
    {
        "��������", "Inverse",
        chanInverseRu,
        chanInverseEn
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&SET_INVERSE_A, OnChange_ChanA_Inverse
};

static void OnChange_ChanA_Inverse(bool active)
{
    FPGA_SetRShift(A, SET_RSHIFT_A);
}

// ����� 1 - ��������� -------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Divider =
{
    Item_Choice, &mpChanA, 0,
    {
        "��������", "Divider",
        chanDividerRu,
        chanDividerEn
    },
    {
        {"����", "Off"},
        {"1/10", "1/10"}
    },
    (int8*)&SET_DIVIDER_A
};

// ����� 1 - ������������� ---------------------------------------------------------------------------------------------------------------------------
static const Button mbChanA_Balance =
{
    Item_Button, &mpChanA, 0,
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
const Page mpChanB =
{
    Item_Page, &mainPage, 0,
    {
        "����� 2", "CHANNEL 2",
        "�������� ��������� ������ 2.",
        "Contains settings of the channel 2."
    },
    Page_ChannelB,
    {
        (void*)&mcChanB_Input,      // ����� 2 - ����
        (void*)&mcChanB_Couple,     // ����� 2 - �����
        (void*)&mcChanB_Bandwidth,  // ����� 2 - ������
        (void*)&mcChanB_Resistance, // ����� 2 - �������������
        (void*)&mcChanB_Inverse,    // ����� 2 - ��������
        (void*)&mcChanB_Divider,    // ����� 2 - ��������
        (void*)&mbChanB_Balance     // ����� 2 - �������������
    }
};

// ����� 2 - ���� ------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Input =
{
    Item_Choice, &mpChanB, IsActive_ChanB_Input,
    {
        "����", "Input",
        chanInputRu,
        chanInputEn
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&SET_ENABLED_B, OnChange_ChanB_Input
};

static bool IsActive_ChanB_Input(void)
{
    return !FPGA_NUM_POINTS_32k;
}

void OnChange_ChanB_Input(bool active)
{
    if (!active)
    {
        Display_ShowWarning(TooLongMemory);
        return;
    }

    if (FPGA_NUM_POINTS_32k && SET_ENABLED_B)
    {
        SET_ENABLED_B = false;
    }
    Panel_EnableLEDChannelB(sChannel_Enabled(B));
}

// ����� 2 - ����� -----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Couple =
{
    Item_Choice, &mpChanB, 0,
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
    (int8*)&SET_COUPLE_B, OnChange_ChanB_Couple
};

static void OnChange_ChanB_Couple(bool active)
{
    FPGA_SetModeCouple(B, SET_COUPLE_B);
}

// ����� 2 - ������ ----------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Bandwidth =
{
    Item_Choice, &mpChanB, 0,
    {
        "������", "Bandwidth",
        "",
        ""
    },
    {
        {"������", "Full"}, 
        {"20���", "20MHz"}
    },
    (int8*)&SET_BANDWIDTH_B, OnChange_ChanB_Bandwidth
};

static void OnChange_ChanB_Bandwidth(bool active)
{
    FPGA_SetBandwidth(B);
}

// ����� 2 - ������������� ---------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Resistance =
{
    Item_Choice, &mpChanB, 0,
    {
        "�� ����", "Resistance",
        "", ""
    },
    {
        {"1 ���", "1 Mohm"},
        {"50 ��", "50 Ohm"}
    },
    (int8*)&SET_RESISTANCE_B, OnChange_ChanB_Resistance
};

static void OnChange_ChanB_Resistance(bool active)
{
    FPGA_SetResistance(B, SET_RESISTANCE_B);
    if (SET_RESISTANCE_B == Resistance_50Om)
    {
        Display_ShowWarning(Warn50Ohms);
    }
}

// ����� 2 - �������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Inverse =
{
    Item_Choice, &mpChanB, 0,
    {
        "��������", "Inverse",
        chanInverseRu,
        chanInverseEn
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&SET_INVERSE_B, OnChange_ChanB_Inverse
};

static void OnChange_ChanB_Inverse(bool active)
{
    FPGA_SetRShift(B, SET_RSHIFT_B);
}

// ����� 2 - ��������� -------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Divider =
{
    Item_Choice, &mpChanB, 0,
    {
        "��������", "Divider",
        chanDividerRu,
        chanDividerEn
    },
    {
        {"����", "Jff"},
        {"1/10", "1/10"}
    },
    (int8*)&SET_DIVIDER_B
};

// ����� 2 - ������������� ---------------------------------------------------------------------------------------------------------------------------
static const Button mbChanB_Balance =
{
    Item_Button, &mpChanB, 0,
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

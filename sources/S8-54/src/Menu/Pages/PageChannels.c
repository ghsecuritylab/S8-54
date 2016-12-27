#include "defines.h"
#include "Log.h"
#include "Settings/SettingsTypes.h"
#include "Menu/MenuItems.h"
#include "Panel/Panel.h"
#include "FPGA/FPGA.h"
#include "FPGA/FPGA_Calibration.h"
#include "Display/Display.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Page mainPage;

#ifdef _MS_VS
#pragma warning(push)
#pragma warning(disable:4132)
#endif

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

#ifdef _MS_VS
#pragma warning(pop)
#endif

//------------------------------------------------------------------------------------------------------------------------------------------------------
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


// ����� 1 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mpChanA =
{
    Item_Page, &mainPage, {"����� 1", "CHANNEL 1"},
    {
        "�������� ��������� ������ 1.",
        "Contains settings of the channel 1."
    },
    EmptyFuncBV, Page_ChannelA,
    {
        (void*)&mcChanA_Input,      // ����� 1 -> ����
        (void*)&mcChanA_Couple,     // ����� 1 -> �����
        (void*)&mcChanA_Bandwidth,  // ����� 1 -> ������
        (void*)&mcChanA_Resistance, // ����� 1 -> �� ����
        (void*)&mcChanA_Inverse,    // ����� 1 -> ��������
        (void*)&mcChanA_Divider,    // ����� 1 -> ��������
        (void*)&mbChanA_Balance     // ����� 1 -> �������������
    }
};


// ����� 1 -> ���� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Input =
{
    Item_Choice, &mpChanA, {"����", "Input"},
    {
        chanInputRu,
        chanInputEn
    },
    EmptyFuncBV,
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&ENABLE_A, OnChange_ChanA_Input, EmptyFuncVII
};

void OnChange_ChanA_Input(bool active)
{
    Panel_EnableLEDChannelA(sChannel_Enabled(A));
}


// ����� 1 -> ����� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Couple =
{
    Item_Choice, &mpChanA, {"�����", "Couple"},
    {
        chanCoupleRu,
        chanCoupleEn
    },
    EmptyFuncBV,
    {
        {"����", "AC"},
        {"�����", "DC"},
        {"�����", "Ground"}
    },
    (int8*)&COUPLE_A, OnChange_ChanA_Couple, EmptyFuncVII
};

static void OnChange_ChanA_Couple(bool active)
{
    FPGA_SetModeCouple(A, COUPLE_A);
}


// ����� 1 -> ������ ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Bandwidth =
{
    Item_Choice, &mpChanA, {"������", "Bandwidth"},
    {
        "����� ������ ����������� ������", "Sets the channel bandwidth"
    },
    EmptyFuncBV,
    {
        {"������", "Full"},
        {"20���", "20MHz"}
    },
    (int8*)&BANDWIDTH_A, OnChange_ChanA_Bandwidth, EmptyFuncVII
};

static void OnChange_ChanA_Bandwidth(bool active)
{
    FPGA_SetBandwidth(A);
}


// ����� 1 -> ������������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Resistance =
{
    Item_Choice, &mpChanA, {"�� ����", "Resistance"},
    {
        "", ""
    },
    EmptyFuncBV,
    {
        {"1 ���", "1 Mohm"},
        {"50 ��", "50 Ohm"}
    },
    (int8*)&RESISTANCE_A, OnChange_ChanA_Resistance, EmptyFuncVII
};

static void OnChange_ChanA_Resistance(bool active)
{
    FPGA_SetResistance(A, RESISTANCE_A);
    if (RESISTANCE_A == Resistance_50Om)
    {
        Display_ShowWarning(Warn50Ohms);
    }
}


// ����� 1 -> �������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Inverse =
{
    Item_Choice, &mpChanA, {"��������", "Inverse"},
    {
        chanInverseRu,
        chanInverseEn
    },
    EmptyFuncBV,
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&INVERSE(A), OnChange_ChanA_Inverse, EmptyFuncVII
};

static void OnChange_ChanA_Inverse(bool active)
{
    FPGA_SetRShift(A, RSHIFT_A);
}


// ����� 1 -> ��������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Divider =
{
    Item_Choice, &mpChanA, {"��������", "Divider"},
    {
        chanDividerRu,
        chanDividerEn
    },
    EmptyFuncBV,
    {
        {"����", "Off"},
        {"1/10", "1/10"}
    },
    (int8*)&DIVIDER_A, EmptyFuncVB, EmptyFuncVII
};

// ����� 1 -> ������������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Button mbChanA_Balance =
{
    Item_Button, &mpChanA,
    {
        "�������������", "Balance"
    },
    {
        "������������� �����",
        "Balancing channel"
    },
    EmptyFuncBV, OnPress_ChanA_Balance, EmptyFuncVII
};

static void OnPress_ChanA_Balance(void)
{
    FPGA_BalanceChannel(A);
}


// ����� 2 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mpChanB =
{
    Item_Page, &mainPage, {"����� 2", "CHANNEL 2"},
    {
        "�������� ��������� ������ 2.",
        "Contains settings of the channel 2."
    },
    EmptyFuncBV, Page_ChannelB,
    {
        (void*)&mcChanB_Input,      // ����� 2 -> ����
        (void*)&mcChanB_Couple,     // ����� 2 -> �����
        (void*)&mcChanB_Bandwidth,  // ����� 2 -> ������
        (void*)&mcChanB_Resistance, // ����� 2 -> �������������
        (void*)&mcChanB_Inverse,    // ����� 2 -> ��������
        (void*)&mcChanB_Divider,    // ����� 2 -> ��������
        (void*)&mbChanB_Balance     // ����� 2 -> �������������
    }
};

// ����� 2 -> ���� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Input =
{
    Item_Choice, &mpChanB, {"����", "Input"},
    {
        chanInputRu,
        chanInputEn
    },
    IsActive_ChanB_Input,
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&ENABLE_B, OnChange_ChanB_Input, EmptyFuncVII
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

    if (FPGA_NUM_POINTS_32k && ENABLE_B)
    {
        ENABLE_B = false;
    }
    Panel_EnableLEDChannelB(sChannel_Enabled(B));
}

// ����� 2 -> ����� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Couple =
{
    Item_Choice, &mpChanB, {"�����", "Couple"},
    {
        chanCoupleRu,
        chanCoupleEn
    },
    EmptyFuncBV,
    {
        {"����", "AC"},
        {"�����", "DC"},
        {"�����", "Ground"}
    },
    (int8*)&COUPLE_B, OnChange_ChanB_Couple, EmptyFuncVII
};

static void OnChange_ChanB_Couple(bool active)
{
    FPGA_SetModeCouple(B, COUPLE_B);
}

// ����� 2 -> ������ ------------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Bandwidth =
{
    Item_Choice, &mpChanB, {"������", "Bandwidth"},
    {
        "", ""
    },
    EmptyFuncBV,
    {
        {"������", "Full"}, 
        {"20���", "20MHz"}
    },
    (int8*)&BANDWIDTH_B, OnChange_ChanB_Bandwidth, EmptyFuncVII
};

static void OnChange_ChanB_Bandwidth(bool active)
{
    FPGA_SetBandwidth(B);
}

// ����� 2 -> ������������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Resistance =
{
    Item_Choice, &mpChanB, {"�� ����", "Resistance"},
    {
        "", ""
    },
    EmptyFuncBV,
    {
        {"1 ���", "1 Mohm"},
        {"50 ��", "50 Ohm"}
    },
    (int8*)&RESISTANCE_B, OnChange_ChanB_Resistance, EmptyFuncVII
};

static void OnChange_ChanB_Resistance(bool active)
{
    FPGA_SetResistance(B, RESISTANCE_B);
    if (RESISTANCE_B == Resistance_50Om)
    {
        Display_ShowWarning(Warn50Ohms);
    }
}

// ����� 2 -> �������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Inverse =
{
    Item_Choice, &mpChanB, {"��������", "Inverse"},
    {
        chanInverseRu,
        chanInverseEn
    },
    EmptyFuncBV,
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&INVERSE(B), OnChange_ChanB_Inverse, EmptyFuncVII
};

static void OnChange_ChanB_Inverse(bool active)
{
    FPGA_SetRShift(B, RSHIFT_B);
}

// ����� 2 -> ��������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanB_Divider =
{
    Item_Choice, &mpChanB, {"��������", "Divider"},
    {
        chanDividerRu,
        chanDividerEn
    },
    EmptyFuncBV,
    {
        {"����", "Jff"},
        {"1/10", "1/10"}
    },
    (int8*)&DIVIDER_B, EmptyFuncVB, EmptyFuncVII
};

// ����� 2 -> ������������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Button mbChanB_Balance =
{
    Item_Button, &mpChanB,
    {
        "�������������", "Balance"
    },
    {
        "������������� �����",
        "Balancing channel"
    },
    EmptyFuncBV, OnPress_ChanB_Balance, EmptyFuncVII
};

static void OnPress_ChanB_Balance(void)
{
    FPGA_BalanceChannel(B);
}

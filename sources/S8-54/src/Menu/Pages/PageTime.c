#include "defines.h"
#include "Settings/Settings.h"
#include "Settings/SettingsTypes.h"
#include "PageMemory.h"
#include "FPGA/FPGAtypes.h"
#include "FPGA/FPGA.h"
#include "Log.h"
#include "Display/Display.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/Math.h" 
#include "Hardware/FSMC.h"
#include "Display/Grid.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Page mainPage;

static const Choice mcTimeSample;
static bool FuncTimeSampleActive(void);
static const Choice mcTimePicDet;
static bool IsActiveChoiceTimePicDeat(void);
       void OnPeacDetChanged(bool active);
static const Choice mcTimeTPos;
       void OnTPosChanged(bool active);
static const Choice mcTimeDivRole;

// ��������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mpTime =
{
    Item_Page, &mainPage,
    {
        "���������", "SCAN"
    },
    {
        "�������� ��������� ��������.",
        "Contains scan settings."
    },
    0, Page_Time,
    {
        (void*)&mcTimeSample,
        (void*)&mcTimePicDet,
        (void*)&mcTimeTPos,
        // (void*)&mcTimeSelfRecorder,
        (void*)&mcTimeDivRole
    }
};

//---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcTimeSample =
{
    Item_Choice, &mpTime, {"�������", "Sampling"},
    {
        "\"��������\" - \n"
        "\"�������������\" -"
        ,
        "\"Real\" - \n"
        "\"Equals\" - "
    },
    FuncTimeSampleActive,
    {
        {"�������� �����", "Real"},
        {"�������������", "Equals"}
    },
    (int8*)&SAMPLE
};

static bool FuncTimeSampleActive(void)
{
    return IN_RANDOM_MODE && !START_MODE_SINGLE;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcTimePicDet =
{
    Item_Choice, &mpTime, {"��� ���", "Pic deat"},
    {
        "��������/��������� ������� ��������.",
        "Turns on/off peak detector."
    },
    IsActiveChoiceTimePicDeat,
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    /* , {"�������",   "Average"} */
    },
    (int8*)&PEACKDET, OnPeacDetChanged
};

static bool IsActiveChoiceTimePicDeat(void)
{
    if (FPGA_NUM_POINTS_32k)                       // ��� 32� ����� �� ����� �� �� ����� �������� ������� ��������
    {
        return false;
    }

    if (FPGA_NUM_POINTS_16k && ENABLE_B) // ��� 16� ������ �� ����� �� ����� �������� ������ � ����� �������
    {
        return false;
    }

    return (TBASE >= MIN_TBASE_PEC_DEAT);
}

void OnPeacDetChanged(bool active)
{
    if(active)
    {
        FPGA_SetPeackDetMode(PEACKDET);
        FPGA_SetTBase(TBASE);
        OnChange_MemoryLength(true);
    }
    else
    {
        if (FPGA_NUM_POINTS_32k)
        {
            Display_ShowWarning(NoPeakDet32k);
        }
        else if (FPGA_NUM_POINTS_16k && ENABLE_B)
        {
            Display_ShowWarning(NoPeakDet16k);
        }
        else
        {
            Display_ShowWarning(TooSmallSweepForPeakDet);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcTimeTPos =
{
    Item_Choice, &mpTime,
    {
        "\x7b", "\x7b"
    },
    {
        "����� ����� �������� �������� �������� �� ������� � ������ - ����� ����, �����, ������ ����.", 
        "Sets the anchor point nuleovgo time offset to the screen - the left edge, center, right edge."
    },
    0,
    {
        {"����", "Left"},
        {"�����", "Center"},
        {"�����", "Right"}
    },
    (int8*)&TPOS, OnTPosChanged
};

void OnTPosChanged(bool active)
{
    OnChange_MemoryLength(active);
    FPGA_SetTShift(TSHIFT);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcTimeDivRole =
{
    Item_Choice, &mpTime, {"�-��� ��/���", "Funct Time/DIV"},
    {
        "����� ������� ��� ����� �����/���: � ������ ����� ���������� (����/���� � ��������� ����):\n"
        "1. \"�����\" - ��������� �������� �� �������.\n"
        "2. \"������\" - ����������� �� ������.",

        "Sets the function to handle TIME/DIV: mode of collecting information (START/STOP to start position):\n"
        "1. \"Time\" - change the time shift.\n"
        "2. \"Memory\" - moving from memory."
    },
    0,
    {
        {"�����", "Time"},
        {"������", "Memory"}
    },
    (int8*)&TIME_DIVXPOS
};

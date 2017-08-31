// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Page mainPage;

static const  Choice cSample;                ///< ��������� - �������
static bool  IsActive_Sample(void);
static const  Choice cPeakDet;               ///< ��������� - ��� ���
static bool  IsActive_PeakDet(void);
       void OnChanged_PeakDet(bool active);
static const  Choice cTPos;                  ///< ��������� - ��
       void OnChanged_TPos(bool active);
static const  Choice cDivRole;               ///< ��������� - �-��� ��/���

// ��������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pTime =
{
    Item_Page, &mainPage, 0,
    {
        "���������", "SCAN",
        "�������� ��������� ��������.",
        "Contains scan settings."
    },
    Page_Time,
    {
        (void *)&cSample,       // ��������� - �������
        (void *)&cPeakDet,      // ��������� - ��� ���
        (void *)&cTPos,         // ��������� - ��
        (void *)&cDivRole       // ��������� - �-��� ��/���
        // (void *)&mcTimeSelfRecorder,
    }
};

// ��������� - ������� -------------------------------------------------------------------------------------------------------------------------------
static const Choice cSample =
{
    Item_Choice, &pTime, IsActive_Sample,
    {
        "�������",          "Sampling"
        ,
        "\"��������\" - \n"
        "\"�������������\" -"
        ,
        "\"Real\" - \n"
        "\"Equals\" - "
    },
    {
        {"�������� �����",  "Real"},
        {"�������������",   "Equals"}
    },
    (int8 *)&SAMPLE_TYPE
};

static bool IsActive_Sample(void)
{
    return IN_RANDOM_MODE && !START_MODE_SINGLE;
}

// ��������� - ��� ��� -------------------------------------------------------------------------------------------------------------------------------
static const Choice cPeakDet =
{
    Item_Choice, &pTime, IsActive_PeakDet,
    {
        "��� ���",      "Pic deat",
        "��������/��������� ������� ��������.",
        "Turns on/off peak detector."
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    /* , {"�������",   "Average"} */
    },
    (int8 *)&SET_PEAKDET, OnChanged_PeakDet
};

static bool IsActive_PeakDet(void)
{
    if (FPGA_POINTS_32k)                       // ��� 32� ����� �� ����� �� �� ����� �������� ������� ��������
    {
        return false;
    }

    if (FPGA_POINTS_16k && SET_ENABLED_B) // ��� 16� ������ �� ����� �� ����� �������� ������ � ����� �������
    {
        return false;
    }

    return (SET_TBASE >= MIN_TBASE_PEC_DEAT);
}

void OnChanged_PeakDet(bool active)
{
    if(active)
    {
        FPGA_SetPeackDetMode(SET_PEAKDET);
        FPGA_SetTBase(SET_TBASE);
        OnChanged_Points(true);
    }
    else
    {
        if (FPGA_POINTS_32k)
        {
            Display_ShowWarning(NoPeakDet32k);
        }
        else if (FPGA_POINTS_16k && SET_ENABLED_B)
        {
            Display_ShowWarning(NoPeakDet16k);
        }
        else
        {
            Display_ShowWarning(TooSmallSweepForPeakDet);
        }
    }
}

// ��������� - �� ------------------------------------------------------------------------------------------------------------------------------------
static const Choice cTPos =
{
    Item_Choice, &pTime, 0,
    {
        "\x7b",     "\x7b",
        "����� ����� �������� �������� �������� �� ������� � ������ - ����� ����, �����, ������ ����.", 
        "Sets the anchor point nuleovgo time offset to the screen - the left edge, center, right edge."
    },
    {
        {"����",    "Left"},
        {"�����",   "Center"},
        {"�����",   "Right"}
    },
    (int8 *)&TPOS, OnChanged_TPos
};

void OnChanged_TPos(bool active)
{
    OnChanged_Points(active);
    FPGA_SetTShift(SET_TSHIFT);
}

// ��������� - �-��� ��/��� --------------------------------------------------------------------------------------------------------------------------
static const Choice cDivRole =
{
    Item_Choice, &pTime, 0,
    {
        "�-��� ��/���", "Funct Time/DIV"
        ,
        "����� ������� ��� ����� �����/���: � ������ ����� ���������� (����/���� � ��������� ����):\n"
        "1. \"�����\" - ��������� �������� �� �������.\n"
        "2. \"������\" - ����������� �� ������."
        ,
        "Sets the function to handle TIME/DIV: mode of collecting information (START/STOP to start position):\n"
        "1. \"Time\" - change the time shift.\n"
        "2. \"Memory\" - moving from memory."
    },
    {
        {"�����",       "Time"},
        {"������",      "Memory"}
    },
    (int8 *)&TIME_DIVXPOS
};

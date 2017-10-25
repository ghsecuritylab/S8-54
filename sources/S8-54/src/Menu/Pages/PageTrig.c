// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"
#include "FPGA/FPGAtypes.h"
#include "FPGA/FPGA.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const   Choice cMode;                    ///< ����� - �����
       void  OnChanged_TrigMode(bool active);   
static const   Choice cSource;                  ///< ����� - ��������
static void  OnChanged_Source(bool active);
static const   Choice cPolarity;                ///< ����� - ����������
static void  OnChanged_Polarity(bool active);   
static const   Choice cInput;                   ///< ����� - ����
static void  OnChanged_Input(bool active);
static const    Page ppSearch;                  ///< ����� - �����
static const   Choice cSearch_Mode;             ///< ����� - ����� - �����
static const   Button bSearch_Search;           ///< ����� - ����� - �����
static bool   IsActive_Search_Search(void);
static void    OnPress_Search_Search(void);
//static const Governor gTimeDelay;               ///< ����� - ���������


extern const Page mainPage;


// ����� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pTrig =
{
    Item_Page, &mainPage, 0,
    {
        "�����", "TRIG",
        "�������� ��������� �������������.",
        "Contains synchronization settings."
    },
    Page_Trig,
    {
        (void *)&cMode,         // ����� - �����
        (void *)&cSource,       // ����� - ��������
        (void *)&cPolarity,     // ����� - ����������
        (void *)&cInput,        // ����� - ����
        (void *)&ppSearch       // ����� - �����
//        (void *)&gTimeDelay      // ����� - ���������
    }
};

// ����� - ����� -------------------------------------------------------------------------------------------------------------------------------------
static const Choice cMode =
{
    Item_Choice, &pTrig, 0,
    {
        "�����",        "Mode"
        ,
        "����� ����� �������:\n"
        "1. \"����\" - ������ ���������� �������������.\n"
        "2. \"������\" - ������ ���������� �� ������ �������������.\n"
        "3. \"�����������\" - ������ ���������� �� ���������� ������ ������������� ���� ���. ��� ���������� ��������� ����� ������ ������ ����/����."
        ,
        "Sets the trigger mode:\n"
        "1. \"Auto\" - start automatically.\n"
        "2. \"Standby\" - the launch takes place at the level of synchronization.\n"
        "3. \"Single\" - the launch takes place on reaching the trigger levelonce. For the next measurement is necessary to press the START/STOP."
    },
    {
        {"���� ",       "Auto"},
        {"������",      "Wait"},
        {"�����������", "Single"}
    },
    (int8 *)&START_MODE, OnChanged_TrigMode
};

void OnChanged_TrigMode(bool active)
{
    FPGA_Stop(false);
    if(!START_MODE_SINGLE)
    {
        FPGA_OnPressStartStop();
    }
    
    // ���� ��������� � ������ �������������
    if(IN_RANDOM_MODE)
    /// \todo ��� ������ ������� sTime_RandomizeModeEnabled() ���� ������� ������, ��� � �������� ����� ������������ �����������
    //if (SET_TBASE < TBase_50ns)
    {
        // � ������������� �� ��������� ����� �������, �� ���� ��������� ��������� ��� �������, ����� ������������ ��� ����������� � ����� 
        // ������������� �������������� ��� ������
        if (START_MODE_SINGLE)
        {
            SAMPLE_TYPE_IS_OLD = SAMPLE_TYPE;
            SAMPLE_TYPE = SampleType_Real;
        }
        else if(START_MODE_AUTO)    // ����� ����������� ����� ����������
        {
            SAMPLE_TYPE = SAMPLE_TYPE_IS_OLD;
        }
    }
}

// ����� - �������� ----------------------------------------------------------------------------------------------------------------------------------
static const Choice cSource =
{
    Item_Choice, &pTrig, 0,
    {
        "��������", "Source",
        "����� ��������� ������� �������������.",
        "Synchronization signal source choice."
    },
    {
        {"����� 1", "Channel 1"},
        {"����� 2", "Channel 2"},
        {"�������", "External"}
    },
    (int8 *)&TRIGSOURCE, OnChanged_Source
};

static void OnChanged_Source(bool active)
{
    FPGA_SetTrigSource(TRIGSOURCE);
}

// ����� - ���������� --------------------------------------------------------------------------------------------------------------------------------
static const Choice cPolarity =
{
    Item_Choice, &pTrig, 0,
    {
        "����������",   "Polarity"
        ,
        "1. \"�����\" - ������ ���������� �� ������ ��������������.\n"
        "2. \"����\" - ������ ���������� �� ����� ��������������."
        ,
        "1. \"Front\" - start happens on the front of clock pulse.\n"
        "2. \"Back\" - start happens on a clock pulse cut."
    },
    {
        {"�����",       "Front"},
        {"����",        "Back"}
    },
    (int8 *)&TRIG_POLARITY, OnChanged_Polarity
};

static void OnChanged_Polarity(bool active)
{
    FPGA_SetTrigPolarity(TRIG_POLARITY);
}

// ����� - ���� --------------------------------------------------------------------------------------------------------------------------------------
static const Choice cInput =
{
    Item_Choice, &pTrig, 0,
    {
        "����", "Input"
        ,
        "����� ����� � ���������� �������������:\n"
        "1. \"��\" - ������ ������.\n"
        "2. \"��\" - �������� ����.\n"
        "3. \"���\" - ������ ������ ������.\n"
        "4. \"���\" - ������ ������� ������."
        ,
        "The choice of communication with the source of synchronization:\n"
        "1. \"SS\" - a full signal.\n"
        "2. \"AS\" - a gated entrance.\n"
        "3. \"LPF\" - low-pass filter.\n"
        "4. \"HPF\" - high-pass filter frequency."
    },
    {
        {"��", "Full"},
        {"��", "AC"},
        {"���", "LPF"},
        {"���", "HPF"}
    },
    (int8 *)&TRIG_INPUT, OnChanged_Input
};

static void OnChanged_Input(bool active)
{
    FPGA_SetTrigInput(TRIG_INPUT);
}

// ����� - ��������� ---------------------------------------------------------------------------------------------------------------------------------
/*
static const Governor gTimeDelay =
{
    Item_Governor, &pTrig, 0,
    {
        "���������, ��", "Holdoff, ms",
        "������������� ����������� ����� ����� ���������.",
        "Sets the minimum time between starts."
    },
    (int16 *)&TRIG_TIME_DELAY, 45, 10000
};
*/

// ����� - ����� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppSearch =
{
    Item_Page, &pTrig, 0,
    {
        "�����", "SEARCH",
        "���������� �������������� ������� ������ �������������.",
        "Office of the automatic search the trigger level."
    },
    Page_Trig_Search,
    {
        (void *)&cSearch_Mode,      // ����� - ����� - �����
        (void *)&bSearch_Search     // ����� - ����� - �����
    }
};

// ����� - ����� - ����� -----------------------------------------------------------------------------------------------------------------------------
static const Choice cSearch_Mode =
{
    Item_Choice, &ppSearch, 0,
    {
        "�����", "Mode"
        ,
        "����� ������ ��������������� ������ �������������:\n"
        "1. \"������\" - ����� ������������ �� ������� ������ \"�����\" ��� �� ��������� � ������� 0.5� ������ �����, ���� ����������� "
        "\"������\x99��� ���� �����\x99�����������\".\n"
        "2. \"��������������\" - ����� ������������ �������������."
        ,
        "Selecting the automatic search of synchronization:\n"
#pragma push
#pragma diag_suppress 192
        "1. \"Hand\" - search is run on pressing of the button \"Find\" or on deduction during 0.5s the ����� button if it is established "
        "\"SERVICE\x99Mode long �����\x99\Autolevel\".\n"
#pragma pop
        "2. \"Auto\" - the search is automatically."
    },
    {
        {"������",          "Hand"},
        {"��������������",  "Auto"}
    },
    (int8 *)&TRIG_MODE_FIND
};

// ����� - ����� - ����� -----------------------------------------------------------------------------------------------------------------------------
static const Button bSearch_Search =
{
    Item_Button, &ppSearch, IsActive_Search_Search,
    {
        "�����", "Search",
        "���������� ����� ������ �������������.",
        "Runs for search synchronization level."
    },
    OnPress_Search_Search, EmptyFuncVII
};

static bool IsActive_Search_Search(void)
{
    return TRIG_MODE_FIND_HAND;
}

static void OnPress_Search_Search(void)
{
    FPGA_FindAndSetTrigLevel();
}

#include "defines.h"
#include "PageCursors.h"
#include "Definition.h"
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"
#include "Panel/Controls.h"
#include "Display/Colors.h"
#include "Display/Grid.h"
#include "Utils/Math.h"
#include "Utils/ProcessingSignal.h"
#include "Utils/GlobalFunctions.h"
#include "Log.h"
#include "Display/Painter.h"
#include "Hardware/Sound.h"
#include "../MenuFunctions.h"


#include <math.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Page mainPage;

#ifdef _MS_VS
#pragma warning(push)
#pragma warning(disable:4132)
#endif

static const Choice mcShow;
static const Choice mcLookModeChanA;
static const Choice mcLookModeChanB;
static const Choice mcShowFreq;

static const Page mspSet;
static const SmallButton sbSet_Exit;
static const SmallButton sbSet_Channel;
static const SmallButton sbSet_U;
static const SmallButton sbSet_T;
static const SmallButton sbSet_100;
static const SmallButton sbSet_Movement;

#ifdef _MS_VS
#pragma warning(pop)
#endif

static void OnRot_Set(int angle);

static void OnPressSB_Set_Exit(void);

static void OnPressSB_Set_Channel(void);
static void FuncDrawSB_Set_Source(int x, int y);
static void FuncDrawSB_Set_SourceA(int x, int y);
static void FuncDrawSB_Set_SourceB(int x, int y);

static void OnPressSB_Set_U(void);
static void FuncDrawSB_Set_U(int x, int y);
static void FuncDrawSB_Set_U_disable(int x, int y);
static void FuncDrawSB_Set_U_disableBoth(int x, int y);
static void FuncDrawSB_Set_U_enableUpper(int x, int y);
static void FuncDrawSB_Set_U_enableLower(int x, int y);
static void FuncDrawSB_Set_U_enableBoth(int x, int y);

static void OnPressSB_Set_T(void);
static void FuncDrawSB_Set_T(int x, int y);
static void FuncDrawSB_Set_T_disable(int x, int y);
static void FuncDrawSB_Set_T_disableBoth(int x, int y);
static void FuncDrawSB_Set_T_enableLeft(int x, int y);
static void FuncDrawSB_Set_T_enableRight(int x, int y);
static void FuncDrawSB_Set_T_enableBoth(int x, int y);

static void OnPressSB_Set_100(void);
static void FuncDrawSB_Set_100(int x, int y);

static void OnPressSB_Set_Movement(void);
static void FuncDrawSB_Set_Movement(int x, int y);
static void FuncDrawSB_Set_Movement_Percents(int x, int y);
static void FuncDrawSB_Set_Movement_Points(int x, int y);

static void MoveCursUonPercentsOrPoints(int delta);
static void MoveCursTonPercentsOrPoints(int delta);

static void SetShiftCursPosU(Channel ch, int numCur, float delta);    // �������� �������� ������� ������� ���������� �� delta �����
static void SetShiftCursPosT(Channel ch, int numCurs, float delta);   // �������� �������� ������� ������� ������� �� delta �����
static void SetCursPos100(Channel ch);                                // ��������� ������� ��������, ��������������� 100%.
static void SetCursSource(Channel ch);                               // ���������� �������� ��������� ���������.
static void IncCursCntrlU(Channel ch);                                // ������� ��������� ������.
static void IncCursCntrlT(Channel ch);                                // ������� ��������� ������.
static void SetCursPosU(Channel ch, int numCur, float pos);           // ���������� ������� ������� ����������.
static void SetCursPosT(Channel ch, int numCur, float pos);           // ���������� �������� ������� �� �������.



// ������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mpCursors =
{
    Item_Page, &mainPage,
    {
        "�������", "CURSORS"
    },
    {
        "��������� ���������.",
        "Cursor measurements."
    },
    EmptyFuncBV, Page_Cursors,
    {
        (void*)&mcShow,             // ������� -> ����������
        (void*)&mcLookModeChanA,    // ������� -> �������� ����� 1
        (void*)&mcLookModeChanB,    // ������� -> �������� ����� 2
        (void*)&mcShowFreq,         // ������� -> 1/dT
        (void*)&mspSet              // ������� -> ����������
    }
};

// ������� -> ���������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcShow =
{
    Item_Choice, &mpCursors, {"����������", "Shown"},
    {
        "��������/��������� �������.",
        "Enable/disable cursors."
    },
    EmptyFuncBV,
    {
        {"���", "No"},
        {"��",  "Yes"}
    },
    (int8*)&set.cursors.showCursors, EmptyFuncVB, EmptyFuncVII
};

// ������� -> �������� ����� 1 ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcLookModeChanA =
{
    Item_Choice, &mpCursors,
    {
        "�������� \x8e, \x9e", "Tracking \x8e, \x9e"
    },
    {
        "����� ����� �������� �� ������ �������� ������� � ����������:\n"
        "1. \"����\" - ������ ������� � ������ ���������� ��������������� �������.\n"
        "2. \"����������\" - ��� ������ ��������� ��������� ������� ������� ������ ���������� ������������� ����������� ��������� �������.\n"
        "3. \"�����\" - ��� ������ ��������� ��������� ������� ���������� ������ ������� ������������� ����������� ��������� �������.\n"
        "4. \"������ � �����\" - ��������� ��� ���� �� ���������� �������, � ����������� �� ����, �� ����� ������ ������������� ��������� �����������."
        ,
        "Sets the mode tracking for second cursor:\n"                   // WARN �������
        "1. \"Disable\" - all cursors are set manually.\n"
        "2. \"Voltage\" - when manually changing the position of the cursor time cursors voltage automatically track changes in the signal.\n"
        "3. \"Time\" - when manually changing the position of the cursor voltage cursors time automatically track changes in the signal.\n"
        "4. \"Volt and time\" - acts as one of the previous modes, depending on which was carried out last effect cursors."
    },
    EmptyFuncBV,
    {
        {DISABLE_RU,        DISABLE_EN},
        {"����������",      "Voltage"},
        {"�����",           "Time"},
        {"������ � �����",  "Volt and time"}
    },
    (int8*)&set.cursors.lookMode[A], EmptyFuncVB, EmptyFuncVII
};

// ������� -> �������� ����� 2 ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcLookModeChanB =
{
    Item_Choice, &mpCursors, {"�������� \x8f, \x9f", "Tracking \x8f, \x9f"},
    {
        "����� ����� �������� �� ������ �������� ������� � ����������:\n"
        "1. \"����\" - ������ ������� � ������ ���������� ��������������� �������.\n"
        "2. \"����������\" - ��� ������ ��������� ��������� ������� ������� ������ ���������� ������������� ����������� ��������� �������.\n"
        "3. \"�����\" - ��� ������ ��������� ��������� ������� ���������� ������ ������� ������������� ����������� ��������� �������.\n"
        "4. \"������ � �����\" - ��������� ��� ���� �� ���������� �������, � ����������� �� ����, �� ����� ������ ������������� ��������� �����������."
        ,
        "Sets the mode tracking cursors channel 2:\n"
        "1. \"Disable\" - all cursors are set manually.\n"
        "2. \"Voltage\" - when manually changing the position of the cursor time cursors voltage automatically track changes in the signal.\n"
        "3. \"Time\" - when manually changing the position of the cursor voltage cursors time automatically track changes in the signal.\n"
        "4. \"Volt and time\" - acts as one of the previous modes, depending on which was carried out last effect cursors."
    },
    EmptyFuncBV,
    {
        {DISABLE_RU,        DISABLE_EN},
        {"����������",      "Voltage"},
        {"�����",           "Time"},
        {"������. � �����", "Volt. and time"}
    },
    (int8*)&set.cursors.lookMode[B], EmptyFuncVB, EmptyFuncVII
};

// ������� -> 1/dT ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcShowFreq =
{
    Item_Choice, &mpCursors, {"1/dT", "1/dT"},
    {
        "���� ������� \"���\", � ������ ������� ���� ��������� ��������, �������� ���������� ����� ��������� ������� - ������� �������, ���� ������ �������� ����� ���������� ����� ���������� ���������.",
        "If you select \"Enable\" in the upper right corner displays the inverse of the distance between cursors time - frequency signal, a period equal to the distance between the time cursors."
    },
    EmptyFuncBV,
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8*)&CURSORS_SHOW_FREQ, EmptyFuncVB, EmptyFuncVII
};


// ������� -> ���������� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page mspSet =
{
    Item_Page, &mpCursors,
    {
        "����������", "SET"
    },
    {
        "������� � ����� ��������� ���������",
        "Switch to cursor measures"
    },
    EmptyFuncBV, Page_SB_Curs,
    {
        (void*)&sbSet_Exit,     // ������� -> ���������� -> �����
        (void*)&sbSet_Channel,  // ������� -> ���������� -> �����
        (void*)&sbSet_U,        // ������� -> ���������� -> ������� U
        (void*)&sbSet_T,        // ������� -> ���������� -> ������� �
        (void*)&sbSet_100,      // ������� -> ���������� -> 100%
        (void*)&sbSet_Movement  // ������� -> ���������� -> �����������
    },
    EmptyFuncVV, EmptyFuncVV, OnRot_Set
};

static void OnRot_Set(int angle)
{
    if (CURS_ACTIVE_U)
    {
        MoveCursUonPercentsOrPoints(angle);
    }
    else
    {
        MoveCursTonPercentsOrPoints(angle);
    }
    Sound_RegulatorShiftRotate();
}


// ������� -> ���������� -> ����� ------------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSet_Exit =
{
    Item_SmallButton, &mspSet,
    {
        "�����",
        "Exit"
    },
    {
        "������ ��� ������ � ���������� ����",
        "Button to return to the previous menu"
    },
    EmptyFuncBV,
    OnPressSB_Set_Exit,
    DrawSB_Exit
};

static void OnPressSB_Set_Exit(void)
{
    Display_RemoveAddDrawFunction();
}


// ������� -> ���������� -> ����� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSet_Channel =
{
    Item_SmallButton, &mspSet,
    {
        "�����",
        "Channel"
    },
    {
        "����� ������ ��� ��������� ���������",
        "Channel choice for measurements"
    },
    EmptyFuncBV,
    OnPressSB_Set_Channel,
    FuncDrawSB_Set_Source,
    {
        {
            FuncDrawSB_Set_SourceA,
            "����� 1",
            "channel 1"
        },
        {
            FuncDrawSB_Set_SourceB,
            "����� 2",
            "channel 2"
        }
    }
};

static void OnPressSB_Set_Channel(void)
{
    Channel source = CURS_SOURCE_A ? B : A;
    SetCursSource(source);
}

static void FuncDrawSB_Set_Source(int x, int y)
{
    static const pFuncVII func[2] = {FuncDrawSB_Set_SourceA, FuncDrawSB_Set_SourceB};
    func[CURS_SOURCE](x, y);
}

static void FuncDrawSB_Set_SourceA(int x, int y)
{
    Painter_DrawText(x + 7, y + 5, "1");
}

static void FuncDrawSB_Set_SourceB(int x, int y)
{
    Painter_DrawText(x + 7, y + 5, "2");
}

// ������� -> ���������� -> ������� U ---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSet_U =      // ����� ������� ���������� - ������ 1, ������ 2, ��� ������� ��� ���������.
{
    Item_SmallButton, &mspSet,
    {
        "������� U",
        "Cursors U"
    },
    {
        "����� �������� ���������� ��� ��������� � ����������",
        "Choice of cursors of voltage for indication and management"
    },
    EmptyFuncBV,
    OnPressSB_Set_U,
    FuncDrawSB_Set_U,
    {
        {FuncDrawSB_Set_U_disable, "������� ���������� ���������", "cursors of tension are switched off"},
        {FuncDrawSB_Set_U_disableBoth, "������� ���������� ��������", "cursors of tension are switched on"},
        {FuncDrawSB_Set_U_enableUpper, "������� ���������� ��������, ���������� ������� ��������", "cursors of tension are switched on, control of the top cursor"},
        {FuncDrawSB_Set_U_enableLower, "������� ���������� ��������, ���������� ������ ��������", "cursors of tension are switched on, control of the lower cursor"},
        {FuncDrawSB_Set_U_enableBoth, "������� ���������� ��������, ���������� ������ ���������", "cursors of tension are switched on, control of both cursors"}
    }
};

static void OnPressSB_Set_U(void)
{
    if (CURS_ACTIVE_U || CURsU_DISABLED)
    {
        IncCursCntrlU(CURS_SOURCE);
    }
    CURS_ACTIVE = CursActive_U;
}

static void FuncDrawSB_Set_U(int x, int y)
{
    Channel source = CURS_SOURCE;
    if (CURsU_DISABLED)
    {
       FuncDrawSB_Set_U_disable(x, y);
    }
    else
    {
        if (!CURS_ACTIVE_U)
        {
            FuncDrawSB_Set_U_disableBoth(x, y);
        }
        else
        {
            bool condTop = false, condDown = false;
            CalculateConditions((int16)sCursors_GetCursPosU(source, 0), (int16)sCursors_GetCursPosU(source, 1), CURsU_CNTRL, &condTop, &condDown);
            if (condTop && condDown)
            {
                FuncDrawSB_Set_U_enableBoth(x, y);
            }
            else if (condTop)
            {
                FuncDrawSB_Set_U_enableUpper(x, y);
            }
            else
            {
                FuncDrawSB_Set_U_enableLower(x, y);
            }
        }
    }
}

static void FuncDrawSB_Set_U_disable(int x, int y)
{
    Painter_DrawText(x + 7, y + 5, "U");
}

static void FuncDrawSB_Set_U_disableBoth(int x, int y)
{
    DrawMenuCursVoltage(x + 7, y + 5, false, false);
}

static void FuncDrawSB_Set_U_enableUpper(int x, int y)
{
    DrawMenuCursVoltage(x + 7, y + 5, true, false);
}

static void FuncDrawSB_Set_U_enableLower(int x, int y)
{
    DrawMenuCursVoltage(x + 7, y + 5, false, true);
}

static void FuncDrawSB_Set_U_enableBoth(int x, int y)
{
    DrawMenuCursVoltage(x + 7, y + 5, true, true);
}


// ������� -> ���������� -> ������� � ---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSet_T =      // ����� ������� ������� - ������ 1, ������ 2, ��� ������� ��� ���������.
{
    Item_SmallButton, &mspSet,
    {
        "������� T",
        "Cursors T"
    },
    {
        "����� �������� ������� ��� ��������� � ����������",
        "Choice of cursors of time for indication and management"
    },
    EmptyFuncBV,
    OnPressSB_Set_T,
    FuncDrawSB_Set_T,
    {
        {FuncDrawSB_Set_T_disable, "������� ������� ���������", "cursors of time are switched off"},
        {FuncDrawSB_Set_T_disableBoth, "������� ������� ��������", "cursors of time are switched on"},
        {FuncDrawSB_Set_T_enableLeft, "������� ������� ��������, ���������� ����� ��������", "cursors of time are switched on, control of the left cursor"},
        {FuncDrawSB_Set_T_enableRight, "������� ������� ��������, ���������� ������ ��������", "cursors of time are switched on, control of the right cursor"},
        {FuncDrawSB_Set_T_enableBoth, "������� ������� ��������, ���������� ������ ���������", "cursors of time are switched on, control of both cursors"}
    }
};

static void OnPressSB_Set_T(void)
{
    if (CURS_ACTIVE_T || CURsT_DISABLED)
    {
        IncCursCntrlT(CURS_SOURCE);
    }
    CURS_ACTIVE = CursActive_T;
}

static void FuncDrawSB_Set_T(int x, int y)
{
    if (CURsT_DISABLED)
    {
        FuncDrawSB_Set_T_disable(x, y);
    }
    else
    {
        if (!CURS_ACTIVE_T)
        {
            FuncDrawSB_Set_T_disableBoth(x, y);
        }
        else
        {
            bool condLeft = false, condDown = false;
            Channel source = CURS_SOURCE;
            CalculateConditions((int16)CURsT_POS(source, 0), (int16)CURsT_POS(source, 1), CURsT_CNTRL, &condLeft, &condDown);
            if (condLeft && condDown)
            {
                FuncDrawSB_Set_T_enableBoth(x, y);
            }
            else if (condLeft)
            {
                FuncDrawSB_Set_T_enableLeft(x, y);
            }
            else
            {
                FuncDrawSB_Set_T_enableRight(x, y);
            }
        }
    }
}

static void FuncDrawSB_Set_T_disable(int x, int y)
{
    Painter_DrawText(x + 7, y + 5, "T");
}

static void FuncDrawSB_Set_T_disableBoth(int x, int y)
{
    DrawMenuCursTime(x, y, false, false);
}

static void FuncDrawSB_Set_T_enableLeft(int x, int y)
{
    DrawMenuCursTime(x, y, true, false);
}

static void FuncDrawSB_Set_T_enableRight(int x, int y)
{
    DrawMenuCursTime(x, y, false, true);
}

static void FuncDrawSB_Set_T_enableBoth(int x, int y)
{
    DrawMenuCursTime(x, y, true, true);
}

// ������� -> ���������� -> 100% ---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSet_100 =    // ��������� 100 ��������� � ������� ����� ��������.
{
    Item_SmallButton, &mspSet,
    {
        "100%",
        "100%"
    },
    {
        "������������ ��� ���������� ���������. ������� �������� ���������� ����� ��������� ��������� ��� 100%",
        "It is used for percentage measurements. Pressing marks distance between active cursors as 100%"
    },
    EmptyFuncBV,
    OnPressSB_Set_100,
    FuncDrawSB_Set_100
};

static void OnPressSB_Set_100(void)
{
    SetCursPos100(CURS_SOURCE);
}

static void FuncDrawSB_Set_100(int x, int y)
{
    Painter_SetFont(TypeFont_5);
    Painter_DrawText(x + 2, y + 3, "100%");
    Painter_SetFont(TypeFont_8);
}


// ������� -> ���������� -> ����������� ---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSet_Movement =     // ������������ ���� ����������� �������� - �� �������� ��� �� ���������.
{
    Item_SmallButton, &mspSet,
    {
        "�����������",
        "Movement"
    },
    {
        "����� ���� ����������� �������� - �������� ��� �����",
        "Choice of a step of movement of cursors - percent or points"
    },
    EmptyFuncBV,
    OnPressSB_Set_Movement,
    FuncDrawSB_Set_Movement,
    {
        {FuncDrawSB_Set_Movement_Percents, "��� ����������� �������� ������ ������ ��������", "the step of movement of cursors is multiple to one percent"},
        {FuncDrawSB_Set_Movement_Points, "��� ����������� ������� ������ ������ �������", "the step of movement of the cursor is multiple to one pixel"}
    }
};

static void OnPressSB_Set_Movement(void)
{
    CircleIncreaseInt8((int8*)&set.cursors.movement, 0, 1);
}

static void FuncDrawSB_Set_Movement(int x, int y)
{
    if (CURS_MOVE_PERCENTS)
    {
        FuncDrawSB_Set_Movement_Percents(x, y);
    }
    else
    {
        FuncDrawSB_Set_Movement_Points(x, y);
    }
}

static void FuncDrawSB_Set_Movement_Percents(int x, int y)
{
    Painter_DrawText(x + 6, y + 5, "\x83");
}

static void FuncDrawSB_Set_Movement_Points(int x, int y)
{
    Painter_SetFont(TypeFont_5);
    Painter_DrawText(x + 4, y + 3, "���");
    Painter_SetFont(TypeFont_8);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MAX_POS_U   200
#define MAX_POS_T   280

static void SetShiftCursPosU(Channel ch, int numCur, float delta)
{
    if (CURS_MOVE_PERCENTS)
    {
        CURsU_POS(ch, numCur) = LimitationFloat(CURsU_POS(ch, numCur) - delta, 0, MAX_POS_U);
    }
    else
    {
        CURsU_POS(ch, numCur) = LimitationFloat(CURsU_POS(ch, numCur) - delta, 0, MAX_POS_U);
    }
}


static void SetCursPosU(Channel ch, int numCur, float pos)
{
    if (CURS_MOVE_PERCENTS)
    {
        CURsU_POS(ch, numCur) = LimitationFloat(pos, 0, MAX_POS_U);
    }
    else
    {
        CURsU_POS(ch, numCur) = LimitationFloat(pos, 0, MAX_POS_U);
    }
}

void SetShiftCursPosT(Channel ch, int numCur, float delta)
{
    if (CURS_MOVE_PERCENTS)
    {
        CURsT_POS(ch, numCur) = LimitationFloat(CURsT_POS(ch, numCur) + delta, 0, MAX_POS_T);
    }
    else
    {
        CURsT_POS(ch, numCur) = LimitationFloat(CURsT_POS(ch, numCur) + delta, 0, MAX_POS_T);
    }
}

void SetCursPosT(Channel ch, int numCur, float pos)
{
    if (CURS_MOVE_PERCENTS)
    {
        CURsT_POS(ch, numCur) = LimitationFloat(pos, 0, MAX_POS_T);
    }
    else
    {
        CURsT_POS(ch, numCur) = LimitationFloat(pos, 0, MAX_POS_T);
    }
}

static void SetCursPos100(Channel ch)
{
    dUperc(ch) = (float)fabs(CURsU_POS(ch, 0) - CURsU_POS(ch, 1));
    dTperc(ch) = (float)fabs(CURsT_POS(ch, 0) - CURsT_POS(ch, 1));
}

static void SetCursSource(Channel ch)
{
    CURS_SOURCE = ch;
}

static void IncCursCntrlU(Channel ch)
{
    CircleIncreaseInt8((int8*)&CURsU_CNTRL_CH(ch), 0, 3);
}

static void IncCursCntrlT(Channel ch)
{
    CircleIncreaseInt8((int8*)&CURsT_CNTRL_CH(ch), 0, 3);
}

void CursorsUpdate(void)
{
    Channel source = CURS_SOURCE;

    float posT0 = 0.0f, posT1 = 0.0f;

    if(CURS_ACTIVE_T && (CURS_LOOK_U(0) || CURS_LOOK_BOTH(0)))
    {
        float posU0 = Processing_GetCursU(source, CURsT_POS(source, 0));
        SetCursPosU(source, 0, posU0);
    }
    if(CURS_ACTIVE_T && (CURS_LOOK_U(1) || CURS_LOOK_BOTH(1)))
    {
        float posU1 = Processing_GetCursU(source, CURsT_POS(source, 1));
        SetCursPosU(source, 1, posU1);
    }
    if(CURS_ACTIVE_U && (CURS_LOOK_T(0) || CURS_LOOK_BOTH(0)))
    {
        float posU0 = CURsU_POS(source, 0);
        posT0 = Processing_GetCursT(source, posU0, 0);
        SetCursPosT(source, 0, posT0);
    }
    if(CURS_ACTIVE_U && (CURS_LOOK_T(1) || CURS_LOOK_BOTH(1)))
    {
        float posU1 = CURsU_POS(source, 1);
        posT1 = Processing_GetCursT(source, posU1, 1);
        SetCursPosT(source, 1, posT1);
    }
}

static void MoveCursUonPercentsOrPoints(int delta)
{
    float value = (float)delta;

    if (CURS_MOVE_PERCENTS)
    {
        value *= dUperc(CURS_SOURCE) / 100.0f;
    }

    if (CURsU_CNTRL_1 || CURsU_CNTRL_1_2)
    {
        SetShiftCursPosU(CURS_SOURCE, 0, value);
    }
    if (CURsU_CNTRL_2 || CURsU_CNTRL_1_2)
    {
        SetShiftCursPosU(CURS_SOURCE, 1, value);
    }
    CursorsUpdate();
}

static void MoveCursTonPercentsOrPoints(int delta)
{
    float value = (float)delta;

    if (CURS_MOVE_PERCENTS)
    {
        value *= dTperc(CURS_SOURCE) / 100.0f;
    }

    if (CURsT_CNTRL_1 || CURsT_CNTRL_1_2)
    {
        SetShiftCursPosT(CURS_SOURCE, 0, value);
    }
    if (CURsT_CNTRL_2 || CURsT_CNTRL_1_2)
    {
        SetShiftCursPosT(CURS_SOURCE, 1, value);
    }
    CursorsUpdate();
}

bool IsRegSetActiveOnCursors(void)
{
    return ((GetNameOpenedPage() == Page_SB_Curs) &&
        ((CURS_ACTIVE_U && CURsU_ENABLED) || (CURS_ACTIVE_T && CURsT_ENABLED)));
}

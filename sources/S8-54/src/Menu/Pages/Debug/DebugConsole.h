#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mspConsole;


// ������� - ������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Governor mgConsole_NumStrings =
{
    Item_Governor, &mspConsole, 0,
    {
        "����� �����", "Number strings",
        "",
        ""
    },
    &CONSOLE_NUM_STRINGS, 0, 33
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_SizeFont =
{
    Item_Choice, &mspConsole, 0,
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_ModeStop =
{
    Item_Choice, &mspConsole, 0,
    {
        "���. ��������", "Mode stop",
        "������������� ����������� ������������ ������ � ������� ���� ������� �� ������ ����/����",
        "It provides the ability to pause the output to the console by pressing the ����/���� button"
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ModePauseConsole
};

const Page mspConsole_Registers;

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_ShowAll =
{
    Item_Choice, &mspConsole_Registers, 0,
    {
        "���������� ���", "Show all",
        "���������� ��� ��������, ���������� � ��������",
        "To show all values transferred in registers"
    },
    {
        {"���", "No"},
        {"��", "Yes"}
    },
    (int8*)&DBG_SHOW_ALL
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool IsActive_Registers(void)
{
    return DBG_SHOW_ALL;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RD_FL =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "RD_FL", "RD_FL",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&DBG_SHOW_FLAG
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RShiftA =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "U ��. 1�", "U shift 1ch",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowRShift[A]
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RShiftB =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "U ��. 2�", "U shift 2ch",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowRShift[B]
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_TrigLev =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "U �����.", "U trig.",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowTrigLev
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RangeA =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "�����/��� 1", "Range 1",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowRange[A]
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_RangeB =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "�����/��� 2", "Range 2",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowRange[B]
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_TrigParam =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "�����. �����.", "Trig param",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowTrigParam
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_ChanParamA =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "�����. ���. 1", "Chan 1 param",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowChanParam[A]
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_ChanParamB =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "�����. ���. 2", "Chan 2 param",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowChanParam[B]
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_TBase =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "�����/���", "TBase",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowTBase
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcConsole_Registers_TShift =
{
    Item_Choice, &mspConsole_Registers, IsActive_Registers,
    {
        "� ��.", "tShift",
        "",
        ""
    },
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&set.dbg_ShowTShift
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Page mspConsole_Registers =
{
    Item_Page, &mspConsole, 0,
    {
        "��������", "REGISTERS",
        "",
        ""
    },
    Page_DebugShowRegisters,
    {
        (void*)&mcConsole_Registers_ShowAll,      // ������� - ������� - �������� - ���������� ���
        (void*)&mcConsole_Registers_RD_FL,        // ������� - ������� - �������� - RD_FL
        (void*)&mcConsole_Registers_RShiftA,      // ������� - ������� - �������� - U ��. 1�
        (void*)&mcConsole_Registers_RShiftB,      // ������� - ������� - �������� - U ��. 2�
        (void*)&mcConsole_Registers_TrigLev,      // ������� - ������� - �������� - U �����
        (void*)&mcConsole_Registers_RangeA,       // ������� - ������� - �������� - �����/��� 1
        (void*)&mcConsole_Registers_RangeB,       // ������� - ������� - �������� - �����/��� 2
        (void*)&mcConsole_Registers_TrigParam,    // ������� - ������� - �������� - �����. �����.
        (void*)&mcConsole_Registers_ChanParamA,   // ������� - ������� - �������� - �����. ���. 1
        (void*)&mcConsole_Registers_ChanParamB,   // ������� - ������� - �������� - �����. ���. 2
        (void*)&mcConsole_Registers_TBase,        // ������� - ������� - �������� - �����/���
        (void*)&mcConsole_Registers_TShift        // ������� - ������� - �������� - � ��.
    }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void FuncDrawSizeSettings(int x, int y)
{
    char buffer[30];
    sprintf(buffer, "����.�����. %d", sizeof(Settings));
    Painter_DrawTextC(x + 6, y + 13, buffer, gColorBack);
    LOG_WRITE(buffer);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Button mbConsole_SizeSettings =
{
    Item_Button, &mspConsole, 0,
    {
        "", "",
        "���������� ������� ������ ��������� ��� ���������� ��������",
        "Displays the current size of the structure to save settings"
    },
    0, FuncDrawSizeSettings
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const Page mspConsole =
{
    Item_Page, &mpDebug, 0,
    {
        "�������", "CONSOLE",
        "",
        ""
    },
    Page_DebugConsole,
    {
        (void*)&mgConsole_NumStrings,   // ������� - ������� - ����� �����
        (void*)&mcConsole_SizeFont,     // ������� - ������� - ������ ������
        (void*)&mcConsole_ModeStop,     // ������� - ������� - ���. ��������
        (void*)&mspConsole_Registers,   // ������� - ������� - ��������
        (void*)&mbConsole_SizeSettings  // ������� - ������� - ����. ��������

    }
};

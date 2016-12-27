#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "PageMemory.h"
#include "Definition.h"
#include "Menu/FileManager.h"
#include "Menu/MenuFunctions.h"
#include "FPGA/FPGA.h"
#include "FPGA/FPGA_Types.h"
#include "FPGA/DataStorage.h"
#include "Display/Colors.h"
#include "Display/Display.h"
#include "Display/font/Font.h"
#include "Display/Painter.h"
#include "Display/Grid.h"
#include "Display/Symbols.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/Math.h"
#include "FlashDrive/FlashDrive.h"
#include "Hardware/FLASH.h"
#include "Hardware/Sound.h"
#include "Log.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Page mainPage;

extern void PressSB_FM_Tab(void);

static const Choice mcLengthMemory;
static bool IsActive_MemoryLength(void);
       void OnChange_MemoryLength(bool active);


static const Page mspLast;
static void OnPress_Last(void);
static void OnDraw_Last(void);
static void OnRot_Last(int angle);

static const SmallButton sbLast_Exit;
static void OnPress_Last_Exit(void);

static const SmallButton sbLast_Next;
static void OnPress_Last_Next(void);
static void Draw_Last_Next(int x, int y);

static const SmallButton sbLast_Prev;
static void OnPress_Last_Prev(void);
static void Draw_Last_Prev(int x, int y);

static const SmallButton sbLast_IntEnter;
static void OnPress_Last_IntEnter(void);
static void Draw_Last_IntEnter(int x, int y);

static const SmallButton sbLast_SaveToDrive;
static void OnPress_Last_SaveToDrive(void);
static void Draw_Last_SaveToDrive(int x, int y);


static const Page mspInt;
static void OnPress_Int(void);
static void OnDraw_Int(void);
static void OnReg_Int(int delta);

static const SmallButton sbInt_Exit;
static void OnPress_Int_Exit(void);

static const SmallButton sbInt_ShowSignalsAlways;
static void OnPress_Int_ShowSignalAlways(void);
static void Draw_Int_ShowSignalAlways(int x, int y);
static void Draw_Int_ShowSignalAllways_Yes(int x, int y);
static void Draw_Int_ShowSignalAllways_No(int x, int y);

static const SmallButton sbInt_ModeShow;
static void OnPress_Int_ModeShow(void);
static void Draw_Int_ModeShow(int x, int y);
static void Draw_Int_ModeShow_Direct(int x, int y);
static void Draw_Int_ModeShow_Saved(int x, int y);
static void Draw_Int_ModeShow_Both(int x, int y);

static const SmallButton sbInt_SaveToMemory;
static void OnPress_Int_SaveToMemory(void);
static void Draw_Int_SaveToMemory(int x, int y);

static const SmallButton sbInt_SaveToDrive;
static void OnPress_Int_SaveToDrive(void);
static void Draw_Int_SaveToDrive(int x, int y);


static const Page mspDrive;
static const Choice mcDrive_Name;
static const Choice mcDrive_ModeSave;
static const Choice mcDrive_ModeBtnMemory;
static const Choice mcDrive_Autoconnect;


static const Page mspDrive_Manager;
static bool FuncOfActiveExtMemFolder(void);
       void OnPressMemoryExtFileManager(void);

static const SmallButton sbExitFileManager;
static void PressSB_FM_Exit(void);

static const SmallButton sbFileManagerTab;
static void DrawSB_FM_Tab(int x, int y);

static const SmallButton sbFileManagerLevelUp;
static void DrawSB_FM_LevelUp(int x, int y);

static const SmallButton sbFileManagerLevelDown;
static void DrawSB_FM_LevelDown(int x, int y);


static const Page mspSetMask;
static bool IsActiveMemoryExtSetMask(void);
static void OnPressMemoryExtMask(void);
static void OnMemExtSetMaskRegSet(int angle);

static const SmallButton sbExitSetMask;
static void PressSB_SetMask_Exit(void);

static const SmallButton sbSetMaskDelete;
static void PressSB_SetMask_Delete(void);
static void DrawSB_SetMask_Delete(int x, int y);

static const SmallButton sbSetMaskBackspace;
static void PressSB_SetMask_Backspace(void);
static void DrawSB_SetMask_Backspace(int x, int y);

static const SmallButton sbSetMaskInsert;
static void PressSB_SetMask_Insert(void);
static void DrawSB_SetMask_Insert(int x, int y);

    const Page mpSetName;
static void OnMemExtSetNameRegSet(int angle);
static const SmallButton sbExitSetName;
static void PressSB_SetName_Exit(void);
static const SmallButton sbSetNameDelete;
static void PressSB_SetName_Delete(void);
static void DrawSB_SetName_Delete(int x, int y);
static const SmallButton sbSetNameBackspace;
static void PressSB_SetName_Backspace(void);
static void DrawSB_SetName_Backspace(int x, int y);
static const SmallButton sbSetNameInsert;
static void PressSB_SetName_Insert(void);
static void DrawSB_SetName_Insert(int x, int y);
static const SmallButton sbSetNameSave;
static void PressSB_MemExtSetNameSave(void);
static void DrawSB_MemExtSetNameSave(int x, int y);


static void DrawSetMask(void);  // ��� ������� ������, ����� ������ ����� ������� �����.
static void DrawSetName(void);  // ��� ������� ������, ����� ����� ������ ��� ����� ��� ����������

static void DrawMemoryWave(int num, bool exist);
static void SaveSignalToIntMemory(void);
static void OnMemExtSetMaskNameRegSet(int angle, int maxIndex);

static const char* symbols[] =
{
    /* 0x00 */ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", /* 0x19 */
    /* 0x1a */ " ", "_", "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", /* 0x26 */
    /* 0x27 */ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", /* 0x40 */
    //         0x41  0x42  0x43  0x44  0x45  0x46   0x47   - ��� ���������� ����� �������� � ���� �������
    /* 0x41 */ "%y", "%m", "%d", "%H", "%M", "%S", "%N" /* 0x47 */
    //         0x01  0x02  0x03  0x04  0x05  0x06   0x07   - ��� ����� ���������� �������� �������� � set.memory.fileNameMask
};

// ������ ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mpMemory =
{
    Item_Page, &mainPage,
    {
        "������", "MEMORY"
    },
    {
        "������ � ������� � ���������� �������.",
        "Working with external and internal memory."
    },
    EmptyFuncBV, Page_Memory,
    {
        (void*)&mcLengthMemory, // ������ -> �����
        (void*)&mspLast,        // ������ -> ���������
        (void*)&mspInt,         // ������ -> ����� ��
        (void*)&mspDrive        // ������ -> ����� ��
    }
};

// ������ -> ����� ---------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcLengthMemory =
{
    Item_Choice, &mpMemory, {"����� ������", "Mem length"},
    {
        "����� ���������� �������� ��� ����������� ��������. "
        "��� ���������� ���������� �������� ����������� ���������� ���������� � ������ ��������.",

        "Choice of number of counting for the saved signals. "
        "At increase in number of counting the quantity of the signals kept in memory decreases."
    },
    IsActive_MemoryLength,
    {
        {"512", "512"},
        {"1�",  "1k"},
        {"2�",  "2k"},
        {"4�",  "4k"},
        {"8�",  "8k"},
        {"16�", "16k"}
        //,{"32�", "32k"}
    },
    (int8*)&FPGA_NUM_POINTS, OnChange_MemoryLength, EmptyFuncVII
};

static bool IsActive_MemoryLength(void)
{
    return PEACKDET_DIS;
}

void OnChange_MemoryLength(bool active)
{
    // ���� ������� ������� ��������, �� �� ����� ����������� ������
    if (PEACKDET_EN && !active)
    {
        Display_ShowWarning(WrongModePeackDet);
        return;
    }

    // ��������� ��������� 32� ����� ������, ���� ������� ������ �����
    if (FPGA_NUM_POINTS_32k && ENABLE_B)
    {
        Display_ShowWarning(DisableChannel2);
        FPGA_NUM_POINTS = FNP_16k;
    }

    int width = GridWidth();
    
    FPGA_Reset();
    if (sMemory_NumBytesInChannel(false) == 281)
    {
        SHIFT_IN_MEMORY = 0;
    }
    else
    {
        if (PEACKDET_EN)
        {
            width *= 2;
        }
        if (TPOS_LEFT)
        {
            SHIFT_IN_MEMORY = 0;
        }
        else if (TPOS_CENTER)
        {
            SHIFT_IN_MEMORY = (int16)(sMemory_NumBytesInChannel(false) / 2 - width / 2);
        }
        else if (TPOS_RIGHT)
        {
            SHIFT_IN_MEMORY = (int16)(sMemory_NumBytesInChannel(false) - width - 2);
        }
    }
    FPGA_Reset();
    FPGA_SetTShift(TSHIFT);
    FPGA_Reset();
    //LOG_WRITE("shift %d, num %d, width %d", SHIFT_IN_MEMORY, sMemory_NumBytesInChannel(false), width);
}

// ������ -> ��������� ---------------------------------------------------------------------------------------------------------------------------------------------------------------
static const Page mspLast =
{
    Item_Page, &mpMemory,
    {
        "���������", "LATEST"
    },
    {
        "������� � ����� ������ � ���������� ����������� ���������",
        "Transition to an operating mode with the last received signals"
    },
    EmptyFuncBV, Page_SB_MemLatest,
    {
        (void*)&sbLast_Exit,        // ������ -> ��������� -> �����
        (void*)0,
        (void*)&sbLast_Next,        // ������ -> ��������� -> ���������
        (void*)&sbLast_Prev,        // ������ -> ��������� -> ����������
        (void*)&sbLast_IntEnter,    // ������ -> ��������� -> ����� ��
        (void*)&sbLast_SaveToDrive  // ������ -> ��������� -> ���������
    },
    OnPress_Last, OnDraw_Last, OnRot_Last
};

static void OnPress_Last(void)
{
    gMemory.currentNumLatestSignal = 0;
    gMemory.runningFPGAbeforeSmallButtons = FPGA_IsRunning() ? 1 : 0;
    FPGA_Stop(false);
    MODE_WORK = ModeWork_Latest;
}

static void OnDraw_Last(void)
{
    char buffer[20];

    int width = 40;
    int height = 10;
    Painter_FillRegionC(GridRight() - width, GRID_TOP, width, height, gColorBack);
    Painter_DrawRectangleC(GridRight() - width, GRID_TOP, width, height, gColorFill);
    Painter_DrawText(GridRight() - width + 2, GRID_TOP + 1, Int2String(gMemory.currentNumLatestSignal + 1, false, 3, buffer));
    Painter_DrawText(GridRight() - width + 17, GRID_TOP + 1, "/");
    Painter_DrawText(GridRight() - width + 23, GRID_TOP + 1, Int2String(DS_NumElementsInStorage(), false, 3, buffer));
}

static void OnRot_Last(int angle)
{
    if (DS_NumElementsInStorage() > 1)
    {
        Sound_RegulatorSwitchRotate();
    }
    if (Math_Sign(angle) > 0)
    {
        OnPress_Last_Next();
    }
    else
    {
        OnPress_Last_Prev();
    }
}

// ������ -> ��������� -> ����� --------------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbLast_Exit =
{
    Item_SmallButton, &mspLast,
    COMMON_BEGIN_SB_EXIT
    OnPress_Last_Exit,
    DrawSB_Exit
};

static void OnPress_Last_Exit(void)
{
    MODE_WORK = ModeWork_Direct;
    if (gMemory.runningFPGAbeforeSmallButtons == 1)
    {
        FPGA_Start();
        gMemory.runningFPGAbeforeSmallButtons = 0;
    }
    Display_RemoveAddDrawFunction();
}

// ������ -> ��������� -> ��������� ----------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbLast_Next =
{
    Item_SmallButton, &mspLast,
    {
        "���������",
        "Next"
    },
    {
        "������� � ���������� �������",
        "Go to the next signal"
    },
    EmptyFuncBV,
    OnPress_Last_Next,
    Draw_Last_Next
};

static void OnPress_Last_Next(void)
{
    CircleIncreaseInt16(&gMemory.currentNumLatestSignal, 0, (int16)(DS_NumElementsInStorage() - 1));
}

static void Draw_Last_Next(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x64');
    Painter_SetFont(TypeFont_8);
}

// ������ -> ��������� -> ���������� ---------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbLast_Prev =
{
    Item_SmallButton, &mspLast,
    {
        "����������",
        "Previous"
    },
    {
        "������� � ����������� �������",
        "Go to the previous signal"
    },
    EmptyFuncBV,
    OnPress_Last_Prev,
    Draw_Last_Prev
};

static void OnPress_Last_Prev(void)
{
    CircleDecreaseInt16(&gMemory.currentNumLatestSignal, 0, (int16)(DS_NumElementsInStorage() - 1));
}

static void Draw_Last_Prev(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x20');
    Painter_SetFont(TypeFont_8);
}

// ������ -> ��������� -> ����� �� -------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbLast_IntEnter =
{
    Item_SmallButton, &mspLast,
    {
        "����� ��",
        "Internal storage"
    },
    {
        "������� ��� ������, ����� ��������� ������ �� ���������� ������������ ����������",
        "Press this button to keep a signal in an internal memory"
    },
    EmptyFuncBV,
    OnPress_Last_IntEnter,
    Draw_Last_IntEnter
};

static void OnPress_Last_IntEnter(void)
{
    return;
    OpenPageAndSetItCurrent(Page_SB_MemInt);
    MODE_WORK = ModeWork_MemInt;
    FLASH_GetData(gMemory.currentNumIntSignal, &gDSmemInt, &gDataAmemInt, &gDataBmemInt);
    gMemory.exitFromIntToLast = 1;
}

static void Draw_Last_IntEnter(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x40');
    Painter_SetFont(TypeFont_8);
}


// ������ -> ��������� -> ��������� ------------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbLast_SaveToDrive =
{
    Item_SmallButton, &mspLast,
    {
        "���������",
        "Save"
    },
    {
        "������ ���������� �������� ��� ������������� ������� ��. ��������� ��������� ������ �� ������ ��",
        "Click this button to save the signal on the external FLASH"
    },
    EmptyFuncBV,
    OnPress_Last_SaveToDrive,
    Draw_Last_SaveToDrive
};

static void OnPress_Last_SaveToDrive(void)
{
    gMemory.exitFromModeSetNameTo = RETURN_TO_LAST_MEM;
    Memory_SaveSignalToFlashDrive();
}

static void Draw_Last_SaveToDrive(int x, int y)
{
    if (gFlashDriveIsConnected)
    {
        Painter_SetFont(TypeFont_UGO2);
        Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x42');
        Painter_SetFont(TypeFont_8);
    }
}


// ������ -> ����� �� ---------------------------------------------------------------------------------------------------------------------------------------------------------------
static const Page mspInt =
{
    Item_Page, &mpMemory,
    {
        "����� ��", "INT STORAGE"
    },
    {
        "������� � ����� ������ � ���������� �������",
        "Transition to an operating mode with internal memory"
    },
    EmptyFuncBV, Page_SB_MemInt,
    {
        (void*)&sbInt_Exit,                 // ������ -> ����� �� -> �����
        (void*)&sbInt_ShowSignalsAlways,    // ������ -> ����� �� -> ���������� ������
        (void*)&sbInt_ModeShow,             // ������ -> ����� �� -> ��� �������
        (void*)0,
        (void*)&sbInt_SaveToMemory,         // ������ -> ����� �� -> ���������
        (void*)&sbInt_SaveToDrive           // ������ -> ����� �� -> ��������� �� ������
    },
    OnPress_Int, OnDraw_Int, OnReg_Int
};

static void OnPress_Int(void)
{
    OpenPageAndSetItCurrent(Page_SB_MemInt);
    MODE_WORK = ModeWork_MemInt;
    FLASH_GetData(gMemory.currentNumIntSignal, &gDSmemInt, &gDataAmemInt, &gDataBmemInt);
}

static void OnDraw_Int(void)
{
    // ������ �������� ��������� ������

    bool exist[MAX_NUM_SAVED_WAVES] = {false};

    FLASH_GetDataInfo(exist);

    for (int i = 0; i < MAX_NUM_SAVED_WAVES; i++)
    {
        DrawMemoryWave(i, exist[i]);
    }
}

static void DrawMemoryWave(int num, bool exist)
{
    char buffer[20];

    int x = GridLeft() + 2 + num * 12;
    int y = GridFullBottom() - 10;
    int width = 12;
    Painter_FillRegionC(x, y, width, 10, num == gMemory.currentNumIntSignal ? COLOR_FLASH_10 : gColorBack);
    Painter_DrawRectangleC(x, y, width, 10, gColorFill);
    Painter_SetColor(num == gMemory.currentNumIntSignal ? COLOR_FLASH_01 : gColorFill);
    if (exist)
    {
        Painter_DrawText(x + 2, y + 1, Int2String(num + 1, false, 2, buffer));
    }
    else
    {
        Painter_DrawText(x + 3, y + 1, "\x88");
    }
}

static void OnReg_Int(int delta)
{
    Sound_RegulatorSwitchRotate();
    if (delta < 0)
    {
        CircleDecreaseInt8(&gMemory.currentNumIntSignal, 0, MAX_NUM_SAVED_WAVES - 1);
    }
    else if (delta > 0)
    {
        CircleIncreaseInt8(&gMemory.currentNumIntSignal, 0, MAX_NUM_SAVED_WAVES - 1);
    }
    FLASH_GetData(gMemory.currentNumIntSignal, &gDSmemInt, &gDataAmemInt, &gDataBmemInt);
    Painter_ResetFlash();
}

// ������ -> ����� �� -> ����� ------------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbInt_Exit =
{
    Item_SmallButton, &mspInt,
    {
        "�����",
        "Exit"
    },
    {
        "������ ��� ������ � ���������� ����",
        "Button to return to the previous menu"
    },
    EmptyFuncBV,
    OnPress_Int_Exit,
    DrawSB_Exit
};

static void OnPress_Int_Exit(void)
{
    FLASH_GetData(gMemory.currentNumIntSignal, &gDSmemInt, &gDataAmemInt, &gDataBmemInt);
    if (gMemory.exitFromIntToLast == 1)
    {
        OpenPageAndSetItCurrent(Page_SB_MemLatest);
        MODE_WORK = ModeWork_Latest;
        gMemory.exitFromIntToLast = 0;
    }
    else
    {
        MODE_WORK = ModeWork_Direct;
        if (gMemory.runningFPGAbeforeSmallButtons == 1)
        {
            FPGA_Start();
            gMemory.runningFPGAbeforeSmallButtons = 0;
        }
        Display_RemoveAddDrawFunction();
        //ShortPressOnPageItem(PagePointerFromName(Page_SB_MemInt), 0);
    }
}


// ������ -> ����� �� -> ���������� ������ --------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbInt_ShowSignalsAlways =
{
    Item_SmallButton, &mspInt,
    {
        "���������� ������",
        "To show always"
    },
    {
        "��������� ������ ���������� ��������� ���������� ������ ������ ��������",
        "Allows to show always the chosen kept signal over the current"
    },
    EmptyFuncBV,
    OnPress_Int_ShowSignalAlways,
    Draw_Int_ShowSignalAlways,
    {
        {
            Draw_Int_ShowSignalAllways_Yes,
            "���������� ��������� ������ �� ���������� ������ ������ ��������",
            "to show the chosen signal from internal memory over the current"
        },
        {
            Draw_Int_ShowSignalAllways_No,
            "������ �� ���������� ������ ����� ������ � ������ ������ � ���������� ������������ �����������",
            "the signal from internal memory is visible only in an operating mode with an internal memory"
        }
    }
};

static void OnPress_Int_ShowSignalAlways(void)
{
    gMemory.alwaysShowMemIntSignal = (gMemory.alwaysShowMemIntSignal == 0) ? 1 : 0;
}

static void Draw_Int_ShowSignalAlways(int x, int y)
{
    if (gMemory.alwaysShowMemIntSignal == 0)
    {
        Draw_Int_ShowSignalAllways_No(x, y);
    }
    else
    {
        Draw_Int_ShowSignalAllways_Yes(x, y);
    }
}

static void Draw_Int_ShowSignalAllways_Yes(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x66');
    Painter_SetFont(TypeFont_8);
}


static void Draw_Int_ShowSignalAllways_No(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x68');
    Painter_SetFont(TypeFont_8);
}

// ������ -> ����� �� -> ��� ������� -------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbInt_ModeShow =
{
    Item_SmallButton, &mspInt,
    {
        "��� �������",
        "Type of a signal"
    },
    {
        "���������� ���������� ��� ������� ������ � ������ ����� ��",
        "Show recorded or current signal in mode Internal Memory"
    },
    EmptyFuncBV,
    OnPress_Int_ModeShow,
    Draw_Int_ModeShow,
    {
        {
            Draw_Int_ModeShow_Direct,
            "�� ������� ������� ������",
            "on the display current signal"
        },
        {
            Draw_Int_ModeShow_Saved,
            "�� ������� ���������� ������",
            "on the display the kept signal"
        }
    }
};

static void OnPress_Int_ModeShow(void)
{
    CircleIncreaseInt8((int8*)&set.memory.modeShowIntMem, 0, 2);
}

static void Draw_Int_ModeShow(int x, int y)
{
    if (SHOW_IN_INT_DIRECT)
    {
        Draw_Int_ModeShow_Direct(x, y);
    }
    else if (SHOW_IN_INT_SAVED)
    {
        Draw_Int_ModeShow_Saved(x, y);
    }
    else
    {
        Draw_Int_ModeShow_Both(x, y);
    }
}

static void Draw_Int_ModeShow_Direct(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x6a');
    Painter_SetFont(TypeFont_8);
}


static void Draw_Int_ModeShow_Saved(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x6c');
    Painter_SetFont(TypeFont_8);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Int_ModeShow_Both(int x, int y)
{
    Painter_DrawText(x + 1, y + 5, "���");
    Painter_DrawVLineC(x + 1, y + 2, y + 14, gColorBack);
    Painter_DrawVLineC(x + 2, y + 6, y + 11, gColorFill);
}


// ������ -> ����� �� -> ��������� � ������ ----------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbInt_SaveToMemory =
{
    Item_SmallButton, &mspInt,
    {
        "��������� � ������",
        "Save to memory"
    },
    {
        "��������� ������ �� ���������� ������������ ����������",
        "To keep a signal in an internal memory"
    },
    EmptyFuncBV,
    OnPress_Int_SaveToMemory,
    Draw_Int_SaveToMemory
};

static void OnPress_Int_SaveToMemory(void)
{
    return;
    SaveSignalToIntMemory();
}

static void SaveSignalToIntMemory(void)
{
    if (gMemory.exitFromIntToLast == 1)
    {
        if (gDSmemLast != 0)
        {
            FLASH_SaveData(gMemory.currentNumIntSignal, gDSmemLast, gDataAmemLast, gDataBmemLast);
            FLASH_GetData(gMemory.currentNumIntSignal, &gDSmemInt, &gDataAmemInt, &gDataBmemInt);
            Display_ShowWarning(SignalIsSaved);
        }
    }
    else
    {
        if (gDSet != 0)
        {
            FLASH_SaveData(gMemory.currentNumIntSignal, gDSet, gDataA, gDataB);
            FLASH_GetData(gMemory.currentNumIntSignal, &gDSet, &gDataAmemInt, &gDataBmemInt);
            Display_ShowWarning(SignalIsSaved);
        }
    }
}

static void Draw_Int_SaveToMemory(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x2c');
    Painter_SetFont(TypeFont_8);
}

// ������ -> ����� �� -> ��������� �� ������ -------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbInt_SaveToDrive =
{
    Item_SmallButton, &mspInt,
    {
        "��������� �� ������",
        "Save to disk"
    },
    {
        "��������� ������ �� ������",
        "Save signal to flash drive"
    },
    EmptyFuncBV,
    OnPress_Int_SaveToDrive,
    Draw_Int_SaveToDrive
};

static void OnPress_Int_SaveToDrive(void)
{
    gMemory.exitFromModeSetNameTo = RETURN_TO_INT_MEM;
    Memory_SaveSignalToFlashDrive();
}

static void Draw_Int_SaveToDrive(int x, int y)
{
    if (gFlashDriveIsConnected)
    {
        Painter_SetFont(TypeFont_UGO2);
        Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x42');
        Painter_SetFont(TypeFont_8);
    }
}


// ������ -> ����� �� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page mspDrive =
{
    Item_Page, &mpMemory,
    {
        "����� ��", "EXT STORAGE"
    },
    {
        "������ � ������� ������������ �����������.",
        "Work with external storage device."
    },
    EmptyFuncBV, Page_MemoryExt,
    {
        (void*)&mspDrive_Manager,       // ������ -> ����� �� -> �������
        (void*)&mcDrive_Name,           // ������ -> ����� �� -> ��� �����
        (void*)&mspSetMask,             // ������ -> ����� �� -> �����
        (void*)&mcDrive_ModeSave,       // ������ -> ����� �� -> ��������� ���
        (void*)&mcDrive_ModeBtnMemory,  // ������ -> ����� �� -> ��� �� ������
        (void*)&mcDrive_Autoconnect     // ������ -> ����� �� -> ���������������
    }
};


// ������ -> ����� �� -> ��� ����� ----------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcDrive_Name =
{
    Item_Choice, &mspDrive, {"��� �����", "File name"},
    {
        "����� ����� ������������ ������ ��� ���������� �� ������� ����������:\n"
        "\"�� �����\" - ����� ��������� ������������� �� ������� �������� ����� (����. ����� ����),\n"
        "\"�������\" - ������ ��� ��� ����� ����� �������� �������",

        "Sets the mode name when saving files to an external drive:\n"
        "\"By mask\" - files are named automatically advance to the entered mask(seq.Menu),\n"
        "\"Manual\" - each time the file name must be specified manually"
    },
    EmptyFuncBV,
    {
        {"�� �����",    "Mask"},
        {"�������",     "Manually"}
    },
    (int8*)&FILE_NAMING_MODE, EmptyFuncVB, EmptyFuncVII
};


// ������ -> ����� �� -> ��������� ��� ---------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcDrive_ModeSave =
{
    Item_Choice, &mspDrive, {"��������� ���", "Save as"},
    {
        "���� ������ ������� \"�����������\", ������ ����� ������� � ������� �������� � ����������� ����� � ����������� BMP\n"
        "���� ������ ������� \"�����\", ������ ����� ������� � ������� �������� � ��������� ���� � ����� � ���������� TXT",
        "If you select \"Image\", the signal will be stored in the current directory in graphic file with the extension BMP\n"
        "If you select \"Text\", the signal will be stored in the current directory as a text file with the extension TXT"
    },
    EmptyFuncBV,
    {
        {"�����������", "Image"},
        {"�����", "Text"}
    },
    (int8*)&MODE_SAVE, EmptyFuncVB, EmptyFuncVII
};

// ������ -> ����� �� -> ��� �� ������ ----------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcDrive_ModeBtnMemory =
{
    Item_Choice, &mspDrive, {"��� �� ������", "Mode btn MEMORY"},
    {
        "",
        ""
    },
    EmptyFuncBV,
    {
        {"����", "Menu"},
        {"����������", "Save"}
    },
    (int8*)&MODE_BTN_MEMORY, EmptyFuncVB, EmptyFuncVII
};

// ������ -> ����� �� -> ��������������� ------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcDrive_Autoconnect =
{
    Item_Choice, &mspDrive, {"���������.", "AutoConnect"},
    {
        "E��� \"���\", ��� ����������� �������� ���������� ���������� �������������� ������� �� �������� ������ - ����� ��",
        "If \"Enable\", when you connect an external drive is automatically transferred to the page MEMORY - Ext.Storage"
    },
    EmptyFuncBV,
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&FLASH_AUTO_CONNECT, EmptyFuncVB, EmptyFuncVII
};


// ������ -> ����� �� -> ������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page mspDrive_Manager =
{
    Item_Page, &mspDrive,
    {
        "�������", "DIRECTORY"
    },
    {
        "��������� ������ � �������� ������� ������������� ����������",
        "Provides access to the file system of the connected drive"
    },
    FuncOfActiveExtMemFolder, Page_SB_FileManager,
    {
        (void*)&sbExitFileManager,      // ������ -> ����� �� -> ������� -> �����
        (void*)&sbFileManagerTab,       // ������ -> ����� �� -> ������� -> Tab
        (void*)0,
        (void*)0,
        (void*)&sbFileManagerLevelUp,   // ������ -> ����� �� -> ������� -> ����� �� ��������
        (void*)&sbFileManagerLevelDown  // ������ -> ����� �� -> ������� -> ����� � �������
    },
    OnPressMemoryExtFileManager, EmptyFuncVV, FM_RotateRegSet
};

static bool FuncOfActiveExtMemFolder(void)
{
    return gFlashDriveIsConnected;
}

void OnPressMemoryExtFileManager(void)
{
    if (gFlashDriveIsConnected)
    {
        FDrive_Mount();
        OpenPageAndSetItCurrent(Page_SB_FileManager);
        Display_SetDrawMode(DrawMode_Hand, FM_Draw);
        gBF.needRedrawFileManager = 1;
    }
    else
    {
        Display_ShowWarning(WarnNeedForFlashDrive);
    }
}

// ������ -> ����� �� -> ������� -> ����� ----------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbExitFileManager =
{
    Item_SmallButton, &mspDrive_Manager,
    {
        "�����",
        "Exit"
    },
    {
        "������ ��� ������ � ���������� ����",
        "Button to return to the previous menu"
    },
    EmptyFuncBV,
    PressSB_FM_Exit,
    DrawSB_Exit
};

static void PressSB_FM_Exit(void)
{
    Display_SetDrawMode(DrawMode_Auto, 0);
    Display_RemoveAddDrawFunction();
}

// ������ -> ����� �� -> ������� -> Tab -------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbFileManagerTab =
{
    Item_SmallButton, &mspDrive_Manager,
    {
        "Tab",
        "Tab"
    },
    {
        "������� ����� ���������� � �������",
        "The transition between the directories and files"
    },
    EmptyFuncBV,
    PressSB_FM_Tab,
    DrawSB_FM_Tab
};

static void DrawSB_FM_Tab(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x6e');
    Painter_SetFont(TypeFont_8);
}

// ������ -> ����� �� -> ������� -> ����� �� �������� ---------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbFileManagerLevelUp =
{
    Item_SmallButton, &mspDrive_Manager,
    {
        "����� �� ��������",
        "Leave from directory"
    },
    {
        "������� � ������������ �������",
        "Transition to the parental catalog"
    },
    EmptyFuncBV,
    PressSB_FM_LevelUp,
    DrawSB_FM_LevelUp
};

static void DrawSB_FM_LevelUp(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x48');
    Painter_SetFont(TypeFont_8);
}

// ������ -> ����� �� -> ������� -> ����� � ������� ------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbFileManagerLevelDown =
{
    Item_SmallButton, &mspDrive_Manager,
    {
        "����� � �������",
        "Enter in directory"
    },
    {
        "������� � ��������� �������",
        "Transition to the chosen catalog"
    },
    EmptyFuncBV,
    PressSB_FM_LevelDown,
    DrawSB_FM_LevelDown
};

static void DrawSB_FM_LevelDown(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x4a');
    Painter_SetFont(TypeFont_8);
}

// ������ -> ����� �� -> ����� ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page mspSetMask =
{
    Item_Page, &mspDrive,
    {
        "�����", "MASK"
    },
    {
        "����� ����� ����� ��� ��������������� ���������� ������",
        "Input mode mask for automatic file naming"
    },
    IsActiveMemoryExtSetMask, Page_SB_MemExtSetMask,
    {
        (void*)&sbExitSetMask,      // ������ -> ����� �� -> ����� -> �����
        (void*)&sbSetMaskDelete,    // ������ -> ����� �� -> ����� -> �������
        (void*)0,
        (void*)0,
        (void*)&sbSetMaskBackspace, // ������ -> ����� �� -> ����� -> Backspace
        (void*)&sbSetMaskInsert     // ������ -> ����� �� -> ����� -> ��������
    },
    EmptyFuncVV, OnPressMemoryExtMask, OnMemExtSetMaskRegSet
};

static bool IsActiveMemoryExtSetMask(void)
{
    return FILE_NAMING_MODE_MASK;
}

static void OnPressMemoryExtMask(void)
{
    OpenPageAndSetItCurrent(Page_SB_MemExtSetMask);
    Display_SetAddDrawFunction(DrawSetMask);
}

static void OnMemExtSetMaskRegSet(int angle)
{
    OnMemExtSetMaskNameRegSet(angle, sizeof(symbols) / 4);
}

// ������ -> ����� �� -> ����� -> ����� -----------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbExitSetMask =
{
    Item_SmallButton, &mspSetMask,
    COMMON_BEGIN_SB_EXIT
    PressSB_SetMask_Exit,
    DrawSB_Exit
};

static void PressSB_SetMask_Exit(void)
{
    Display_RemoveAddDrawFunction();
}

// ������ -> ����� �� -> ����� -> ������� ----------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSetMaskDelete =
{
    Item_SmallButton, &mspSetMask,
    {
        "�������",
        "Delete"
    },
    {
        "������� ��� �������� �������",
        "Deletes all entered symbols"
    },
    EmptyFuncBV,
    PressSB_SetMask_Delete,
    DrawSB_SetMask_Delete
};

static void PressSB_SetMask_Delete(void)
{
    FILE_NAME_MASK[0] = '\0';
}

static void DrawSB_SetMask_Delete(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_MEMORY_MASK_DELETE);
    Painter_SetFont(TypeFont_8);
}

// ������ -> ����� �� -> ����� -> Backspace --------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSetMaskBackspace =
{
    Item_SmallButton, &mspSetMask,
    {
        "Backspace",
        "Backspace"
    },
    {
        "������� ��������� �������� ������",
        "Deletes the last entered symbol"
    },
    EmptyFuncBV,
    PressSB_SetMask_Backspace,
    DrawSB_SetMask_Backspace
};

static void PressSB_SetMask_Backspace(void)
{
    int size = strlen(FILE_NAME_MASK);
    if (size > 0)
    {
        if (size > 1 && FILE_NAME_MASK[size - 2] == 0x07)
        {
            FILE_NAME_MASK[size - 2] = '\0';
        }
        else
        {
            FILE_NAME_MASK[size - 1] = '\0';
        }
    }
}

static void DrawSB_SetMask_Backspace(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x20');
    Painter_SetFont(TypeFont_8);
}

// ������ -> ����� �� -> ����� -> �������� ----------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSetMaskInsert =
{
    Item_SmallButton, &mspSetMask,
    {
        "��������",
        "Insert"
    },
    {
        "��������� ��������� ������",
        "Inserts the chosen symbol"
    },
    EmptyFuncBV,
    PressSB_SetMask_Insert,
    DrawSB_SetMask_Insert
};

static void PressSB_SetMask_Insert(void)
{
    int index = INDEX_SYMBOL;
    int size = strlen(FILE_NAME_MASK);
    if (size == MAX_SYMBOLS_IN_FILE_NAME - 1)
    {
        return;
    }
    if (index < 0x41)
    {
        FILE_NAME_MASK[size] = symbols[index][0];
        FILE_NAME_MASK[size + 1] = '\0';
    }
    else
    {
        index -= 0x40;
        if (index == 0x07)  // ��� %nN - ��������� ������
        {
            if (size < MAX_SYMBOLS_IN_FILE_NAME - 2 && size > 0)
            {
                if (FILE_NAME_MASK[size - 1] >= 0x30 && FILE_NAME_MASK[size - 1] <= 0x39) // ���� ����� ������� �����
                {
                    FILE_NAME_MASK[size] = FILE_NAME_MASK[size - 1] - 0x30;
                    FILE_NAME_MASK[size - 1] = 0x07;
                    FILE_NAME_MASK[size + 1] = '\0';
                }
            }
        }
        else
        {
            FILE_NAME_MASK[size] = (char)index;
            FILE_NAME_MASK[size + 1] = '\0';
        }
    }
}

static void DrawSB_SetMask_Insert(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, SYMBOL_MEMORY_SET_NAME_INSERT);
    Painter_SetFont(TypeFont_8);
}

// �������� ���������� ��� ����� ����� ����� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page mpSetName =
{
    Item_Page, 0,
    {
        "", ""
    },
    {
        "", ""
    },
    EmptyFuncBV, Page_SB_MemExtSetName,
    {
        (void*)&sbExitSetName,
        (void*)&sbSetNameDelete,
        (void*)0,
        (void*)&sbSetNameBackspace,
        (void*)&sbSetNameInsert,
        (void*)&sbSetNameSave
    },
    EmptyFuncVV, EmptyFuncVV, OnMemExtSetNameRegSet
};

static void OnMemExtSetNameRegSet(int angle)
{
    OnMemExtSetMaskNameRegSet(angle, sizeof(symbols) / 4 - 7);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbExitSetName =   // ����� ��� ������ �� ������ ������� ����� ������������ �������. ������������ ������ ������ �� ����������
{
    Item_SmallButton, &mpSetName,
    {
        "�����",
        "Exit"
    },
    {
        "����� �� ����������",
        "Failure to save"
    },
    EmptyFuncBV,
    PressSB_SetName_Exit,
    DrawSB_Exit
};


static void PressSB_SetName_Exit(void)
{
    Display_RemoveAddDrawFunction();
    if (gMemory.exitFromModeSetNameTo == RETURN_TO_DISABLE_MENU)
    {
        ShortPressOnPageItem(PagePointerFromName(Page_SB_MemExtSetName), 0);
    }
    else if (gMemory.exitFromModeSetNameTo == RETURN_TO_LAST_MEM)
    {
        OpenPageAndSetItCurrent(Page_SB_MemLatest);
    }
    else if (gMemory.exitFromModeSetNameTo == RETURN_TO_INT_MEM)
    {
        OpenPageAndSetItCurrent(Page_SB_MemInt);
    }
    gMemory.exitFromModeSetNameTo = RETURN_TO_DISABLE_MENU;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSetNameDelete =
{
    Item_SmallButton, &mpSetName,
    {
        "�������",
        "Delete"
    },
    {
        "������� ��� �������� �������",
        "Deletes all entered characters"
    },
    EmptyFuncBV,
    PressSB_SetName_Delete,
    DrawSB_SetName_Delete
};

static void PressSB_SetName_Delete(void)
{
    FILE_NAME[0] = '\0';
}

static void DrawSB_SetName_Delete(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_MEMORY_SET_NAME_DELETE);
    Painter_SetFont(TypeFont_8);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSetNameBackspace =
{
    Item_SmallButton, &mpSetName,
    {
        "Backspace",
        "Backspace"
    },
    {
        "������� ��������� ������",
        "Delete the last character"
    },
    EmptyFuncBV,
    PressSB_SetName_Backspace,
    DrawSB_SetName_Backspace
};

static void PressSB_SetName_Backspace(void)
{
    int size = strlen(FILE_NAME);
    if (size > 0)
    {
        FILE_NAME[size - 1] = '\0';
    }
}

static void DrawSB_SetName_Backspace(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x20');
    Painter_SetFont(TypeFont_8);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSetNameInsert =
{
    Item_SmallButton, &mpSetName,
    {
        "��������",
        "Insert"
    },
    {
        "������ ��������� ������",
        "Print the next character"
    },
    EmptyFuncBV,
    PressSB_SetName_Insert,
    DrawSB_SetName_Insert
};

static void PressSB_SetName_Insert(void)
{
    int size = strlen(FILE_NAME);
    if (size < MAX_SYMBOLS_IN_FILE_NAME - 1)
    {
        FILE_NAME[size] = symbols[INDEX_SYMBOL][0];
        FILE_NAME[size + 1] = '\0';
    }
}

static void DrawSB_SetName_Insert(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x26');
    Painter_SetFont(TypeFont_8);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static const SmallButton sbSetNameSave =
{
    Item_SmallButton, &mpSetName,
    {
        "���������",
        "Save"
    },
    {
        "���������� �� ���� ��� �������� ������",
        "Saving to flashdrive with the specified name"
    },
    EmptyFuncBV,
    PressSB_MemExtSetNameSave,
    DrawSB_MemExtSetNameSave
};

static void PressSB_MemExtSetNameSave(void)
{
    if (gFlashDriveIsConnected)
    {
        PressSB_SetName_Exit();
        gMemory.needForSaveToFlashDrive = 1;
    }
}

static void DrawSB_MemExtSetNameSave(int x, int y)
{
    if (gFlashDriveIsConnected)
    {
        Painter_SetFont(TypeFont_UGO2);
        Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x42');
        Painter_SetFont(TypeFont_8);
    }
}





























































//------------------------------------------------------------------------------------------------------------------------------------------------------
void DrawSB_MemLastSelect(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 3, y + 2, set.memory.strMemoryLast.isActiveModeSelect ? '\x2a' : '\x28');
    Painter_SetFont(TypeFont_8);
}

void PressSB_MemLastSelect(void)
{
    set.memory.strMemoryLast.isActiveModeSelect = !set.memory.strMemoryLast.isActiveModeSelect;
}






static void OnMemExtSetMaskNameRegSet(int angle, int maxIndex)
{
    int8(*func[3])(int8 *, int8, int8) =
    {
        CircleDecreaseInt8,
        CircleDecreaseInt8,
        CircleIncreaseInt8
    };

    Painter_ResetFlash();
    if (INDEX_SYMBOL > maxIndex)
    {
        INDEX_SYMBOL = (int8)(maxIndex - 1);
    }
    func[Math_Sign(angle) + 1](&INDEX_SYMBOL, 0, (int8)(maxIndex - 1));
    Sound_RegulatorSwitchRotate();

}


void DrawSB_MemExtNewFolder(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 1, y, '\x46');
    Painter_SetFont(TypeFont_8);
}

extern const Page mpMemory;
extern const Page mspDrive;

void DrawStr(int index, int x, int y)
{
    const char *str = symbols[index];
    if(index == INDEX_SYMBOL)
    {
        Painter_FillRegionC(x - 1, y, Font_GetLengthText(str), 9, COLOR_FLASH_10);
    }
    Painter_DrawTextC(x, y, symbols[index], index == INDEX_SYMBOL ? COLOR_FLASH_01 : gColorFill);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DrawSetName(void)
{
    int x0 = GridLeft() + 40;
    int y0 = GRID_TOP + 60;
    int width = GridWidth() - 80;
    int height = 80;

    Painter_DrawRectangleC(x0, y0, width, height, gColorFill);
    Painter_FillRegionC(x0 + 1, y0 + 1, width - 2, height - 2, gColorBack);

    int index = 0;
    int position = 0;
    int deltaX = 10;
    int deltaY0 = 5;
    int deltaY = 12;

    // ������ ������� ����� ����������� ��������
    while (symbols[index][0] != ' ')
    {
        DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0);
        index++;
        position++;
    }

    // ������ ������ ����� � ������
    position = 0;
    while (symbols[index][0] != 'a')
    {
        DrawStr(index, x0 + deltaX + 50 + position * 7, y0 + deltaY0 + deltaY);
        index++;
        position++;
    }

    // ������ ������ ����� ����� ��������
    position = 0;
    while (symbols[index][0] != '%')
    {
        DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0 + deltaY * 2);
        index++;
        position++;
    }

    int x = Painter_DrawTextC(x0 + deltaX, y0 + 65, FILE_NAME, gColorFill);
    Painter_FillRegionC(x, y0 + 65, 5, 8, COLOR_FLASH_10);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawFileMask(int x, int y)
{
    char *ch = FILE_NAME_MASK;

    Painter_SetColor(gColorFill);
    while (*ch != '\0')
    {
        if (*ch >= 32)
        {
            x = Painter_DrawChar(x, y, *ch);
        }
        else
        {
            if (*ch == 0x07)
            {
                x = Painter_DrawChar(x, y, '%');
                x = Painter_DrawChar(x, y, (char)(0x30 | *(ch + 1)));
                x = Painter_DrawChar(x, y, 'N');
                ch++;
            }
            else
            {
                x = Painter_DrawText(x, y, symbols[*ch + 0x40]);
            }
        }
        ch++;
    }
    Painter_FillRegionC(x, y, 5, 8, COLOR_FLASH_10);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void DrawSetMask(void)
{
    int x0 = GridLeft() + 40;
    int y0 = GRID_TOP + 20;
    int width = GridWidth() - 80;
    int height = 160;

    Painter_DrawRectangleC(x0, y0, width, height, gColorFill);
    Painter_FillRegionC(x0 + 1, y0 + 1, width - 2, height - 2, gColorBack);

    int index = 0;
    int position = 0;
    int deltaX = 10;
    int deltaY0 = 5;
    int deltaY = 12;

    // ������ ������� ����� ����������� ��������
    while(symbols[index][0] != ' ')
    {
        DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0);
        index++;
        position++;
    }
    
    // ������ ������ ����� � ������
    position = 0;
    while(symbols[index][0] != 'a')
    {
        DrawStr(index, x0 + deltaX + 50 + position * 7, y0 + deltaY0 + deltaY);
        index++;
        position++;
    }

    // ������ ������ ����� ����� ��������
    position = 0;
    while(symbols[index][0] != '%')
    {
        DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0 + deltaY * 2);
        index++;
        position++;
    }

    // ������ ������ �����������
    position = 0;
    while (index < (sizeof(symbols) / 4))
    {
        DrawStr(index, x0 + deltaX + 26 + position * 20, y0 + deltaY0 + deltaY * 3);
        index++;
        position++;
    }

    DrawFileMask(x0 + deltaX, y0 + 65);

    static const char* strings[] =
    {
        "%y - ���, %m - �����, %d - ����",
        "%H - ����, %M - ������, %S - �������",
        "%nN - ���������� �����, ���",
        "n - ����������� ���������� ������ ��� N"
    };

    deltaY--;
    Painter_SetColor(gColorFill);
    for(int i = 0; i < sizeof(strings) / 4; i++)
    {
        Painter_DrawText(x0 + deltaX, y0 + 100 + deltaY * i, strings[i]);
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void Memory_SaveSignalToFlashDrive(void)
{
    if (gFlashDriveIsConnected)
    {
        if (FILE_NAMING_MODE_MANUAL)
        {
            OpenPageAndSetItCurrent(Page_SB_MemExtSetName);
            Display_SetAddDrawFunction(DrawSetName);
        }
        else
        {
            gMemory.needForSaveToFlashDrive = 1;
        }
    }
    else
    {
        gMemory.exitFromModeSetNameTo = 0;
    }
}

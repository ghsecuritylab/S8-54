// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "PageMemory.h"
#include "Data/Data.h"
#include "Data/DataBuffer.h"
#include "Display/Grid.h"
#include "Display/Symbols.h"
#include "FlashDrive/FlashDrive.h"
#include "FPGA/FPGA.h"
#include "Hardware/FLASH.h"
#include "Hardware/Sound.h"
#include "Menu/FileManager.h"
#include "Menu/Menu.h"
#include "Menu/MenuFunctions.h"
#include "Menu/MenuItemsLogic.h"
#include "Menu/Pages/Definition.h"
#include "Utils/Dictionary.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/Math.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Page mainPage;

extern void PressSB_FM_Tab(void);

static const    Choice cPoints;                                 ///< ������ - �����
static bool    IsActive_Points(void);
       void   OnChanged_Points(bool active);
static const     Page ppLast;                                   ///< ������ - ���������
static void     OnPress_Last(void);
static void      OnDraw_Last(void);
static void    OnRegSet_Last(int angle);
static const   SButton bLast_Exit;                              ///< ������ - ��������� - �����
static void     OnPress_Last_Exit(void);
static const   SButton bLast_Next;                              ///< ������ - ��������� - ���������
static void     OnPress_Last_Next(void);
static void        Draw_Last_Next(int x, int y);
static const   SButton bLast_Prev;                              ///< ������ - ��������� - ����������
static void     OnPress_Last_Prev(void);
static void        Draw_Last_Prev(int x, int y);
static const   SButton bLast_SaveToROM;                         ///< ������ - ��������� - ����� ��
static void     OnPress_Last_SaveToROM(void);
static void        Draw_Last_SaveToROM(int x, int y);
static const   SButton bLast_SaveToDrive;                       ///< ������ - ��������� - ���������
static void     OnPress_Last_SaveToDrive(void);
static void        Draw_Last_SaveToDrive(int x, int y);
static const     Page ppInternal;                               ///< ������ - ����� ��
static void     OnPress_Internal(void);
static void      OnDraw_Internal(void);
static void    OnRegSet_Internal(int delta);
static const   SButton bInternal_Exit;                          ///< ������ - ����� �� - �����
static void     OnPress_Internal_Exit(void);
static const   SButton bInternal_ShowAlways;                    ///< ������ - ����� �� - ���������� ������
static void     OnPress_Internal_ShowAlways(void);
static void        Draw_Internal_ShowAlways(int x, int y);
static void        Draw_Internal_ShowAlways_Yes(int x, int y);
static void        Draw_Internal_ShowAlways_No(int x, int y);
static const   SButton bInternal_ModeShow;                      ///< ������ - ����� �� - ��� �������
static void     OnPress_Internal_ModeShow(void);
static void        Draw_Internal_ModeShow(int x, int y);
static void        Draw_Internal_ModeShow_Direct(int x, int y); 
static void        Draw_Internal_ModeShow_Saved(int x, int y);
static void        Draw_Internal_ModeShow_Both(int x, int y);
/*
static const   SButton bInternal_EraseAll;                      ///< ������ - ����� �� - ������� ���
static void     OnPress_Internal_EraseAll(void);
static void        Draw_Internal_EraseAll(int x, int y);
*/
static const   SButton bInternal_Scale;                         ///< ������ - ����� �� - �������
static void     OnPress_Internal_Scale(void);
static void        Draw_Internal_Scale(int x, int y);
static void        Draw_Internal_Scale_Recalculated(int x, int y);
static void        Draw_Internal_Scale_Original(int x, int y);
static const   SButton bInternal_SaveToMemory;                  ///< ������ - ����� �� - ���������
static void     OnPress_Internal_SaveToMemory(void);
static void        Draw_Internal_SaveToMemory(int x, int y);
static const   SButton bInternal_SaveToDrive;                   ///< ������ - ����� �� - ��������� �� ������
static void     OnPress_Internal_SaveToDrive(void);
static void        Draw_Internal_SaveToDrive(int x, int y);
static const     Page ppDrive;                                  ///< ������ - ����� ��
static const    Choice cDrive_Name;                             ///< ������ - ����� �� - ��� �����
static const    Choice cDrive_SaveAs;                           ///< ������ - ����� �� - ��������� ���
static const    Choice cDrive_ModeBtnMemory;                    ///< ������ - ����� �� - ����� �� ������
static const    Choice cDrive_Autoconnect;                      ///< ������ - ����� �� - ��������������
static const    Page pppDrive_Manager;                          ///< ������ - ����� �� - �������
static bool    IsActive_Drive_Manager(void);
       void     OnPress_Drive_Manager(void);
static const   SButton bDrive_Manager_Exit;                     ///< ������ - ����� �� - ������� - �����
static void     OnPress_Drive_Manager_Exit(void);
static const   SButton bDrive_Manager_Tab;                      ///< ������ - ����� �� - ������� - Tab
static void        Draw_Drive_Manager_Tab(int x, int y);
static const   SButton bDrive_Manager_LevelUp;                  ///< ������ - ����� �� - ������� - ����� �� ��������
static void        Draw_Drive_Manager_LevelUp(int x, int y);
static const   SButton bDrive_Manager_LevelDown;                ///< ������ - ����� �� - ������� - ����� � �������
static void        Draw_Drive_Manager_LevelDown(int x, int y);
static const    Page pppDrive_Mask;                             ///< ������ - ����� �� - �����
static bool    IsActive_Drive_Mask(void);
static void     OnPress_Drive_Mask(void);
static void    OnRegSet_Drive_Mask(int angle);
static const   SButton bDrive_Mask_Exit;                        ///< ������ - ����� �� - ����� - �����
static const   SButton bDrive_Mask_Delete;                      ///< ������ - ����� �� - ����� - �������
static void     OnPress_Drive_Mask_Delete(void);
static void        Draw_Drive_Mask_Delete(int x, int y);
static const   SButton bDrive_Mask_Backspace;                   ///< ������ - ����� �� - ����� - Backspace
static void     OnPress_Drive_Mask_Backspace(void);
static void        Draw_Drive_Mask_Backspace(int x, int y);
static const   SButton bDrive_Mask_Insert;                      ///< ������ - ����� �� - ����� - ��������
static void     OnPress_Drive_Mask_Insert(void);
static void        Draw_Drive_Mask_Insert(int x, int y);
            const Page pSetName;                                ///< ��������� �����
static void    OnRegSet_SetName(int angle);
static const   SButton bSetName_Exit;                           ///< ��������� ����� - �����
static void     OnPress_SetName_Exit(void);
static const   SButton bSetName_Delete;                         ///< ��������� ����� - �������
static void     OnPress_SetName_Delete(void);
static void        Draw_SetName_Delete(int x, int y);
static const   SButton bSetName_Backspace;                      ///< ��������� ����� - Backspace
static void     OnPress_SetName_Backspace(void);
static void        Draw_SetName_Backspace(int x, int y);
static const   SButton bSetName_Insert;                         ///< ��������� ����� - ��������
static void     OnPress_SetName_Insert(void);
static void        Draw_SetName_Insert(int x, int y);
static const   SButton bSetName_Save;                           ///< ��������� ����� - ���������
static void     OnPress_SetName_Save(void);
static void        Draw_SetName_Save(int x, int y);

static void DrawSetMask(void);  // ��� ������� ������, ����� ������ ����� ������� �����.
static void DrawFileMask(int x, int y);
static void DrawSetName(void);  // ��� ������� ������, ����� ����� ������ ��� ����� ��� ����������

static void DrawMemoryWave(int num, bool exist);
static void SaveSignalToIntMemory(void);
       void OnMemExtSetMaskNameRegSet(int angle, int maxIndex);


// ������ ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pMemory =
{
    Item_Page, &mainPage, 0,
    {
        "������", "MEMORY",
        "������ � ������� � ���������� �������.",
        "Working with external and internal memory."
    },
    Page_Memory,
    {
        (void *)&cPoints,       // ������ - �����
        (void *)&ppLast,        // ������ - ���������
        (void *)&ppInternal,    // ������ - ����� ��
        (void *)&ppDrive        // ������ - ����� ��
    }
};

// ������ - ����� ------------------------------------------------------------------------------------------------------------------------------------
static const Choice cPoints =
{
    Item_Choice, &pMemory, IsActive_Points,
    {
        "����� ������", "Mem length"
        ,
        "����� ���������� �������� ��� ����������� ��������. "
        "��� ���������� ���������� �������� ����������� ���������� ���������� � ������ ��������."
        ,
        "Choice of number of counting for the saved signals. "
        "At increase in number of counting the quantity of the signals kept in memory decreases."
    },
    {
        {"512", "512"},
        {"1�",  "1k"},
        {"2�",  "2k"},
        {"4�",  "4k"},
        {"8�",  "8k"},
        {"16�", "16k"}
        //,{"32�", "32k"}
    },
    (int8 *)&FPGA_ENUM_POINTS, OnChanged_Points
};

static bool IsActive_Points(void)
{
    return SET_PEAKDET_DIS;
}

void OnChanged_Points(bool active)
{
    // ���� ������� ������� ��������, �� �� ����� ����������� ������
    if (SET_PEAKDET_EN && !active)
    {
        Display_ShowWarning(WrongModePeackDet);
        return;
    }

    // ��������� ��������� 32� ����� ������, ���� ������� ������ �����
    if (FPGA_POINTS_32k && SET_ENABLED_B)
    {
        Display_ShowWarning(DisableChannel2);
        FPGA_ENUM_POINTS = FNP_16k;
    }

    int width = GridWidth();
    
    FPGA_Reset();
    
    if (SET_PEAKDET_EN)
    {
        width *= 2;
    }
    if (TPOS_IS_LEFT)
    {
        SHIFT_IN_MEMORY = 0;
    }
    else if (TPOS_IS_CENTER)
    {
        SHIFT_IN_MEMORY = (int16)(SET_BYTES_IN_CHANNEL / 2 - width / 2);
    }
    else if (TPOS_IS_RIGHT)
    {
        SHIFT_IN_MEMORY = (int16)(SET_BYTES_IN_CHANNEL - width - 2);
    }
    
    FPGA_Reset();
    FPGA_SetTShift(SET_TSHIFT);
    FPGA_Reset();
}

// ������ - ��������� --------------------------------------------------------------------------------------------------------------------------------
static const Page ppLast =
{
    Item_Page, &pMemory, 0,
    {
        "���������", "LATEST",
        "������� � ����� ������ � ���������� ����������� ���������",
        "Transition to an operating mode with the last received signals"
    },
    PageSB_Memory_Last,
    {
        (void *)&bLast_Exit,        // ������ - ��������� - �����
        (void *)0,
        (void *)&bLast_Next,        // ������ - ��������� - ���������
        (void *)&bLast_Prev,        // ������ - ��������� - ����������
        (void *)&bLast_SaveToROM,   // ������ - ��������� - ����� ��
        (void *)&bLast_SaveToDrive  // ������ - ��������� - ���������
    },
    true, OnPress_Last, OnDraw_Last, OnRegSet_Last
};

static void OnPress_Last(void)
{
    NUM_RAM_SIGNAL = 0;
    RUN_FPGA_BEFORE_SB = FPGA_IS_RUNNING ? 1 : 0;
    FPGA_Stop(false);
    MODE_WORK = ModeWork_RAM;
}

static void OnDraw_Last(void)
{
    char buffer[20];

    int width = 40;
    int height = 10;
    Painter_FillRegionC(GridRight() - width, GRID_TOP, width, height, gColorBack);
    Painter_DrawRectangleC(GridRight() - width, GRID_TOP, width, height, gColorFill);
    Painter_DrawText(GridRight() - width + 2, GRID_TOP + 1, Int2String(NUM_RAM_SIGNAL + 1, false, 3, buffer));
    Painter_DrawText(GridRight() - width + 17, GRID_TOP + 1, "/");
    Painter_DrawText(GridRight() - width + 23, GRID_TOP + 1, Int2String(DS_NumElementsInStorage(), false, 3, buffer));
}

static void OnRegSet_Last(int angle)
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

// ������ - ��������� - ����� ------------------------------------------------------------------------------------------------------------------------
static const SButton bLast_Exit =
{
    Item_SmallButton, &ppLast,
    COMMON_BEGIN_SB_EXIT,
    OnPress_Last_Exit,
    DrawSB_Exit
};

static void OnPress_Last_Exit(void)
{
    MODE_WORK = ModeWork_Dir;
    if (RUN_FPGA_BEFORE_SB)
    {
        FPGA_Start();
        RUN_FPGA_BEFORE_SB = 0;
    }
    OnPressSB_Exit();
}

// ������ - ��������� - ��������� --------------------------------------------------------------------------------------------------------------------
static const SButton bLast_Next =
{
    Item_SmallButton, &ppLast, 0,
    {
        "���������", "Next",
        "������� � ���������� �������",
        "Go to the next signal"
    },
    OnPress_Last_Next,
    Draw_Last_Next
};

static void OnPress_Last_Next(void)
{
    CircleIncreaseInt16(&NUM_RAM_SIGNAL, 0, (int16)(DS_NumElementsInStorage() - 1));
}

static void Draw_Last_Next(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x64');
    Painter_SetFont(TypeFont_8);
}

// ������ - ��������� - ���������� -------------------------------------------------------------------------------------------------------------------
static const SButton bLast_Prev =
{
    Item_SmallButton, &ppLast, 0,
    {
        "����������", "Previous",
        "������� � ����������� �������",
        "Go to the previous signal"
    },
    OnPress_Last_Prev,
    Draw_Last_Prev
};

static void OnPress_Last_Prev(void)
{
    CircleDecreaseInt16(&NUM_RAM_SIGNAL, 0, (int16)(DS_NumElementsInStorage() - 1));
}

static void Draw_Last_Prev(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, SYMBOL_BACKSPACE);
    Painter_SetFont(TypeFont_8);
}

// ������ - ��������� - ����� �� ---------------------------------------------------------------------------------------------------------------------
static const SButton bLast_SaveToROM =
{
    Item_SmallButton, &ppLast, 0,
    {
        "����� ��", "Internal storage",
        "������� ��� ������, ����� ��������� ������ �� ���������� ������������ ����������",
        "Press this button to keep a signal in an internal memory"
    },
    OnPress_Last_SaveToROM,
    Draw_Last_SaveToROM
};

static void OnPress_Last_SaveToROM(void)
{
    SBPage_SetCurrent(&ppInternal);
    MODE_WORK = ModeWork_ROM;   // ��������� � ������ ����������� ��
    EXIT_FROM_ROM_TO_RAM = 1;   // ���� ������� �� ������������� ��� ����, �����:
                                // 1 - �� ������� ������ ����� �� �������� "����� ��" �������� � "���������", � �� � �������� ����;
                                // 2 - ��� ����, ����� �� �������� "����� ��" �������� �� ��������� ��������� ������, � ��������� �� �������� 
                                // "���������";
                                // 3 - ����� � Data_Load() ������������� ��������������� ���������.
}

static void Draw_Last_SaveToROM(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_ROM);
    Painter_SetFont(TypeFont_8);
}

// ������ - ��������� - ��������� --------------------------------------------------------------------------------------------------------------------
static const SButton bLast_SaveToDrive =
{
    Item_SmallButton, &ppLast, 0,
    {
        "���������", "Save",
        "������ ���������� �������� ��� ������������� ������� ��. ��������� ��������� ������ �� ������ ��",
        "Click this button to save the signal on the external FLASH"
    },
    OnPress_Last_SaveToDrive,
    Draw_Last_SaveToDrive
};

static void OnPress_Last_SaveToDrive(void)
{
    EXIT_FROM_SETNAME_TO = RETURN_TO_LAST_MEM;
    Memory_SaveSignalToFlashDrive();
}

void Memory_SaveSignalToFlashDrive(void)
{
    if (FDRIVE_IS_CONNECTED)
    {
        if (FILE_NAMING_MODE_MANUAL)
        {
            Display_SetAddDrawFunction(DrawSetName);
        }
        else
        {
            NEED_SAVE_TO_FLASHDRIVE = 1;
        }
    }
    else
    {
        EXIT_FROM_SETNAME_TO = 0;
    }
}

static void DrawSetName(void)
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
    while (symbolsAlphaBet[index][0] != ' ')
    {
        DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0);
        index++;
        position++;
    }

    // ������ ������ ����� � ������
    position = 0;
    while (symbolsAlphaBet[index][0] != 'a')
    {
        DrawStr(index, x0 + deltaX + 50 + position * 7, y0 + deltaY0 + deltaY);
        index++;
        position++;
    }

    // ������ ������ ����� ����� ��������
    position = 0;
    while (symbolsAlphaBet[index][0] != '%')
    {
        DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0 + deltaY * 2);
        index++;
        position++;
    }

    int x = Painter_DrawTextC(x0 + deltaX, y0 + 65, FILE_NAME, gColorFill);
    Painter_FillRegionC(x, y0 + 65, 5, 8, COLOR_FLASH_10);
}

static void Draw_Last_SaveToDrive(int x, int y)
{
    if (FDRIVE_IS_CONNECTED)
    {
        Painter_SetFont(TypeFont_UGO2);
        Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_FLASH_DRIVE_BIG);
        Painter_SetFont(TypeFont_8);
    }
}

// ������ - ����� �� ---------------------------------------------------------------------------------------------------------------------------------
static const Page ppInternal =
{
    Item_Page, &pMemory, 0,
    {
        "����� ��", "INT STORAGE",
        "������� � ����� ������ � ���������� �������",
        "Transition to an operating mode with internal memory"
    },
    PageSB_Memory_Internal,
    {
        (void *)&bInternal_Exit,            // ������ - ����� �� - �����
        (void *)&bInternal_ShowAlways,      // ������ - ����� �� - ���������� ������
        (void *)&bInternal_ModeShow,        // ������ - ����� �� - ��� �������
        (void *)0,
        //(void *)&bInternal_EraseAll,
        //(void *)&bInternal_Scale,           // ������ - ����� �� - �������
        (void *)&bInternal_SaveToMemory,    // ������ - ����� �� - ���������
        (void *)&bInternal_SaveToDrive      // ������ - ����� �� - ��������� �� ������
    },
    true, OnPress_Internal, OnDraw_Internal, OnRegSet_Internal
};

static void OnPress_Internal(void)
{
    MODE_WORK = ModeWork_ROM;
}

static void OnDraw_Internal(void)
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
    Painter_FillRegionC(x, y, width, 10, num == NUM_ROM_SIGNAL ? COLOR_FLASH_10 : gColorBack);
    Painter_DrawRectangleC(x, y, width, 10, gColorFill);
    Painter_SetColor(num == NUM_ROM_SIGNAL ? COLOR_FLASH_01 : gColorFill);
    if (exist)
    {
        Painter_DrawText(x + 2, y + 1, Int2String(num + 1, false, 2, buffer));
    }
    else
    {
        Painter_DrawText(x + 3, y + 1, "\x88");
    }
}

static void OnRegSet_Internal(int delta)
{
    Sound_RegulatorSwitchRotate();
    if (delta < 0)
    {
        CircleDecreaseInt8(&NUM_ROM_SIGNAL, 0, MAX_NUM_SAVED_WAVES - 1);
    }
    else if (delta > 0)
    {
        CircleIncreaseInt8(&NUM_ROM_SIGNAL, 0, MAX_NUM_SAVED_WAVES - 1);
    }
    Painter_ResetFlash();
}

// ������ - ����� �� - ����� -------------------------------------------------------------------------------------------------------------------------
static const SButton bInternal_Exit =
{
    Item_SmallButton, &ppInternal, 0,
    {
        "�����", "Exit",
        "������ ��� ������ � ���������� ����",
        "Button to return to the previous menu"
    },
    OnPress_Internal_Exit,
    DrawSB_Exit
};

static void FuncForInternalExit(void)
{
    SBPage_SetCurrent(&ppLast);
}

static void OnPress_Internal_Exit(void)
{
    if (EXIT_FROM_ROM_TO_RAM)
    {
        MODE_WORK = ModeWork_RAM;
        EXIT_FROM_ROM_TO_RAM = 0;
        Menu_RunAfterUpdate(FuncForInternalExit);
    }
    else
    {
        MODE_WORK = ModeWork_Dir;
        if (RUN_FPGA_BEFORE_SB)
        {
            FPGA_Start();
            RUN_FPGA_BEFORE_SB = 0;
        }
        OnPressSB_Exit();
        //ShortPressOnPageItem(PagePointerFromName(PageSB_Memory_Internal), 0);
    }
}

// ������ - ����� �� - ���������� ������ -------------------------------------------------------------------------------------------------------------
static const SButton bInternal_ShowAlways =
{
    Item_SmallButton, &ppInternal, 0,
    {
        "���������� ������", "To show always",
        "��������� ������ ���������� ��������� ���������� ������ ������ ��������",
        "Allows to show always the chosen kept signal over the current"
    },
    OnPress_Internal_ShowAlways,
    Draw_Internal_ShowAlways,
    {
        {
            Draw_Internal_ShowAlways_Yes,
            "���������� ��������� ������ �� ���������� ������ ������ ��������",
            "to show the chosen signal from internal memory over the current"
        },
        {
            Draw_Internal_ShowAlways_No,
            "������ �� ���������� ������ ����� ������ � ������ ������ � ���������� ������������ �����������",
            "the signal from internal memory is visible only in an operating mode with an internal memory"
        }
    }
};

static void OnPress_Internal_ShowAlways(void)
{
    ALWAYS_SHOW_ROM_SIGNAL = ALWAYS_SHOW_ROM_SIGNAL ? 0 : 1;
}

static void Draw_Internal_ShowAlways(int x, int y)
{
    if (ALWAYS_SHOW_ROM_SIGNAL == 0)
    {
        Draw_Internal_ShowAlways_No(x, y);
    }
    else
    {
        Draw_Internal_ShowAlways_Yes(x, y);
    }
}

static void Draw_Internal_ShowAlways_Yes(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x66');
    Painter_SetFont(TypeFont_8);
}

static void Draw_Internal_ShowAlways_No(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x68');
    Painter_SetFont(TypeFont_8);
}

// ������ - ����� �� - ��� ������� -------------------------------------------------------------------------------------------------------------------
static const SButton bInternal_ModeShow =
{
    Item_SmallButton, &ppInternal, 0,
    {
        "��� �������", "Type of a signal",
        "���������� ���������� ��� ������� ������ � ������ ����� ��",
        "Show recorded or current signal in mode Internal Memory"
    },
    OnPress_Internal_ModeShow,
    Draw_Internal_ModeShow,
    {
        {
            Draw_Internal_ModeShow_Direct,
            "�� ������� ������� ������",
            "on the display current signal"
        },
        {
            Draw_Internal_ModeShow_Saved,
            "�� ������� ���������� ������",
            "on the display the kept signal"
        },
        {
            Draw_Internal_ModeShow_Both,
            "�� ������� ��� �������",
            "on the display both signals"
        }
    }
};

static void OnPress_Internal_ModeShow(void)
{
    CircleIncreaseInt8((int8 *)&SHOW_IN_INT, 0, 2);
}

static void Draw_Internal_ModeShow(int x, int y)
{
    if (SHOW_IN_INT_DIRECT)
    {
        Draw_Internal_ModeShow_Direct(x, y);
    }
    else if (SHOW_IN_INT_SAVED)
    {
        Draw_Internal_ModeShow_Saved(x, y);
    }
    else
    {
        Draw_Internal_ModeShow_Both(x, y);
    }
}

static void Draw_Internal_ModeShow_Direct(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x6a');
    Painter_SetFont(TypeFont_8);
}


static void Draw_Internal_ModeShow_Saved(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x6c');
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Draw_Internal_ModeShow_Both(int x, int y)
{
    Painter_DrawText(x + 1, y + 5, "���");
    Painter_DrawVLineC(x + 1, y + 2, y + 14, gColorBack);
    Painter_DrawVLineC(x + 2, y + 6, y + 11, gColorFill);
}

/*
// ������ - ����� �� - ������� �� -------------------------------------------------------------------------------------------------------------------
static const SButton bInternal_EraseAll =
{
    Item_SmallButton, &ppInternal, 0,
    {
        "������� ��", "Erase all",
        "������� ��� ������ �� ������� �������� ������, ������� ������� �����������. ��������� ��������������",
        "It erases all data from the storage area, including the area inoformatsiya. The total format"
    },
    OnPress_Internal_EraseAll,
    Draw_Internal_EraseAll,
    {
        {
            Draw_Internal_EraseAll,
            "������� ��� ������",
            "Erase all data"
        }
    }
};

static void OnPress_Internal_EraseAll(void)
{
    Display_FuncOnWaitStart("������. ���������", "Erase. Wait", false);
    FLASH_DeleteAllData();
    Display_FuncOnWaitStop();
}

static void Draw_Internal_EraseAll(int x, int y)
{
    Painter_DrawText(x + 5, y + 5, "E");
}
*/

// ������ - ����� �� - ������� -----------------------------------------------------------------------------------------------------------------------
static const SButton bInternal_Scale =
{
    Item_SmallButton, &ppInternal, 0,
    {
        "�������", "Scale",
        "��������� ��� ��� ���������� ������ � ������� ����������",
        "Whether or not to record the recorded signal to the current settings"
    },
    OnPress_Internal_Scale,
    Draw_Internal_Scale,
    {
        {
            Draw_Internal_Scale_Recalculated,
            "������ ������� � ������� ���������� ������������",
            "The signal is given to the current oscilloscope settings"
        },
        {
            Draw_Internal_Scale_Original,
            "������ �������� � ����� ����, � ������� ������",
            "The signal is drawn in the form in which the readout"
        }
    }
};

void OnPress_Internal_Scale(void)
{
    CircleIncreaseInt8((int8 *)&MEM_DATA_SCALE, 0, 1);
}

void Draw_Internal_Scale(int x, int y)
{
    if (MEM_DATA_SCALE_RECALC)
    {
        Draw_Internal_Scale_Recalculated(x, y);
    }
    else
    {
        Draw_Internal_Scale_Original(x, y);
    }
}

void Draw_Internal_Scale_Recalculated(int x, int y)
{
    Painter_DrawText(x + 8, y + 2, DICT(DM));
    Painter_SetFont(TypeFont_5);
    Painter_DrawText(x + 5, y + 9, DICT(DABS));
    Painter_SetFont(TypeFont_8);
}

void Draw_Internal_Scale_Original(int x, int y)
{
    Painter_DrawText(x + 8, y + 2, DICT(DM));
    Painter_SetFont(TypeFont_5);
    Painter_DrawText(x + 5, y + 9, DICT(DREL));
    Painter_SetFont(TypeFont_8);
}


// ������ - ����� �� - ��������� � ������ ------------------------------------------------------------------------------------------------------------
static const SButton bInternal_SaveToMemory =
{
    Item_SmallButton, &ppInternal, 0,
    {
        "��������� � ������", "Save to memory",
        "��������� ������ �� ���������� ������������ ����������",
        "To keep a signal in an internal memory"
    },
    OnPress_Internal_SaveToMemory,
    Draw_Internal_SaveToMemory
};

static void OnPress_Internal_SaveToMemory(void)
{
    Display_FuncOnWaitStart(DICT(DStoredInMemory), false);
    SaveSignalToIntMemory();
    Display_FuncOnWaitStop();
}

static void SaveSignalToIntMemory(void)
{
    // ������� � ��������� DS, DATA_A, DATA_B ������ �� ��� ��� ��������� ��������� ������, � ����������� �� ����, �� ������ ������ ����� � 
    // "������-����� ��"
    Data_ReadFromRAM(EXIT_FROM_ROM_TO_RAM ? NUM_RAM_SIGNAL : 0, 0, false);

    if (DS)                                             // ���� ���� ��� ���������
    {
        FLASH_SaveData(NUM_ROM_SIGNAL, DS, IN_A, IN_B);   // �� ��������� ������ �� DS, DATA_A, DATA_B �� ����� NUM_ROM_SIGNAL � ����
        Display_ShowWarning(SignalIsSaved);
    }
}

static void Draw_Internal_SaveToMemory(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x2c');
    Painter_SetFont(TypeFont_8);
}

// ������ - ����� �� - ��������� �� ������ -----------------------------------------------------------------------------------------------------------
static const SButton bInternal_SaveToDrive =
{
    Item_SmallButton, &ppInternal, 0,
    {
        "��������� �� ������", "Save to disk",
        "��������� ������ �� ������",
        "Save signal to flash drive"
    },
    OnPress_Internal_SaveToDrive,
    Draw_Internal_SaveToDrive
};

static void OnPress_Internal_SaveToDrive(void)
{
    EXIT_FROM_SETNAME_TO = RETURN_TO_INT_MEM;
    Memory_SaveSignalToFlashDrive();
}

static void Draw_Internal_SaveToDrive(int x, int y)
{
    if (FDRIVE_IS_CONNECTED)
    {
        Painter_SetFont(TypeFont_UGO2);
        Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_FLASH_DRIVE_BIG);
        Painter_SetFont(TypeFont_8);
    }
}

// ������ - ����� �� ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page ppDrive =
{
    Item_Page, &pMemory, 0,
    {
        "����� ��", "EXT STORAGE",
        "������ � ������� ������������ �����������.",
        "Work with external storage device."
    },
    Page_Memory_Drive,
    {
        (void *)&pppDrive_Manager,      // ������ - ����� �� - �������
        (void *)&cDrive_Name,           // ������ - ����� �� - ��� �����
        (void *)&pppDrive_Mask,         // ������ - ����� �� - �����
        (void *)&cDrive_SaveAs,         // ������ - ����� �� - ��������� ���
        (void *)&cDrive_ModeBtnMemory,  // ������ - ����� �� - ��� �� ������
        (void *)&cDrive_Autoconnect     // ������ - ����� �� - ���������������
    }
};

// ������ - ����� �� - ��� ����� ---------------------------------------------------------------------------------------------------------------------
static const Choice cDrive_Name =
{
    Item_Choice, &ppDrive, 0,
    {
        "��� �����", "File name"
        ,
        "����� ����� ������������ ������ ��� ���������� �� ������� ����������:\n"
        "\"�� �����\" - ����� ��������� ������������� �� ������� �������� ����� (����. ����� ����),\n"
        "\"�������\" - ������ ��� ��� ����� ����� �������� �������"
        ,
        "Sets the mode name when saving files to an external drive:\n"
        "\"By mask\" - files are named automatically advance to the entered mask(seq.Menu),\n"
        "\"Manual\" - each time the file name must be specified manually"
    },
    {
        {"�� �����",    "Mask"},
        {"�������",     "Manually"}
    },
    (int8 *)&FILE_NAMING_MODE
};

// ������ - ����� �� - ��������� ��� ---------------------------------------------------------------------------------------------------------------
static const Choice cDrive_SaveAs =
{
    Item_Choice, &ppDrive, 0,
    {
        "��������� ���",    "Save as"
        ,
        "���� ������ ������� \"�����������\", ������ ����� ������� � ������� �������� � ����������� ����� � ����������� BMP\n"
        "���� ������ ������� \"�����\", ������ ����� ������� � ������� �������� � ��������� ���� � ����� � ���������� TXT"
        ,
        "If you select \"Image\", the signal will be stored in the current directory in graphic file with the extension BMP\n"
        "If you select \"Text\", the signal will be stored in the current directory as a text file with the extension TXT"
    },
    {
        {"�����������",     "Image"},
        {"�����",           "Text"}
    },
    (int8 *)&MODE_SAVE
};

// ������ - ����� �� - ��� �� ������ ---------------------------------------------------------------------------------------------------------------
static const Choice cDrive_ModeBtnMemory =
{
    Item_Choice, &ppDrive, 0,
    {
        "��� �� ������",    "Mode btn MEMORY",
        "",
        ""
    },
    {
        {"����",            "Menu"},
        {"����������",      "Save"}
    },
    (int8 *)&MODE_BTN_MEMORY
};

// ������ - ����� �� - ��������������� -------------------------------------------------------------------------------------------------------------
static const Choice cDrive_Autoconnect =
{
    Item_Choice, &ppDrive, 0,
    {
        "���������.",   "AutoConnect",
        "E��� \"���\", ��� ����������� �������� ���������� ���������� �������������� ������� �� �������� ������ - ����� ��",
        "If \"Enable\", when you connect an external drive is automatically transferred to the page MEMORY - Ext.Storage"
    },
    {
        {DISABLE_RU,    DISABLE_EN},
        {ENABLE_RU,     ENABLE_EN}
    },
    (int8 *)&FLASH_AUTO_CONNECT
};

// ������ - ����� �� - ������� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page pppDrive_Manager =
{
    Item_Page, &ppDrive, IsActive_Drive_Manager,
    {
        "�������", "DIRECTORY",
        "��������� ������ � �������� ������� ������������� ����������",
        "Provides access to the file system of the connected drive"
    },
    PageSB_Memory_Drive_Manager,
    {
        (void *)&bDrive_Manager_Exit,       // ������ - ����� �� - ������� - �����
        (void *)&bDrive_Manager_Tab,        // ������ - ����� �� - ������� - Tab
        (void *)0,
        (void *)0,
        (void *)&bDrive_Manager_LevelUp,    // ������ - ����� �� - ������� - ����� �� ��������
        (void *)&bDrive_Manager_LevelDown   // ������ - ����� �� - ������� - ����� � �������
    },
    true, OnPress_Drive_Manager, 0, FM_RotateRegSet
};

static bool IsActive_Drive_Manager(void)
{
    return FDRIVE_IS_CONNECTED;
}

void OnPress_Drive_Manager(void)
{
    if (FDRIVE_IS_CONNECTED)
    {
        FDrive_Mount();
        Display_SetDrawMode(DrawMode_Auto, FM_Draw);
        FM_NEED_REDRAW = FM_REDRAW_FULL;
    }
    else
    {
        Display_ShowWarning(WarnNeedForFlashDrive);
    }
}

// ������ - ����� �� - ������� - ����� ------------------------------------------------------------------------------------------------------------
static const SButton bDrive_Manager_Exit =
{
    Item_SmallButton, &pppDrive_Manager, 0,
    {
        "�����", "Exit",
        "������ ��� ������ � ���������� ����",
        "Button to return to the previous menu"
    },
    OnPress_Drive_Manager_Exit,
    DrawSB_Exit
};

static void OnPress_Drive_Manager_Exit(void)
{
    Display_SetDrawMode(DrawMode_Auto, 0);
    OnPressSB_Exit();
}

// ������ - ����� �� - ������� - Tab --------------------------------------------------------------------------------------------------------------
static const SButton bDrive_Manager_Tab =
{
    Item_SmallButton, &pppDrive_Manager, 0,
    {
        "Tab", "Tab",
        "������� ����� ���������� � �������",
        "The transition between the directories and files"
    },
    PressSB_FM_Tab,
    Draw_Drive_Manager_Tab
};

static void Draw_Drive_Manager_Tab(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_TAB);
    Painter_SetFont(TypeFont_8);
}

// ������ - ����� �� - ������� - ����� �� �������� ------------------------------------------------------------------------------------------------
static const SButton bDrive_Manager_LevelUp =
{
    Item_SmallButton, &pppDrive_Manager, 0,
    {
        "����� �� ��������", "Leave from directory",
        "������� � ������������ �������",
        "Transition to the parental catalog"
    },
    PressSB_FM_LevelUp,
    Draw_Drive_Manager_LevelUp
};

static void Draw_Drive_Manager_LevelUp(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x48');
    Painter_SetFont(TypeFont_8);
}

// ������ - ����� �� - ������� - ����� � ������� --------------------------------------------------------------------------------------------------
static const SButton bDrive_Manager_LevelDown =
{
    Item_SmallButton, &pppDrive_Manager, 0,
    {
        "����� � �������", "Enter in directory",
        "������� � ��������� �������",
        "Transition to the chosen catalog"
    },
    PressSB_FM_LevelDown,
    Draw_Drive_Manager_LevelDown
};

static void Draw_Drive_Manager_LevelDown(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x4a');
    Painter_SetFont(TypeFont_8);
}

// ������ - ����� �� - ����� ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const Page pppDrive_Mask =
{
    Item_Page, &ppDrive, IsActive_Drive_Mask,
    {
        "�����", "MASK",
        "����� ����� ����� ��� ��������������� ���������� ������",
        "Input mode mask for automatic file naming"
    },
    PageSB_Memory_Drive_Mask,
    {
        (void *)&bDrive_Mask_Exit,      // ������ - ����� �� - ����� - �����
        (void *)&bDrive_Mask_Delete,    // ������ - ����� �� - ����� - �������
        (void *)0,
        (void *)0,
        (void *)&bDrive_Mask_Backspace, // ������ - ����� �� - ����� - Backspace
        (void *)&bDrive_Mask_Insert     // ������ - ����� �� - ����� - ��������
    },
    true, OnPress_Drive_Mask, 0, OnRegSet_Drive_Mask
};

static bool IsActive_Drive_Mask(void)
{
    return FILE_NAMING_MODE_MASK;
}

static void OnPress_Drive_Mask(void)
{
    Display_SetAddDrawFunction(DrawSetMask);
}

static void DrawSetMask(void)
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
    while (symbolsAlphaBet[index][0] != ' ')
    {
        DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0);
        index++;
        position++;
    }

    // ������ ������ ����� � ������
    position = 0;
    while (symbolsAlphaBet[index][0] != 'a')
    {
        DrawStr(index, x0 + deltaX + 50 + position * 7, y0 + deltaY0 + deltaY);
        index++;
        position++;
    }

    // ������ ������ ����� ����� ��������
    position = 0;
    while (symbolsAlphaBet[index][0] != '%')
    {
        DrawStr(index, x0 + deltaX + position * 7, y0 + deltaY0 + deltaY * 2);
        index++;
        position++;
    }

    // ������ ������ �����������
    position = 0;
    while (index < (sizeof(symbolsAlphaBet) / 4))
    {
        DrawStr(index, x0 + deltaX + 26 + position * 20, y0 + deltaY0 + deltaY * 3);
        index++;
        position++;
    }

    DrawFileMask(x0 + deltaX, y0 + 65);

    static const char * const strings[] =
    {
        "%y - ���, %m - �����, %d - ����",
        "%H - ����, %M - ������, %S - �������",
        "%nN - ���������� �����, ���",
        "n - ����������� ���������� ������ ��� N"
    };

    deltaY--;
    Painter_SetColor(gColorFill);
    for (int i = 0; i < sizeof(strings) / 4; i++)
    {
        Painter_DrawText(x0 + deltaX, y0 + 100 + deltaY * i, strings[i]);
    }
}

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
                x = Painter_DrawText(x, y, symbolsAlphaBet[*ch + 0x40]);
            }
        }
        ch++;
    }
    Painter_FillRegionC(x, y, 5, 8, COLOR_FLASH_10);
}

static void OnRegSet_Drive_Mask(int angle)
{
    OnMemExtSetMaskNameRegSet(angle, sizeof(symbolsAlphaBet) / 4);
}

// ������ - ����� �� - ����� - ����� --------------------------------------------------------------------------------------------------------------
static const SButton bDrive_Mask_Exit =
{
    Item_SmallButton, &pppDrive_Mask,
    COMMON_BEGIN_SB_EXIT,
    OnPressSB_Exit,
    DrawSB_Exit
};

// ������ - ����� �� - ����� - ������� ------------------------------------------------------------------------------------------------------------
static const SButton bDrive_Mask_Delete =
{
    Item_SmallButton, &pppDrive_Mask, 0,
    {
        "�������", "Delete",
        "������� ��� �������� �������",
        "Deletes all entered symbols"
    },
    OnPress_Drive_Mask_Delete,
    Draw_Drive_Mask_Delete
};

static void OnPress_Drive_Mask_Delete(void)
{
    FILE_NAME_MASK[0] = '\0';
}

static void Draw_Drive_Mask_Delete(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_DELETE);
    Painter_SetFont(TypeFont_8);
}

// ������ - ����� �� - ����� - Backspace ----------------------------------------------------------------------------------------------------------
static const SButton bDrive_Mask_Backspace =
{
    Item_SmallButton, &pppDrive_Mask, 0,
    {
        "Backspace", "Backspace",
        "������� ��������� �������� ������",
        "Deletes the last entered symbol"
    },
    OnPress_Drive_Mask_Backspace,
    Draw_Drive_Mask_Backspace
};

static void OnPress_Drive_Mask_Backspace(void)
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

static void Draw_Drive_Mask_Backspace(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_BACKSPACE);
    Painter_SetFont(TypeFont_8);
}

// ������ - ����� �� - ����� - �������� -----------------------------------------------------------------------------------------------------------
static const SButton bDrive_Mask_Insert =
{
    Item_SmallButton, &pppDrive_Mask, 0,
    {
        "��������", "Insert",
        "��������� ��������� ������",
        "Inserts the chosen symbol"
    },
    OnPress_Drive_Mask_Insert,
    Draw_Drive_Mask_Insert
};

static void OnPress_Drive_Mask_Insert(void)
{
    int index = INDEX_SYMBOL;
    int size = strlen(FILE_NAME_MASK);
    if (size == MAX_SYMBOLS_IN_FILE_NAME - 1)
    {
        return;
    }
    if (index < 0x41)
    {
        FILE_NAME_MASK[size] = symbolsAlphaBet[index][0];
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

static void Draw_Drive_Mask_Insert(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, SYMBOL_INSERT);
    Painter_SetFont(TypeFont_8);
}

// �������� ���������� ��� ����� ����� ����� /////////////////////////////////////////////////////////////////////////////////////////////////////////
const Page pSetName =
{
    Item_Page, 0, 0,
    {
        "", "",
        "",
        ""
    },
    PageSB_Memory_SetName,
    {
        (void *)&bSetName_Exit,         // ���� ����� ����� - �����
        (void *)&bSetName_Delete,       // ���� ����� ����� - �������
        (void *)0,
        (void *)&bSetName_Backspace,    // ���� ����� ����� - Backspace
        (void *)&bSetName_Insert,       // ���� ����� ����� - ��������
        (void *)&bSetName_Save          // ���� ����� ����� - ���������
    },
    true, 0, 0, OnRegSet_SetName
};

static void OnRegSet_SetName(int angle)
{
    OnMemExtSetMaskNameRegSet(angle, sizeof(symbolsAlphaBet) / 4 - 7);
}

void OnMemExtSetMaskNameRegSet(int angle, int maxIndex)
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

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const SButton bSetName_Exit =   // ����� ��� ������ �� ������ ������� ����� ������������ �������. ������������ ������ ������ �� ����������
{
    Item_SmallButton, &pSetName, 0,
    {
        "�����", "Exit",
        "����� �� ����������",
        "Failure to save"
    },
    OnPress_SetName_Exit,
    DrawSB_Exit
};


static void OnPress_SetName_Exit(void)
{
    OnPressSB_Exit();
    if (EXIT_FROM_SETNAME_TO == RETURN_TO_DISABLE_MENU)
    {
        ShortPressOnPageItem(PagePointerFromName(PageSB_Memory_SetName), 0);
    }
    else if (EXIT_FROM_SETNAME_TO == RETURN_TO_LAST_MEM)
    {
    }
    else if (EXIT_FROM_SETNAME_TO == RETURN_TO_INT_MEM)
    {
    }
    EXIT_FROM_SETNAME_TO = RETURN_TO_DISABLE_MENU;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const SButton bSetName_Delete =
{
    Item_SmallButton, &pSetName, 0,
    {
        "�������", "Delete",
        "������� ��� �������� �������",
        "Deletes all entered characters"
    },
    OnPress_SetName_Delete,
    Draw_SetName_Delete
};

static void OnPress_SetName_Delete(void)
{
    FILE_NAME[0] = '\0';
}

static void Draw_SetName_Delete(int x, int y) //-V524
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_DELETE);
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const SButton bSetName_Backspace =
{
    Item_SmallButton, &pSetName, 0,
    {
        "Backspace", "Backspace",
        "������� ��������� ������",
        "Delete the last character"
    },
    OnPress_SetName_Backspace,
    Draw_SetName_Backspace
};

static void OnPress_SetName_Backspace(void)
{
    int size = strlen(FILE_NAME);
    if (size > 0)
    {
        FILE_NAME[size - 1] = '\0';
    }
}

static void Draw_SetName_Backspace(int x, int y) //-V524
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_BACKSPACE);
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const SButton bSetName_Insert =
{
    Item_SmallButton, &pSetName, 0,
    {
        "��������", "Insert",
        "������ ��������� ������",
        "Print the next character"
    },
    OnPress_SetName_Insert,
    Draw_SetName_Insert
};

static void OnPress_SetName_Insert(void)
{
    int size = strlen(FILE_NAME);
    if (size < MAX_SYMBOLS_IN_FILE_NAME - 1)
    {
        FILE_NAME[size] = symbolsAlphaBet[INDEX_SYMBOL][0];
        FILE_NAME[size + 1] = '\0';
    }
}

static void Draw_SetName_Insert(int x, int y) //-V524
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x26');
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static const SButton bSetName_Save =
{
    Item_SmallButton, &pSetName, 0,
    {
        "���������", "Save",
        "���������� �� ���� ��� �������� ������",
        "Saving to flashdrive with the specified name"
    },
    OnPress_SetName_Save,
    Draw_SetName_Save
};

static void OnPress_SetName_Save(void)
{
    if (FDRIVE_IS_CONNECTED)
    {
        OnPress_SetName_Exit();
        NEED_SAVE_TO_FLASHDRIVE = 1;
    }
}

static void Draw_SetName_Save(int x, int y)
{
    if (FDRIVE_IS_CONNECTED)
    {
        Painter_SetFont(TypeFont_UGO2);
        Painter_Draw4SymbolsInRect(x + 2, y + 1, SYMBOL_FLASH_DRIVE_BIG);
        Painter_SetFont(TypeFont_8);
    }
}

/*

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


void DrawSB_MemExtNewFolder(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 1, y, '\x46');
    Painter_SetFont(TypeFont_8);
}

extern const Page pMemory;
extern const Page ppDrive;

*/

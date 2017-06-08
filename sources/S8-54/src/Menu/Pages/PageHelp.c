#include "defines.h"
#include "Utils/GlobalFunctions.h"
#include "Globals.h"
#include "Menu/MenuItems.h"
#include "Definition.h"
#include "HelpContent.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern const Page mpHelp;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawSB_Help_ParagraphEnter(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 2, '\x4a');
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawSB_Help_ParagraphLeave(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x48');
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawSB_Help_ParagraphPrev(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 5, '\x4c');
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawSB_Help_ParagraphNext(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 5, '\x4e');
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnHelpRegSet(int angle) 
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const SmallButton sbHelpParagraphEnter =
{
    Item_SmallButton, &mpHelp, HelpContent_EnterParagraphIsActive,
    {
        "�������",  "Open",
        "��������� ������ �������",
        "Opens the section of the reference"
    },
    HelpContent_EnterParagraph,
    DrawSB_Help_ParagraphEnter
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const SmallButton sbHelpParagraphLeave =
{
    Item_SmallButton, &mpHelp, HelpContent_LeaveParagraphIsActive,
    {
        "�������", "Close",
        "��������� ������ �������",
        "Closes the section of the reference"
    },
    HelpContent_LeaveParagraph,
    DrawSB_Help_ParagraphLeave
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const SmallButton sbHelpParagraphPrev =
{
    Item_SmallButton, &mpHelp, 0,
    {
        "���������� ������", "Previous section",
        "������� ���������� ������ �������",
        "To choose the previous section of the reference"
    },
    HelpContent_PrevParagraph,
    DrawSB_Help_ParagraphPrev
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const SmallButton sbHelpParagraphNext =
{
    Item_SmallButton, &mpHelp, 0,
    {
        "", "",
        "", ""
    },
    HelpContent_NextParagraph,
    DrawSB_Help_ParagraphNext
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void PressSB_Help_Exit(void)
{
    Display_RemoveAddDrawFunction();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const SmallButton sbExitHelp =
{
    Item_SmallButton, &mpHelp,
    COMMON_BEGIN_SB_EXIT,
    PressSB_Help_Exit,
    DrawSB_Exit
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const Page mpHelp =
{
    Item_Page, &mainPage, 0,
    {
        "������", "HELP",
        "������� ������� ������",
        "To open sections of the help"
    },
    Page_SB_Help, 
    {
        (void*)&sbExitHelp,
        (void*)&sbHelpParagraphEnter,
        (void*)&sbHelpParagraphLeave,
        (void*)0,
        (void*)&sbHelpParagraphPrev,
        (void*)&sbHelpParagraphNext
    },  
    0, HelpContent_Draw, OnHelpRegSet
};

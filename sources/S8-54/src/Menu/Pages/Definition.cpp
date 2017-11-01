#include "defines.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
extern const Page mainPage;
extern const Page pDisplay;
extern const Page pChanA;
extern const Page pChanB;
extern const Page pTrig;
extern const Page pTime;
extern const Page pCursors;
extern const Page pMemory;
extern const Page pMeasures;
extern const Page pService;
extern const Page pHelp;
extern const Page pDebug;
*/


/// ���� 
const Page mainPage =
{
    Item_Page, 0, 0,
    {
        "����", "MENU",
        "", ""
    },
    Page_Main,
    {
        (void *)0,  // �������
        (void *)0,    // ����� 1
        (void *)0,    // ����� 2
        (void *)0,     // �����
        (void *)0,     // ���������
        (void *)0,  // �������
        (void *)0,   // ������
        (void *)0, // ���������
        (void *)0,  // ������
        (void *)0,     // ������
        (void *)0     // �������
    }
};

//----------------------------------------------------------------------------------------------------------------------------------------------------
const void *PageForButton(PanelButton button)
{
    static const void *pages[] = {  
        0,                  // B_Empty
        0,    // B_Channel1
        0,  // B_Service
        0,    // B_Channel2
        0,  // B_Display
        0,     // B_Time
        0,   // B_Memory
        0,     // B_Trig
        0,                  // B_Start
        0,  // B_Cursors
        0, // B_Measures
        0,                  // B_Power
        0,     // B_Help
        0,                  // B_Menu
        0,                  // B_F1
        0,                  // B_F2
        0,                  // B_F3
        0,                  // B_F4
        0,                  // B_F5
    };

    return pages[button];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool IsMainPage(const void *item)
{
    return item == &mainPage;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawSB_Exit(int x, int y)
{
    Painter_SetFont(TypeFont_UGO2);
    Painter_Draw4SymbolsInRect(x + 2, y + 1, '\x2e');
    Painter_SetFont(TypeFont_8);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OnPressSB_Exit(void)
{
    Display_RemoveAddDrawFunction();
}

#pragma once
#include "Display/Colors.h"
#include "Display/Display.h"
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Menu
 *  @{
 *  @defgroup MenuItems Menu Items
 *  @{
 */

#define MAX_NUM_SUBITEMS_IN_CHOICE  12  // ������������ ���������� ��������� ������ � �������� Choice.
#define MAX_NUM_ITEMS_IN_PAGE       16  // ������������ ���������� ������� �� ��������.
#define MENU_ITEMS_ON_DISPLAY       5   // ������� ������� ���� ���������� �� ������ �� ���������.
#define MAX_NUM_CHOICE_SMALL_BUTTON 6   // ������������ ���������� ��������� ��������� ������ + 1


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������ ���� ������� ����
typedef enum
{
    Item_None,           
    Item_Choice,        // ����� ������ - ��������� ������� ���� �� ���������� �������� ��������.
    Item_Button,        // ������.
    Item_Page,          // ��������.
    Item_Governor,      // ��������� - ��������� ������� ����� ����� �������� �������� �� ������� ��������� ����������.
    Item_Time,          // ��������� ������ �����.
    Item_IP,            // ��������� ������ IP-�����.
    Item_SwitchButton,
    Item_GovernorColor, // ��������� ������� ����.
    Item_Formula,       // ��������� ������� ���� � ������������ ��� �������������� ������� (��������� � ��������)
    Item_MAC,           // MAC-�����
    Item_ChoiceReg,     // ������� ������, � ������� ����� �������������� �� �������, � ������
    Item_SmallButton,   // ������ ��� ������ ����� ������
    Item_NumberItems
} TypeItem;

// ����� ID ���� �������������� � ���� �������
typedef enum
{
    Page_Display,               // ������
    Page_DisplayAccumulation,   // ������� - ����������
    Page_DisplayAverage,        // ������� - ����������
    Page_DisplayGrid,           // ������� - �����
    Page_DisplaySettings,       // ������� - ���������
    Page_MainPage,              // ������� �������� ����. �� �� ������ ��� ���������
    Page_Debug,                 // �������
    Page_DebugConsole,          // ������� - �������
    Page_DebugADC,              // ������� - ���
    Page_DebugADCbalance,       // ������� - ��� - ������
    Page_DebugADCstretch,       // ������� - ��� - ��������
    Page_DebugADCrShift,        // ������� - ��� - ���. ��������
    Page_DebugADCaltShift,      // ������� - ��� - ���. ����. ���.
    Page_DebugShowRegisters,    // ������� - ��������
    Page_DebugRandomizer,       // ������� - ����-���
    Page_DebugChannels,         // ������� - ������
    Page_DebugSound,            // ������� - ����
    Page_DebugAltera,           // ������� - �������
    Page_ChannelA,              // ����� 1
    Page_ChannelB,              // ����� 2
    Page_Cursors,               // �������
    Page_Trig,                  // �����.
    Page_Memory,                // ������
    Page_MemoryExt,             // ������ - �����. ��
    Page_Measures,              // ���������
    Page_MeasuresField,         // ��������� - ����
    Page_Service,               // ������
    Page_ServiceDisplayColors,  // ������ - ������� - �����
    Page_ServiceCalibrator,     // ������ - ����������
    Page_ServiceCalibratorCalibration,  // ������ - ���������� - ����������
    Page_ServiceEthernet,       // ������ - ETHERNET
    Page_ServiceFreqMeter,      // ������ - ����������
    Page_ServiceSound,          // ������ - ����
    Page_ServiceTime,           // ������ - �����
    Page_Help,                  // ������
    Page_Time,                  // ���������
    Page_Math,                  // ������ - ����������
    Page_MathFFT,
    Page_TrigAuto,              // ����� - ��� �����
    Page_SB_Curs,               // ������� �������� ������� - ���������
    Page_SB_MeasTuneMeas,       // ������� �������� ��������� - ���������
    Page_SB_MeasTuneField,      // ������� �������� ��������� - ���� - ������
    Page_SB_MemLatest,          // ������� �������� ������ - ���������
    Page_SB_MemInt,             // ������� �������� ������ - ����� ��
    Page_SB_MemExtSetMask,      // ������� �������� ������ - ����� �� - �����
    Page_SB_MemExtSetName,      // ���������� ����� ����������� ����� �� ������ ��� ������� ����� ����� ��� ��������������� ����� ����� �� - ��� �����
    Page_SB_FileManager,        // ������� �������� ������ - ����� �� - �����
    Page_SB_Help,               // ������� �������� HELP
    Page_SB_MathCursorsFFT,     // ������� �������� ������ - ���������� - �������
    Page_SB_MathFunction,       // ������ - ���������� - �������
    Page_SB_ServiceInformation, // ������ - ����������
    Page_SB_DebugShowSetInfo,   // ������� - ��������
    Page_SB_SerialNumber,       // ������� - �/�
    Page_NumPages,
    Page_NoPage
} NamePage;             // ��� ���������� ������� ����� �������� ������������� SettingsMenu � SSettings.c

#define COMMON_PART_MENU_ITEM                                                                                   \
    TypeItem                type;           /* ��� ����� */                                                     \
    const struct Page*      keeper;         /* ����� ��������, ������� �����������. ��� Page_MainPage = 0 */    \
    pFuncBV                 funcOfActive;   /* ������� �� ������ ������� */                                     \
    const char*             titleHint[4];   /* �������� �������� �� ������� � ���������� ������. ����� ��������� ��� ������ ������ */

// ��������� �������� ����.
struct Page
{
    COMMON_PART_MENU_ITEM
    NamePage                name;                               // ��� �� ������������ NamePage
    void*                   items[MAX_NUM_ITEMS_IN_PAGE];       // ����� ��������� �� ������ ���� �������� (� ������� ��������)
                                                                // ��� �������� ����� ������  ����� �������� 6 ���������� �� SButton : 0 - B_Menu, 1...5 - B_F1...B_F5
    pFuncVV                 funcOnPress;                        // ����� ���������� ��� ������� �� �������� ��������
    pFuncVV                 funcOnDraw;                         // ����� ���������� ����� ��������� ������
    pFuncVI                 funcRegSetSB;                       // � �������� ����� ������ ���������� ��� �������� ����� ���������
};

typedef struct Page Page;

// ������ �������
typedef struct
{
    COMMON_PART_MENU_ITEM
} Empty;

// ��������� ������.
typedef struct
{
    COMMON_PART_MENU_ITEM
    pFuncVV         funcOnPress;                // �������, ������� ���������� ��� ������� �� ������.
    pFuncVII        funcForDraw;                // ������� ����� ���������� �� ����� ��������� ������.
} Button;

typedef struct
{
    pFuncVII    funcDrawUGO;    // ��������� �� ������� ��������� ����������� �������� ������
    const char *helpUGO[2];     // ������� � ������� �����������.
} StructHelpSmallButton;

// ��������� ������ ��� ��������������� ������ ����.
typedef struct
{
    COMMON_PART_MENU_ITEM
    pFuncVV                 funcOnPress;        // ��� ������� ��������� ��� ��������� ������� ������.
    pFuncVII                funcOnDraw;         // ��� ������� ���������� ��� ��������� ������ � ����� � ������������ x, y.
    StructHelpSmallButton   hintUGO[MAX_NUM_CHOICE_SMALL_BUTTON]; 
} SButton;

// ��������� ���������.
typedef struct
{
    COMMON_PART_MENU_ITEM
    int16*              cell;
    int16               minValue;                   // ���������� ��������, ������� ����� ��������� ���������.
    int16               maxValue;                   // ������������ ��������.
    pFuncVV             funcOfChanged;              // �������, ������� ����� �������� ����� ����, ��� �������� ���������� ����������.
    pFuncVV             funcBeforeDraw;             // �������, ������� ���������� ����� ����������
} Governor;

typedef struct
{
    COMMON_PART_MENU_ITEM
    uint8*  ip0;
    uint8*  ip1;
    uint8*  ip2;
    uint8*  ip3;
    pFuncVB funcOfChanged;
    uint16* port;
} IPaddress;

typedef struct
{
    COMMON_PART_MENU_ITEM
    uint8*  mac0;
    uint8*  mac1;
    uint8*  mac2;
    uint8*  mac3;
    uint8*  mac4;
    uint8*  mac5;
    pFuncVB funcOfChanged;
} MACaddress;

// ��������� ������� ���� ��� ��������� ������������� � ������ �������������� �������
#define FIELD_SIGN_MEMBER_1_ADD 0
#define FIELD_SIGN_MEMBER_1_MUL 1
#define FIELD_SIGN_MEMBER_2_ADD 2
#define FIELD_SIGN_MEMBER_2_MUL 3
#define POS_SIGN_MEMBER_1       0
#define POS_KOEFF_MEMBER_1      1
#define POS_SIGN_MEMBER_2       2
#define POS_KOEFF_MEMBER_2      3
typedef struct
{
    COMMON_PART_MENU_ITEM
    int8*           function;                   // ����� ������, ��� �������� Function, �� ������� ������ ���� ��������
    int8*           koeff1add;                  // ����� ������������ ��� ������ ����� ��� ��������
    int8*           koeff2add;                  // ����� ������������ ��� ������ ����� ��� ��������
    int8*           koeff1mul;                  // ����� ������������ ��� ������ ����� ��� ���������
    int8*           koeff2mul;                  // ����� ������������ ��� ������ ����� ��� ���������
    int8*           curDigit;                   // ������� ������ : 0 - ���� ������� �����, 1 - ����������� ������� �����,
                                                //  2 - ���� ������� �����, 3 - ����������� ������� �����
    pFuncVV         funcOfChanged;              // ��� ������� ���������� ����� ��������� ��������� �������� ����������.
} Formula;

typedef struct
{
    COMMON_PART_MENU_ITEM
    ColorType*      colorType;                  // ��������� ��� �������� �����.
    pFuncVV         funcOnChanged;              // ��� ������� ����� �������� ����� ��������� �������� ��������.
} GovernorColor;

typedef struct
{
    COMMON_PART_MENU_ITEM
    const char*     names[MAX_NUM_SUBITEMS_IN_CHOICE][2];   // �������� ������ �� ������� � ���������� ������.
    int8*           cell;                                   // ����� ������, � ������� �������� ������� �������� ������.
    pFuncVB			funcOnChanged;                          // ������� ������ ���������� ����� ��������� �������� ��������.
    pFuncVII        funcForDraw;                            // ������� ���������� ����� ��������� ��������. 
} Choice;


#define iEXIT   0
#define iDAY    1
#define iMONTH  2
#define iYEAR   3
#define iHOURS  4
#define iMIN    5
#define iSEC    6
#define iSET    7

// ������������� � ���������� �����.
typedef struct
{
    COMMON_PART_MENU_ITEM
    int8*       curField;       // ������� ���� ���������. 0 - �����, 1 - ���, 2 - ���, 3 - ����, 4 - ����, 5 - �����, 6 - ���, 7 - ����������.
    int8*       hours;
    int8*       minutes;
    int8*       seconds;
    int8*       month;
    int8*       day;
    int8*       year;
} Time;


// ��������� ��� �������� ����, ����������� �� ������� �����
typedef struct
{
    int16 i;
} StructFuncReg;

#define CHOICE_RUN_FUNC_CHANGED(c, val)     \
    if(c->funcOnChanged)                    \
    {                                       \
        c->funcOnChanged(val);              \
    }

/** @}  @}
 */

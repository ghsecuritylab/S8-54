#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/MenuFunctions.h"
#include "Settings/Settings.h"
#include "Menu/MenuItemsLogic.h"
#include "Utils/GlobalFunctions.h"
#include "Menu/MenuDrawing.h"
#include "Hardware/RTC.h"
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Governor_DrawOpened(Governor *governor, int x, int y);
static void MACaddress_DrawOpened(MACaddress *mac, int x, int y);
static void IPaddress_DrawOpened(IPaddress *ip, int x, int y);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawGovernorChoiceColorFormulaHiPart(void *item, int x, int y, bool pressed, bool shade, bool opened)
{
    int delta = pressed && !shade ? 1 : 0;
    int width = MI_WIDTH_VALUE;

    if (TypeMenuItem(item) == Item_IP && opened && ((IPaddress*)item)->port != 0)
    {
        width += MOI_WIDTH_D_IP;
    }

    Color color = shade ? ColorMenuTitleLessBright() : (COLOR_SCHEME_IS_WHITE_LETTERS ? COLOR_WHITE :COLOR_BLACK);
    painter.DrawHLine(y + 1, x, x + width + 3, ColorBorderMenu(false));

    painter.DrawVolumeButton(x + 1, y + 2, width + 2, MI_HEIGHT_VALUE + 3, 1, ColorMenuItem(false), ColorMenuItemBrighter(), ColorMenuItemLessBright(), 
        pressed, shade);

    painter.DrawTextC(x + 6 + delta, y + 6 + delta, TitleItem(item), color);
    
    TypeItem type = TypeMenuItem(item);

    if(CurrentItem() == item)
    {
        char symbol = 0;

        if (type == Item_Governor)
        {
            symbol = GetSymbolForGovernor(*((Governor*)item)->cell);
        }
        else if (type == Item_Governor || type == Item_ChoiceReg ||  (ItemIsOpened(item) && type == Item_Choice))
        {
            symbol = GetSymbolForGovernor(*((Choice*)item)->cell);
        }
        else if (type == Item_Time)
        {
            Time *time = (Time*)item;
            if ((OpenedItem() == item) && (*time->curField != iEXIT) && (*time->curField != iSET))
            {
                int8 values[7] =
                {
                    0,
                    *time->day,
                    *time->month,
                    *time->year,
                    *time->hours,
                    *time->minutes,
                    *time->seconds
                };
                symbol = GetSymbolForGovernor(values[*time->curField]);
            }
        }

        painter_Draw4SymbolsInRectC(x + MI_WIDTH - 13, y + 5 + (ItemIsOpened(item) ? 0 : 15), symbol, shade ? color : COLOR_BLACK);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawGovernorLowPart(Governor *governor, int x, int y, bool pressed, bool shade)
{
    char buffer[20];
    
    Color colorTextDown = COLOR_BLACK;

    painter.DrawVolumeButton(x + 1, y + 17, MI_WIDTH_VALUE + 2, MI_HEIGHT_VALUE + 3, 2, COLOR_MENU_FIELD, 
        ColorMenuItemBrighter(), ColorMenuItemLessBright(), true, shade);
    if(shade)
    {
        colorTextDown = ColorMenuItem(false);
    }

    x = painter.DrawTextC(x + 4, y + 21, "\x80", colorTextDown);
    if(OpenedItem() != governor)
    {
        int delta = (int)Governor_Step(governor);
        if(delta == 0)
        {
            x = painter.DrawText(x + 1, y + 21, Int2String(*governor->cell, false, 1, buffer));
        }
        else
        {
            int drawX = x + 1;
            int limX = x + 1;
            int limY = y + 19;
            int limWidth = MI_WIDTH_VALUE;
            int limHeight = MI_HEIGHT_VALUE - 1;
            if(delta > 0)
            {
                x = painter.DrawTextWithLimitationC(drawX, y + 21 - delta, Int2String(*governor->cell, false, 1, buffer), 
                                            COLOR_BLACK, limX, limY, limWidth, limHeight);
                painter.DrawTextWithLimitationC(drawX, y + 21 + 10 - delta, Int2String(Governor_NextValue(governor), false, 1, buffer),
                                            COLOR_BLACK, limX, limY, limWidth, limHeight);
            }
            if(delta < 0)
            {
                x = painter.DrawTextWithLimitationC(drawX, y + 21 - delta, Int2String(*governor->cell, false, 1, buffer), 
                                            COLOR_BLACK, limX, limY, limWidth, limHeight);
                painter.DrawTextWithLimitationC(drawX, y + 21 - 10 - delta, Int2String(Governor_PrevValue(governor), false, 1, buffer),
                    COLOR_BLACK, limX, limY, limWidth, limHeight);
            }
        }
    }
    else
    {
        x = painter.DrawTextC(x + 1, y + 21, Int2String(*governor->cell, false, 1, buffer), COLOR_WHITE);
    }
    painter.DrawTextC(x + 1, y + 21, "\x81", colorTextDown);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawIPaddressLowPart(IPaddress *ip, int x, int y, bool pressed, bool shade)
{
    const int SIZE = 20;
    char buffer[SIZE];

    Color colorTextDown = COLOR_BLACK;

    painter.DrawVolumeButton(x + 1, y + 17, MI_WIDTH_VALUE + 2, MI_HEIGHT_VALUE + 3, 2, COLOR_MENU_FIELD,
                             ColorMenuItemBrighter(), ColorMenuItemLessBright(), true, shade);
    if (shade)
    {
        colorTextDown = ColorMenuItem(false);
    }

    snprintf(buffer, SIZE, "%03d.%03d.%03d.%03d", *ip->ip0, *ip->ip1, *ip->ip2, *ip->ip3);

    if (OpenedItem() != ip)
    {
        
        painter.DrawTextC(x + 4, y + 21, buffer, colorTextDown);
    }
    else
    {
        painter.DrawTextC(x + 4, y + 21, buffer, COLOR_WHITE);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawMACaddressLowPart(MACaddress *mac, int x, int y, bool pressed, bool shade)
{
    const int SIZE = 20;
    char buffer[SIZE];

    Color colorTextDown = COLOR_BLACK;

    painter.DrawVolumeButton(x + 1, y + 17, MI_WIDTH_VALUE + 2, MI_HEIGHT_VALUE + 3, 2, COLOR_MENU_FIELD,
                             ColorMenuItemBrighter(), ColorMenuItemLessBright(), true, shade);
    if (shade)
    {
        colorTextDown = ColorMenuItem(false);
    }

    snprintf(buffer, SIZE, "%02X.%02X.%02X.%02X.%02X.%02X", *mac->mac0, *mac->mac1, *mac->mac2, *mac->mac3, *mac->mac4, *mac->mac5);

    if (OpenedItem() != mac)
    {

        painter.DrawTextC(x + 4, y + 21, buffer, colorTextDown);
    }
    else
    {
        painter.DrawTextC(x + 4, y + 21, buffer, COLOR_WHITE);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WriteTextFormula(Formula *formula, int x, int y, bool opened)
{
    Function function = (Function)(*formula->function);
    
    if (function != Function_Mul && function != Function_Sum)
    {
        return;
    }

    bool funcIsMul = function == Function_Mul;
    int8 koeff1 = funcIsMul ? *formula->koeff1mul : *formula->koeff1add;
    int8 koeff2 = funcIsMul ? *formula->koeff2mul : *formula->koeff2add;
    if (koeff1 != 0)
    {
       painter.DrawChar(x, y, koeff1 < 0 ? '-' : '+');
    }
    painter.DrawChar(x + 5, y, (char)(koeff1 + 0x30));
    painter.DrawChar(x + 10, y, '*');
    painter.DrawText(x + 14, y, "K1");
    painter.DrawChar(x + 27, y, funcIsMul ? '*' : '+');
    if (koeff2 != 0)
    {
       painter.DrawChar(x + 30, y, koeff2 < 0 ? '-' : '+');
    }
    painter.DrawChar(x + 39, y, (char)(koeff2 + 0x30));
    painter.DrawChar(x + 44, y, '*');
    painter.DrawText(x + 48, y, "K2");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawFormulaLowPart(Formula *formula, int x, int y, bool pressed, bool shade)
{
    Color colorTextDown = COLOR_BLACK;

    painter.DrawVolumeButton(x + 1, y + 17, MI_WIDTH_VALUE + 2, MI_HEIGHT_VALUE + 3, 2, COLOR_MENU_FIELD,
                     ColorMenuItemBrighter(), ColorMenuItemLessBright(), true, shade);
    if (shade)
    {
        colorTextDown = ColorMenuItem(false);
    }
    painter.SetColor(colorTextDown);
    WriteTextFormula(formula, x + 6, y + 21, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Governor_DrawClosed(Governor *governor, int x, int y)
{
    bool pressed = IsPressed(governor);
    bool shade = IsShade(governor) || !ItemIsAcitve(governor);
    DrawGovernorLowPart(governor, x, y, pressed, shade);
    DrawGovernorChoiceColorFormulaHiPart(governor, x, y, pressed, shade, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void IPaddress_DrawClosed(IPaddress *ip, int x, int y)
{
    bool pressed = IsPressed(ip);
    bool shade = IsShade(ip) || !ItemIsAcitve(ip);
    DrawIPaddressLowPart(ip, x, y, pressed, shade);
    DrawGovernorChoiceColorFormulaHiPart(ip, x, y, pressed, shade, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void MACaddress_DrawClosed(MACaddress *mac, int x, int y)
{
    bool pressed = IsPressed(mac);
    bool shade = IsShade(mac) || !ItemIsAcitve(mac);
    DrawMACaddressLowPart(mac, x, y, pressed, shade);
    DrawGovernorChoiceColorFormulaHiPart(mac, x, y, pressed, shade, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Formula_DrawClosed(Formula *formula, int x, int y)
{
    bool pressed = IsPressed(formula);
    bool shade = IsShade(formula) || !ItemIsAcitve(formula);
    DrawFormulaLowPart(formula, x, y, pressed, shade);
    DrawGovernorChoiceColorFormulaHiPart(formula, x, y, pressed, shade, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
// ���� selPos == -1, ������������ �� �����
static void DrawValueWithSelectedPosition(int x, int y, int value, int numDigits, int selPos, bool hLine, bool fillNull)
{
    int firstValue = value;
    int height = hLine ? 9 : 8;
    for (int i = 0; i < numDigits; i++)
    {
        int rest = value % 10;
        value /= 10;
        if (selPos == i)
        {
            painter.FillRegion(x - 1, y, 5, height, gColorFill);
        }
        if (!(rest == 0 && value == 0) || (firstValue == 0 && i == 0))
        {
            painter.DrawCharC(x, y, (char)(rest + 48), selPos == i ? COLOR_BLACK : COLOR_WHITE);
        }
        else if (fillNull)
        {
            painter.DrawCharC(x, y, '0', selPos == i ? COLOR_BLACK : COLOR_WHITE);
        }
        if (hLine)
        {
            painter_DrawLineC(x, y + 9, x + 3, y + 9, COLOR_WHITE);
        }
        x -= 6;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawGovernorValue(int x, int y, Governor *governor)
{
    char buffer[20];

    int startX = x + 40;
    int16 value = *governor->cell;
    int signGovernor = *governor->cell < 0 ? -1 : 1;
    if(signGovernor == -1)
    {
        value = -value;
    }
    painter.SetFont(TypeFont_5);
    bool sign = governor->minValue < 0;
    painter.DrawTextC(x + 55, y - 5, Int2String(governor->maxValue, sign, 1, buffer), COLOR_WHITE);
    painter.DrawText(x + 55, y + 2, Int2String(governor->minValue, sign, 1, buffer));
    painter.SetFont(TypeFont_8);

    DrawValueWithSelectedPosition(startX, y, value, Governor_NumDigits(governor), gCurDigit, true, true);

    if(sign)
    {
       painter.DrawChar(startX - 30, y, signGovernor < 0 ? '\x9b' : '\x9a');
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawIPvalue(int x, int y, IPaddress *ip)
{
    if (gCurDigit > (ip->port == 0 ? 11 : 16))
    {
        gCurDigit = 0;
    }

    uint8 *bytes = ip->ip0;

    x += 15;

    y += 1;

    int numIP = 0;
    int selPos = 0;

    IPaddress_GetNumPosIPvalue(&numIP, &selPos);

    for (int i = 0; i < 4; i++)
    {
        DrawValueWithSelectedPosition(x, y, bytes[i], 3, numIP == i ? selPos : -1, false, true);
        if (i != 3)
        {
            painter.DrawCharC(x + 5, y, '.', COLOR_WHITE);
        }
        x += 19;
    }

    if (ip->port != 0)
    {
        painter.DrawCharC(x - 13, y, ':', COLOR_WHITE);
        DrawValueWithSelectedPosition(x + 14, y, *ip->port, 5, numIP == 4 ? selPos : -1, false, true);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawMACvalue(int x, int y, MACaddress *mac)
{
    if (gCurDigit > 5)
    {
        gCurDigit = 0;
    }
    uint8 *bytes = mac->mac0;
    x += MOI_WIDTH - 14;
    y++;
    for (int num = 5; num >= 0; num--)
    {
        int value = (int)(*(bytes + num));
        if (gCurDigit == num)
        {
            painter.FillRegion(x - 1, y, 10, 8, COLOR_WHITE);
        }
        const int SIZE = 20;
        char buffer[SIZE];
        snprintf(buffer, SIZE, "%02X", value);
        painter.DrawTextC(x, y, buffer, gCurDigit == num ? COLOR_BLACK : COLOR_WHITE);
        x -= 12;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Governor_Draw(Governor *governor, int x, int y, bool opened)
{
    if (governor->funcBeforeDraw)
    {
        governor->funcBeforeDraw();
    }
    if(opened)
    {
        Governor_DrawOpened(governor, x, y);
    }
    else
    {
        Governor_DrawClosed(governor, x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void IPaddress_Draw(IPaddress *ip, int x, int y, bool opened)
{
    if (opened)
    {
        IPaddress_DrawOpened(ip, x - (ip->port == 0 ? 0 : MOI_WIDTH_D_IP), y);
    }
    else
    {
        IPaddress_DrawClosed(ip, x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void MACaddress_Draw(MACaddress *mac, int x, int y, bool opened)
{
    if (opened)
    {
        MACaddress_DrawOpened(mac, x, y);
    }
    else
    {
        MACaddress_DrawClosed(mac, x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Formula_Draw(Formula *formula, int x, int y, bool opened)
{
    if (opened)
    {
        
    }
    else
    {
        Formula_DrawClosed(formula, x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawGovernorColorValue(int x, int y, GovernorColor *govColor, int delta)
{
    char buffer[20];
    
    ColorType *ct = govColor->colorType;
    int8 field = ct->currentField;
    char *texts[4] = {"��", "��", "��", "��"};

    uint16 color = COLOR(ct->color);
    int red = R_FROM_COLOR(color);
    int green = G_FROM_COLOR(color);
    int blue = B_FROM_COLOR(color);
    Color_Init(ct, false);
    int16 vals[4] = {(int16)(ct->brightness * 100.0f), (int16)blue, (int16)green, (int16)red};

    painter.FillRegion(x, y, MI_WIDTH + delta - 2, MI_HEIGHT / 2 - 3, COLOR_BLACK);
    x += 92;
    
    for(int i = 0; i < 4; i++)
    {
        Color colorBack = (field == i) ? COLOR_WHITE : COLOR_BLACK;
        Color colorDraw = (field == i) ? COLOR_BLACK : COLOR_WHITE;
        painter.FillRegion(x - 1, y + 1, 29, 10, colorBack);
        painter.DrawTextC(x, y + 2, texts[i], colorDraw);
        painter.DrawText(x + 14, y + 2, Int2String(vals[i], false, 1, buffer));
        x -= 30;
    }
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void GovernorColor_DrawOpened(GovernorColor *gov, int x, int y)
{
    static const int delta = 43;
    x -= delta;
    Color_Init(gov->colorType, false);
    painter.DrawRectangle(x - 1, y - 1, MI_WIDTH + delta + 2, MI_HEIGHT + 2, COLOR_BLACK);
    painter.DrawRectangle(x, y, MI_WIDTH + delta, MI_HEIGHT, ColorMenuTitle(false));
    painter.DrawVolumeButton(x + 1, y + 1, MI_WIDTH_VALUE + 2 + delta, MI_HEIGHT_VALUE + 3, 2, ColorMenuItem(false), 
        ColorMenuItemBrighter(), ColorMenuItemLessBright(), IsPressed(gov), IsShade(gov));
    painter.DrawHLine(y + MI_HEIGHT / 2 + 2, x, x + MI_WIDTH + delta, ColorMenuTitle(false));
    painter.DrawStringInCenterRectC(x + (IsPressed(gov) ? 2 : 1), y + (IsPressed(gov) ? 2 : 1), MI_WIDTH + delta, MI_HEIGHT / 2 + 2, TitleItem(gov), 
        COLOR_WHITE);
    DrawGovernorColorValue(x + 1, y + 19, gov, delta);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void GovernorColor_DrawClosed(GovernorColor *gov, int x, int y)
{
    Color_Init(gov->colorType, false);
    DrawGovernorChoiceColorFormulaHiPart(gov, x, y, IsPressed(gov), IsShade(gov) || !ItemIsAcitve(gov), true);
    painter.FillRegion(x + 2, y + 20, MI_WIDTH_VALUE, MI_HEIGHT_VALUE - 1, gov->colorType->color);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void GovernorColor_Draw(GovernorColor *govColor, int x, int y, bool opened)
{
    if(opened)
    {
        GovernorColor_DrawOpened(govColor, x, y);
    }
    else
    {
        GovernorColor_DrawClosed(govColor, x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Choice_DrawOpened(Choice *choice, int x, int y)
{
    int height = HeightOpenedItem(choice);

    painter.DrawRectangle(x - 2, y - 1, MP_TITLE_WIDTH + 3, height + 3, gColorBack);
    
    DrawGovernorChoiceColorFormulaHiPart(choice, x - 1, y - 1, IsPressed(choice), false, true);
    painter.DrawRectangle(x - 1, y, MP_TITLE_WIDTH + 1, height + 1, ColorMenuTitle(false));
 
    painter.DrawHLine(y + MOI_HEIGHT_TITLE - 1, x, x + MOI_WIDTH);
    painter.DrawVolumeButton(x, y + MOI_HEIGHT_TITLE, MOI_WIDTH - 1, height - MOI_HEIGHT_TITLE, 1, COLOR_BLACK, ColorMenuTitleBrighter(),
                        ColorMenuTitleLessBright(), false, IsShade(choice));
    int8 index = *choice->cell;
    for(int i = 0; i < Choice_NumSubItems(choice); i++)
    {
        int yItem = y + MOI_HEIGHT_TITLE + i * MOSI_HEIGHT + 1;
        bool pressed = i == index;
        if(pressed)
        {
            painter.DrawVolumeButton(x + 1, yItem, MOI_WIDTH - 2 , MOSI_HEIGHT - 2, 2, COLOR_MENU_FIELD, ColorMenuTitleBrighter(),
                ColorMenuTitleLessBright(), pressed, IsShade(choice));
        }
        painter.DrawTextC(x + 4, yItem + 2, NameSubItem(choice, i), pressed ? COLOR_BLACK : COLOR_MENU_FIELD);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Time_DrawOpened(Time *time, int x, int y)
{
    char buffer[20];
    
    int width = MI_WIDTH_VALUE + 3;
    int height = 61;
    painter.DrawRectangle(x - 1, y - 1, width + 2, height + 3, gColorBack);
    DrawGovernorChoiceColorFormulaHiPart(time, x - 1, y - 1, IsPressed(time), false, true);

    painter.DrawRectangle(x - 1, y, width + 1, height + 1, ColorMenuTitle(false));

    painter.DrawHLine(y + MOI_HEIGHT_TITLE - 1, x, x + MOI_WIDTH);
    painter.DrawVolumeButton(x, y + MOI_HEIGHT_TITLE, MOI_WIDTH - 1, height - MOI_HEIGHT_TITLE, 1, COLOR_BLACK, ColorMenuTitleBrighter(),
                             ColorMenuTitleLessBright(), false, IsShade(time));

    int y0 = 21;
    int y1 = 31;

    typedef struct 
    {
        int x;
        int y;
        int width;
    } StructPaint;
    
    int y2 = 41;
    int y3 = 51;
    int dX = 13;
    int wS = 10;
    int x0 = 41;
    StructPaint strPaint[8] =
    {
        {3,             y3, 60},    // �� ���������
        {x0,            y0, wS},    // ����
        {x0 + dX,       y0, wS},    // �����
        {x0 + 2 * dX,   y0, wS},    // ���
        {x0,            y1, wS},    // ����
        {x0 + dX,       y1, wS},    // ���
        {x0 + 2 * dX,   y1, wS},    // ���
        {3,             y2, 46}     // ���������
    };

    char strI[8][20];
    strcpy(strI[iEXIT],     "�� ���������");
    strcpy(strI[iDAY],      Int2String(*time->day,      false, 2, buffer));
    strcpy(strI[iMONTH],    Int2String(*time->month,    false, 2, buffer));
    strcpy(strI[iYEAR],     Int2String(*time->year,     false, 2, buffer));
    strcpy(strI[iHOURS],    Int2String(*time->hours,    false, 2, buffer));
    strcpy(strI[iMIN],      Int2String(*time->minutes,  false, 2, buffer));
    strcpy(strI[iSEC],      Int2String(*time->seconds,  false, 2, buffer));
    strcpy(strI[iSET],      "���������");

    painter.DrawTextC(x + 3, y + y0, "� � � - ", COLOR_WHITE);
    painter.DrawText(x + 3, y + y1, "� � � - ");

    for (int i = 0; i < 8; i++)
    {
        if (*time->curField == i)
        {
            painter.FillRegion(x + strPaint[i].x - 1, y + strPaint[i].y, strPaint[i].width, 8, COLOR_FLASH_10);
        }
        painter.DrawTextC(x + strPaint[i].x, y + strPaint[i].y, strI[i], *time->curField == i ? COLOR_FLASH_01 : COLOR_WHITE);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void GovernorIpCommon_DrawOpened(void *item, int x, int y, int dWidth)
{
    int height = 34;
    painter.DrawRectangle(x - 2, y - 1, MP_TITLE_WIDTH + 3 + dWidth, height + 3, gColorBack);
    painter.DrawRectangle(x - 1, y, MP_TITLE_WIDTH + 1 + dWidth, height + 1, ColorMenuTitle(false));
    painter.DrawHLine(y + MOI_HEIGHT_TITLE - 1, x, x + MOI_WIDTH + dWidth);
    DrawGovernorChoiceColorFormulaHiPart(item, x - 1, y - 1, IsPressed(item), false, true);
    painter.DrawVolumeButton(x, y + MOI_HEIGHT_TITLE, MOI_WIDTH - 1 + dWidth, height - MOI_HEIGHT_TITLE, 1, COLOR_BLACK, ColorMenuTitleBrighter(),
                             ColorMenuTitleLessBright(), false, IsShade(item));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void Governor_DrawOpened(Governor *governor, int x, int y)
{
    GovernorIpCommon_DrawOpened(governor, x, y, 0);
    DrawGovernorValue(x, y + 22, governor);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void IPaddress_DrawOpened(IPaddress *ip, int x, int y)
{
    GovernorIpCommon_DrawOpened(ip, x, y, ip->port == 0 ? 0 : MOI_WIDTH_D_IP);
    DrawIPvalue(x, y + 22, ip);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void MACaddress_DrawOpened(MACaddress *mac, int x, int y)
{
    GovernorIpCommon_DrawOpened(mac, x, y, 0);
    DrawMACvalue(x, y + 22, mac);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Choice_DrawClosed(Choice *choice, int x, int y)
{
    bool pressed = IsPressed(choice);
    bool shade = IsShade(choice) || ! ItemIsAcitve(choice);
        
    painter.DrawVolumeButton(x + 1, y + 17, MI_WIDTH_VALUE + 2, MI_HEIGHT_VALUE + 3, 1, COLOR_MENU_FIELD, ColorMenuItemBrighter(), 
        ColorMenuItemLessBright(), true, shade);

    int deltaY = (int)Choice_Step(choice);
    Color colorText = shade ? ColorMenuItem(true) : COLOR_BLACK;
    painter.SetColor(colorText);
    if(deltaY == 0)
    {
        painter.DrawText(x + 4, y + 21, NameCurrentSubItem(choice));
    }
    else
    {
        painter.DrawTextWithLimitationC(x + 4, y + 21 - deltaY, NameCurrentSubItem(choice), colorText, x, y + 19, MI_WIDTH_VALUE, MI_HEIGHT_VALUE - 1);
        painter.DrawHLine(y + (deltaY > 0 ? 31 : 19) - deltaY, x + 3, x + MI_WIDTH_VALUE + 1, COLOR_BLACK);
        painter.DrawTextWithLimitationC(x + 4, y + (deltaY > 0 ? 33 : 9) - deltaY, deltaY > 0 ? NameNextSubItem(choice) : NamePrevSubItem(choice), 
            colorText, x, y + 19, MI_WIDTH_VALUE, MI_HEIGHT_VALUE - 1);
    }
    painter.DrawHLine(y + MI_HEIGHT + 1, x, x + MI_WIDTH, ColorBorderMenu(false));

    if(choice->funcForDraw)
    {
        choice->funcForDraw(x, y);
    }
    DrawGovernorChoiceColorFormulaHiPart(choice, x, y, pressed, shade, false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Choice_Draw(Choice *choice, int x, int y, bool opened)
{
    if(opened)
    {
        Choice_DrawOpened(choice, x, y);
    }
    else
    {
        Choice_DrawClosed(choice, x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Time_DrawClosed(Time *item, int x, int y)
{
    char buffer[20];
    
    bool pressed = IsPressed(item);
    bool shade = IsShade(item);
    DrawGovernorChoiceColorFormulaHiPart(item, x, y, pressed, shade, false);

    painter.DrawVolumeButton(x + 1, y + 17, MI_WIDTH_VALUE + 2, MI_HEIGHT_VALUE + 3, 1, COLOR_MENU_FIELD, ColorMenuItemBrighter(), 
        ColorMenuItemLessBright(), true, shade);

    int deltaField = 10;
    int deltaSeparator = 2;
    int startX = 3;
    y += 21;
    PackedTime time = RTC_GetPackedTime();
    painter.DrawTextC(x + startX, y, Int2String(time.hours, false, 2, buffer), shade ? ColorMenuItem(true) : COLOR_BLACK);
    painter.DrawText(x + startX + deltaField, y, ":");
    painter.DrawText(x + startX + deltaField + deltaSeparator, y, Int2String(time.minutes, false, 2, buffer));
    painter.DrawText(x + startX + 2 * deltaField + deltaSeparator, y, ":");
    painter.DrawText(x + startX + 2 * deltaField + 2 * deltaSeparator, y, Int2String(time.seconds, false, 2, buffer));

    startX = 44;
    painter.DrawText(x + startX, y, Int2String(time.day, false, 2, buffer));
    painter.DrawText(x + startX + deltaField, y, ":");
    painter.DrawText(x + startX + deltaField + deltaSeparator, y, Int2String(time.month, false, 2, buffer));
    painter.DrawText(x + startX + 2 * deltaField + deltaSeparator, y, ":");
    painter.DrawText(x + startX + 2 * deltaField + 2 * deltaSeparator, y, Int2String(time.year, false, 2, buffer));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Time_Draw(Time *time, int x, int y, bool opened)
{
    if(opened)
    {
        Time_DrawOpened(time, x, y);
    }
    else
    {
        Time_DrawClosed(time, x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Button_Draw(Button *button, int x, int y)
{
    bool pressed = IsPressed(button);
    bool shade = IsShade(button) || !ItemIsAcitve(button);

    painter.DrawHLine(y + 1, x, x + MI_WIDTH, ColorMenuTitle(shade));
    Color color = shade ? ColorMenuItem(true) : COLOR_WHITE;
    painter.FillRegion(x + 1, y + 2, MI_WIDTH - 2, MI_HEIGHT - 2, ColorMenuItem(false));
    painter.DrawVolumeButton(x + 3, y + 4, MI_WIDTH - 6, MI_HEIGHT - 6, 2, ColorMenuItem(false), ColorMenuItemBrighter(), 
                            ColorMenuItemLessBright(), pressed, shade);

    int delta = (pressed && (!shade)) ? 2 : 1;
    
    painter.DrawStringInCenterRectC(x + delta, y + delta, MI_WIDTH, MI_HEIGHT, TitleItem(button), color);

    CallFuncOnDrawButton(button, x, y);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SmallButton_Draw(SButton *smallButton, int x, int y)
{
    if (ItemIsAcitve(smallButton))
    {
        if (IsPressed(smallButton))
        {
            painter.FillRegion(x, y, WIDTH_SB, WIDTH_SB, gColorFill);
            painter.SetColor(COLOR_BLACK);
        }
        else
        {
            painter.DrawRectangle(x, y, WIDTH_SB, WIDTH_SB, gColorFill);
        }
        if (smallButton->funcOnDraw)
        {
            smallButton->funcOnDraw(x, y);
        }
    }
    else
    {
        painter.DrawRectangle(x, y, WIDTH_SB, WIDTH_SB, gColorFill);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Page_Draw(Page *page, int x, int y)
{
    bool isShade = IsShade(page) || !ItemIsAcitve(page);
    bool isPressed = IsPressed(page);
    painter.DrawHLine(y + 1, x, x + MI_WIDTH, ColorBorderMenu(false));

    painter.DrawVolumeButton(x + 1, y + 2, MI_WIDTH - 2, MI_HEIGHT - 2, 1, ColorMenuItem(false), ColorMenuItemBrighter(), ColorMenuItemLessBright(), 
        isPressed, isShade);

    Color colorText = isShade ? ColorMenuItem(true) : COLOR_BLACK;
    int delta = 0;
    if(isPressed && (!isShade))
    {
        colorText = COLOR_WHITE;
        delta = 1;
    }
    painter.DrawStringInCenterRectC(x + delta, y + delta, MI_WIDTH, MI_HEIGHT, TitleItem(page), colorText);
}

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "Log.h"
#include "Display/font/Font.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ��� �������� ��������� �������� �� �������.
typedef struct
{
    const char * const name[2];    // �������� ��������� � ��������� ����, ��������� ��� ������ �� �����.
} TBaseStruct;


// ������ �������� �������� ��������� �� �������.
static const TBaseStruct tBases[TBaseSize] =
{
    {"1\x10��",     "1\x10ns"},
    {"2\x10��",     "2\x10ns"},
    {"5\x10��",     "5\x10ns"},
    {"10\x10��",    "10\x10ns"},
    {"20\x10��",    "20\x10ns"},
    {"50\x10��",    "50\x10ns"},
    {"0.1\x10���",  "0.1\x10us"},
    {"0.2\x10���",  "0.2\x10us"},
    {"0.5\x10���",  "0.5\x10us"},
    {"1\x10���",    "1\x10us"},
    {"2\x10���",    "2\x10us"},
    {"5\x10���",    "5\x10us"},
    {"10\x10���",   "10\x10us"},
    {"20\x10���",   "20\x10us"},
    {"50\x10���",   "50\x10us"},
    {"0.1\x10��",   "0.1\x10ms"},
    {"0.2\x10��",   "0.2\x10ms"},
    {"0.5\x10��",   "0.5\x10ms"},
    {"1\x10��",     "1\x10ms"},
    {"2\x10��",     "2\x10ms"},
    {"5\x10��",     "5\x10ms"},
    {"10\x10��",    "10\x10ms"},
    {"20\x10��",    "20\x10ms"},
    {"50\x10��",    "50\x10ms"},
    {"0.1\x10�",    "0.1\x10s"},
    {"0.2\x10�",    "0.2\x10s"},
    {"0.5\x10�",    "0.5\x10s"},
    {"1\x10�",      "1\x10s"},
    {"2\x10�",      "2\x10s"},
    {"5\x10�",      "5\x10s"},
    {"10\x10�",     "10\x10s"}
};

/// ������� �������� �������� � ������������ ��� ����� ������
const char * const symbolsAlphaBet[] =
{
    /* 0x00 */ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", /* 0x19 */
    /* 0x1a */ " ", "_", "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", /* 0x26 */
    /* 0x27 */ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", /* 0x40 */
    //         0x41  0x42  0x43  0x44  0x45  0x46   0x47   - ��� ���������� ����� �������� � ���� �������
    /* 0x41 */ "%y", "%m", "%d", "%H", "%M", "%S", "%N" /* 0x47 */
    //         0x01  0x02  0x03  0x04  0x05  0x06   0x07   - ��� ����� ���������� �������� �������� � set.memory.fileNameMask
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ENumSignalsInSec Tables_ENumSignalsInSecToENUM(int numSignalsInSec)
{
    if(numSignalsInSec == 1)
    {
        return ENumSignalsInSec_1;
    }
    else if(numSignalsInSec == 2)
    {
        return ENumSignalsInSec_2;
    }
    else if(numSignalsInSec == 5)
    {
        return ENumSignalsInSec_5;
    }
    else if(numSignalsInSec == 10)
    {
        return ENumSignalsInSec_10;
    }
    else if(numSignalsInSec == 25)
    {
        return ENumSignalsInSec_25;
    }
    LOG_ERROR_TRACE("����� �������� � ������� ����� %d", numSignalsInSec);
    return ENumSignalsInSec_1;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Tables_ENUMtoENumSignalsInSec(ENumSignalsInSec numSignalsInSec)
{
    static const int fps[] = {25, 10, 5, 2, 1};
    if(numSignalsInSec <= ENumSignalsInSec_1)
    {
        return fps[numSignalsInSec];
    }
    LOG_ERROR_TRACE("������������ �������� %d", (int)numSignalsInSec);
    return 1;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Tables_GetTBaseString(TBase tBase)
{
    return tBases[tBase].name[LANG];
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Tables_GetTBaseStringEN(TBase tBase)
{
    return tBases[tBase].name[English];
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Tables_RangeNameFromValue(Range range)
{
    static const char * const names[RangeSize] =
    {
        "Range_2mV",
        "Range_5mV",
        "Range_10mV",
        "Range_20mV",
        "Range_50mV",
        "Range_100mV",
        "Range_200mV",
        "Range_500mV",
        "Range_1V",
        "Range_2V",
        "Range_5V"
    };
    return names[range];
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
int Tables_GetNumChannel(Channel ch)
{
    return ch == A ? 1 : 2;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawStr(int index, int x, int y)
{
    const char *str = symbolsAlphaBet[index];
    if (index == INDEX_SYMBOL)
    {
        Painter_FillRegionC(x - 1, y, Font_GetLengthText(str), 9, COLOR_FLASH_10);
    }
    Painter_DrawTextC(x, y, symbolsAlphaBet[index], index == INDEX_SYMBOL ? COLOR_FLASH_01 : gColorFill);
}

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Settings/Settings.h"
#include "Log.h"
#include "Tables.h"
#include "Utils/GlobalFunctions.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ��� �������� ��������� �������� �� �������.
typedef struct
{
    const char* name[2];    // �������� ��������� � ��������� ����, ��������� ��� ������ �� �����.
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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* Tables_GetTBaseString(TBase tBase)
{
    return tBases[tBase].name[LANG];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* Tables_GetTBaseStringEN(TBase tBase)
{
    return tBases[tBase].name[English];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* Tables_RangeNameFromValue(Range range)
{
    static const char* names[RangeSize] =
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
int Tables_GetNumChannel(Channel ch)
{
    return ch == A ? 1 : 2;
}

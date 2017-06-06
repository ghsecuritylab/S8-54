#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    ExcessValues        // ���������� �������� ���������� �������� � "����������", "����������", "��� ����"
} WarningWithNumber;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ENumSignalsInSec Tables_ENumSignalsInSecToENUM(int numSignalsInSec);
int             Tables_ENUMtoENumSignalsInSec(ENumSignalsInSec numSignalsInSec);
const char*     Tables_GetTBaseString(TBase tBase);
const char*     Tables_GetTBaseStringEN(TBase tBase);
const char*     Tables_RangeNameFromValue(Range range);
int             Tables_GetNumChannel(Channel ch);     // ���������� ����� ������ �� 1 �� 2

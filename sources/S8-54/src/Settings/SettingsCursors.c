#include "Settings.h"
#include "Display/Grid.h"
#include "SettingsCursors.h"
#include "Utils/Math.h"
#include "Utils/GlobalFunctions.h"
#include "Menu/MenuFunctions.h"
#include "FPGA/FPGAtypes.h"
#include <math.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float sCursors_GetCursPosU(Channel ch, int numCur)
{
    return CURsU_POS(ch, numCur) / (grid.ChannelBottom() == grid.FullBottom() ? 1.0f : 2.0f);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
bool sCursors_NecessaryDrawCursors(void)
{
    return (CURsU_ENABLED || CURsT_ENABLED) && (CURS_SHOW || GetNameOpenedPage() == PageSB_Cursors_Set);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *sCursors_GetCursVoltage(Channel source, int numCur, char buffer[20])
{
    float voltage = math.VoltageCursor(sCursors_GetCursPosU(source, numCur), SET_RANGE(source), SET_RSHIFT(source));
    if (SET_DIVIDER_10(source))
    {
        voltage *= 10.0f;
    }
    return trans.Voltage2String(voltage, true, buffer);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *sCursors_GetCursorTime(Channel source, int numCur, char buffer[20])
{
//    float pos = 0.0;

    /// \todo ���� �-�� ���� � ����������. ��������� �������.
    //memcpy(&pos, &CURsT_POS(source, numCur), sizeof(float));

    float time = math.TimeCursor(CURsT_POS(source, numCur), SET_TBASE);
        
    return trans.Time2String(time, true, buffer);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *sCursors_GetCursorPercentsU(Channel source, char buffer[20])
{
    buffer[0] = 0;
    /** \todo ��� ����� ����. ��� ������� �������� HardFault. ��������, ��-�� ����������� ������������ Settings.
        ���� �������� */

    // float dPerc = dUperc(source);     
    float dPerc = 100.0f;
    memcpy(&dPerc, &dUperc(source), sizeof(float));

    float dValue = fabsf(sCursors_GetCursPosU(source, 0) - sCursors_GetCursPosU(source, 1));
    char bufferOut[20];
    char *percents = trans.Float2String(dValue / dPerc * 100.0f, false, 5, bufferOut);
    strcat(buffer, percents);
    strcat(buffer, "%");
    return buffer;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *sCursors_GetCursorPercentsT(Channel source, char buffer[20])
{
    buffer[0] = 0;
    
    float dPerc = 100.0f;
    memcpy(&dPerc, &dTperc(source), sizeof(float));
    
    float dValue = fabsf(CURsT_POS(source, 0) - CURsT_POS(source, 1));
    char bufferOut[20];
    char *percents = trans.Float2String(dValue / dPerc * 100.0f, false, 6, bufferOut);
    strcat(buffer, percents);
    strcat(buffer, "%");
    return buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
float GetCursPosT(Channel ch, int num)
{
    float retValue = 0.0f;
    memcpy(&retValue, &set.curs_PosCurT[ch][num], sizeof(float));
    return retValue;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void SetCursPosT_temp(Channel ch, int num, float value)
{
    memcpy(&set.curs_PosCurT[ch][num], &value, sizeof(float));
}

#include "Globals.h"
#include "PainterDataNew.h"
#include "Display/Grid.h"
#include "FPGA/Data.h"
#include "FPGA/DataBuffer.h"
#include "FPGA/DataStorage.h"
#include "FPGA/FPGA.h"
#include "Settings/Settings.h"
#include "Utils/Math.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���������� ������, ������� ���������� ��, ���� � ��� ���������� ����� ModeWork_Dir.
static void DrawData_ModeDir(void);
/// ���������� ������, ������� ���������� ��, ���� � ��� ���������� ����� ModeWork_RAM.
static void DrawData_ModeRAM(void);
/// ���������� ������, ������� ���������� ��, ���� � ��� ���������� ����� ModeWork_ROM.
static void DrawData_ModeROM(void);
/// ���������� ������ �� outA, outB.
static void DrawData_OutAB(void);
/// ���������� ������ �� outA ��� outB.
static void DrawData_Out(Channel ch, uint8 *data);
/// ���������� ������ �� outA ��� outB c ����������� ������� ����������.
static void DrawData_Out_Normal(Channel ch, uint8 data[281], int left, int bottom, float scaleY);
/// ���������� ������ �� outA ��� outB � ���������� ������� ����������.
static void DrawData_Out_PeakDet(Channel ch, uint8 data[281 * 2], int left, int bottom, float scaleY);
/// \brief ������������ � ������ �������� ���������. � in �������� ��� ��������, ��������������� ������������� � ������������. 
/// ��� ������������ � out � ������������ ������� out[0] = min, out[1] = max. ���������� false, ���� ����� �� ������� - ���� �� ���� �������� == 0.
static bool CalcMinMax(uint8 in[2], uint8 out[2]);


/// ������� ����, ��� �� �������� ������ ����� �������� ������� ������ ����������� ������
#define NEED_DRAW_DYNAMIC_P2P (IN_P2P_MODE && FPGA_IsRunning())

/// ������� ����, ��� �� ��������� � ������ ������ ���������� � �� �������� ������ ������ ���� ��������� �����������
#define STAND_P2P (START_MODE_WAIT && IN_P2P_MODE && DS_NumElementsWithCurrentSettings() > 1)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PainterDataNew_DrawData(void)
{
    // ���������� �����
    if (MODE_WORK_DIR)                              // ������������� ����� - ����������������
    {
        if (ALWAYS_SHOW_ROM_SIGNAL)                 // ���� ����� ���������� ������ �� ����
        {
            DrawData_ModeROM();
        }
        DrawData_ModeDir();                         // ������ ������ ����������� ������
    }
    // ������ - ���������
    else if (MODE_WORK_RAM)
    {
        DrawData_ModeRAM();                         
    }
    // ������ - ����� ��
    else
    {
        if (SHOW_IN_INT_BOTH || SHOW_IN_INT_SAVED)
        {
            DrawData_ModeROM();
        }
        if (SHOW_IN_INT_BOTH || SHOW_IN_INT_DIRECT) // ���� ����� ���������� �� ������ ���������� ������
        {
            if (EXIT_FROM_ROM_TO_RAM)               // � �� ������� �� �������� "������-����� ��" �� �������� "������-���������"
            {
                DrawData_ModeRAM();
            }
            else                                    // � ���� ������� �� ����������� �����
            {
                DrawData_ModeDir();                 // �� �������� ������ ����������� ������
            }
        }
    }
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_ModeDir(void)
{
    if (START_MODE_WAIT && IN_P2P_MODE && DS_NumElementsWithCurrentSettings() > 1)
    {
        Data_ReadDataRAM(1);
    }
    else
    {
        Data_ReadDataRAM(0);
    }
    DrawData_OutAB();


}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_ModeRAM(void)
{
    Data_ReadDataRAM(NUM_RAM_SIGNAL);
    DrawData_OutAB();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_ModeROM(void)
{
    Data_ReadDataROM();
    DrawData_OutAB();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_OutAB(void)
{
    if (DS)
    {
        if (LAST_AFFECTED_CH_IS_A)
        {
            DrawData_Out(B, outB);
            DrawData_Out(A, outA);
        }
        else
        {
            DrawData_Out(A, outA);
            DrawData_Out(B, outB);
        }
    }

    Painter_DrawRectangleC(GridLeft(), GRID_TOP, GridWidth(), GridFullHeight(), gColorFill);                                                                                                                         
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_Out(Channel ch, uint8 *data)
{
    if (!G_ENABLED(ch))
    {
        return;
    }

    Painter_SetColor(gColorChan[ch]);

    int pointFirst = 0;
    int pointLast = 0;
    sDisplay_PointsOnDisplay(&pointFirst, &pointLast);

    int left = GridLeft();
    int bottom = GridChannelBottom();
    int top = GRID_TOP;

    float scaleY = (bottom - top) / (float)(MAX_VALUE - MIN_VALUE);

    /// \todo ���������� �� ������ �������.
    if(G_PEACKDET)
    {
        DrawData_Out_PeakDet(ch, data + pointFirst * 2, left, bottom, scaleY);  
    }
    else
    {
        uint8 *pData = data;
        int pointer = 0;

        if (!STAND_P2P)
        {
            if (NEED_DRAW_DYNAMIC_P2P)
            {
                uint8 d[281] = {0};

                for (int i = 0; i < G_BYTES_IN_CHANNEL; i++)
                {
                    if (data[i])
                    {
                        d[pointer] = data[i];
                        pointer = (pointer + 1) % 281;
                    }
                }

                pData = d;
                pointFirst = 0;
            }
        }

        DrawData_Out_Normal(ch, pData + pointFirst, left, bottom, scaleY);

        if (!STAND_P2P)
        {
            if (NEED_DRAW_DYNAMIC_P2P)
            {
                DataSettings *ds = 0;
                uint8 *dA = 0;
                uint8 *dB = 0;
                if (DS_GetLastFrameP2P_RAM(&ds, &dA, &dB) < SET_POINTS_IN_CHANNEL)
                {
                    Painter_DrawVLineC(left + pointer - 1, bottom, GRID_TOP, gColorGrid);
                }
            }
        }
    }

    Painter_RunDisplay();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_Out_Normal(Channel ch, uint8 data[281], int left, int bottom, float scaleY)
{
    float k = bottom + MIN_VALUE * scaleY;

    for(int i = 0; i < 280; ++i)                        /// \todo �������� ����� �� ��������.
    {
        uint8 val = data[i];

        if(val == 0)
        {
            continue;                                   // ���� ��� �������� ����������� - ��������� � ��������� �����
        }

        LIMITATION(val, val, MIN_VALUE, MAX_VALUE);

        int y = k - val * scaleY;                       //int y = bottom - (val - MIN_VALUE) * scaleY;

        int x = left + i;

        if(MODE_DRAW_SIGNAL_POINTS)
        {
            Painter_SetPoint(x, y);
        }
        else
        {
            int yNext = k - data[i + 1] * scaleY;       //int yNext = bottom - (data[i + 1] - MIN_VALUE) * scaleY;

            if(yNext < y)
            {
                Painter_DrawVLine(x, y, yNext + 1);
            }
            else if(yNext > y)
            {
                Painter_DrawVLine(x, y, yNext - 1);
            }
            else
            {
                Painter_SetPoint(x, y);
            }

        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_Out_PeakDet(Channel ch, uint8 data[281 * 2], int left, int bottom, float scaleY)
{
    float k = bottom + MIN_VALUE * scaleY;

    for(int i = 0; i < 280; i++)
    {

#define Y_MIN in[0]
#define Y_MAX in[1]
#define Y_MIN_NEXT inNext[0]
#define Y_MAX_NEXT inNext[1]

        uint8 in[2];            // ����� ����� ��������� ��������������� �� ����������� ��������
        if(!CalcMinMax(data + i * 2, in))
        {
            continue;
        }
        
        uint8 inNext[2];
        if(!CalcMinMax(data + (i + 1) * 2, inNext))
        {
            Y_MIN_NEXT = Y_MIN;
            Y_MAX_NEXT = Y_MAX;
        }

        int min = k - Y_MAX * scaleY;
        int max = k - Y_MIN * scaleY;
        int minNext = k - Y_MAX_NEXT * scaleY;
        int maxNext = k - Y_MIN_NEXT * scaleY;

        int x = left + i;

        if(maxNext < min)
        {
            min = maxNext + 1;
        }
        if(minNext > max)
        {
            max = minNext - 1;
        }

        if(MODE_DRAW_SIGNAL_POINTS)
        {
            Painter_SetPoint(x, min);
            Painter_SetPoint(x, max);
        }
        else
        {
            if(min == max)
            {
                Painter_SetPoint(x, min);
            }
            else
            {
                Painter_DrawVLine(x, min, max);
            }
        }
    }

#undef Y_MIN
#undef Y_MAX
#undef Y_MIN_NEXT
#undef Y_MAX_NEXT
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool CalcMinMax(uint8 in[2], uint8 out[2])
{
    uint8 val1 = in[0];
    uint8 val2 = in[1];
    if(val1 == 0 || val2 == 0)
    {
        return false;
    }

    LIMITATION(val1, val1, MIN_VALUE, MAX_VALUE);
    LIMITATION(val2, val2, MIN_VALUE, MAX_VALUE);

    if(val1 < val2)
    {
        out[0] = val1;
        out[1] = val2;
    }
    else
    {
        out[0] = val2;
        out[1] = val1;
    }

    return true;
}

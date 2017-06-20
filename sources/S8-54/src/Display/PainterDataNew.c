#include "Globals.h"
#include "PainterDataNew.h"
#include "Display/Grid.h"
#include "FPGA/Data.h"
#include "FPGA/DataBuffer.h"
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PainterDataNew_DrawData(void)
{
    if (MODE_WORK_DIR)                              // ������������� ����� - ����������������
    {
        if (ALWAYS_SHOW_ROM_SIGNAL)                 // ���� ����� ���������� ������ �� ����
        {
            DrawData_ModeROM();
        }
        DrawData_ModeDir();                         // ������ ������ ����������� ������
    }
    else if (MODE_WORK_RAM)                         // ������������� ����� ��������� - ������ - ���������
    {
        DrawData_ModeRAM();                         
    }
    else                                            // ������������� ����� ��������� - ������ - ����� ��
    {
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
        if (SHOW_IN_INT_BOTH || SHOW_IN_INT_SAVED)
        {
            DrawData_ModeROM();
        }
    }
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_ModeDir(void)
{
    Data_ReadDataRAM(0);
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
        DrawData_Out_Normal(ch, data + pointFirst, left, bottom, scaleY);
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

    for(int i = 0; i < 281; i++)
    {
        uint8 min = data[i * 2];
        uint8 max = data[i * 2 + 1];

        if(min == 0 || max == 0)
        {
            continue;
        }

        LIMITATION(min, min, MIN_VALUE, MAX_VALUE);
        LIMITATION(max, max, MIN_VALUE, MAX_VALUE);

        int yMin = k - min  * scaleY;
        int yMax = k - max  * scaleY;

        int x = left + i;

        if(MODE_DRAW_SIGNAL_POINTS)
        {
            Painter_SetPoint(x, yMin);
            Painter_SetPoint(x, yMax);
        }
        else
        {
            Painter_DrawVLine(x, yMin, yMax);
        }
    }
}

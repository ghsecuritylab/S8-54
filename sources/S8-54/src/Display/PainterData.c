#include "Globals.h"
#include "PainterData.h"
#include "Symbols.h"
#include "Display/Grid.h"
#include "FPGA/Data.h"
#include "FPGA/DataBuffer.h"
#include "FPGA/DataStorage.h"
#include "FPGA/FPGA.h"
#include "Hardware/RAM.h"
#include "Settings/Settings.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/Math.h"
#include "Utils/ProcessingSignal.h"


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
/// ���������� true, ���� ����������� ������� ������� �� ������� ������.
static bool DataBeyondTheBorders(const uint8 *data, int firstPoint, int lastPoint);
/// \brief �������� ��������� �� ������ � ������ ������� �� ������� ������.
/// delta - ���������� �� ���� �����, �� ������� ��������� ���������. ���� delta < 0 - ��������� ����� �����
static void DrawLimitLabel(int delta);

static void DrawDataChannel(Channel ch, uint8 *dataIn);

static int FillDataP2P(uint8 *data, DataSettings **ds);

static void DrawMarkersForMeasure(float scale);

static void DrawSignalLined(const uint8 *data, int startPoint, int endPoint, int minY, int maxY, float scaleY, float scaleX, bool calculateFiltr);

static void DrawSignalPointed(const uint8 *data, int startPoint, int endPoint, int minY, int maxY, float scaleY, float scaleX);

static int FillDataP2PforRecorder(int numPoints, int numPointsDS, int pointsInScreen, uint8 *src, uint8 *dest);

static int FillDataP2PforNormal(int numPoints, int numPointsDS, int pointsInScreen, uint8 *src, uint8 *dest);

static void DrawDataInRect(int x, uint width, const uint8 *data, int numElems, bool peackDet);

static void DrawTPos(int leftX, int rightX);

static void DrawTShift(int leftX, int rightX, int numPoints);

static int Ordinate(uint8 x, float scale);
/// ���������� ����� � �������� ����������. ���� ����� �� ������� (NONE_VALUE), ���������� -1.
static void SendToDisplayDataInRect(int x, const int *min, const int *max, uint width);
/// ���������� ������ � ���� ������
void DrawMemoryWindow(void);


/// ������� ����, ��� �� �������� ������ ����� �������� ������� ������ ����������� ������
#define NEED_DRAW_DYNAMIC_P2P (IN_P2P_MODE && FPGA_IsRunning())

/// ������� ����, ��� �� ��������� � ������ ������ ���������� � �� �������� ������ ������ ���� ��������� �����������
#define STAND_P2P (START_MODE_WAIT && IN_P2P_MODE && DS_NumElementsWithCurrentSettings() > 1)

#define CONVERT_DATA_TO_DISPLAY(out, inVal)                     \
    int in = inVal;                                             \
    if(in < MIN_VALUE) { in = MIN_VALUE; }                      \
    if(in > MAX_VALUE) { in = MAX_VALUE; }                      \
    out = (uint8)(maxY - (int)(((in) - MIN_VALUE) * scaleY));   \
    if(out < (uint8)minY)   { out = (uint8)minY; }              \
    if(out > (uint8)maxY)   { out = (uint8)maxY; };

/// ��������� ��� �������� �� ����������� : val1 - �������, val2 - �������
#define PLACE_2_ASCENDING(v1, v2) if((v1) > (v2)) { int qwerty = v1; v1 = v2; v2 = qwerty; }


static bool interruptDrawing = false;
static Channel curCh = A;           ///< ������� �������� �����.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PainterDataNew_InterruptDrawing(void)
{
    interruptDrawing = true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterDataNew_DrawData(void)
{
    interruptDrawing = false;

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
        DrawMemoryWindow();
    }
    // ������ - ����� ��
    else
    {
        if (SHOW_IN_INT_BOTH || SHOW_IN_INT_SAVED)
        {
            DrawData_ModeROM();
            DrawMemoryWindow();
        }
        if (SHOW_IN_INT_BOTH || SHOW_IN_INT_DIRECT) // ���� ����� ���������� �� ������ ����������� ������
        {
            if (EXIT_FROM_ROM_TO_RAM)               // � �� ������� �� �������� "������-����� ��" �� �������� "������-���������"
            {
                DrawData_ModeRAM();
                DrawMemoryWindow();
            }
            else                                    // � ���� ������� �� ����������� �����
            {
                DrawData_ModeDir();                 // �� �������� ������ ����������� ������
                DrawMemoryWindow();
            }
        }
    }
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawData_ModeDir(void)
{
    NUM_DRAWING_SIGNALS++;

    if (STAND_P2P)
    {
        Data_ReadDataRAM(1);
    }
    else
    {
        Data_ReadDataRAM(0);
    }
    DrawData_OutAB();
    DrawMemoryWindow();

    if (MODE_ACCUM_NO_RESET && !IN_P2P_MODE)
    {
        int numAccum = NUM_ACCUM;
        int numSignalsInStorage = DS_NumElementsWithCurrentSettings();
        if (numSignalsInStorage < numAccum)
        {
            numAccum = numSignalsInStorage;
        }

        if (ENUM_ACCUM_INF)                     // ���� ����������� ����������
        {
            numAccum = numSignalsInStorage;     // �� ����� �������� ��� �������
        }

        int i = 0;
        while (i < numAccum && !interruptDrawing)
        {
            Data_ReadDataRAM(i);
            DrawData_OutAB();
            ++i;
        }
    }
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
    if (!SET_ENABLED(ch) || !G_ENABLED(ch))
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

    float scaleY = (bottom - top) / (float)(MAX_VALUE - MIN_VALUE + 1);

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

        if (!DataBeyondTheBorders(pData, pointFirst, pointLast))
        {
            DrawData_Out_Normal(ch, pData + pointFirst, left, bottom, scaleY);
        }

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

//----------------------------------------------------------------------------------------------------------------------------------------------------
static bool DataBeyondTheBorders(const uint8 *data, int firstPoint, int lastPoint)
{
    if (IN_P2P_MODE)
    {
        return false;   /// \todo ��������, ������ ��� � ���� ������� ����� ������ ��� ������������ �� ���������� �����
    }
    int numMin = 0; // ����� ���������� ��������, ������� ��� ������ MIN_VALUE
    int numMax = 0; // ����� ���������� ��������, ������� ��� ������ MAX_VALUE
    int numPoints = lastPoint - firstPoint;
    for (int i = firstPoint; i < lastPoint; i++)
    {
        if (data[i] <= MIN_VALUE) //-V108
        {
            numMin++;
        }
        if (data[i] >= MAX_VALUE) //-V108
        {
            numMax++;
        }
    }
    if (numMin >= numPoints - 1)
    {
        DrawLimitLabel(-10);
        return true;
    }
    else if (numMax >= numPoints - 1)
    {
        DrawLimitLabel(10);
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawLimitLabel(int delta)
{
    int width = 150;
    int height = 20;

    Color color = Painter_GetColor();

    int x = GridWidth() / 2 - width / 2 + GridLeft();
    int y = 0;
    if (delta < 0)
    {
        y = GridFullBottom() + delta - height;
    }
    else
    {
        y = GRID_TOP + delta;
    }

    Painter_FillRegionC(x, y, width, height, gColorBack);
    Painter_DrawRectangleC(x, y, width, height, color);
    Painter_DrawStringInCenterRect(x, y, width, height, "������ �� ��������� ������");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData_DrawMath(void)
{
    if (!FUNC_ENABLED || DS_GetData_RAM(A, 0) == 0 || DS_GetData_RAM(B, 0) == 0)
    {
        return;
    }

    uint8 *dataRel0 = outA;
    uint8 *dataRel1 = outB;

    float *dataAbsA = (float*)RAM(DRAW_MATH_DATA_REL_A);
    float *dataAbsB = (float*)RAM(DRAW_MATH_DATA_REL_B);

    int numPoints = BYTES_IN_CHANNEL(DS);

    Math_PointsRelToVoltage(dataRel0, numPoints, G_RANGE_A, G_RSHIFT_A, dataAbsA);
    Math_PointsRelToVoltage(dataRel1, numPoints, G_RANGE_B, G_RSHIFT_B, dataAbsB);

    Math_CalculateMathFunction(dataAbsA, dataAbsB, numPoints);

    uint8 points[FPGA_MAX_POINTS];

    Math_PointsVoltageToRel(dataAbsA, numPoints, SET_RANGE_MATH, SET_RSHIFT_MATH, points);

    DrawDataChannel(Math, points);

    static const int WIDTH = 71;
    static const int HEIGHT = 10;
    int delta = (SHOW_STRING_NAVI_ALL && FUNC_MODE_DRAW_TOGETHER) ? 10 : 0;
    Painter_DrawRectangleC(GridLeft(), GridMathTop() + delta, WIDTH, HEIGHT, gColorFill);
    Painter_FillRegionC(GridLeft() + 1, GridMathTop() + 1 + delta, WIDTH - 2, HEIGHT - 2, gColorBack);
    Divider divider = set.math_Divider;
    Painter_DrawTextC(GridLeft() + 2, GridMathTop() + 1 + delta, sChannel_Range2String(SET_RANGE_MATH, divider), gColorFill);
    Painter_DrawText(GridLeft() + 25, GridMathTop() + 1 + delta, ":");
    char buffer[20];
    Painter_DrawText(GridLeft() + 27, GridMathTop() + 1 + delta, sChannel_RShift2String(SET_RSHIFT_MATH, SET_RANGE_MATH, divider, buffer));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDataChannel(Channel ch, uint8 *dataIn)
{
    curCh = ch;

    int minY = curCh == Math ? GridMathTop() : GRID_TOP;
    int maxY = curCh == Math ? GridMathBottom() : GridChannelBottom();

    bool calculateFiltr = true;
    int sizeBuffer = BYTES_IN_CHANNEL(DS);
    uint8 data[sizeBuffer];

    int firstPoint = 0;
    int lastPoint = 280;

    if (!IN_P2P_MODE ||                                     // ���� �� ��������� � ������ ��������� ���������� ��������
        (IN_P2P_MODE && TIME_MS(DS)))                       // ��� � ����������, �� ������ ��� �������
    {
        sDisplay_PointsOnDisplay(&firstPoint, &lastPoint);  // �� ������� ������ � ��������� �����, ��������� �� �����
    }

    if (IN_P2P_MODE &&                                      // ���� ��������� � ������ ��������� ���������� ��������
        TIME_MS(DS) == 0)                                   // � ���������� ������� ������ ������ ��� �� ���������
    {
        lastPoint = FillDataP2P(data, &DS);
        if (lastPoint < 2)                                  // ���� ������ ������ ���� ����� - �����
        {
            return;
        }
        dataIn = data;
    }

    if (!sChannel_NeedForDraw(dataIn, curCh, DS))
    {
        return;
    }
    float scaleY = (float)(maxY - minY) / (MAX_VALUE - MIN_VALUE);
    float scaleX = (float)GridWidth() / 280.0f;

    if (SHOW_MEASURES)
    {
        DrawMarkersForMeasure(scaleY);
    }

    Painter_SetColor(gColorChan[curCh]);

    //    if (!DataBeyondTheBorders(dataIn, firstPoint, lastPoint))   // ���� ������ �� ������� �� ������� ������
    {
        if (MODE_DRAW_SIGNAL_LINES)
        {
            DrawSignalLined(dataIn, firstPoint, lastPoint, minY, maxY, scaleY, scaleX, calculateFiltr);
        }
        else
        {
            DrawSignalPointed(dataIn, firstPoint, lastPoint, minY, maxY, scaleY, scaleX);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static int FillDataP2P(uint8 *data, DataSettings **ds)
{
    int pointsInScreen = 281;
    if (SET_PEACKDET_EN)
    {
        pointsInScreen *= 2;
    }

    uint8 *dataA = 0;
    uint8 *dataB = 0;

    int numPoints = DS_GetLastFrameP2P_RAM(ds, &dataA, &dataB); // �������� ����� ����������� ������

    int numPointsDS = BYTES_IN_CHANNEL(*ds);

    uint8 *dat[] = {dataA, dataB};

    return RECORDER_MODE ?
        FillDataP2PforRecorder(numPoints, numPointsDS, pointsInScreen, dat[curCh], data) :   // ��� ����������, ���� ������� ����� ������������
        FillDataP2PforNormal(numPoints, numPointsDS, pointsInScreen, dat[curCh], data);      // � ��� � ���������� ������
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static int FillDataP2PforRecorder(int numPoints, int numPointsDS, int pointsInScreen, uint8 *src, uint8 *dest)
{
    // ���� ����� ������, ��� ��������� �� ����� - ������ �������� �� � �����
    if (numPoints <= pointsInScreen)
    {
        RAM_MemCpy16(src, dest, numPoints);
        return numPoints;
    }

    // ���� ����� ������, �� � ����� �������� ��������� 281
    int allPoints = numPoints <= numPointsDS ? numPoints : numPointsDS;
    int startIndex = allPoints - pointsInScreen;
    RAM_MemCpy16(src + startIndex, dest, pointsInScreen);
    return pointsInScreen;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static int FillDataP2PforNormal(int numPoints, int numPointsDS, int pointsInScreen, uint8 *src, uint8 *dest)
{
    int deltaNumPoints = numPoints - numPointsDS;
    if (deltaNumPoints < 0)
    {
        deltaNumPoints = 0;
    }

    if (numPoints > 0)
    {
        RAM_MemCpy16(src, dest, numPoints < numPointsDS ? numPoints : numPointsDS);
    }

    //    int kP2P = SET_PEACKDET_EN ? 2 : 1;

    if (numPoints > pointsInScreen)
    {
        int numScreens = numPoints / pointsInScreen;                                                        // ����� ������ ������������ �������.
        uint8 dataTemp[pointsInScreen];

        memcpy(dataTemp, dest + (numScreens - 1) * pointsInScreen - deltaNumPoints, pointsInScreen);        // ������ ��������� ��������� ������ ����� � �����

        memcpy(dataTemp, dest + numScreens * pointsInScreen - deltaNumPoints, numPoints % pointsInScreen);  // ������ ��������� ������� � ������ ������

                                                                                                            //        xP2P = GridLeft() + ((numPoints  % pointsInScreen) / kP2P) - 1;

        memcpy(dest, dataTemp, pointsInScreen);                                                             // ������ ��������� ��������� ����� � ��������
    }
    else
    {
        //        xP2P = GridLeft() + numPoints / kP2P - 1;
    }

    return numPoints > pointsInScreen ? pointsInScreen : numPoints;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawMarkersForMeasure(float scale)
{
    if (curCh == Math)
    {
        return;
    }
    Painter_SetColor(ColorCursors(curCh));
    for (int numMarker = 0; numMarker < 2; numMarker++)
    {
        int pos = Processing_GetMarkerHorizontal(curCh, numMarker);
        if (pos != ERROR_VALUE_INT && pos > 0 && pos < 200)
        {
            Painter_DrawDashedHLine(GridFullBottom() - (int)(pos * scale), GridLeft(), GridRight(), 3, 2, 0);
        }

        pos = Processing_GetMarkerVertical(curCh, numMarker);
        if (pos != ERROR_VALUE_INT && pos > 0 && pos < GridRight())
        {
            Painter_DrawDashedVLine(GridLeft() + (int)(pos * scale), GRID_TOP, GridFullBottom(), 3, 2, 0);
        }

    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawSignalLined(const uint8 *data, int startPoint, int endPoint, int minY, int maxY, float scaleY, float scaleX, bool calculateFiltr)
{
    uint8 dataCD[281];

    if (endPoint < startPoint)
    {
        return;
    }

    int gridLeft = GridLeft();
    if (G_PEACKDET == PeackDet_Disable)
    {
        int gridRight = GridRight();
        int numSmoothing = sDisplay_NumPointSmoothing();
        int numPoints = BYTES_IN_CHANNEL(DS);
        for (int i = startPoint; i < endPoint; i++)
        {

            float x0 = gridLeft + (i - startPoint) * scaleX;
            if (x0 >= gridLeft && x0 <= gridRight)
            {
                int index = i - startPoint;
                int y = calculateFiltr ? Math_CalculateFiltr(data, i, numPoints, numSmoothing) : data[i]; //-V108
                int newY = 0;
                CONVERT_DATA_TO_DISPLAY(newY, y);
                dataCD[index] = (uint8)newY;
            }
        }
    }
    else
    {
        for (int i = 1; i < 280 * 2; i += 2)
        {
            float x = gridLeft + i / 2.0f * scaleX;

            int index = startPoint * 2 + i;

            int y0 = 0, y1 = 0;
            {
                CONVERT_DATA_TO_DISPLAY(y0, data[index++]);
            }
            {
                CONVERT_DATA_TO_DISPLAY(y1, data[index++]);
            }

            PLACE_2_ASCENDING(y0, y1);

            Painter_DrawVLine((int)x, y0, y1);

            int z0 = 0;
            int z1 = 0;
            {
                CONVERT_DATA_TO_DISPLAY(z0, data[index++]);
            }
            {
                CONVERT_DATA_TO_DISPLAY(z1, data[index]);
            }

            PLACE_2_ASCENDING(z0, z1);

            if (y1 < z0)
            {
                Painter_DrawVLine((int)x, y1, z0);
            }
            else if (y0 > z1)
            {
                Painter_DrawVLine((int)(x + 1), z1, y0);
            }
        }
    }
    if (endPoint - startPoint < 281)
    {
        int numPoints = 281 - (endPoint - startPoint);
        for (int i = 0; i < numPoints + 1; i++)
        {
            int index = endPoint - startPoint + i;
            CONVERT_DATA_TO_DISPLAY(dataCD[index], 0);
        }
    }
    if (G_PEACKDET == PeackDet_Disable)
    {
        CONVERT_DATA_TO_DISPLAY(dataCD[280], data[endPoint]); //-V108
        Painter_DrawSignal(GridLeft(), dataCD, true);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawSignalPointed(const uint8 *data, int startPoint, int endPoint, int minY, int maxY, float scaleY, float scaleX)
{
    int numPoints = BYTES_IN_CHANNEL(DS);
    int numSmoothing = sDisplay_NumPointSmoothing();

    if (scaleX == 1.0f) //-V550
    {
        uint8 dataCD[281];
        for (int i = startPoint; i < endPoint; i++)
        {
            int index = i - startPoint;
            CONVERT_DATA_TO_DISPLAY(dataCD[index], Math_CalculateFiltr(data, i, numPoints, numSmoothing));
        }
        Painter_DrawSignal(GridLeft(), dataCD, false);
    }
    else
    {
        for (int i = startPoint; i < endPoint; i++)
        {
            int index = i - startPoint;
            int dat = 0;
            CONVERT_DATA_TO_DISPLAY(dat, Math_CalculateFiltr(data, i, numPoints, numSmoothing));
            Painter_SetPoint(GridLeft() + (int)(index * scaleX), dat);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawMemoryWindow(void)
{
    Data_ReadDataRAM(0);

    int leftX = 3;
    int top = 0;
    int height = GRID_TOP - 3;
    int bottom = top + height;
    int16 shiftInMemory = (int16)sDisplay_ShiftInMemoryInPoints();
    static const int rightXses[3] = {276, 285, 247};
    int rightX = rightXses[MODE_WORK];
    if (sCursors_NecessaryDrawCursors())
    {
        rightX = 68;
    }
    float scaleX = (float)(rightX - leftX + 1) / SET_POINTS_IN_CHANNEL;
    const int xVert0 = leftX + (int)(shiftInMemory * scaleX);
    int width = (int)((rightX - leftX) * (282.0f / SET_POINTS_IN_CHANNEL));

    if ((SET_ENABLED_A && G_ENABLED_A) || (SET_ENABLED_B && G_ENABLED_B))                // �� ������ ������ ����������, ��� ������ ����. � �� � ���������� ������ �������� ����� ��� ������������ � �������
    {                           // ����� ������ ����������.
        bool needReleaseHeap = false;

        uint8 *datA = outA;
        uint8 *datB = outB;
        uint8 *dA = 0;  // ���� ������� ������ ������� �� RAM
        uint8 *dB = 0;

        if (MODE_WORK_DIR || MODE_WORK_RAM)
        {
            needReleaseHeap = true;

            datA = outA;
            datB = outB;

            if (TBASE(DS_DataSettingsFromEnd(0)) >= MIN_TBASE_P2P)          // ���� ��������� � ������ ����������� ������
            {
                DS_GetLastFrameP2P_RAM(&DS, &datA, &datB);
            }

            // ����� ���������� �� �������� ��� � ����, ������ ��
            dA = AllocMemForChannelFromHeap(A, DS);
            dB = AllocMemForChannelFromHeap(B, DS);

            int numBytes = BYTES_IN_CHANNEL(DS);

            RAM_MemCpy16(datA, dA, numBytes);
            RAM_MemCpy16(datB, dB, numBytes);

            datA = dA;
            datB = dB;
        }

        Channel lastAffectedChannel = LAST_AFFECTED_CH;
        //if (((uint)NumPoints_2_ENumPoints(BYTES_IN_CHANNEL(DS)) == G_ENUM_BYTES) && DS)
        if (DS)
        {
            Channel chanFirst = lastAffectedChannel == A ? B : A;
            Channel chanSecond = lastAffectedChannel == A ? A : B;
            const uint8 *dataFirst = lastAffectedChannel == A ? datB : datA;
            const uint8 *dataSecond = lastAffectedChannel == A ? datA : datB;

            bool peackDet = G_PEACKDET != PeackDet_Disable;

            if (sChannel_NeedForDraw(dataFirst, chanFirst, DS))
            {
                curCh = chanFirst;
                DrawDataInRect(1, rightX + 3, dataFirst, BYTES_IN_CHANNEL(DS), peackDet);
            }
            if (sChannel_NeedForDraw(dataSecond, chanSecond, DS))
            {
                curCh = chanSecond;
                DrawDataInRect(1, rightX + 3, dataSecond, BYTES_IN_CHANNEL(DS), peackDet);
            }
        }
        if (needReleaseHeap)
        {
            free(dA);
            free(dB);
        }
    }

    Painter_DrawRectangleC(xVert0, top, width - (FPGA_POINTS_8k ? 1 : 0), bottom - top + 1, gColorFill); //-V2007

    DrawTPos(leftX, rightX);

    DrawTShift(leftX, rightX, BYTES_IN_CHANNEL(DS));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDataInRect(int x, uint width, const uint8 *data, int numBytes, bool peackDet)
{
    if (numBytes == 0)
    {
        return;
    }

    width--;
    float elemsInColumn = (float)numBytes / (float)width;
    uint8 min[width + 1];
    uint8 max[width + 1];

    if (SET_PEACKDET_EN)                                                    // ���� ���. ���. ��������
    {
        uint8 *iMin = &min[0];
        uint8 *iMax = &max[0];

        for (uint col = 0; col < width; col++, iMin++, iMax++)
        {
            uint firstElem = (uint)(col * elemsInColumn);
            uint lastElem = (uint)firstElem + elemsInColumn - 1;
            *iMin = data[firstElem];
            *iMax = data[firstElem];
            for (uint elem = firstElem + 1; elem <= lastElem; elem++)
            {
                SET_MIN_IF_LESS(data[elem], *iMin);
                SET_MAX_IF_LARGER(data[elem], *iMax);
            }
        }
    }
    else                                                                // ���� ���. ���. �������
    {
        for (int col = 0; col < width; col++)
        {
            uint firstElem = (uint)col * elemsInColumn;
            uint lastElem = (uint)firstElem + elemsInColumn - 1;
            min[col] = data[firstElem];
            max[col] = data[firstElem];
            for (uint elem = firstElem + 1; elem <= lastElem; elem++)
            {
                SET_MIN_IF_LESS(data[elem], min[col]);
                SET_MAX_IF_LARGER(data[elem], max[col]);
            }
        }
    }

    int height = 17;
    float scale = (float)height / (float)(MAX_VALUE - MIN_VALUE);

    const int SIZE_BUFFER = width + 1;

    int mines[SIZE_BUFFER];     // ������ ��� ������������ �������� � ������ ��������
    int maxes[SIZE_BUFFER];     // ������ ��� ����������� �������� � ������ ��������

    mines[0] = Ordinate(max[0], scale);
    maxes[0] = Ordinate(min[0], scale);

    for (int i = 1; i < width; i++)
    {
        maxes[i] = Ordinate((uint8)((max[i] < min[i - 1]) ? min[i - 1] : max[i]), scale);
        mines[i] = Ordinate((uint8)((min[i] > max[i - 1]) ? max[i - 1] : min[i]), scale);
    }

    // ������ ������� ���������� �����, ������� ����� ���������� (������� �� ����, ��� � �������� ������ � ������������� ������ ��� �����,
    // � � ���������� ������ ��������� �� ����������� �������

    uint numPoints = 0;
    for (int i = 0; i < width; i++)
    {
        if (maxes[i] == -1 && mines[i] == -1)
        {
            break;
        }          // ���� ��� ����� �� ���� �������, �� �������
        numPoints++;
    }

    if (numPoints != width)                     // ���� ����� �������� �� ��� �����,
    {
        numPoints--;                            // �� ������� �� ���� ������ - �� ��������� ��������� � ����� ������
    }

    if (numPoints > 1)
    {
        if (numPoints < 256)
        {
            SendToDisplayDataInRect(x, mines, maxes, numPoints);
        }
        else
        {
            SendToDisplayDataInRect(x, mines, maxes, 255);
            numPoints -= 255;
            SendToDisplayDataInRect(x + 255, mines + 255, maxes + 255, numPoints);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawTPos(int leftX, int rightX)
{
    int x[] = {leftX, (rightX - leftX) / 2 + leftX, rightX};
    int x0 = x[TPOS];
    Painter_FillRegionC(x0 - 3, 10, 6, 6, gColorBack);
    Painter_DrawCharC(x0 - 3, 10, SYMBOL_TPOS_1, gColorFill);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawTShift(int leftX, int rightX, int numBytes)
{
    float scale = (float)(rightX - leftX + 1) / ((float)numBytes - (numBytes == 281 ? 1 : 0));
    int xShift = (int)(1.5f + (sTime_TPosInBytes() - sTime_TShiftInPoints()) * scale) - 1;
    if (SET_PEACKDET_EN)
    {
        if (TPOS_RIGHT)
        {
            --xShift;
        }
    }
    if (FPGA_POINTS_512)
    {
        ++xShift;                           /// \todo �������
    }
    LIMIT_ABOVE(xShift, rightX - 2);

    int dX01 = 1, dX02 = 2, dX11 = 3, dY11 = 7, dY12 = 6;

    if (xShift < leftX - 2)
    {
        xShift = leftX - 2;
        dX01 = 3; dX02 = 1; dY12 = 6;
    }
    else if (xShift > rightX - 1)
    {
        xShift = rightX - 2;
        dX11 = 1;
    }
    else
    {
        dY11 = 5; dY12 = 7;
    }

    Painter_FillRegionC((int)xShift - 1, 1, 6, 6, gColorBack);
    Painter_FillRegionC((int)xShift, 2, 4, 4, gColorFill); //-V112
    Painter_DrawLineC((int)xShift + dX01, 3, (int)xShift + dX11, dY11 - 2, gColorBack);
    Painter_DrawLine((int)xShift + dX02, 4, (int)xShift + 2, dY12 - 2); //-V112
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/// ���������� (-1), ���� ����� �� ������� (NONE_VALUE)
static int Ordinate(uint8 x, float scale)
{
    const float bottom = 17.0;

    if (x == NONE_VALUE)
    {
        return -1;
    }

    return (bottom - scale * LimitationInt(x - MIN_VALUE, 0, (MAX_VALUE - MIN_VALUE))) + 0.5f;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
// ��������� ������������ width ������ 255
//----------------------------------------------------------------------------------------------------------------------------------------------------
static void SendToDisplayDataInRect(int x, const int *min, const int *max, uint width)
{
    LIMIT_ABOVE(width, 255);

    uint8 points[width * 2];

    //    uint8 _min = 255;
    //    uint8 _max = 0;

    for (uint i = 0; i < width; i++)
    {
        points[i * 2] = max[i];
        /*
        if (points[i * 2] > _max)
        {
        _max = points[i * 2];
        }
        */
        points[i * 2 + 1] = min[i];
    }

    Painter_DrawVLineArray(x, (int)width, points, gColorChan[curCh]); //-V202
}

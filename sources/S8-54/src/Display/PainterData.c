#include "PainterData.h"
#include "DisplayTypes.h"
#include "Settings/SettingsDisplay.h"
#include "FPGA/DataStorage.h"
#include "Settings/Settings.h"
#include "Grid.h"
#include "Utils/ProcessingSignal.h"
#include "Utils/Math.h"
#include "Utils/Debug.h"
#include "Hardware/RAM.h"
#include "Hardware/FSMC.h"
#include "Hardware/Timer.h"
#include "Symbols.h"
#include "Log.h"
#include "Settings/SettingsDisplay.h"
#include "Utils/GlobalFunctions.h"


#ifdef _MS_VS
#pragma warning(push)
#pragma warning(disable:4204)
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CONVERT_DATA_TO_DISPLAY(out, inVal)                     \
    int in = inVal;                                             \
    if(in < MIN_VALUE) { in = MIN_VALUE; }                      \
    if(in > MAX_VALUE) { in = MAX_VALUE; }                      \
    out = (uint8)(maxY - (int)(((in) - MIN_VALUE) * scaleY));   \
    if(out < (uint8)minY)   { out = (uint8)minY; }              \
    if(out > (uint8)maxY)   { out = (uint8)maxY; };


// ��������� ��� �������� �� ����������� : val1 - �������, val2 - �������
#define PLACE_2_ASCENDING(v1, v2) if((v1) > (v2)) { int qwerty = v1; v1 = v2; v2 = qwerty; }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int xP2P = 0;                // ����� �������� �������� ��� ��������� ������������ �����
static Channel curCh = A;           // ������� �������� ������
static DataSettings *curDS = 0;     // DataSettings ��� ��������� �������


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void  DrawDataMemInt(void);
static void  DrawDataInModeNormal(void);
static void  DrawDataInModeWorkLatest(void);
static void  DrawDataMinMax(void);
static void  DrawDataChannel(uint8 *dataIn, int minY, int maxY);
static void  DrawDataInRect(int x, int width, const uint8 *data, int numElems, bool peackDet);
static void  DrawTPos(int leftX, int rightX);
static void  DrawTShift(int leftX, int rightX, int numPoints);
static void  DrawBothChannels(uint8 *dataA, uint8 *dataB);                       // ���������� ��� ������. ���� data == 0, �� ������ ������� �� Processing_GetData
static int   FillDataP2P(uint8 *data, DataSettings **ds);
static void  DrawMarkersForMeasure(float scale);
static bool  DataBeyondTheBorders(uint8 *data, int firstPoint, int lastPoint);   // ���������� true, ���� ����������� ������� ������� �� ������� ������
static void  DrawSignalLined(const uint8 *data, int startPoint, int endPoint, int minY, int maxY, float scaleY, float scaleX, bool calculateFiltr);
static void  DrawSignalPointed(const uint8 *data, int startPoint, int endPoint, int minY, int maxY, float scaleY, float scaleX);
static uint8 Ordinate(uint8 x, int bottom, float scale);
static int   FillDataP2PforRecorder(int numPoints, int numPointsDS, int pointsInScreen, uint8 *src, uint8 *dest);
static int   FillDataP2PforNormal(int numPoints, int numPointsDS, int pointsInScreen, uint8 *src, uint8 *dest);
static void  DrawLimitLabel(int delta);      // �������� ��������� �� ������ � ������ ������� �� ������� ������. delta - ���������� �� ���� �����, �� ������� ��������� ���������. ���� delta < 0 - ��������� ����� �����
static void  SendToDisplayDataInRect(int x, uint8 *min, uint8 *max, int width);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PainterData_DrawData(void)
{
    xP2P = 0;

	if (DS_NumElementsInStorage() == 0)
	{
        Painter_DrawRectangleC(GridLeft(), GRID_TOP, GridWidth(), GridFullHeight(), gColorFill);
		return;
	}

	// ����� ��������� ��������, ���������� � ����
	if (WORK_INT)
	{
		if (SHOW_IN_INT_SAVED || SHOW_IN_INT_BOTH)
		{
			DrawDataMemInt();
		}
		if (SHOW_IN_INT_DIRECT || SHOW_IN_INT_BOTH)
		{
			DrawDataInModeNormal();
		}
	}
	// ����� ��������� �������� ���
	else if (WORK_LAST)
	{
		DrawDataInModeWorkLatest();
	}
	// ���������� �����
	else
	{
		if (ALWAYS_SHOW_MEM_INT_SIGNAL)    // ���� ����� ���������� ������� �� ����
		{
			DrawDataMemInt();                       // �� ����������
		}
		DrawDataInModeNormal();                     // � ������ ��������� ������    
	}

	if (DISPLAY_NUM_MIN_MAX != 1)
	{
		DrawDataMinMax();
	}

    if (xP2P)
    {
        Painter_DrawVLineC(xP2P, GRID_TOP, GridFullBottom(), gColorGrid);
    }

    Painter_DrawRectangleC(GridLeft(), GRID_TOP, GridWidth(), GridFullHeight(), gColorFill);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
void PainterData_DrawMath(void)
{
    if (!FUNC_ENABLED || DS_GetData_RAM(A, 0) == 0 || DS_GetData_RAM(B, 0) == 0)
    {
        return;
    }

    uint8 *dataRel0 = 0;
    uint8 *dataRel1 = 0;
    Processing_GetData(&dataRel0, &dataRel1, &curDS);

    float *dataAbsA = (float*)RAM(DRAW_MATH_DATA_REL_A);
    float *dataAbsB = (float*)RAM(DRAW_MATH_DATA_REL_B);

    int numPoints = NumBytesInChannel(curDS);

    Math_PointsRelToVoltage(dataRel0, numPoints, (Range)curDS->range[A], curDS->rShift[A], dataAbsA);
    Math_PointsRelToVoltage(dataRel1, numPoints, (Range)curDS->range[B], curDS->rShift[B], dataAbsB);

    Math_CalculateMathFunction(dataAbsA, dataAbsB, numPoints);

    uint8 points[FPGA_MAX_POINTS];

    Math_PointsVoltageToRel(dataAbsA, numPoints, RANGE_MATH, RSHIFT_MATH, points);

    curCh = Math;
    DrawDataChannel(points, GridMathTop(), GridMathBottom());

    static const int WIDTH = 71;
    static const int HEIGHT = 10;
    int delta = (SHOW_STRING_NAVI_ALL && FUNC_MODE_DRAW_TOGETHER) ? 10 : 0;
    Painter_DrawRectangleC(GridLeft(), GridMathTop() + delta, WIDTH, HEIGHT, gColorFill);
    Painter_FillRegionC(GridLeft() + 1, GridMathTop() + 1 + delta, WIDTH - 2, HEIGHT - 2, gColorBack);
    Divider divider = set.math.divider;
    Painter_DrawTextC(GridLeft() + 2, GridMathTop() + 1 + delta, sChannel_Range2String(RANGE_MATH, divider), gColorFill);
    Painter_DrawText(GridLeft() + 25, GridMathTop() + 1 + delta, ":");
    char buffer[20];
    Painter_DrawText(GridLeft() + 27, GridMathTop() + 1 + delta, sChannel_RShift2String(RSHIFT_MATH, RANGE_MATH, divider, buffer));
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
// ���������� ���� ������
void PainterData_DrawMemoryWindow(void)
{
    uint8 *datA = gDataAmemInt;
    uint8 *datB = gDataBmemInt;
    DataSettings *ds = gDSmemInt;

    uint8 *dA = 0;  // ���� ������� ������ ������� �� RAM
    uint8 *dB = 0;

    if (WORK_DIRECT || WORK_LAST)
    {
        datA = gDataA;
        datB = gDataB;
        ds = gDSet;

        if (DS_DataSettingsFromEnd(0)->tBase >= MIN_TBASE_P2P)          // ���� ��������� � ������ ����������� ������
        {
            DS_GetLastFrameP2P_RAM(&ds, &datA, &datB);
        }

        // ����� ���������� �� �������� ��� � ����, ������ ��
        dA = AllocMemForChannelFromHeap(A, ds);
        dB = AllocMemForChannelFromHeap(B, ds);

        int numBytes = NumBytesInChannel(ds);

        RAM_MemCpy16(datA, dA, numBytes);
        RAM_MemCpy16(datB, dB, numBytes);

        datA = dA;
        datB = dB;
    }

    int leftX = 3;
    int top = 0;
    int height = GRID_TOP - 3;
    int bottom = top + height;

    static const int rightXses[3] = {276, 285, 247};
    int rightX = rightXses[MODE_WORK];
    if (sCursors_NecessaryDrawCursors())
    {
        rightX = 68;
    }

    float scaleX = (float)(rightX - leftX + 1) / sMemory_NumPointsInChannel();
    int width = (int)((rightX - leftX) * (282.0f / sMemory_NumPointsInChannel()));

    int16 shiftInMemory = (int16)sDisplay_ShiftInMemoryInPoints();

    const int xVert0 = leftX + (int)(shiftInMemory * scaleX);

    Channel lastAffectedChannel = LAST_AFFECTED_CH;
    if (((uint)NumPoints_2_FPGA_NUM_POINTS(sMemory_NumBytesInChannel(false)) == gDSet->indexLength) && (gDataA || gDataB))
    {
        Channel chanFirst = lastAffectedChannel == A ? B : A;
        Channel chanSecond = lastAffectedChannel == A ? A : B;
        const uint8 *dataFirst = lastAffectedChannel == A ? datB : datA;
        const uint8 *dataSecond = lastAffectedChannel == A ? datA : datB;

        bool peackDet = ds->peackDet != PeackDet_Disable;

        if (sChannel_NeedForDraw(dataFirst, chanFirst, ds))
        {
            curCh = chanFirst;
            DrawDataInRect(1, rightX + 3, dataFirst, sMemory_NumBytesInChannel(false), peackDet);
        }
        if (sChannel_NeedForDraw(dataSecond, chanSecond, ds))
        {
            curCh = chanSecond;
            DrawDataInRect(1, rightX + 3, dataSecond, sMemory_NumBytesInChannel(false), peackDet);
        }
    }

    Painter_DrawRectangleC(xVert0, top, width - (FPGA_NUM_POINTS_8k ? 1 : 0), bottom - top + 1, gColorFill);

    DrawTPos(leftX, rightX);

    DrawTShift(leftX, rightX, sMemory_NumBytesInChannel(false));

    free(dA);
    free(dB);
}


//---------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDataMemInt(void)
{
    if (gDSmemInt != 0)
    {
        curDS = gDSmemInt;
        curCh = A;
        DrawDataChannel(gDataAmemInt, GRID_TOP, GridChannelBottom());
        curCh = B;
        DrawDataChannel(gDataBmemInt, GRID_TOP, GridChannelBottom());
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDataInModeNormal(void)
{
    if ((uint)NumPoints_2_FPGA_NUM_POINTS(sMemory_NumBytesInChannel(false)) != gDSet->indexLength) // ���� ���������� ����� � ������ �� ������������� �������������� � ���������� - ������ �������
    {
        return;     // WARN ��� ��������. �� �������� ����� ��������������� ��� ��, ��� �� ����������� tShift, rShift, Range, TBase
    }

    int16 numSignals = (int16)DS_NumElementsWithSameSettings();
    LIMITATION(numSignals, numSignals, 1, DISPLAY_NUM_ACCUM);
    if (numSignals == 1 ||  // � ��������� ������ ���� ������ � �������� �����������
        NUM_ACCUM_INF ||  // ��� ����������� ����������
        MODE_ACCUM_RESET ||  // ��� �������������� ������� ������ ��� ����������
        IN_RANDOM_MODE)             // ��� � ������ �������������
    {
        DrawBothChannels(0, 0);                                     // ����� 0, ������ ������ ��������� ������
    }
    else
    {
        for (int i = 0; i < numSignals; i++)                        // ����� ������ ����������� ����� ��������� ��������
        {
            DrawBothChannels(DS_GetData_RAM(A, i), DS_GetData_RAM(B, i));
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDataInModeWorkLatest(void)
{
    if (gDSmemLast != 0)
    {
        curDS = gDSmemInt;
        curCh = A;
        DrawDataChannel(gDataAmemLast, GRID_TOP, GridChannelBottom());
        curCh = B;
        DrawDataChannel(gDataBmemLast, GRID_TOP, GridChannelBottom());
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDataMinMax(void)
{
    ModeDrawSignal modeDrawSignalOld = MODE_DRAW_SIGNAL;
    MODE_DRAW_SIGNAL = ModeDrawSignal_Lines;
    curDS = gDSet;
    if (LAST_AFFECTED_CH == B)
    {
        curCh = A;
        DrawDataChannel(DS_GetLimitation(A, 0), GRID_TOP, GridChannelBottom());
        DrawDataChannel(DS_GetLimitation(A, 1), GRID_TOP, GridChannelBottom());
        curCh = B;
        DrawDataChannel(DS_GetLimitation(B, 0), GRID_TOP, GridChannelBottom());
        DrawDataChannel(DS_GetLimitation(B, 1), GRID_TOP, GridChannelBottom());
    }
    else
    {
        curCh = B;
        DrawDataChannel(DS_GetLimitation(B, 0), GRID_TOP, GridChannelBottom());
        DrawDataChannel(DS_GetLimitation(B, 1), GRID_TOP, GridChannelBottom());
        curCh = A;
        DrawDataChannel(DS_GetLimitation(A, 0), GRID_TOP, GridChannelBottom());
        DrawDataChannel(DS_GetLimitation(A, 1), GRID_TOP, GridChannelBottom());
    }
    MODE_DRAW_SIGNAL = modeDrawSignalOld;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDataChannel(uint8 *dataIn, int minY, int maxY)
{
    bool calculateFiltr = true;
    int sizeBuffer = NumBytesInChannel(curDS);
#ifndef _MS_VS
    uint8 data[sizeBuffer];                                 // �����, ���� ����� ��������� ������ ������ �� �������� ���
#else
    uint8 data[10];
#endif

    int firstPoint = 0;
    int lastPoint = 280;

    if (!IN_P2P_MODE ||                                     // ���� �� ��������� � ������ ��������� ���������� ��������
        (IN_P2P_MODE && curDS->time.timeMS))                   // ��� � ����������, �� ������ ��� �������
    {
        sDisplay_PointsOnDisplay(&firstPoint, &lastPoint);  // �� ������� ������ � ��������� �����, ��������� �� �����
    }

    if (IN_P2P_MODE &&                                      // ���� ��������� � ������ ��������� ���������� ��������
        curDS->time.timeMS == 0)                               // � ���������� ������� ������ ������ ��� �� ���������
    {
        lastPoint = FillDataP2P(data, &curDS);
        if (lastPoint < 2)                                  // ���� ������ ������ ���� ����� - �����
        {
            return;
        }
        dataIn = data;
    }
    else if (dataIn == 0)                                   // ������, ��� ������ ���������� ��������� ��������� ������ �� Processing_GetData()
    {
        calculateFiltr = false;
        if (curCh == A)
        {
            Processing_GetData(&dataIn, 0, &curDS);
        }
        else
        {
            Processing_GetData(0, &dataIn, &curDS);
        }
        RAM_MemCpy16(dataIn, data, sizeBuffer);
        dataIn = data;
    }

    if (!sChannel_NeedForDraw(dataIn, curCh, curDS))
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

    if (!DataBeyondTheBorders(dataIn, firstPoint, lastPoint))   // ���� ������ �� ������� �� ������� ������
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

//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawDataInRect(int x, int width, const uint8 *data, int numBytes, bool peackDet)
{
    if (numBytes == 0)
    {
        return;
    }

    width--;
    float elemsInColumn = (float)numBytes / (float)width;
    uint8 min[width + 1];
    uint8 max[width + 1];

    if (peackDet == PeackDet_Disable)              // ���� ���. ���. ��������
    {
        uint8 *iMin = &min[0];
        uint8 *iMax = &max[0];

        for (int col = 0; col < width; col++, iMin++, iMax++)
        {
            int firstElem = (int)(col * elemsInColumn);
            int lastElem = firstElem + (int)elemsInColumn - 1;
            *iMin = data[firstElem];
            *iMax = data[firstElem];
            for (int elem = firstElem + 1; elem <= lastElem; elem++)
            {
                SET_MIN_IF_LESS(data[elem], *iMin);
                SET_MAX_IF_LARGER(data[elem], *iMax);
            }
        }
    }
    else                                // ���� ���. ���. �������
    {
        for (int col = 0; col < width; col++)
        {
            float firstElem = col * elemsInColumn;
            float lastElem = firstElem + elemsInColumn - 1;
            min[col] = data[(int)firstElem];
            max[col] = data[(int)firstElem];
            for (int elem = (int)firstElem + 1; elem <= (int)lastElem; elem++)
            {
                SET_MIN_IF_LESS(data[elem], min[col]);
                SET_MAX_IF_LARGER(data[elem], max[col]);
            }
        }
    }

    int bottom = 17;
    int height = 17;
    float scale = (float)height / (float)(MAX_VALUE - MIN_VALUE);

    uint8 val0[width + 1];
    uint8 val1[width + 1];

    val0[0] = Ordinate(max[0], bottom, scale);
    val1[0] = Ordinate(min[0], bottom, scale);

    for (int i = 1; i < width; i++)
    {
        int value0 = min[i] > max[i - 1] ? max[i - 1] : min[i];
        int value1 = max[i] < min[i - 1] ? min[i - 1] : max[i];
        val1[i] = Ordinate((uint8)value1, bottom, scale);
        val0[i] = Ordinate((uint8)value0, bottom, scale);
    }

    SendToDisplayDataInRect(x, val0, val1, width);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void SendToDisplayDataInRect(int x, uint8 *min, uint8 *max, int width)
{
    int start = 0;
    for (; start < width; start++)
    {
        if (min[start] || max[start])
        {
            int end = start + 1;
            for (; (end < width) && (end - start < 250) && (min[end] || max[end]); end++)   // WARN ��� �������� ������
            {
            }
            int numPoints = end - start;
            uint8 points[numPoints * 2];
            for (int i = start; i < end; i++)
            {
                points[i * 2 - start * 2] = max[i];
                points[i * 2 + 1 - start * 2] = min[i];
            }

            Painter_DrawVLineArray(x + start, numPoints, points, gColorChan[curCh]);
            start = end;
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawTPos(int leftX, int rightX)
{
    int x[] = {leftX, (rightX - leftX) / 2 + leftX, rightX};
    int x0 = x[TPOS];
    Painter_FillRegionC(x0 - 3, 10, 6, 6, gColorBack);
    Painter_DrawCharC(x0 - 3, 10, SYMBOL_TPOS_1, gColorFill);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawTShift(int leftX, int rightX, int numBytes)
{
    float scale = (float)(rightX - leftX + 1) / ((float)numBytes - (numBytes == 281 ? 1 : 0));
    int xShift = (int)(1.5f + (sTime_TPosInBytes() - sTime_TShiftInPoints()) * scale) - 1;
    if (PEACKDET_EN)
    {
        if (TPOS_RIGHT)
        {
            --xShift;
        }
    }
    if (FPGA_NUM_POINTS_512)
    {
        ++xShift;                           // WARN �������
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
    Painter_FillRegionC((int)xShift, 2, 4, 4, gColorFill);
    Painter_DrawLineC((int)xShift + dX01, 3, (int)xShift + dX11, dY11 - 2, gColorBack);
    Painter_DrawLine((int)xShift + dX02, 4, (int)xShift + 2, dY12 - 2);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawBothChannels(uint8 *dataA, uint8 *dataB)
{
    curDS = gDSet;
    if (LAST_AFFECTED_CH == B)
    {
        if (gDSet->enableChA)
        {
            curCh = A;
            DrawDataChannel(dataA, GRID_TOP, GridChannelBottom());
        }
        if (gDSet->enableChB)
        {
            curCh = B;
            DrawDataChannel(dataB, GRID_TOP, GridChannelBottom());
        }
    }
    else
    {
        if (gDSet->enableChB)
        {
            curCh = B;
            DrawDataChannel(dataB, GRID_TOP, GridChannelBottom());
        }
        if (gDSet->enableChA)
        {
            curCh = A;
            DrawDataChannel(dataA, GRID_TOP, GridChannelBottom());
        }
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static int FillDataP2P(uint8 *data, DataSettings **ds)
{
    int pointsInScreen = 281;
    if (PEACKDET_EN)
    {
        pointsInScreen *= 2;
    }

    uint8 *dataA = 0;
    uint8 *dataB = 0;

    int numPoints = DS_GetLastFrameP2P_RAM(ds, &dataA, &dataB); // �������� ����� ����������� ������

    int numPointsDS = NumBytesInChannel(*ds);

    uint8 *dat[] = {dataA, dataB};

    return RECORDER_MODE ?
        FillDataP2PforRecorder(numPoints, numPointsDS, pointsInScreen, dat[curCh], data) :   // ��� ����������, ���� ������� ����� ������������
        FillDataP2PforNormal(numPoints, numPointsDS, pointsInScreen, dat[curCh], data);      // � ��� � ���������� ������
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
static bool DataBeyondTheBorders(uint8 *data, int firstPoint, int lastPoint)
{
    int numMin = 0; // ����� ���������� ��������, ������� ��� ������ MIN_VALUE
    int numMax = 0; // ����� ���������� ��������, ������� ��� ������ MAX_VALUE
    int numPoints = lastPoint - firstPoint;
    for (int i = firstPoint; i < lastPoint; i++)
    {
        if (data[i] <= MIN_VALUE)
        {
            numMin++;
        }
        if (data[i] >= MAX_VALUE)
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawSignalLined(const uint8 *data, int startPoint, int endPoint, int minY, int maxY, float scaleY, float scaleX, bool calculateFiltr)
{
    if (endPoint < startPoint)
    {
        return;
    }

    uint8 dataCD[281];

    int gridLeft = GridLeft();
    int gridRight = GridRight();

    int numPoints = sMemory_NumBytesInChannel(false);
    int numSmoothing = sDisplay_NumPointSmoothing();

    if (curDS->peackDet == PeackDet_Disable)
    {
        for (int i = startPoint; i < endPoint; i++)
        {

            float x0 = gridLeft + (i - startPoint) * scaleX;
            if (x0 >= gridLeft && x0 <= gridRight)
            {
                int index = i - startPoint;
                int y = calculateFiltr ? Math_CalculateFiltr(data, i, numPoints, numSmoothing) : data[i];
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
            float x = gridLeft + i / 2 * scaleX;

            int index = i + startPoint * 2;

            int y0 = 0, y1 = 0;
            { CONVERT_DATA_TO_DISPLAY(y0, data[index++]); }
            { CONVERT_DATA_TO_DISPLAY(y1, data[index++]); }

            PLACE_2_ASCENDING(y0, y1);

            Painter_DrawVLine((int)x, y0, y1);

            int z0 = 0;
            int z1 = 0;
            { CONVERT_DATA_TO_DISPLAY(z0, data[index++]); }
            { CONVERT_DATA_TO_DISPLAY(z1, data[index]); }

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

    if (curDS->peackDet == PeackDet_Disable)
    {
        CONVERT_DATA_TO_DISPLAY(dataCD[280], data[endPoint]);
        Painter_DrawSignal(GridLeft(), dataCD, true);
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawSignalPointed(const uint8 *data, int startPoint, int endPoint, int minY, int maxY, float scaleY, float scaleX)
{
    int numPoints = sMemory_NumBytesInChannel(false);
    int numSmoothing = sDisplay_NumPointSmoothing();

    if (scaleX == 1.0f)
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
static uint8 Ordinate(uint8 x, int bottom, float scale)
{
    return (x == NONE_VALUE) ? 0 : (uint8)(((float)bottom - scale * LimitationInt(x - MIN_VALUE, 0, (MAX_VALUE - MIN_VALUE))) + 0.5f);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------------------------------------------------------------------------------
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

    int kP2P = PEACKDET_EN ? 2 : 1;

    if (numPoints > pointsInScreen)
    {
#ifndef _MS_VS
        int numScreens = numPoints / pointsInScreen;                                                        // ����� ������ ������������ �������.
        uint8 dataTemp[pointsInScreen];
#endif

        memcpy(dataTemp, dest + (numScreens - 1) * pointsInScreen - deltaNumPoints, pointsInScreen);        // ������ ��������� ��������� ������ ����� � �����

        memcpy(dataTemp, dest + numScreens * pointsInScreen - deltaNumPoints, numPoints % pointsInScreen);  // ������ ��������� ������� � ������ ������

        xP2P = GridLeft() + ((numPoints  % pointsInScreen) / kP2P) - 1;

        memcpy(dest, dataTemp, pointsInScreen);                                                             // ������ ��������� ��������� ����� � ��������
    }
    else
    {
        xP2P = GridLeft() + numPoints / kP2P - 1;
    }

    return numPoints > pointsInScreen ? pointsInScreen : numPoints;
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


















































































#ifdef _MS_VS
#pragma warning(pop)
#endif

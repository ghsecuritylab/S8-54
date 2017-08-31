#include "Display.h"
#include "Painter.h"
#include "Hardware/Timer.h"
#include "main.h"
#include "Utils/Math.h"
#include "Settings/Settings.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    TypeWelcomeScreen_Vague,
    TypeWelcomeScreen_Wave,
    TypeWelcomeScreen_VagueWave
} TypeWelcomeScreen;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void DrawProgressBar(uint dT);
static void DrawBigMNIPI(void);
static int RandValue(int min, int max);
static void InitPoints(void);

typedef struct
{
    uint16 x;
    uint8 y;
} Vector;


int numPoints = 0;
Vector array[7000] __attribute__ ((section("CCM_DATA")));

static TypeWelcomeScreen typeScreen = TypeWelcomeScreen_Wave;

#define VAGUE (typeScreen == TypeWelcomeScreen_Vague)
#define WAVE (typeScreen == TypeWelcomeScreen_Wave)
#define ALL (typeScreen == TypeWelcomeScreen_VagueWave)
#define VAGUE_OR_ALL (VAGUE || ALL)
#define WAVE_OR_ALL (WAVE || ALL)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitHardware(void)
{
    GPIO_InitTypeDef isGPIO_ =
    {
        GPIO_PIN_11,
        GPIO_MODE_INPUT,
        GPIO_NOPULL,
        GPIO_SPEED_HIGH,
        GPIO_AF0_MCO,
    };
    // ������ ���������� �������  � ����� �������
    HAL_GPIO_Init(GPIOG, &isGPIO_);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display_Init(void)
{
    ms->display.value = 0.0f;
    ms->display.isRun = false;
    ms->display.timePrev = 0;
    ms->display.direction = 10.0f;

    gColorBack = COLOR_BLACK;
    gColorFill = COLOR_WHITE;

    for (int i = 0; i < 14; i++)
    {
        float red = i / 14.0f * 31.0f + 0.5f;
        float green = i / 14.0f * 63.0f + 0.5f;
        float blue = i / 14.0f * 31.0f + 0.5f;
        set.display.colors[i + 2] = MAKE_COLOR((int)red, (int)green, (int)blue);
    }

    Painter_ResetFlash();

    InitHardware();

    Painter_LoadPalette(0);
    Painter_LoadPalette(1);
    Painter_LoadPalette(2);

    //Painter_LoadFont(TypeFont_5);
    Painter_LoadFont(TypeFont_8);
    //Painter_LoadFont(TypeFont_UGO);
    //Painter_LoadFont(TypeFont_UGO2);
    Painter_SetFont(TypeFont_8);

    InitPoints();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawButton(int x, int y, char *text)
{
    int width = 25;
    int height = 20;
    Painter_DrawRectangle(x, y, width, height);
    Painter_DrawStringInCenterRect(x, y, width + 2, height - 1, text);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Display_Update(void)
{
    ms->display.isRun = true;

    uint dT = gTimerMS - ms->display.timePrev;
    ms->display.timePrev = gTimerMS;

    Painter_BeginScene(COLOR_BLACK);

    Painter_SetColor(COLOR_WHITE);

    if (ms->state == State_Start || ms->state == State_Ok)
    {
        Painter_BeginScene(gColorBack);
#ifdef S8_54
        Painter_SetColor(gColorFill);
        Painter_DrawRectangle(0, 0, 319, 239);
        DrawBigMNIPI();
        Painter_SetColor(COLOR_WHITE);
        Painter_DrawStringInCenterRect(0, 180, 320, 20, "��� ��������� ������ ������� � ����������� ������ ������");
        Painter_DrawStringInCenterRect(0, 205, 320, 20, "����� ����������: ���./����. 8-017-262-57-50");
        Painter_DrawStringInCenterRect(0, 220, 320, 20, "������������: e-mail: mnipi-24(@)tut.by, ���. 8-017-262-57-51");
#endif
        Painter_EndScene();
    }
    else if (ms->state == State_Mount)
    {
        DrawProgressBar(dT);
    }
    else if (ms->state == State_WrongFlash)
    {
        Painter_DrawStringInCenterRectC(0, 0, 320, 200, "�� ������� ��������� ����", COLOR_FLASH_10);
        Painter_DrawStringInCenterRectC(0, 20, 320, 200, "���������, ��� �������� ������� FAT32", COLOR_WHITE);
    }
    else if (ms->state == State_RequestAction)
    {
        Painter_DrawStringInCenterRect(0, 0, 320, 200, "���������� ����������� �����������");
        Painter_DrawStringInCenterRect(0, 20, 320, 200, "���������� ���?");

        DrawButton(290, 55, "��");
        DrawButton(290, 195, "���");
    }
    else if (ms->state == State_Upgrade)
    {
        Painter_DrawStringInCenterRect(0, 0, 320, 190, "��������� ����������");
        Painter_DrawStringInCenterRect(0, 0, 320, 220, "��������� ������������ �����������");

        int height = 30;
        int fullWidth = 280;
        int width = fullWidth * ms->percentUpdate;

        Painter_FillRegion(20, 130, width, height);
        Painter_DrawRectangle(20, 130, fullWidth, height);
    }

    Painter_EndScene();
    ms->display.isRun = false;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void DrawProgressBar(uint dT)
{
    const int WIDTH = 300;
    const int HEIGHT = 20;
    const int X = 10;
    const int Y = 200;
    
    float step = dT / ms->display.direction;

    ms->display.value += step;

    if (ms->display.direction > 0.0f && ms->display.value > WIDTH)
    {
        ms->display.direction = -ms->display.direction;
        ms->display.value -= step;
    }
    else if (ms->display.direction < 0.0f && ms->display.value < 0)
    {
        ms->display.direction = -ms->display.direction;
        ms->display.value -= step;
    }

    int dH = 15;
    int y0 = 50;

    Painter_DrawStringInCenterRectC(X, y0, WIDTH, 10, "��������� USB-����.", COLOR_WHITE);
    Painter_DrawStringInCenterRect(X, y0 + dH, WIDTH, 10, "��� ����� ������������ �����������");
    Painter_DrawStringInCenterRect(X, y0 + 2 * dH, WIDTH, 10, "���������...");

    Painter_DrawRectangle(X, Y, WIDTH, HEIGHT);
    Painter_FillRegion(X, Y, ms->display.value, HEIGHT);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Display_IsRun(void)
{
    return ms->display.isRun;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void DrawBigMNIPI(void)
{
    static uint startTime = 0;
    static bool first = true;
    
    if(first)
    {
        first = false;
        startTime = gTimerMS;
    }

    uint time = gTimerMS - startTime;

    int numColor = 0;
    LIMITATION(numColor, time / (float)TIME_WAIT * 13.0f, 0, 13);
    Painter_SetColor((Color)(numColor + 2));

    float amplitude = 3.0f - (time / (TIME_WAIT / 2.0f)) * 3;
    LIMIT_BELOW(amplitude, 0.0f);
    float frequency = 0.05f;

    float radius = 5000.0f * (TIME_WAIT) / 3000.0f / time;
    LIMIT_BELOW(radius, 0);

    float shift[240];

    for (int i = 0; i < 240; i++)
    {
        shift[i] = WAVE_OR_ALL ? amplitude * sin(frequency * time + i / 5.0f) : 0;
    }

    for (int i = 0; i < numPoints; i++)
    {
        int x = array[i].x + (VAGUE_OR_ALL ? RandValue(-radius, radius) : 0) + shift[array[i].y];
        int y = array[i].y + (VAGUE_OR_ALL ? RandValue(-radius, radius) : 0);
        if (x > 0 && x < 319 && y > 0 && y < 239)
        {
            Painter_SetPoint(x, y);
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------]
static int RandValue(int min, int max)
{
    int value = rand() % (max - min + 1);

    return value + min;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
static void InitPoints(void)
{
    uint8 buffer[320][240];

    Painter_DrawBigTextInBuffer(31, 70, 9, "�����", buffer);

    for (int x = 0; x < 320; x++)
    {
        for (int y = 0; y < 240; y++)
        {
            if (buffer[x][y])
            {
                array[numPoints].x = x;
                array[numPoints].y = y;
                numPoints++;
            }
        }
    }
}

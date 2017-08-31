#pragma once
#include "Colors.h"
#include "DisplayTypes.h"
#include "PainterText.h"
#include "PainterC.h"


void Painter_SendToDisplay(uint8 *bytes, int numBytes);
void Painter_BeginScene(Color color);
void Painter_EndScene(void);
void Painter_SendFrame(bool first);
void Painter_ResetFlash(void);
void Painter_SetColor(Color color);
void Painter_LoadPalette(int num);
void Painter_SetPalette(Color color);
void Painter_SetPoint(int x, int y);
void Painter_DrawHLine(int y, int x0, int x1);
void Painter_DrawVLine(int x, int y0, int y1);
void Painter_DrawHPointLine(int y, int x0, int x1, float delta);
void Painter_DrawMultiVPointLine(int numLines, int y, uint16 x[], int delta, int count, Color color);
void Painter_DrawMultiHPointLine(int numLines, int x, uint8 y[], int delta, int count, Color color);
void Painter_DrawLine(int x0, int y0, int x1, int y1);
/// \brief ������ ����������� �������������� �����. dFill - ����� ������, dEmpty - �����. ����� ��������.
/// ����� ������ ���������� �� ������. dStart ��������� �������� ������ �������� ����� ������������ ������ ������.
void Painter_DrawDashedHLine(int y, int x0, int x1, int dFill, int dEmpty, int dStart);
///  ������ ����������� ������������ �����.
void Painter_DrawDashedVLine(int x, int y0, int y1, int dFill, int dEmpty, int dStart);
void Painter_DrawRectangle(int x, int y, int width, int height);
void Painter_FillRegion(int x, int y, int width, int height);
void Painter_DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);
/// ���������� ������� �������.
void Painter_SetBrightnessDisplay(int16 brightness);
uint16 Painter_ReduceBrightness(uint16 colorValue, float newBrightness);
/// ���������� ������ ������������ �����. ����� �������� ���� �� ������. y0y1 - ������ ������������ ���������.
void Painter_DrawVLineArray(int x, int numLines, uint8 *y0y1, Color color);
/// modeLines - true - �������, false - �������.
void Painter_DrawSignal(int x, uint8 data[281], bool modeLines);
void Painter_DrawPicture(int x, int y, int width, int height, uint8 *address);

#pragma once
#include "Colors.h"
#include "DisplayTypes.h"
#include "PainterText.h"
#include "PainterC.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void CalculateCurrentColor(void);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Display
 *  @{
 *  @defgroup Painter
 *  @brief Функции рисования
 *  @{
 */

/// Вызывается в начале отрисовки каждого кадра. Заполняет буфер цветом color
void Painter_BeginScene(Color color);
/// Вызывается в конце отрисовки каждого кадра. Переносит содержимое буфера на экран
void Painter_EndScene(void);
/// Послать изображение во внешнее устройство через USB или LAN. Если first == true, то посылается шрифт
void Painter_SendFrame(bool first);
/// Сброс таймера мигания. Нужно для того, чтобы мигающие значки при перемещении не исчезали с экрана
void Painter_ResetFlash(void);
/// Установить цвет рисования
void    Painter_SetColor(Color color);
/// Возвращает текущий цвет рисования
Color   Painter_GetColor(void);

void    Painter_LoadPalette(int num);
void    Painter_SetPalette(Color color);
void    Painter_SetPoint(int x, int y);
void    Painter_DrawHLine(int y, int x0, int x1);
void    Painter_DrawVLine(int x, int y0, int y1);
void    Painter_DrawHPointLine(int y, int x0, int x1, float delta);
void    Painter_DrawMultiVPointLine(int numLines, int y, uint16 x[], int delta, int count, Color color);
void    Painter_DrawMultiHPointLine(int numLines, int x, uint8 y[], int delta, int count, Color color);
void    Painter_DrawLine(int x0, int y0, int x1, int y1);
void    Painter_DrawDashedHLine(int y, int x0, int x1, int dFill, int dEmpty, int dStart);  // Рисует прерывистую горизонтальную линию. dFill - длина штриха, dEmpty - расст. между штрихами. Линия всегда начинается со штриха. dStart указывает смещение первой рисуемой точки относительно начала штриха.
void    Painter_DrawDashedVLine(int x, int y0, int y1, int dFill, int dEmpty, int dStart);  // Рисует прерывистую вертикальную линию.
void    Painter_DrawRectangle(int x, int y, int width, int height);
void    Painter_FillRegion(int x, int y, int width, int height);
void    Painter_DrawVolumeButton(int x, int y, int width, int height, int thickness, Color normal, Color bright, Color dark, bool isPressed, bool isShade);
void    Painter_SetBrightnessDisplay(int16 brightness);                                     // Установить яркость дисплея.
uint16  Painter_ReduceBrightness(uint16 colorValue, float newBrightness);
void    Painter_DrawVLineArray(int x, int numLines, uint8 *y0y1, Color color);              // Нарисовать массив вертикальных линий. Линии рисуются одна за другой. y0y1 - массив вертикальных координат
void    Painter_DrawSignal(int x, uint8 data[281], bool modeLines);                         // modeLines - true - точками, false - точками
void    Painter_DrawPicture(int x, int y, int width, int height, uint8 *address);

#if _USE_LFN > 0
void Painter_SaveScreenToFlashDrive(TCHAR *fileName);
#else
bool Painter_SaveScreenToFlashDrive(void);
#endif

void    Painter_SendToDisplay(uint8 *bytes, int numBytes);
void    Painter_SendToInterfaces(uint8 *pointer, int size);

#define WRITE_BYTE(offset, value)   *(command + offset) = (uint8)value
#define WRITE_SHORT(offset, value)  *((uint16*)(command + offset)) = (uint16)value

/** @} @}
 */

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "defines.h"
#include "DisplayPrimitives.h"
#include "Display/Painter.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProgressBar_Draw(const ProgressBar *bar)
{
    int x = bar->x;
    int y = bar->y;
    const int SIZE = 100;
    char buffer[SIZE] = {0};
    float passedPercents = bar->fullTime == 0 ? 0 : bar->passedTime / bar->fullTime * 100; //-V550
    snprintf(buffer, 100, "��������� %.1f %%", passedPercents);
    Painter_DrawStringInCenterRectC(x, y - 15, bar->width, bar->height, buffer, gColorFill);
    Painter_DrawRectangle(bar->x, bar->y, bar->width, bar->height);
    Painter_FillRegion(bar->x, bar->y, (int)(bar->width * passedPercents / 100.0f), bar->height);
    buffer[0] = 0;
    snprintf(buffer, 100, "�������� %.1f �", (int)(bar->fullTime - bar->passedTime) / 1000.0f);
    Painter_DrawStringInCenterRect(x, y + bar->height, bar->width, bar->height, buffer);
}

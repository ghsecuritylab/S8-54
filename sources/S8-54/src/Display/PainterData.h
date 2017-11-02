#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** @addtogroup Painter
 *  @{
 *  @defgroup PainterData
 *  @brief ������� ��������� ������
 *  @{
 */


class PainterData
{
public:
    /// ��������� ������� �� �������� ������.
    void DrawData(void);
    /// �������� ������� ���������
    void InterruptDrawing(void);
    /// ���������� ��������� �������������� �������
    void DrawMath(void);
};


extern PainterData painterData;


/** @}  @}
 */

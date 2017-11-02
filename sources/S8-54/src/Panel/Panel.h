#pragma once 
#include "defines.h"
#include "Panel/Controls.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @defgroup Panel 
 *  @brief ������ � ������� ����������
 *  @{
 */

class Panel
{
public:
    /// ������������� ����������� �����������
    void Init(void);
    /// ������� ����� �������� ������ ���� ��� ��������� ���������� � ������ ����� ������� ����������
    void Update(void);
    /// ��������/��������� �������� ������ �� �������
    void EnableLEDChannel(Channel ch, bool enable);
    /// ��������/��������� �������� ���������
    void EnableLEDRegSet(bool enable);
    /// ��������/��������� �������� �����
    void EnableLEDTrig(bool enable);
    /// �������� ������ � �� ����������
    void TransmitData(uint16 data);
    /// �������� ������ ����������
    /** ����� ������ ���������, �� ���������� ���� ���������� ��������� ���������� releasedButton */
    void Disable(void);
    /// �������� ������ ����������
    void Enable(void);
    /// ���������� ���������� �������
    bool ProcessingCommandFromPIC(uint16 command);
    /// ���������� ��������� ������, �������������� ��� �������� � ������, �� ������
    uint16 NextData(void);
    /// �������� ������� �������
    PanelButton WaitPressingButton(void);
    /// ��������� ������, ���� ���� ������ ������ �������
    void DisableIfNessessary(void);
};


extern Panel panel;


/**  @}
 */

#pragma once
#include "defines.h"
#include "Settings/SettingsTypes.h"
#include "Hardware/RTC.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup FPGA
 *  @{
 *  @defgroup DataStorage Data Storage
 *  @{
 */

class DataStorage
{
public:
    /// �������� ���� ���������� ���������.
    void Clear(void);
    /// �������� ��������� ������. ��� ���� ����������� ��������� ������� ��������� �������.
    void AddData(uint8 *dataA, uint8 *dataB, DataSettings dss);
    /// ���������� ����� ����������� ���������, ������� � ����������, � ������ �� �����������, ��� � ����������.
    int NumElementsWithSameSettings(void);
    /// ���������� ����� ����������� ���������, ������� � ����������, � �������� ����������� �������.
    int NumElementsWithCurrentSettings(void);
    /// ���������� ���������� ���������� ���������.
    int NumElementsInStorage(void);
    /// �������� ������. ���� ��� � �����. ������� ����� ��������� �� ������� ds, dataA, dataB..
    bool GetDataFromEnd(int fromEnd, DataSettings *ds, uint8 *dataA, uint8 *dataB);
    /// �������� ��������� �� ���������� ������. ������ �������� � ���.
    bool GetDataFromEnd_RAM(int fromEnd, DataSettings **ds, uint16 **dataA, uint16 **dataB);
    /// ��������� ���������, ������� ��������� �� ������ � ������ �������� ���. ������ � ������ �������������� �� ����������
    uint8 *GetData_RAM(Channel ch, int fromEnd);
    /// �������� ���������� ������ �� ���������� ����������
    uint8 *GetAverageData(Channel ch);
    /// ���������� ��������� �� ������, ��������� �� indexFromEnd o� ���������� �����������
    DataSettings *DataSettingsFromEnd(int indexFromEnd);
    /// �������� �������������� ����� ������� 0 - �����, 1 - ������
    bool GetLimitation(Channel ch, uint8 *data, int direction);
    /// ������� ��������� ����� ���� ��������� ��� ����� �� ����� ������, ��� � ���������� �����������
    int NumberAvailableEntries(void);

    //////////////////////////////// ������� ��� ����������� ������ ////////////////////////////////////////

    /// ������ � ��������� ����� ��� ��������� ���� �����.������ ����� ������ ����� �������� GetDataFromEnd_RAM(0...)
    void NewFrameP2P(DataSettings *dss);
    /// ��������� ��������� ��������� ����� � ���������� ���������� ��� ��� �����
    void AddPointsP2P(uint16 dataA, uint16 dataB);
    /// \brief �������� ������ ������ ����������� ������. ��������� ���������� ������ ����� �������� ������� GetDataFromEnd_RAM(1...). 
    /// ���������� ����� ���������� ����� (��� ����� ���� ������, ��� ���������� ����� � ������. � ���� ������ � ������ ��������� ��������� 
    /// numPointsInChan �����.
    int GetFrameP2P_RAM(DataSettings **ds, uint8 **dataA, uint8 **dataB);
};

extern DataStorage dS;

////////////////////////////// ������� ��� ��������� //////////////////////////////////////////////////

/** @}  @}
 */

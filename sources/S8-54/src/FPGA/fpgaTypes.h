#pragma once
#include "Hardware/FSMC.h"
#include "Settings/SettingsTypes.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup FPGA
 *  @{
 *  @defgroup FPGA_Types FPGA Types
 *  @{
 */

/// ����������� �������� �������� ������ �� ����������, ���������� � ���������� �����. ������������� �������� 10 ������ ���� �� ����������� �����
#define RShiftMin           100
/// ������� �������� �������� ������ �� ����������, ���������� � ���������� �����. ������������� ������������ ������ �� ������ ������
#define RShiftZero          32500
/// ������������ �������� �������� ������ �� ����������, ���������� � ���������� �����. ������������� �������� 10 ������ ����� �� ����������� �����
#define RShiftMax           64900
/// ������� ����� �������� � ����� ������
#define RSHIFT_IN_CELL (((RShiftMax) - (RShiftMin)) / 24)
/// �� ������� ������ ����� �������� �������� ��������, ����� ������ �������� �� ���������� ������������ �� ���� �����
#define STEP_RSHIFT ((RSHIFT_IN_CELL) / GRID_DELTA)
/// ����������� �������� ������ �������������, ���������� � ������
#define TrigLevMin  RShiftMin
/// ������������ ���������� ������ �������������, ���������� � ���������� �����
#define TrigLevMax  RShiftMax
/// ������� �������� ������ �������������, ���������� � ������. ������ ������������� ��� ���� ���������� �� ����� ������ � �������� �������� �� ����������
#define TrigLevZero RShiftZero
/// ����������� �������� �������� �� ������� ������������ ����� �������������, ���������� � �������
#define TShiftMax   16000
/// ��� �������� �������� �������, ��������� � ���, ������������� ������ �����. ���� �������� == 0, ������, ��� ���. ��� ����� ��� ������� ������������� � ����������� ������ p2p, � ����� ��� tShift ����� ���������� �������
#define AVE_VALUE   128
/// ��� �������� �������� �������, ��������� � ���, ������������� ������ ������� ����� (-5 ������ �� ������). ���� �������� == 0, ������, ��� ���. ��� ����� ��� ������� ������������� � ����������� ������ p2p, � ����� ��� tShift ����� ���������� �������
#define MIN_VALUE   (AVE_VALUE - 125)
/// ��� �������� �������� �������, ��������� � ���, ������������� ������� ������� ����� (+5 ������ �� ������)
#define MAX_VALUE   (AVE_VALUE + 125)
/// ���� �������� == 0, ������, ��� ���. ��� ����� ��� ������� ������������� � ����������� ������ p2p, � ����� ��� tShift ����� ���������� �������
#define NONE_VALUE  0
/// ������� ����� ���������� �� ������ �� ������� �� ������ �������
#define POINTS_IN_SCREEN_VERT ((MAX_VALUE) - (MIN_VALUE))
/// ����������� ������� �� �������, ��� ������� �������� ��������� ������ �������� ���������
#define MIN_TBASE_PEC_DEAT  TBase_500ns
/// � ����� �������� tBase ������ ���������� ����� ����������� ������
#define MIN_TBASE_P2P       TBase_50ms
/// ������� ����� ����� �������� ������ �� ���������� ������ �� ���� ���������
#define FPGA_MAX_POINTS     16384

#define WR_START        ((uint16 *)(ADDR_FPGA + (0x00 << 1)))    ///< ������ ����� ���������. ��� ������� ����� �������� 1
#define WR_RAZV         ((uint16 *)(ADDR_FPGA + (0x01 << 1)))
#define WR_PRED         ((uint16 *)(ADDR_FPGA + (0x02 << 1)))
#define WR_POST         ((uint16 *)(ADDR_FPGA + (0x03 << 1)))
#define WR_TRIG         ((uint16 *)(ADDR_FPGA + (0x04 << 1)))
#define WR_UPR          ((uint16 *)(ADDR_FPGA + (0x05 << 1)))
#define UPR_BIT_PEAKDET            1    ///< ������� �������� - 0/1 ����/���
#define UPR_BIT_CALIBRATOR_AC_DC    2   ///< ����������/����������
#define UPR_BIT_CALIBRATOR_VOLTAGE  3   ///< 0/4�
#define UPR_BIT_RECORDER            4   ///< 0 - ������� �����, 1 - �����������
#define WR_ADDR_NSTOP   ((uint16 *)(ADDR_FPGA + (0x06 << 1)))
#define WR_FL_RESET     ((uint16 *)(ADDR_FPGA + (0x08 << 1)))
#define WR_RESET        ((uint16 *)(ADDR_FPGA + (0x1f << 1)))

#define RD_ADC_A        ((uint16 *)(ADDR_FPGA + (0x00 << 1)))
#define RD_ADC_B        ((uint16 *)(ADDR_FPGA + (0x02 << 1)))

#define RD_ADDR_NSTOP   ((uint16 *)(ADDR_FPGA + (0x08 << 1)))
/*
    �������� ����������������� ������ �������
    1. ������� RD_ADDR.
    2. ������� ����� 1.
    3. �������� RD_ADDR � ���������� � ������ ����.
    4. �������� � WR_ADDR ����� �����.
    5. ������� ����� 2.

    ��������� ��� 32� 1-�� ������
    �  ������� ����������� �������� 8192 �� 16384
*/

#define WR_FREQ_METER_PARAMS    ((uint16 *)(ADDR_FPGA + (0x0a << 1)))

#define RD_FREQ_LOW             ((uint16 *)(ADDR_FPGA + (0x10 << 1)))
#define RD_FREQ_HI              ((uint16 *)(ADDR_FPGA + (0x18 << 1)))
#define RD_PERIOD_LOW           ((uint16 *)(ADDR_FPGA + (0x20 << 1)))
#define RD_PERIOD_HI            ((uint16 *)(ADDR_FPGA + (0x28 << 1)))

#define RD_FL                   ((uint16 *)(ADDR_FPGA + (0x30 << 1)))  
#define FL_DATA_READY       0   ///< 0 - ������ ������
#define FL_TRIG_READY       1   ///< 1 - ������� ��������������
#define FL_PRED_READY       2   ///< 2 - ��������� ����� �����������
#define FL_POINT_READY      3   ///< 3 - ������� ����, ��� ����� ������ (� ���������� ������)
#define FL_FREQ_READY       4   ///< 4 - ����� ��������� �������
#define FL_PERIOD_READY     5   ///< 5 - ����� ��������� ������
#define FL_LAST_RECOR       6   ///< 6 - ������� ��������� ������ - ����������, ����� ��� ������� ������
#define FL_OVERFLOW_FREQ    8   ///< 8 - ������� ������������ �������� �������
#define FL_OVERFLOW_PERIOD  9   ///< 9 - ������� ������������ �������� �������


extern uint16 *addressesADC[NumChannels];
#define ADDRESS_READ(ch)    addressesADC[ch];


/** @}  @}
 */

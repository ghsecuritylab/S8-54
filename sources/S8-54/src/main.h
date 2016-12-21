/** @file
  * @version V0.1
  * @date 14-March-2014
  * @brief ����� ����� - ������������� � ������� ����
  * @verbatim
  *
  * ����� ����� ��������
  *
  * @note
  * ��� ���������� ����������� MDK5.11.1.0 � �������������� ��������
  *     ARV CMSIS 4.1.4
  *     Keil MDK-Middleware 6.1.0
  *     Keil STM32F2xx_DFP 1.0.7
  *
  * ���������� � ������������
  * � ��������, ������ � ������� ��������� �� ������ ���������, ����������� ������� �� ������ �������������. ��������, Display_.
  * �������, ������������ ������ ������ ��������/����������, ������ �������� �� �����.
  * ������� ����������/������ �������� (���������� SSettings) ���������� � Get/Set/Inc/Dec/Add/Sub/Is. ��� �� ������ �� ��������� �������, 
  * ������ ������ ��� ������/������ ��������. ����������� �������� ������� SetIncreaseSmoothlyRange(), SetDecreaseSmoothlyRange(). ��� �������� FPGA_SetRange().
  *
  c:\Keil_v5\ARM\Pack\ARM\CMSIS\4.1.1\CMSIS\Include\
  c:\Keil_v5\ARM\Pack\Keil\STM32F2xx_DFP\1.0.7\Device\Include\

  * @endverbatim
  */ 

/*
���������� ���� � ���� �������
1.  ������ CDC_Standalone �� STM32Cube V1.1.0 ������� ���������� �� 
    ������� ��� ���������� � startup_stm32f217xx.s � ����� ����������
    c startup_stm32f207xx.s, �� � ���� ������, ���� ���������� � ������������,
    ��������� ��������� ��������� ������ 10 � ������ � ����������� ����
    ����������.
    ������������ ��������, ��� � startup_stm32f217xx.s
    Stack_Size �������� �� 0x2000, � Heap_Size - �� 0x4000. ��� ���� �����
    ��������� ���������� � � startup_stm32f207xx.s
2.The ST's USBD_CDC_TransmitPacket() function contains a bug: it sets the 
    'transmission in progress' flag AFTER starting the actual transmission,
    so if the 'transmission done' interrupt happens too early, the flag will
    be set AFTER the interrupt and hence will never be cleared. To fix this,
    move "hcdc->TxState = 1" line before the call to USBD_LL_Transmit():
        if(hcdc->TxState == 0) {
            hcdc->TxState = 1;
            USBD_LL_Transmit(pdev, CDC_IN_EP, hcdc->TxBuffer,
            hcdc->TxLength);
            return USBD_OK;
        }
*/
  
  
  // ����� WARN � ����������� �������� ������ � ����.
  // ����� BUG �������� ������ � ����.

#pragma once

#include "Settings/Settings.h"

#include <usbd_desc.h>
#include <usbd_cdc.h>
#include <usbd_cdc_interface.h>

/* MAC ADDRESS: MAC_ADDR0:MAC_ADDR1:MAC_ADDR2:MAC_ADDR3:MAC_ADDR4:MAC_ADDR5 */
// 00 13 8f af 2e 8b
// #define MAC_ADDR0   0x8b
// #define MAC_ADDR1   0x2e
// #define MAC_ADDR2   0xaf
// #define MAC_ADDR3   0x8f
// #define MAC_ADDR4   0x13
// #define MAC_ADDR5   0x00

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
// 192.168.1.92
#define IP_ADDR0   set.eth.ip0
#define IP_ADDR1   set.eth.ip1
#define IP_ADDR2   set.eth.ip2
#define IP_ADDR3   set.eth.ip3

/*NETMASK*/
#define NETMASK_ADDR0   set.eth.mask0
#define NETMASK_ADDR1   set.eth.mask1
#define NETMASK_ADDR2   set.eth.mask2
#define NETMASK_ADDR3   set.eth.mask3

/*Gateway Address*/
#define GW_ADDR0   set.eth.gw0
#define GW_ADDR1   set.eth.gw1
#define GW_ADDR2   set.eth.gw2
#define GW_ADDR3   set.eth.gw3

#define MII_MODE

/* Uncomment the define below to clock the PHY from external 25MHz crystal (only for MII mode) */
#ifdef 	MII_MODE
#define PHY_CLOCK_MCO
#endif


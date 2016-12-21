
/*!*****************************************************************************
 @file		Siluet_main.h
 @author	��������� �.�.
 @date		2012.09
 @version	V0.5
 @brief		Siluet CPU main header
 @details	�����������, ������������ � �������
 @note		STM32F207ZC, 120 MHz, 256K Flash, 112K + 16K RAM, 4K Backup 
 @note		1 cycle = 8.33 ns, 3 cycles = 25 ns
 @note		ExtMem 256Kx16 (512KB)
 *******************************************************************************/

#ifndef MAIN_H				// �������� ���� ������ ���� ���
#define MAIN_H

/*__ ���������� ����������� �������� __________________________________________*/

/* ��� ���������������� (����� ������ � ��������� �������) */
// #define STM32F2XX

/* ��������� 8 MHz */
// #define HSE_VALUE ((uint32_t)8000000)

// ������ ���������, ��� ���������
#define MANUFACT "�����"
#define VERSION "1.0"


/* ������������� ��������� ������������ ��� ������� ��������� */

/* External RAM - IS62WV25616BLL-55T 256K x 16 Ultra Low Power CMOS SRAM */
#define XRAM_BASE	0x64000000UL	//!< ��������� ����� �������� ���
#define XRAM_SIZE	0x80000UL	//!< ������ �������� ��� (� ������)

/* FPGA - ������ ���� (16-������� ����, A25:A1 �������� � AB24:AB0)
 16 16-������� ���������, �������������������� ���� ����� / ������ */
#define	PL_BASE		((uint32_t)0x68000000)	//!< FPGA base address

/* LCD Controller - S1D13706 */
#define DPYCTRL_BASE	((uint32_t)0x6C000000)	//!< Dysplay base address

/*! ����� ��� �� ������� ������ */
#define	DPYBUF_BASE	(XRAM_BASE + XRAM_SIZE - DPYMEM_SIZE)
// #define DPYMEM	DPYMEM_BASE	// ������������ ���������� ������ ���
// #define DPYMEM	DPYBUF		// ������������ ����� ��� �� ������� ������


/* ����������� ��� �������� ���������� */

// #define LED_TEST
// #define BLINK_TEST
// #define DISPLAY_TEST
// #define SIGNAL_TEST
// #define MARKS_DRAW
// #define SWEEP_TEST		// ���� ������������ ���������
// #define BKG_GRAY		// ����� ��� ��� �������
#define TRIGDIV_USE		// ������������ �������� �������������
#define INVPOS_USE		// ������������ �������� �������
// #define SICUBE		// ���������� ������������
#define SILINE			// �������� ������������
#define STRA_VECT		// ������ �������
#define MATH_USE		// ���������� (�����, ������������, ���)
// #define USE_USB_INTERFACE
// #define USE_SCPI


/*__ ������������ ����� ����������� ___________________________________________*/

#include "stm32f2xx.h"		// ����������� ��������� � �����
#include <stdbool.h>		// bool, true, false
#include <math.h>		// sin, cos
#include <stdlib.h>		// rand
// #include <stdio.h>		// printf
#include "cmsis_os.h"		// CMSIS-RTOS RTX

#ifdef USE_USB_INTERFACE
  #include "usb_add_module.h"	// USB
#endif


/*__ ���������� ���� ������ ___________________________________________________*/

/*!*****************************************************************************
 @brief		Setup variable declaration macros
 @note		�����, ����� ���������� ������������ � ������������������ ���� �������
		� ����� ����� (xx_main.c) ������������ VAR_DECLS ����� �������������� xx_main.h
		� ��������� ������ ������������ xx_main.h, ������� ���������� - extern
 */
#ifndef VAR_DECLS
#define _DECL extern
#define _INIT(x)
#else
#define _DECL
#define _INIT(x) = x
#endif

/*__ ���������� ������������ __________________________________________________*/

/*!*****************************************************************************
 @brief		Define bits through bit-banding
 @details	����������� ����� ������������ ��������� ����� bit-band alias
 @param		VarPtr - ��������� �� ������� ��������� ������������� ����������
 @param		BitNum - ����� ���� � �������� ���������
 @note		������������ ALIAS_PTR ��� ������������ ��������� ����������������
 */
#define ALIAS(VarAddr, BitNum) \
  *((volatile uint32_t *) ((VarAddr & 0xF0000000) | 0x02000000 \
  + ((VarAddr & 0xFFFFF) <<5) | (BitNum <<2)))

#define ALIAS_PTR(VarPtr, BitNum) \
  *((volatile uint32_t *) (((uint32_t) &(VarPtr) & 0xF0000000) | 0x02000000 \
  + (((uint32_t) &(VarPtr) & 0xFFFFF) <<5) | (BitNum <<2)))


/*! ���������������� ���������� � �������� 0...MAX */
#define INC_MAX(Var, MAX)  Var = (Var == MAX)? 0 : Var + 1

/*! ���������������� ���������� � �������� 0...MAX */
#define DEC_MAX(Var, MAX)  Var = (Var == 0)? MAX : Var - 1 


/*__ ���������� ���������� ____________________________________________________*/

// DECL uint32_t Temporal;		// ��������� ���������� ��� ������ � ������

/// DECL volatile uint32_t Temporal INIT(0);
// _DECL volatile uint32_t Test _INIT(0);
/* ������ �������� � 1 ms ����������, ���������������� �� ���������� SysTick */
/// _DECL volatile uint32_t TimerTicks _INIT(0);
/// _DECL bool PL_Ready _INIT(false);		// ���� ����������������
// DECL uint16 * TestWord INIT(EXTRAM_START);	// �������� �����


/// extern osThreadId	Main_id;	//!< ��������� �� ������ main
/// extern osMutexId	MutDpy_id;	//!< ��������� �� �������

/*__ ������������ ����� ������� _______________________________________________*/

#include "s1d13706.h"
#include "Siluet_Control.h"
#include "Siluet_Display.h"
#include "Siluet_Interface.h"
#include "Siluet_Signal.h"
#ifdef USE_SCPI
  #include "SCPI_include.h"
#endif

#endif

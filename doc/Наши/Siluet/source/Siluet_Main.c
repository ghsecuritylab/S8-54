
/*!*****************************************************************************
 @file		Siluet_main.c
 @author	��������� �.�.
 @date		2012.10 - 2013.09
 @version	V1.0
 @brief		Siluet CPU main program
 @details	����������� ������
 @note		STM32F207ZC
 *******************************************************************************
 @verbatim
 ����������� ��������� �������� � Backup RAM
 
 Main ������ ���������� ������� ����������� �� ���������
 Display ������ �������
 ��������������� ����������� ���������� ������ Meas 
 
 @endverbatim
 *******************************************************************************/
 
#define VAR_DECLS		// ����� ����� ��������� ����������

/*__ ������������ ����� _______________________________________________________*/

#include "Siluet_Main.h"	// ��� ��������� ������ � ����� �����

#ifdef USE_USB_INTERFACE
// global struct with device type
USB_OTG_CORE_HANDLE    USB_OTG_dev;
#endif	// USE_USB_INTERFACE

#ifdef	USE_SCPI
extern Ring_Buffer_TypeDef RingRxBuffer;
#endif	// USE_SCPI

/*__ ��������� ������� ________________________________________________________*/

void Panel_thread(void const *argument);
void Signal_thread(void const *argument);
void Meas_thread(void const *argument);
#ifdef	USE_SCPI
void SCPI_thread(void const *argument);
#endif	// USE_SCPI


/*__ ���������� _______________________________________________________________*/


/* ��������� �� ������ (�������������� �����) */
osThreadId	Main_id;	//!< ��������� �� ������ main
osThreadId	Panel_id;	//!< ��������� �� ������ Panel_thread
osThreadId	Signal_id;	//!< ��������� �� ������ Signal_thread
osThreadId	Meas_id;	//!< ��������� �� ������ Meas_thread
#ifdef	USE_SCPI
osThreadId	SCPI_id;	//!< ��������� �� ������ SCPI_thread
#endif	/* USE_SCPI */

/* ����������� ����� (���������)
   osThreadDef(name, priority, instances, stacksz) */
// osThreadDef(Panel_thread, osPriorityNormal, 1, 0);
osThreadDef(Panel_thread, osPriorityAboveNormal, 1, 0);
// osThreadDef(Panel_thread, osPriorityNormal, 1, 400);
// osThreadDef(Signal_thread, osPriorityBelowNormal, 1, 0);
// osThreadDef(Signal_thread, osPriorityNormal, 1, 0);
// osThreadDef(Signal_thread, osPriorityHigh, 1, 512);
osThreadDef(Signal_thread, osPriorityAboveNormal, 1, 512);
osThreadDef(Meas_thread, osPriorityAboveNormal, 1, 0);
#ifdef	USE_SCPI
osThreadDef(SCPI_thread, osPriorityAboveNormal, 1, 0);
#endif	/* USE_SCPI */

/* ������� ������� � ������ ���������� */
osMutexDef	(MutexDpy);	//!< ��� ��������
osMutexId	MutDpy_id;	//!< ��������� �� �������


/*__ ���������� ������� _______________________________________________________*/

/*!*****************************************************************************
 @brief		Main thread
 @details	�������� ������ - ���������������� ����������
 @param	
 @return	
 @note		����� ���������� ������ ������������
 */
int32_t main(void) {

/* ���������������� ����������� ��������������� */
  MCU_init();
 
/* ��������� ������� ��� */
//  XRAM_test();
//  if (ErrorState == ERROR_XRAM) Led_blink(62500);	// 8 ��� � ���
  
/* �������� ������ ����������� ��� (������ ������ ������)
   ��� ����� �� ������ ����� ���
   ��� ��������� ����������� � ���������, ������� ������� �� ����� */
//  LcdMem_clear();

/* ���������������� ���������� ��� */  
  LcdCtrl_init();

#ifdef DISPLAY_TEST
  LcdMem_test();
  if (ErrorState == ERROR_DPY) Led_blink(125000);	// 4 ���� � ���
#endif

/* ��������� ������������� ������! */
  if (SFMID_read() != M25PE40ID) {
    ErrorState = ERROR_SFM;
    Led_blink(250000);					// 2 ���� � ���
  }
  
/* ������������ ����
   ����� ��������� ���� ��������� � ��������� POR � ������ STATUSn ������
   4 ������� ������������ ���� */
  for (uint32_t trials = 4; trials--; ) {
    ErrorState = PL_config();
    if (ErrorState == ERROR_NONE) break;
  }
  
/* ��� ���� ����� �������� ����� Config_Done � User_Mode 650 �s
   �������� ������ ������ ��� */
  DpyScreen_blank();
  
/* ���� ���� �� ������������������, �� ������� ���� �� ��������
   ���� ��� ���� ������������, ������ ��������� */
///  if (ErrorState == ERROR_CONF) Led_blink(500000);	// 1 ��� � ���
  if (ErrorState == ERROR_CODE || ErrorState == ERROR_CONF) LED_ON();
/* ���������������� �������� ����, ���� ���������������� */ 
  else PL_init();		// ���� �� ����� ����������������  

/* ������������ ��������� �������� � ������� */
  Balance_init();
  
/* ���������������� ������ ���������� */
  Ctrl_init();

/* ������ ��������� �������� � ���������� ������ */
  AnaReg_send();
  // ANADAC(DAC_CHAN1, Chan1Ctrl.SigPos << 2);
  // FpPos1_hand(0);
  // ANADAC(DAC_CHAN2, Chan2Ctrl.SigPos << 2);
  // FpPos2_hand(0);
  ANADAC(DAC_LEVEL, TrigCtrl.Level << 2);

/* ������� ����������� �������� ������������� */
  uint32_t tmts = SFMWord_read(SFMINTERP);
  if (~tmts) {
    Interp.Tmts = tmts;
    Interp.Tmad = SFMWord_read(SFMINTERP + 4);
  }
 
/* ��������� ����� ��� �� ������� ������ */
#ifdef BKG_GRAY
  DpyRect_fill(DPYPOS(0, 0), 320, 240, 0x0000FF20);	// �������� ��� (�����)
#endif
  Manufact_draw();		// �������� ��� �������������
  DpyScale_draw();		// ���������� �����
  MemBar_draw();
  MemBarPret_draw(true);
  MemBarPos_draw(true);
  MemSizeBuf_disp();
  Chan1St_disp();
  Chan2St_disp();
  TimeSt_disp();
  SweepSt_disp();
  TrigSt_disp();

#ifdef MARKS_DRAW
/* ���������� ������� � ����� ������ */
  DpyRect_fill(DPYPOS(0,       0),       2, 2, 0x0000FFFC);
  DpyRect_fill(DPYPOS(320 - 2, 240 - 2), 2, 2, 0x0000FFF3);
#endif
  
#ifdef SIGNAL_TEST
/* ��������� ������ �������� ��������� ��������� */
  SigChanAC_load();			// ��������� ����� ������� � ���������
//  SigChanDC_load();			// ��������� ����� ���������� �����������
  SigChans_redraw();
#endif

  PosChans_redraw();
  TrigLev_draw(true);
  Pret_draw(true);
  
  DpyBuf2Mem_copy(0, 320 * 240);


  


/* ������ (� ��������) ��������� �������������, ������������ */
  if (PL->STAT & PL_STAT_TRIGDET)	// ���� ���� �������������
    PanCtrl.TxBuf &= ~(1 << 4);		// ������ ���� �������������
  else
    PanCtrl.TxBuf |=  (1 << 4);		// �������� ���� �������������
  PanCtrl.TxBuf |= 0x40;
  USART3->DR = PanCtrl.TxBuf;		// ������� � ������

/* ������ ������� ��������� */  
  Sweep_init();

#ifdef	USE_USB_INTERFACE
//* ������������ USB ���������   *//
	USBD_Init(&USB_OTG_dev, USB_OTG_HS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
#endif	/*	USE_USB_INTERFACE	*/

/* ������ ������������� ������ */
  Main_id = osThreadGetId();
  osThreadSetPriority(Main_id, osPriorityAboveNormal);
  
  MutDpy_id = osMutexCreate(osMutex(MutexDpy));
  
/* ������ �������������� ������ ����� */
  Panel_id = osThreadCreate(osThread(Panel_thread), NULL);
#ifdef	USE_SCPI
	SCPI_id = osThreadCreate(osThread(SCPI_thread), NULL);
#endif	/* USE_SCPI	*/

  if (ErrorState != ERROR_CODE || ErrorState != ERROR_CONF) {
    Signal_id = osThreadCreate(osThread(Signal_thread), NULL);
    Meas_id = osThreadCreate(osThread(Meas_thread), NULL);
  }

  osDelay(100);
  
// �������� PWM
  *(uint16_t *)PWMCVCONF |= 0x10;

/* Main task Superloop */
  for ( ; ; ) {
    // IWDG->KR =  0xAAAA;		// Reload Independent Whatchdog Timer  
    osSignalWait(0, osWaitForever);	// ������� ������ ������� �� �����
//    LED_ON();
    osMutexWait(MutDpy_id, osWaitForever);
    DpyBuf2Mem_copy(0, 320 * 240);
    osMutexRelease(MutDpy_id);
//    LED_OFF();
    // osDelay(100);			// �������� �� 100 ms
    // osDelay(50);			// �������� �� 50 ms
  }

}


/*__ ������ ___________________________________________________________________*/


/*!*****************************************************************************
 @brief		Panel thread
 @details	���������� ������ ����������
 @param		
 @return	
 @note	
 */
void Panel_thread(void const *argument) {
  for ( ; ; ) {
    osSignalWait(0, osWaitForever);	// ������� ������ �� ���������
    // osSignalClear(Main_id, 1);
    osMutexWait(MutDpy_id, osWaitForever);
    Panel_Process();
    osMutexRelease(MutDpy_id);
///    osSignalSet(Display_id, 1);
    osSignalSet(Main_id, 1);  		// ������ �� ���������
  }
}


/*!*****************************************************************************
 @brief		Signal Service task
 @details	������ ��������� �������
 @param		
 @return	
 @note	
 */
#if false
void Signal_thread(void const *arguments) {
  for ( ; ; ) {
    if (!PLIRQ_GET()) {			// ������� ������ ����������
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      if (stat & PL_STAT_TDTIF) {	// ���� ���� ���������� �� ���������...
        if (stat & PL_STAT_TRIGDET)	// ���� ���� �������������
	  PanCtrl.TxBuf &= ~(1 << 4);	// ������ ���� �������������
	else
	  PanCtrl.TxBuf |=  (1 << 4);	// �������� ���� �������������
        PanCtrl.TxBuf |= 0x40;
        USART3->DR = PanCtrl.TxBuf;	// ������� � ������
      }
/* ���� ��� ����� � ���� ����� ����� ��� ����� */
      if (!SweepCtrl.Stop && stat & (PL_STAT_FRMIF | PL_STAT_DOTIF)) {
        osMutexWait(MutDpy_id, osWaitForever);
        Sweep_exe();
        // Math_exe();
	// XYDots_draw(true);
        osMutexRelease(MutDpy_id);
//	if (MeasCtrl.On) {
//	  osMutexWait(MutDpy_id, osWaitForever);
//	  SigPar_meas();			// ��������� (���� ����)
//	  osMutexRelease(MutDpy_id);
//	  osDelay(200);				// 5 ��� � ���
//	}
        if (MeasCtrl.On) osSignalSet(Meas_id, 1);
        osSignalSet(Main_id, 2); 
      }
    }					// if PLIRQ
  }					// for (;;)
}
#endif

void Signal_thread(void const *arguments) {
  for ( ; ; ) {
    osSignalWait(0, osWaitForever);	// ����� ������ �� ����
    uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    if (stat & PL_STAT_TDTIF) {		// ���� ���� ���������� �� ���������...
      if (stat & PL_STAT_TRIGDET)	// ���� ���� �������������
        PanCtrl.TxBuf &= ~(1 << 4);	// ������ ���� �������������
      else
	PanCtrl.TxBuf |=  (1 << 4);	// �������� ���� �������������
      PanCtrl.TxBuf |= 0x40;
      USART3->DR = PanCtrl.TxBuf;	// ������� � ������
    }
/* ���� ��� ����� � ���� ����� ����� ��� ����� */
    if (!SweepCtrl.Stop && stat & (PL_STAT_FRMIF | PL_STAT_DOTIF)) {
      osMutexWait(MutDpy_id, osWaitForever);	// ����� ������������ ��������
      Sweep_exe();
      // Math_exe();
      // XYDots_draw(true);
      osMutexRelease(MutDpy_id);
      if (MeasCtrl.On) osSignalSet(Meas_id, 0x00000001);
      osSignalSet(Main_id, 0x00000002); 
    }
  }					// for (;;)
}



/*!*****************************************************************************
 @brief		Signal Measure task
 @details	������ �������������� ��������� �������
 @param		
 @return	
 @note	
 */
void Meas_thread(void const *arguments) {
  for ( ; ; ) {
    osSignalWait(0, osWaitForever);	// ������� ������ �� ���������
    osDelay(200);			// � ms! 5 ��� � ���  
    osMutexWait(MutDpy_id, osWaitForever);
    SigPar_meas();			// ���������
    osMutexRelease(MutDpy_id);
    osSignalSet(Main_id, 1);      
  }
}

#ifdef	USE_SCPI
/*!*****************************************************************************
 @brief		SCPI task
 @details	������ ������� ������, �������� ����� ������� ���������
 @param		
 @return	
 @note	
 */
void SCPI_thread(void const *arguments) {
  for ( ; ; ) {
		osEvent RcvdSignal;
		RcvdSignal = osSignalWait(0, osWaitForever);
	  osMutexWait(MutDpy_id, osWaitForever);
#ifdef	USE_RING_BUFFER	
  do {
    SCPI_ParseOneCommandFromBuffer( &RingRxBuffer);
  } while (CorrectRingBufferIndexes(&RingRxBuffer));
#else
  SCPI_ParseOneCommandFromBuffer(USB_Rx_Buffer.Data);
#endif /* USE_RING_BUFFER */
   // ho-ho, here will be cucle for calling   SCPI_ParseOneCommandFromBuffer() till ringbuffer will not be empty.
	 // also here should be some trigger for starting & stoping parsing process.
	 osMutexRelease(MutDpy_id);
  }
}
#endif	/* USE_SCPI	*/


/*__ ����������� ���������� ___________________________________________________*/


/*!*****************************************************************************
 @brief		NonMaskable Interrupt Handler
 @details	�������� ���� ���������� CSS
 @param		none
 @return	
 @note	
 */
void NMI_Handler(void) {
  RCC->CIR |= RCC_CIR_CSSC;
}

/*!*****************************************************************************
 @brief		HardFault Handler
 @details	���������� ����������, ������ ����� �������, �� ������� ��������
 @param		none
 @return	
 @note		� �������� ���������
 */
__asm void HardFault_Handler(void) {
  TST LR, #4 
  ITE EQ 
  MRSEQ R0, MSP				; Main Stack was used, put MSP in R0
  MRSNE R0, PSP				; Process Stack was used, put PSP in R0
  LDR R0, [R0, #24]			; Get stacked PC from stack

  LDR R1, =0x40020418			; GPIOB->BSRR
  MOVS R2, #0x0002			; Bit 2
  STRH R2, [R1, #2]			; Reset bit (LED_ON)
  B .
}

/*!*****************************************************************************
 @brief		HardFault generate 
 @details	������� �������������� ������� (��� ��������)
 @param		none
 @return	
 @note		Create unaligned multiple load/store
 */
__asm void HardFault_generate(void) {
  MOVS R0, #1
  LDM R0, {R1-R2}
  B .
}

/*!*****************************************************************************
 @brief		USART3 Receive IRQ Handler
 @details	���������� ���������� �� ������ ���������� �� USART3
 @param		none
 @return	
 @note		LSB ���������� ������
 */
void USART3_IRQHandler(void) {
  uint8_t tmp = USART3->DR;		// ��������� �������� ��������� �����
  if (PanCtrl.First) {			// ���� ������ ���� ���������
    PanCtrl.RcBuf[1] = tmp;		// �������� ������ ����
    PanCtrl.Ready = 1;			// ��������� ������� - ������
    PanCtrl.First = 0;			// ����� ������� ����� ��������� �������
    osSignalSet(Panel_id, 1);
  }
  else {				// ���� ��� ������� ����� ���������
    if (tmp < 32) {			// ���� ����� ������ ����������
      PanCtrl.RcBuf[0] = tmp;		// �������� ������ ����
      PanCtrl.First = 1;		// ������ ���� ������
      PanCtrl.Ready = 0;		// �� ������ ������ "�� ������"
    }
  }
}

#ifdef	USE_SCPI
/*!*****************************************************************************
 @brief		USART2 Receive IRQ Handler
 @details	���������� ���������� �� ���������� RS-232
 @param		none
 @return	
 @note		
 */
void USART2_IRQHandler(void) {
  uint8_t tmp = USART3->DR;
  RING_BUFF_WRITE(RingRxBuffer, tmp);
  RingRxBuffer.source = RS232;
  if(!tmp) osSignalSet(SCPI_id, 1);
}
#endif	/* USE_SCPI */

/*!*****************************************************************************
 \brief		EXTI9_5 IRQ Handler
 \note		����� ���������� ��� ���������� ���������� ����������!
 */
void EXTI9_5_IRQHandler(void) {
  osSignalSet(Signal_id, 0x00000001);
  EXTI->PR = EXTI_PR_PR7;	// Clear pending bit
}


#if false
/*!*****************************************************************************
 @brief		printf remap
 @param		none
 @return	
 @note		
 */
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}
#endif

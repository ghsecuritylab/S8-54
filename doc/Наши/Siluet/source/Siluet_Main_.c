
/*!*****************************************************************************
 @file		Siluet_main.c
 @author	��������� �.�.
 @date		2012.10
 @version	V0.5
 @brief		Siluet CPU main program
 @details	����������� ������
 @note		STM32F207ZC
 *******************************************************************************/

#define VAR_DECLS		// ����� ����� ��������� ����������

/*__ ������������ ����� _______________________________________________________*/

#include "Siluet_Main.h"	// ��� ��������� ������ � ����� �����

/*__ ��������� ������� ________________________________________________________*/

void Panel_thread(void const *argument);
// void Display_thread(void const *argument);
void Signal_thread(void const *argument);
void Meas_thread(void const *argument);

/*__ ���������� _______________________________________________________________*/

/* ��������� �� ������ (�������������� �����) */
osThreadId	Main_id;	//!< ��������� �� ������ main
osThreadId	Panel_id;	//!< ��������� �� ������ Panel_thread
// osThreadId Display_id;	//!< ��������� �� ������ Display_thread
osThreadId	Signal_id;	//!< ��������� �� ������ Signal_thread
osThreadId	Meas_id;	//!< ��������� �� ������ Meas_thread

/* ����������� ����� (���������)
   osThreadDef(name, priority, instances, stacksz) */
// osThreadDef(Panel_thread, osPriorityNormal, 1, 0);
osThreadDef(Panel_thread, osPriorityAboveNormal, 1, 0);
// osThreadDef(Display_thread, osPriorityAboveNormal, 1, 0);
// osThreadDef(Signal_thread, osPriorityBelowNormal, 1, 0);
osThreadDef(Signal_thread, osPriorityNormal, 1, 0);
osThreadDef(Meas_thread, osPriorityNormal, 1, 0);


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
// while (1)
  LcdMem_test();
  if (ErrorState == ERROR_DPY) Led_blink(125000);	// 4 ���� � ���
#endif

/* ��������� ������������� ������! */
  if (SFMID_read() != M25PE40ID) {
    ErrorState = ERROR_SFM;
    Led_blink(250000);					// 2 ���� � ���
  }
  
/* ������������� (������������) ����
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
  else PL_init();			// ���� �� ����� ����������������  

/* ��������� ����� ��� �� ������� ������ */
#ifdef BKG_GRAY
  DpyRect_fill(DPYPOS(0, 0), 320, 240, 0x0000FF20);	// �������� ��� (�����)
#endif
  MNIPI_draw();
  DpyScale_draw();			// ���������� �����
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
  Pret_draw(1);
  
  DpyBuf2Mem_copy(0, 320 * 240);

  
/* ������ ��������� �������� � ���������� ������ */
  AnaReg_send(); 
  ANADAC(DAC_CHAN1, Chan1Ctrl.SigPos << 2);
  ANADAC(DAC_CHAN2, Chan2Ctrl.SigPos << 2);
  ANADAC(DAC_LEVEL, TrigCtrl.Level << 2);

/* ������� ����������� �������� ������������� */
  uint32_t tmts = SFMWord_read(SFMINTERP);
  if (~tmts) {
    Interp.Tmts = tmts;
    Interp.Tmad = SFMWord_read(SFMINTERP + 4);
  }
  
/* ������� ����������� ������ ������� */
  SFMRead_start(SFMBAL1);
  Bal1Ctrl.Ofs20DC = SFMByte_read();
  Bal1Ctrl.Ofs20AC = SFMByte_read();
  Bal1Ctrl.Ofs10DC = SFMByte_read();
  Bal1Ctrl.Ofs10AC = SFMByte_read();
  Bal1Ctrl.Ofs5DC = SFMByte_read();
  Bal1Ctrl.Ofs5AC = SFMByte_read();
  Bal1Ctrl.Ofs5GND = SFMByte_read();
  Bal1Ctrl.Ofs2DC = SFMByte_read();
  Bal1Ctrl.Ofs2AC = SFMByte_read();
  Bal1Ctrl.Ofs2GND = SFMByte_read();
  SFMRead_stop();

  SFMRead_start(SFMBAL2);
  Bal2Ctrl.Ofs20DC = SFMByte_read();
  Bal2Ctrl.Ofs20AC = SFMByte_read();
  Bal2Ctrl.Ofs10DC = SFMByte_read();
  Bal2Ctrl.Ofs10AC = SFMByte_read();
  Bal2Ctrl.Ofs5DC = SFMByte_read();
  Bal2Ctrl.Ofs5AC = SFMByte_read();
  Bal2Ctrl.Ofs5GND = SFMByte_read();
  Bal2Ctrl.Ofs2DC = SFMByte_read();
  Bal2Ctrl.Ofs2AC = SFMByte_read();
  Bal2Ctrl.Ofs2GND = SFMByte_read();  
  SFMRead_stop();

/* ������ (� ��������) ��������� �������������, ������������ */
  if (PL->STAT & PL_STAT_TRIGDET)	// ���� ���� �������������
    PanCtrl.TxBuf &= ~(1 << 4);		// ������ ���� �������������
  else
    PanCtrl.TxBuf |=  (1 << 4);		// �������� ���� �������������
  PanCtrl.TxBuf |= 0x40;
  USART3->DR = PanCtrl.TxBuf;		// ������� � ������
  
/* ������ ������� ��������� */  
  Sweep_init();

/* ������ ������������� ������ */
  Main_id = osThreadGetId();
  osThreadSetPriority(Main_id, osPriorityAboveNormal);
  
  MutDpy_id = osMutexCreate(osMutex(MutexDpy));
  
/* ������ �������������� ������ ����� */
  Panel_id = osThreadCreate(osThread(Panel_thread), NULL);
///  Display_id = osThreadCreate(osThread(Display_thread), NULL);
  if (ErrorState != ERROR_CODE || ErrorState != ERROR_CONF)
    Signal_id = osThreadCreate(osThread(Signal_thread), NULL);
  Meas_id = osThreadCreate(osThread(Meas_thread), NULL);

///  osThreadTerminate(Main_id);
  osDelay(100);
// �������� PWM
  *(uint16_t *)PWMCVCONF |= 0x10;

/* Superloop */
  for ( ; ; ) {  
    osSignalWait(0, osWaitForever);	// ������� ������ ������� �� �����
//    LED_ON();
    osMutexWait(MutDpy_id, osWaitForever);
    DpyBuf2Mem_copy(0, 320 * 240);
    osMutexRelease(MutDpy_id);
//    LED_OFF();
    // osDelay(100);			// �������� �� 100 ms
    // osDelay(50);			// �������� �� 50 ms
  }

  
/*_____________________________________________________________________________*/  

// FPI.FP_TBf = 0x7f;

  while (1) {
    if (GenCtrl.Redr) {
      GenCtrl.Redr = 0;
      // DELAYLONG_WAIT();
      if (Timer_check()) {
        DpyBuf2Mem_copy(0, 320 * 240);
        DELAY_START(10000);		// 100 ms ������ 10 ������ � ������� ����
#ifdef SLOOP_TEST
        LED_OFF();
#endif
      }
    }
  //  while (!(DMA2->ISR & DMA_ISR_TCIF1));	// ����� ���� ����������    
    if (PanCtrl.Ready) {
      PanCtrl.Ready = 0;
      GenCtrl.Redr = 1;
      Panel_Process();
    }
  //  while (!(DMA2->ISR & DMA_ISR_TCIF1));	// ����� ���� ����������
  //  Num_draw(Sweep.TimePos);
  //  Num_draw(ExeNum);    
  //  Num_draw(CodeCnt);
  //  general = SFMID_read();
  //  Num_draw(general);  
  //  Dump_draw (uint8_t *)DPYBUF);

  //  SigChan1_draw(3);
  //  SigChan2_draw(3);
  // Num_draw(Chan1.DispPos);

  //  uint16_t *pExtTest = (uint16_t *)(EXTDPY+LCDWAV*320+LCDWAH);
  //  for (uint32_t i=16; i--; ) {
  //  *pExtTest++ = (uint16_t)pExtTest;
  //  }
  
    // if (!Gen.Stop && !PLIRQn_get()) {
    if (!SweepCtrl.Stop && !PLIRQ_GET()) {
#ifdef SLOOP_TEST
      LED_ON();
#endif
      Sweep_exe();
    }
// ��������� �������������
/*  
      if (PL->STAT & PL_STAT_TRIGDET) FPI.FP_TBf &= ~(1<<4);	// on LED
      else				FPI.FP_TBf |= (1<<4);	// off LED
      FPI.FP_TBf |= 0x40;
      USART3->DR = FPI.FP_TBf;    
 */   
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
///    osSignalSet(Display_id, 1);		// ������ �� ���������
    osSignalSet(Main_id, 1);  
  }
}

/*!*****************************************************************************
 @brief		Display Drawing task
 @details	������ ������ �����������
 @param		
 @return	
 @note	
 */
void Display_thread(void const *arguments) {
  for ( ; ; ) {  
    osSignalWait(0, osWaitForever);	// ������� ������ ������� �� ����� (Gen.Redr)
    DpyBuf2Mem_copy(0, 320 * 240);
    // osDelay(10);			// �������� �� 10 ms
  }
}

/*!*****************************************************************************
 @brief		Signal Service task
 @details	������ ��������� �������
 @param		
 @return	
 @note	
 */
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
	Math_exe();
        osMutexRelease(MutDpy_id);
//	if (MeasCtrl.On) {
//	  osMutexWait(MutDpy_id, osWaitForever);
//	  SigPar_meas();			// ��������� (���� ����)
//	  osMutexRelease(MutDpy_id);
//	  osDelay(200);				// 5 ��� � ���
//	}
        osSignalSet(Main_id, 2); 
      }
    }					// if PLIRQ
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
    // osDelay(40);			// 5 ��� � ���  
    if (MeasCtrl.On) {
      osMutexWait(MutDpy_id, osWaitForever);
      SigPar_meas();			// ��������� (���� ����)
      osMutexRelease(MutDpy_id);
      osSignalSet(Main_id, 1);      
    }
  }
}

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

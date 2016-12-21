
/*!*****************************************************************************
 @file		Siluet_Signal.c
 @author	��������� �.�.
 @date		2013.03
 @version	V1.0
 @brief		Signal Processing functions
 @details	������� ��������� � ��������� �������
 @note		
 *******************************************************************************
 @verbatim
 2013.09.11
  ������� ������� ���������, ������ �������� ��� ��, ��� � ��� ����� 
 
 2013.04.22
   �������� ������� ����� � ���� ���������, ������������ INVPOS_USE.
   ����� ���������� INVPOS_USE, ���������� ������������� � ������,
   � ������ �������. ��� ���������������� ����� �����.
   ����� INVPOS_USE �� ����������, ������������� ������ ������, �
   ������������� � ��� �� �������, ��� ����. ������� �� ������ �� ��������.
   �� ���� ������ �������������� ���, �� ��� ����������� ���������� ������
   � �������� ������!
   �������� �������� ������ ��� ������ �� �����.
   ��� ������������-������������ ����� ������������� ��������.
 
 2013.04.19
   TimPos ������ ��������� �� ������ ������ � ������ �������.
 
 2012.04.12
   ��� ��������� ��������� ������� ��������� ������� ����� ������� ���������
   �������. ��� ������ � ����������� �� ��������� ��������� ������� ���������, 
   ��������� ��������� ����� � ������������� ������ � ������� ������ � ����� 
   � ������� ������ �������.
   TimePos ������������� ������ ������ (�� ��������� ���������� ���������
   � �������� ������ � ���� - 5 �������).
   ������ ����� �������� ����� SigBeg � SigEnd.
   
	SigBuf[][]	0(TimePos)	125			Dpy_width
	[		<		!		>	>	]
			   xxxxxxxxxxxxxxxxxxxxx_
			   ^			^
			   SigBeg		SigEnd (don't draw)

 2012.04
   ������� ��������� ������ �� ������
   ����� ���������� ������������ ��� ������ (�������� �������).
   �������� �������� ���������� �� 1, ����� ����� ����� ��������� ��� ����������.   

 2011.02
   ��������� ������� ��� ������ � ������� ��� �� ������� ���
   ������� LCDMEM �� EXTDPY
 @endverbatim
 *******************************************************************************/

/*! @addtogroup	Signal
    @{ */

/*__ ������������ ����� _______________________________________________________*/

#include "Siluet_Main.h"	// ��� ��������� ������ � ����� �����
#include "FFT_Windows.h"	// ������� ������� �������

/*__ ����������� �������� _____________________________________________________*/

/* ������� ������� ������� ������ */
#define DPYWAMIN ((uint8_t *)(DPYBUF_BASE + 320 * DPYWAV + DPYWAH))
#define DPYWAMAX ((uint8_t *)(DPYBUF_BASE + 320 * (DPYWAV + 200) + DPYWAH + 300))

/* ������������ ���������� ������� ������� */
#define WATT_RECT	1
#define WATT_HANN	0.5
#define WATT_HAMM	0.53888984
#define WATT_BART	0.5
// #define WATT_FLAT	0.21570319
#define WATT_FLAT	0.254

/*__ ������������ _____________________________________________________________*/


/*__ ��������� ���� ������ ____________________________________________________*/


/*__ ��������� ���������� _____________________________________________________*/

/*! ������������� ����� ��� �������� ����� ������� */
uint16_t DotBuf[16384];		// Chan2<<8 | Chan1
uint16_t *pDotBuf = DotBuf;	//!< ��������� �� ���������� ����� � ������


/*__ ��������� ��������� ������� ______________________________________________*/

void SigDots_rdavr(void);

void SigChan1Dot_draw(uint32_t bright);
void SigChan2Dot_draw(uint32_t bright);
void SigChan1Vect_draw(uint32_t bright);
void Vect1_draw(int32_t s1, int32_t brk, int32_t s2, 
		uint32_t dpos, uint32_t bright);
void SigChan2Vect_draw(uint32_t bright);
void Vect2_draw(int32_t s1, int32_t brk, int32_t s2, 
		uint32_t dpos, uint32_t bright);

void SigChans_clear(void);
void Sweep_start(void);

void Sum_draw(bool bright);
void SumDots_draw(bool bright);
void SumVect_draw(bool bright);
void Mult_draw(bool bright);
void MultDots_draw(bool bright);
void MultVect_draw(bool bright);
void VectMath_draw(int32_t s1, int32_t brk, int32_t s2,
		   uint32_t dpos, bool bright);
		
void FFT_calc(void);
void FFT_draw(bool bright);

void NumWrong_conv(uint8_t *pBuf);
void Num2Volt_conv(int32_t Num, uint32_t Volts, uint8_t *pBuf);
void Num2Time_conv(int32_t Num, uint8_t *pBuf);
void Num2Freq_conv(int32_t Num, uint8_t *pBuf);

void XYDots_draw(bool bright);

/*__ ���������� ������� _______________________________________________________*/


/*!*****************************************************************************
 @brief		Sweep initialize
 @details	���������������� ��������� ������� ��������� �������
 @param		void
 @return	
 @note		Sweep.TimeNum:	0..TIME_DOT(6)	- Dots,
				 ..26		- Full Frame,
				 ..TIMECNT(36)	- Sparse Frame 
 */
void Sweep_init(void) {

/* Dots */
  if (SweepCtrl.TimeNum <= TIME_DOT) {
  
/* Dots, ROLL */  
    if (SweepCtrl.Roll) {
      SigCtrl.SigNum = ROLL;
      SigCtrl.SigInx = 0;
      SigCtrl.SigBeg = SigCtrl.SigEnd = (1024 << MemCtrl.SizeNum) - 1;
    }
    
/* Dots, SCAN */    
    else {
      SigCtrl.SigNum = SCAN_PRE;
      pDotBuf = DotBuf;		// ��������� ����� - � ������ ������      
    }
  }
  
/* Frame, Full FRAME */  
  else if (SweepCtrl.TimeNum < TIME_SPR) {
    SigCtrl.SigNum = FRAME_FULL;
    SigCtrl.SigBeg = 0;
    SigCtrl.SigEnd = (1024 << MemCtrl.SizeNum) - 1;	// ����� ������ + 1
    // SigCtrl.SigBeg = 25;
    // SigCtrl.SigEnd = (1024 << MemCtrl.SizeNum) - 25;    
  }
  
/* Frame, SPARSE Frame */  
  else {
    SigCtrl.SigNum = FRAME_SPARSE;
    SigChans_clear();
    SigCtrl.SigBeg = 0;
    SigCtrl.SigEnd = (1024 << MemCtrl.SizeNum) - 1;	// ����� ������
  }
  if (!SweepCtrl.Stop) PL->STAT = PL_START_ACQUST;	// Start new frame
}

/*!*****************************************************************************
 @brief		Sweep execute
 @details	������� ��������� ������� � ��������
 @param		void
 @return	
 @note		
 */
void Sweep_exe(void) {
#ifdef SWEEP_TEST
  LED_ON();
#endif
  uint_fast16_t temp_stat = PL->STAT;	// read (reset interrupt request)
  // Temporal = temp_stat;		// ��� ��������� � ���������

/* �������������� ������� ������������� trig - second sample */
  if (SweepCtrl.TimeNum > TIME_DOT && temp_stat & PL_STAT_TRIGDET) {

    // Interp.Tcur = PL->ITRP;
    while (!(ADC2->SR & ADC_SR_JEOC));	// ����, ���� ��� ����� ��������������
    ADC2->SR &= ~ADC_SR_JEOC;		// �������� ��� ����� ��������������
    Interp.Tcur = ADC2->JDR1;

    PL->STAT = PL_START_ITDCST;		// ������ �������� �������������
    // Num_draw(Interp.Tcur);
    // Num_draw(Interp.Tmts >> 16);
    // Num_draw(Interp.Tmad >> 16);
    
    // if (Interp.Tcur > Interp.Tmin - 32 && Interp.Tcur < Interp.Tmax + 32)
    // if (Interp.Tcur > Interp.Tmin - 32)
    if (Interp.Tcur > Interp.Tmin - 256 && Interp.Tcur < Interp.Tmax + 256)
    //  if (Interp.Tcur > 32 && Interp.Tcur < 4096 - 32)
    {
      if (Interp.Awgt < MAXWGT) Interp.Awgt++;	// ��������� ��� ����������
      Interp.Tmts = Interp.Tmts - Interp.Tmts / Interp.Awgt
		  + (Interp.Tcur << 16) / Interp.Awgt;
      int32_t dev = Interp.Tmts - (Interp.Tcur << 16);
      Interp.Tmad = Interp.Tmad - Interp.Tmad / Interp.Awgt
	  	  + ((dev >= 0) ? dev : -dev) / Interp.Awgt;
      Interp.Tmin = (Interp.Tmts - Interp.Tmad * 2) >> 16;
      Interp.Tmax = (Interp.Tmts + Interp.Tmad * 2) >> 16;    
      if (ServCtrl.Calibr) {
        // Num_draw(Interp.Tcur);
        Num_draw(Interp.Tmts >> 16);
        // Num_draw(Interp.Tmad >> 16);
        // Num_draw(Interp.Tmin);
        // Num_draw(Interp.Tmax);
      }
    }
  }

/* �������� ����������� �������� �����
   ��-�� ������� ����� ���������� ������ ����� �� ������� ���������� */
  ///  if (Chan1Ctrl.On) SigChan1_draw(0);	// clear old wave
  ///  if (Chan2Ctrl.On) SigChan2_draw(0);	// clear old wave
  //  if (SweepCtrl.XY) XYDots_draw(false);	// clear old XY
  static uint16_t *pSigChan1;		// ��������� � ������ ������� 1
  static uint16_t *pSigChan2;		// ��������� � ������ ������� 2

/* ROLL */
  if (SigCtrl.SigNum == ROLL) {		
    uint_fast16_t temp_dot = PL->RINT;	// read Dot from Both Channels
    // Temporal = temp_dot;		// ��� ��������� � ���������
    if (Chan1Ctrl.On) {
// ��������� ��������� � �������� ����� � ����� ������� 1
      pSigChan1 = SigChan1.Buf16K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
      pSigChan1 += SigCtrl.SigInx;
      *pSigChan1 = temp_dot << 8;	// Chan1 (int part)
    }
    if (Chan2Ctrl.On) {
// ��������� ��������� � �������� ����� � ����� ������� 2
      pSigChan2 = SigChan2.Buf16K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
      pSigChan2 += SigCtrl.SigInx;
      *pSigChan2 = temp_dot & 0xFF00;	// Chan2 (int part)
    }
// ��������� ������; ���� �� ���� ������ ������� ������, ��������
    SigCtrl.SigInx++;
    if (SigCtrl.SigInx >= (1024 << MemCtrl.SizeNum)) SigCtrl.SigInx = 0;
// ���������� ������ ������ ������� � ������ ������    
    if (SigCtrl.SigBeg) SigCtrl.SigBeg--;
  }

/* SCAN_PRE */
  else if (SigCtrl.SigNum == SCAN_PRE) {
    *pDotBuf++ = PL->RINT;		// Read-write dot to DotBuf
    if (pDotBuf == DotBuf + 16384) pDotBuf = DotBuf;  
    if (temp_stat & PL_STAT_TRIGDN) {	// Triggered
      pDotBuf -= SweepCtrl.Pret << MemCtrl.SizeNum + 5;
      if (pDotBuf < DotBuf) pDotBuf += 16384;	// ������ �������� �����
// ������-��������� ����� ����� �� �����������      
      SigDots_rdavr();
      // SigCtrl.SigInx = Sweep.Pret;	// ������ ��� ������� ����� �����
// �������� � ������ 16-������� ������� ������� (� ��������, �� � ������!)
      pSigChan1 = SigChan1.Buf16K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
      pSigChan1 += SweepCtrl.Pret << MemCtrl.SizeNum + 5;
      pSigChan2 = SigChan2.Buf16K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
      pSigChan2 += SweepCtrl.Pret << MemCtrl.SizeNum + 5;
      SigCtrl.SigNum = SCAN_PST;	// ������ �������� �� ������
    }
  }
  
/* SCAN_PST */  
  else if (SigCtrl.SigNum == SCAN_PST) {
    uint32_t cnt = FrameCnt;		// ������� ������ � ���������� �������
    uint32_t clog = 0;			// �������� �������� ������������ ������
    while (cnt >>= 1) clog++;
    clog--;				// ��� 1-�� ����� ��� ���������� (>>0)
    uint32_t aver = AcquCtrl.Aver >> 2;	// ��� ����������
    if (clog < aver) aver = clog;
// �������� ����� �� ���������� ������
    uint32_t temp_mem;
    uint32_t temp_dot = PL->RINT;	// ��������� ��� ������ (00002211)
    if (Chan1Ctrl.On) {
      temp_mem = *pSigChan1 << 16;	// ��������� � ������� ������� (iiff0000)
      temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
      temp_mem += ((temp_dot & 0x00ff) << 24) >> aver;	// �������� ����� ������
      *pSigChan1++ = temp_mem >> 16;	// ��������� ������� �������
    }
    if (Chan2Ctrl.On) {
      temp_mem = *pSigChan2 << 16;	// ��������� � ������� ������� (iiff0000)
      temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
      temp_mem += ((temp_dot & 0xff00) << 16) >> aver;	// �������� ����� ������
      *pSigChan2++ = temp_mem >> 16;	// ��������� ������� �������
    }
    if (temp_stat & PL_STAT_POSTDN) {
      // if (!SweepCtrl.Stop) PL->STAT = PL_START_ACQUST;	// Start new frame
      Sweep_start();
      // pDotBuf = DotBuf;			// ��������� ����� - � ������ ������
      SigCtrl.SigNum = SCAN_PRE;
    }     
  }  

/* FRAME_FULL */  
  else if (SigCtrl.SigNum == FRAME_FULL) {
// ��������� � ��������� ���, ���� ��� �� ������ �� �������      
    // SigChans_read();
// ���� ���������� ����� �� ������������ ����� ���������, �����
    // if (Interp.Tcur >= Interp.Tmin || Interp.Tcur <= Interp.Tmax)

    SigChans_rdavr();			// Read-average channels
    
    FrameCnt++;				// ��������� ������� ������ � ���������� �������
    if (!FrameCnt) FrameCnt--;		// ���� ���� ������������, �������� �� ���������
    uint32_t cnt = FrameCnt;		// ������� ������ � ���������� �������
    uint32_t clog = 0;			// �������� �������� ������������ ������
    while (cnt >>= 1) clog++;
    clog--;				// ��� 1-�� ����� ��� ���������� (>>0)
    uint32_t aver = AcquCtrl.Aver >> 2;	// ��� ����������
    if (clog < aver) aver = clog;

/* �������� � ������ 16-������� ������� ������� (� ��������, �� � ������!) */  
    uint16_t *pSigChan1 = SigChan1.Buf16K
			+ (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
    uint16_t *pSigChan2 = SigChan2.Buf16K
			+ (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;

// �������������� ��������� �� ���������� ���������
/*  
  if (Interp.Tcur > Interp.Tmts >> 16) {
    DpyCharPad_draw(DPYPOS(DPYWAH + 300 - 2 * 8 - 2, 1), '>', 0xf3f30000);
    pSigChan1 += 1; 
    pSigChan2 += 1; 
  }
  else DpyCharPad_draw(DPYPOS(DPYWAH + 300 - 2 * 8 - 2, 1), '<', 0xf3f30000);
  // Num_draw(Interp.Tcur);
 */

    uint32_t temp_pld;
    uint32_t temp_mem;
    
/* ���������� ���������� ������ */
    for (uint32_t i = 1024 << MemCtrl.SizeNum; i--; ) {
      temp_pld = (uint32_t)PL->MINT;	// ��������� ��� ������ (00002211)
      if (Chan1Ctrl.On) {
        temp_mem = *pSigChan1 << 16;	// ��������� � ������� ������� (iiff0000)
        temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
        temp_mem += ((temp_pld & 0x00FF) << 24) >> aver;	// �������� ����� ������
        *pSigChan1++ = temp_mem >> 16;	// ��������� ������� �������
      }
      if (Chan2Ctrl.On) {
        temp_mem = *pSigChan2 << 16;	// ��������� � ������� ������� (iiff0000)
        temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
        temp_mem += ((temp_pld & 0xFF00) << 16) >> aver;	// �������� ����� ������
        *pSigChan2++ = temp_mem >> 16;	// ��������� ������� �������
      }
    }
    // if (!SweepCtrl.Stop) PL->STAT = PL_START_ACQUST;	// Start new frame
    Sweep_start();
  }
  
/* FRAME_SPARSE
   ���� ���� �������������� �� PL � DotBuf.
   �� DotBuf ���������� ����� ����� �� Sweep.Pret - Sweep.Pret / Sweep.TimeItp
   � �������������� � ����������� � SigChan1, SigChan2 
   �� ��������� Tofs = TimeItp * (Tcur - Tmin) / (Tmax - Tmin + 1)
   � ����� Sweep.TimeItp, ���� �� ���������� �����.
   
   ������� ������������� Tmin...Tmax ����������� �� �������
   Tmin,Tmax = Tmts � 2 * Tmad, ���: 
   Tmts - ������� �������� ������� ����� ��������������� �
	  ������ ������ �������������
   Tmad - ������� ���������� ���������� �� �������� ������� 
	  (�������� �� �������������)
   ��� ��� �������� ������������� � �����������, ����� ���� �������������.
   
   ���� ������������� ���, ����� Tofs �������� �������������, ��������������� 
   �� ��������� 0...TimeItp.
   AD7910 ���� 10-������� ��������� ���������,
   ����� ������� TimeItp = 200 (0.5 ns/div).
   ��� � STM32 ���� 12-��������� ���������.
 */
  else {
// ���� ���������� ����� �� ������������ ����� ���������, �����
    if (Interp.Tcur < Interp.Tmin || Interp.Tcur > Interp.Tmax) {
      // if (!SweepCtrl.Stop) PL->STAT = PL_START_ACQUST;	// Start new frame
      Sweep_start();
      return;
    }
    
// ���������� ���� ���� �� ���� � ������������� �����  
    pDotBuf = DotBuf;
    for (uint32_t i = 1024 << MemCtrl.SizeNum; i--; ) {
      *pDotBuf++ = PL->MINT;
    }
    
// ���������� ��������� � ������������� ������
    // pDotBuf = DotBuf + SweepCtrl.Pret - SweepCtrl.Pret / SweepCtrl.TimeItp;
    // pDotBuf = DotBuf
    //    + ((SweepCtrl.Pret - SweepCtrl.Pret / SweepCtrl.TimeItp)
    //        << MemCtrl.SizeNum);
    pDotBuf = DotBuf
	    + (SweepCtrl.Pret << MemCtrl.SizeNum + 5)
	    - (SweepCtrl.Pret << MemCtrl.SizeNum + 5) / SweepCtrl.TimeItp;    
    
// ��������� �������� � ������ ��������
    uint32_t static Tofs;
    if (temp_stat & PL_STAT_TRIGDET) {
    /*
      Tofs = SweepCtrl.TimeItp * 2 * (Interp.Tcur - Interp.Tmin)
           / (uint32_t)(Interp.Tmax - Interp.Tmin + 1);
      */
    //  Tofs = SweepCtrl.TimeItp * (Interp.Tcur - Interp.Tmin)
    //       / (uint32_t)(Interp.Tmax - Interp.Tmin + 1);
      Tofs = SweepCtrl.TimeItp * (Interp.Tcur - Interp.Tmin)
           / (Interp.Tmad * 4 >> 16);
	   
    }
// ���� ��� �������������, �������� Tofs ���������������
    else {
      Tofs++;
      if (Tofs >= SweepCtrl.TimeItp) Tofs = 0;
    }
  
// ������ ��������� � ������ ��������  
    pSigChan1 = SigChan1.Buf16K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
	      + Tofs + 0;
    pSigChan2 = SigChan2.Buf16K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
	      + Tofs + 0;
/*
    if (Interp.Tcur > Interp.Tmts >> 16) {
      DpyCharPad_draw(DPYPOS(DPYWAH + 300 - 2 * 8 - 2, 1), '>', 0xf3f30000);
      pSigChan1 += 2; 
      pSigChan2 += 2; 
    }
    else DpyCharPad_draw(DPYPOS(DPYWAH + 300 - 2 * 8 - 2, 1), '<', 0xf3f30000);
 */   
// ���������� ��� ����������
    FrameCnt++;				// ��������� ������� ������ � ���������� �������
    if (!FrameCnt) FrameCnt--;		// ���� ���� ������������, �������� �� ���������
    uint32_t cnt = FrameCnt;		// ������� ������ � ���������� �������
    uint32_t clog = 0;			// �������� �������� ������������ ������
    while (cnt >>= 1) clog++;
    clog--;				// ��� 1-�� ����� ��� ���������� (>>0)
    uint32_t aver = AcquCtrl.Aver >> 2;	// ��� ����������
    if (clog < aver) aver = clog;

    uint32_t temp_dot;
    uint32_t temp_mem;
// ���������� � ����������� ����������� �������, ���� �� ���������� ����� �������
    do {
      temp_dot = (uint32_t)*pDotBuf++;	// ��������� ��� ������ (00002211)
      if (Chan1Ctrl.On) {
        temp_mem = *pSigChan1 << 16;	// ��������� � ������� ������� (iiff0000)
        temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
        temp_mem += ((temp_dot & 0x00ff) << 24) >> aver;	// �������� ����� ������
        *pSigChan1 = temp_mem >> 16;	// ��������� ������� �������
      }
      pSigChan1 += SweepCtrl.TimeItp;
      if (Chan2Ctrl.On) {
        temp_mem = *pSigChan2 << 16;	// ��������� � ������� ������� (iiff0000)
        temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
        temp_mem += ((temp_dot & 0xff00) << 16) >> aver;	// �������� ����� ������
        *pSigChan2 = temp_mem >> 16;	// ��������� ������� �������
      }
      pSigChan2 += SweepCtrl.TimeItp;
    } while ( (pSigChan1 <= SigChan1.Buf16K
		        + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1))
	   || (pSigChan2 <= SigChan2.Buf16K
		        + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1)) );
    // if (!SweepCtrl.Stop) PL->STAT = PL_START_ACQUST;	// Start new frame
    Sweep_start();
  }

/* ���������� ����� �����, ����� ��� ����� ���� */
//    if (Chan1Ctrl.On) {
//      Chan1Ctrl.DispPos = 0;		// clear display position
//      SigChan1_draw(3);			// draw new wave
//    }
//    if (Chan2Ctrl.On) {
//      Chan2Ctrl.DispPos = 0;		// clear display position
//      SigChan2_draw(3);			// draw new wave
//    }

  if (Chan1Ctrl.On) Chan1Ctrl.DispPos = 0;
  if (Chan2Ctrl.On) Chan2Ctrl.DispPos = 0;
  DpyWork_clear(MASK_MATSIG);
  SigChans_draw();
  // XYDots_draw(true);
    
#ifdef SWEEP_TEST
  LED_OFF();
#endif

}



/*!*****************************************************************************
 @brief		Signal Channels draw
 @details	���������� ������� (�� ������� ��� XY)
 @return	
 */
void SigChans_draw(void) {
  if (!SweepCtrl.XY) {
    if (Chan1Ctrl.On) SigChan1_draw(3);
    if (Chan2Ctrl.On) SigChan2_draw(3);
    Math_exe();
  }
  else XYDots_draw(true);
}

/*!*****************************************************************************
 @brief		Signal Channels redraw after close MENU
 @details	������������ ������� ����� �������� ����
 @return	
 */
void SigChans_redraw(void) {
  if (!SweepCtrl.XY) {
    if (Chan1Ctrl.On) SigChan1_draw(3);
    if (Chan2Ctrl.On) SigChan2_draw(3);
    Math_exe();
  }
  else XYDots_draw(true);
}

/*!*****************************************************************************
 @brief		Position Channels redraw
 @details	
 @return	
 @note	
 */
void PosChans_redraw(void) {
  if (Chan1Ctrl.On) PosChan1_draw(true);
  if (Chan2Ctrl.On) PosChan2_draw(true);
}

/*!*****************************************************************************
 @brief		Signal Channel1 draw in ExtRAM
 @details	
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note	
 */
void SigChan1_draw(uint32_t bright) {
  // if (!DispCtrl.Vect || (SigCtrl.SigNum == FRAME_SPARSE && FrameCnt < 1000))
  if (!DispCtrl.Vect)
       SigChan1Dot_draw(bright);
  else SigChan1Vect_draw(bright);
}

/*!*****************************************************************************
 @brief		Signal Channel2 draw
 @details	
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		
 */
void SigChan2_draw(uint32_t bright) {
  // if (!DispCtrl.Vect  || (SigCtrl.SigNum == FRAME_SPARSE && FrameCnt < 1000))
  if (!DispCtrl.Vect)
       SigChan2Dot_draw(bright);
  else SigChan2Vect_draw(bright);
}

/*!*****************************************************************************
 @brief		Signal Channel1 Dots draw
 @details	���������� ����� �������, ����������� �� ������� � ������
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		lmarg, rmarg - ������� ��������� �������
 */
void SigChan1Dot_draw(uint32_t bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  int32_t lmarg = (SigCtrl.SigBeg > SweepCtrl.TimePos) ?
                   SigCtrl.SigBeg - SweepCtrl.TimePos : 0;
  int32_t rmarg = (SigCtrl.SigEnd < SweepCtrl.TimePos + width) ?
                   SigCtrl.SigEnd - SweepCtrl.TimePos : width;
  if (lmarg >= width || rmarg < 0) return;
  uint16_t *pSig = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum 
		 + SweepCtrl.TimePos 
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pLim = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
  if (pSig >= pLim) pSig -= (1024 << MemCtrl.SizeNum);
  volatile uint8_t *pDpy;
  for (uint32_t i = lmarg; i < rmarg; i++) {
    int16_t temp = (*pSig++) >> 8;	// ������� (�����) ����� �����
    if (pSig >= pLim) pSig -= (1024 << MemCtrl.SizeNum);
#ifdef INVPOS_USE
    if (Chan1Ctrl.Inv) temp = 0x100 - temp;
#else
    if (Chan1Ctrl.Inv) temp = (Chan1Ctrl.SigPos) - temp - 256 - Chan1Ctrl.DispPos;
#endif
    temp = (Chan1Ctrl.DispPos / 2U + temp);
    pDpy = (uint8_t *)(DPYBUF_BASE + DPYWAH + i + 320 * (DPYWAV + 228 - temp));
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) { 
      uint8_t pix = *pDpy;  pix ^= (pix ^ bright) & 0x03;  *pDpy = pix;
    }
  }
}

/*!*****************************************************************************
 @brief		Signal Channel2 Dots draw
 @details	���������� ����� �������, ����������� �� ������� � ������
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		lmarg, rmarg - ������� ��������� ������� �� ������ (0..width)
 */
void SigChan2Dot_draw(uint32_t bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  // uint32_t pos = Sweep.TimePos;
  int32_t lmarg = (SigCtrl.SigBeg > SweepCtrl.TimePos) ? 
                   SigCtrl.SigBeg - SweepCtrl.TimePos : 0;
  int32_t rmarg = (SigCtrl.SigEnd < SweepCtrl.TimePos + width) ? 
                   SigCtrl.SigEnd - SweepCtrl.TimePos : width;
  // Hex32_draw (lmarg);
  // if (lmarg >= rmarg) return;
  if (lmarg >= width || rmarg < 0) return;
  // Hex32_draw (lmarg);
  uint16_t *pSig = SigChan2.Buf16K  
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
		 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
//  uint16_t *pSig = SigChan2.Buf8K  
//                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum)
//		 + SigCtrl.SigInx + SigCtrl.SigBeg;
  uint16_t *pLim = SigChan2.Buf16K
                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
  if (pSig >= pLim) pSig -= (1024 << MemCtrl.SizeNum); 
  // Hex32_draw ((uint32_t)pSig);
  // Hex32_draw ((uint32_t)pLim);
  
  volatile uint8_t *pDpy; 

  for (uint32_t i = lmarg; i < rmarg; i++) {
    int32_t temp = (*pSig++) >> 8;	// ������� (�����) ����� �����
    if (pSig >= pLim) pSig -= (1024 << MemCtrl.SizeNum);
#ifdef INVPOS_USE
    if (Chan2Ctrl.Inv) temp = 0x100 - temp;
#else
    if (Chan2Ctrl.Inv) temp = (Chan2Ctrl.SigPos) - temp - 256 - Chan2Ctrl.DispPos;
#endif
    temp = (Chan2Ctrl.DispPos / 2U + temp);
    // Temporal = temp;
    pDpy = (uint8_t *)(DPYBUF_BASE + DPYWAH + i + 320 * (DPYWAV + 228 - temp));
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
      uint8_t pix = *pDpy; pix ^= (pix ^ bright << 2) & 0x03 << 2; *pDpy = pix;
    }
  }
}

#if false
/*!*****************************************************************************
 @brief		Signal Channel1 Dots draw
 @details	
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		lmarg, rmarg - ������� ��������� �������
 */
void SigChan1Dot_draw(uint32_t bright) {
  uint32_t width = DispCtrl.Wide? 300 : 250;
  volatile uint8_t *pDpy;
  uint32_t pos = Sweep.TimePos;
  uint32_t lmarg = (SigCtrl.SigBeg > pos) ? SigCtrl.SigBeg - pos : 0;
  uint32_t rmarg = (SigCtrl.SigEnd < pos + width) ? SigCtrl.SigEnd - pos : width;
  if (lmarg >= rmarg) return;
  uint16_t *pSig = SigChan1.Buf8K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum 
		 + pos + lmarg;
  for (int32_t i = lmarg; i < rmarg; i++) {
    int16_t temp = (*pSig++) >> 8;	// ������� (�����) ����� �����
    temp = (Chan1.DispPos / 2U + temp);
    pDpy = (uint8_t *)(DPYMEM + DPYWAH + i + 320 * (DPYWAV + 228 - temp));
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) { 
      uint8_t pix = *pDpy;  pix ^= (pix ^ bright) & 0x03;  *pDpy = pix;
    }
  }
}

/*!*****************************************************************************
 @brief		Signal Channel2 Dots draw
 @details	
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		
 */
void SigChan2Dot_draw(uint32_t bright) {
  uint32_t width = DispCtrl.Wide? 300:250;
  volatile uint8_t *pDpy;
  uint32_t pos = Sweep.TimePos;
  uint32_t lmarg = (SigCtrl.SigBeg > pos) ? SigCtrl.SigBeg - pos : 0;
  uint32_t rmarg = (SigCtrl.SigEnd < pos + width) ? SigCtrl.SigEnd - pos : width;
  if (lmarg >= rmarg) return;
  uint16_t *pSig = SigChan2.Buf8K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum 
		 + pos + lmarg;
  for (int32_t i = lmarg; i < rmarg; i++) {
    int16_t temp = (*pSig++) >> 8;	// ������� (�����) ����� �����
    if (Chan2.Inv) temp = 0x100 - temp;
    temp = (Chan2.DispPos / 2U + temp);
    pDpy = (uint8_t *)(DPYMEM + DPYWAH + i + 320 * (DPYWAV + 228 - temp));
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) { 	
      uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 2) & 0x03 << 2;  *pDpy = pix;
    }
  }
}
#endif

#ifdef SICUBE
/*!*****************************************************************************
 @brief		Signal Channel1 Vectors draw
 @details	���������� ������ ������ 1 ��������� � ���������� �������������
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		
 */
void SigChan1Vect_draw(uint32_t bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  uint16_t *BufBeg = SigChan1.Buf8K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
  uint16_t *pSig = BufBeg + Sweep.TimePos;
  int32_t s0, s1, s2, s3;			// samples
  int32_t brk;
/* ������ ������ ����������� */
  if (pSig == BufBeg)  s0 = (*pSig) >> 8;	// s0/2
  else  s0 = (*(pSig - 1)) >> 8;
  s1 = (*pSig++) >> 8; s2 = (*pSig++) >> 8; s3 = (*pSig++) >> 8;
  brk = ((s1 + s2) * 9 - s0 - s3) / 16;
  // margin = (s1 + s2)>>1;
  // margin = ((s1 + s2) * 9U - s0 - s3) >> 4;
  Vect1_draw(s1, brk, s2, 0, bright);
/* ���� ����� ������ �������� � ��������� */
  for (uint32_t i = 1; i < width - 1; i++) {
    s0 = s1; s1 = s2; s2 = s3; s3 = (*pSig++) >> 8;
    brk = ((s1 + s2) * 9 - s0 - s3) / 16;
    // margin = (s1 + s2)>>1;
    // margin = ((s1 + s2) * 9U - s0 - s3) >> 4;  
    Vect1_draw(s1, brk, s2, i, bright);
  }
/* ��������� ������ ����������� */
  s0 = s1; s1 = s2; s2 = s3;
  if (pSig == BufBeg + (1024 << MemCtrl.SizeNum))  s3 = (*(pSig - 1)) >> 8;
  else  s3 = (*pSig) >> 8;
  brk = ((s1 + s2) * 9 - s0 - s3) / 16;
  // margin = (s1 + s2)>>1;
  // margin = ((s1 + s2) * 9U - s0 - s3) >> 4;
  Vect1_draw(s1, brk, s2, width-1, bright);      
}
#endif	// SICUBE

#ifdef SILINE
/*!*****************************************************************************
 @brief		Signal Channel1 Vectors draw
 @details	���������� ������ ������ 1 ��������� � �������� �������������
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		
 */
void SigChan1Vect_draw(uint32_t bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  // uint32_t pos = Sweep.TimePos;
  int32_t lmarg = (SigCtrl.SigBeg > SweepCtrl.TimePos) ?
                   SigCtrl.SigBeg - SweepCtrl.TimePos : 0;
  int32_t rmarg = (SigCtrl.SigEnd < SweepCtrl.TimePos + width) ?
                   SigCtrl.SigEnd - SweepCtrl.TimePos : width;
  if (lmarg >= width || rmarg < 0) return;
  uint16_t *pSig = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
                 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pLim = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
  if (pSig >= pLim) pSig -= (1024 << MemCtrl.SizeNum);		 
  int32_t s1, s2;			// previous & next samples
  int32_t brk;
/* ���� ����� ������ �������� � ��������� */
  for (int32_t i = lmarg; i < rmarg; i++) {
    s1 = (*pSig++) >> 8;		// integer part, begin
    if (pSig >= pLim) pSig -= (1024 << MemCtrl.SizeNum);
    s2 = (*pSig) >> 8;			// integer part, end
#ifdef INVPOS_USE
    if (Chan1Ctrl.Inv) {
      s1 = 0x100 - s1;
      s2 = 0x100 - s2;
    }
#else
    if (Chan1Ctrl.Inv) {
      s1 = (Chan1Ctrl.SigPos) - s1 - 256 - Chan1Ctrl.DispPos;
      s2 = (Chan1Ctrl.SigPos) - s2 - 256 - Chan1Ctrl.DispPos;
    }
#endif
#ifdef STRA_VECT
    brk = (s1 == s2) ? s1 : ((s1 > s2) ? (s1 - 1) : (s1 + 1));
#else    
    brk = (s1 + s2) >> 1;		// jump from left to right column
#endif
    Vect1_draw(s1, brk, s2, i, bright);
  }
}
#endif					// SILINE

/*!*****************************************************************************
 @brief		Vector1 draw
 @details	���������� ������ (� ���� �������� ��������)
 @param		s1, brk, s2
 @param		dpos - ������� ������ ������� �� �����������
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		
 */
void Vect1_draw(int32_t s1, int32_t brk, int32_t s2, uint32_t dpos, uint32_t bright)
{
  if (SigCtrl.SigNum == FRAME_SPARSE && (!(s1) || !(s2))) return;
  s1 += Chan1Ctrl.DispPos / 2;
  brk += Chan1Ctrl.DispPos / 2;
  s2 += Chan1Ctrl.DispPos / 2;
  uint32_t size;			// ������ �������
  uint8_t *pDpy = (uint8_t *)(DPYBUF_BASE + DPYWAH + dpos + 320 * (DPYWAV + 228 - s1));
/* �� ����� ������� �� �������� */
  if (s1 < brk) {			// up vector			
    size = brk - s1;
    for (uint32_t j=size; j--; ) {
      pDpy -= 320;			// ����������� - ����������
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy;  pix ^= (pix ^ bright) & 0x03;  *pDpy = pix;
      }
    }
  }
  else if (s1 > brk) {		// down vector
    size = s1 - brk;
    for (uint32_t j=size; j--; ) {
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy;  pix ^= (pix ^ bright) & 0x03;  *pDpy = pix;
      }
      pDpy += 320;			// ���������� - �����������
    }
  }
  else {				// s1 == brk, right vector
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
      uint8_t pix = *pDpy;  pix ^= (pix ^ bright) & 0x03;  *pDpy = pix;
    }
  }
/* ����� �� ��������� ��� */
  pDpy++;				
/* �� �������� �� ������ ������� */    
  if (brk < s2) {			// up vector  
    size = s2 - brk;
    for (uint32_t j=size; j--; ) {
      pDpy -= 320;			// ����������� - ����������    
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy;  pix ^= (pix ^ bright) & 0x03;  *pDpy = pix;
      }
    }
  }
  else if (brk > s2) {		// down vector
    size = brk - s2;
    for (uint32_t j=size; j--; ) {
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy;  pix ^= (pix ^ bright) & 0x03;  *pDpy = pix;
      }
      pDpy += 320;			// ���������� - �����������      
    }
  }
//  else {				// s1 == brk, right vector
//    if (pDpy >= (uint8_t *)(LCD_MEM_START+LCDWAH+320*LCDWAV) &&
//        pDpy <= (uint8_t *)(LCD_MEM_START+LCDWAH+320*(LCDWAV+200))) {
//      uint8_t pix = *pDpy;  pix ^= (pix ^ bright) & 0x03;  *pDpy = pix;
//    }
//  }
}

#ifdef SICUBE
/*!*****************************************************************************
 @brief		Signal Channel2 Vectors draw
 @details	���������� ������ ������ 2 ��������� � ���������� �������������
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		
 */
void SigChan2Vect_draw(uint32_t bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  uint16_t *BufBeg = SigChan2.Buf8K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
  uint16_t *pSig = BufBeg + Sweep.TimePos;
  int32_t s0, s1, s2, s3;			// samples
  int32_t brk;
/* ������ ������ ����������� */
  if (pSig == BufBeg)  s0 = (*pSig) >> 8;	// s0/2
  else  s0 = (*(pSig - 1)) >> 8;
  s1 = (*pSig++) >> 8; s2 = (*pSig++) >> 8; s3 = (*pSig++) >> 8;
  if (Chan2.Inv) { s0 = 0x100 - s0;  s1 = 0x100 - s1;  s2 = 0x100 - s2;  s3 = 0x100 - s3; }
  brk = ((s1 + s2) * 9 - s0 - s3) / 16;
  // margin = (s1 + s2)>>1;
  // margin = ((s1 + s2) * 9U - s0 - s3) >> 4;
  Vect2_draw(s1, brk, s2, 0, bright);
/* ���� ����� ������ �������� � ��������� */
  for (uint32_t i = 1; i < width - 1; i++) {
    s0 = s1; s1 = s2; s2 = s3; s3 = (*pSig++) >> 8;
  if (Chan2.Inv)  s3 = 0x100 - s3;
    brk = ((s1 + s2) * 9 - s0 - s3) / 16;
    // margin = (s1 + s2)>>1;
    // margin = ((s1 + s2) * 9U - s0 - s3) >> 4;
    Vect2_draw(s1, brk, s2, i, bright);
  }
/* ��������� ������ ����������� */
  s0 = s1; s1 = s2; s2 = s3;
  if (pSig == BufBeg + (1024 << MemCtrl.SizeNum))  s3 = (*(pSig - 1)) >> 8;
  else  s3 = (*pSig) >> 8;
  if (Chan2.Inv)  s3 = 0x100 - s3;
  brk = ((s1 + s2) * 9 - s0 - s3) / 16;
  // margin = (s1 + s2)>>1;
  // margin = ((s1 + s2) * 9U - s0 - s3) >> 4;
  Vect2_draw(s1, brk, s2, width - 1, bright);      
}
#endif	// SICUBE

#ifdef SILINE
/*!*****************************************************************************
 @brief		Signal Channel2 Vectors draw
 @details	���������� ������ ������ 2 ��������� � �������� �������������
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note	
 */
void SigChan2Vect_draw(uint32_t bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  // uint32_t pos = Sweep.TimePos;
  int32_t lmarg = (SigCtrl.SigBeg > SweepCtrl.TimePos) ?
                   SigCtrl.SigBeg - SweepCtrl.TimePos : 0;
  int32_t rmarg = (SigCtrl.SigEnd < SweepCtrl.TimePos + width) ?
                   SigCtrl.SigEnd - SweepCtrl.TimePos : width;
  if (lmarg >= width || rmarg < 0) return;
  uint16_t *pSig = SigChan2.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum 
		 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pLim = SigChan2.Buf16K
                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
  if (pSig >= pLim) pSig -= (1024 << MemCtrl.SizeNum);		 
  int32_t s1, s2;			// samples
  int32_t brk;
/* ���� ����� ������ �������� � ��������� */
  for (uint32_t i = lmarg; i < rmarg - 1; i++) {
    s1 = (*pSig++) >> 8;
    if (pSig >= pLim) pSig -= (1024 << MemCtrl.SizeNum);
    s2 = (*pSig) >> 8;
#ifdef INVPOS_USE
    if (Chan2Ctrl.Inv) {
      s1 = 0x100 - s1;
      s2 = 0x100 - s2;
    }
#else
    if (Chan2Ctrl.Inv) {
      s1 = (Chan2Ctrl.SigPos) - s1 - 256 - Chan2Ctrl.DispPos;
      s2 = (Chan2Ctrl.SigPos) - s2 - 256 - Chan2Ctrl.DispPos;
    }
#endif
#ifdef STRA_VECT
    brk = (s1 == s2) ? s1 : ((s1 > s2) ? (s1 - 1) : (s1 + 1));
#else
    brk = (s1 + s2) >> 1;
#endif
    Vect2_draw(s1, brk, s2, i, bright);
  }
}
#endif	// SILINE

/*!*****************************************************************************
 @brief		Vector2
 @details	���������� ������ (� ���� �������� ��������)
 @param		s1, brk, s2
 @param		dpos - ������� ������ ������� �� �����������
 @param		bright - ������� � ��������� 3, 2, 1, 0 (����)
 @return	
 @note		
 */
void Vect2_draw(int32_t s1, int32_t brk, int32_t s2, uint32_t dpos, uint32_t bright)
{
  if (SigCtrl.SigNum == FRAME_SPARSE && (!(s1) || !(s2))) return;
  s1 += Chan2Ctrl.DispPos / 2;
  brk += Chan2Ctrl.DispPos / 2;
  s2 += Chan2Ctrl.DispPos / 2;
//  uint8_t thresh = (uint8_t)((thr_bri>>6)&0x0c);
//  uint8_t bright = (uint8_t)(thr_bri);
  uint32_t size;			// ������ �������
  uint8_t *pDpy = (uint8_t *)(DPYBUF_BASE + DPYWAH + dpos + 320 * (DPYWAV + 228 - s1));
/* �� ����� ������� �� �������� */
  if (s1 < brk) {			// up vector			
    size = brk - s1;
    for (uint32_t j=size; j--; ) {
      pDpy -= 320;			// ����������� - ����������
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 2) & 0x03 << 2;  *pDpy = pix;
      }
    }
  }
  else if (s1 > brk) {		// down vector
    size = s1 - brk;
    for (uint32_t j=size; j--; ) {
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 2) & 0x03 << 2;  *pDpy = pix;
      }
      pDpy += 320;			// ���������� - �����������
    }
  }
  else {				// s1 == brk, right vector
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
      uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 2) & 0x03 << 2;  *pDpy = pix;
    }
  }
/* ����� �� ��������� ��� */
  pDpy++;				
/* �� �������� �� ������ ������� */    
  if (brk < s2) {			// up vector  
    size = s2 - brk;
    for (uint32_t j=size; j--; ) {
      pDpy -= 320;			// ����������� - ����������    
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 2) & 0x03 << 2;  *pDpy = pix;
      }
    }
  }
  else if (brk > s2) {		// down vector
    size = brk - s2;
    for (uint32_t j=size; j--; ) {
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 2) & 0x03 << 2;  *pDpy = pix;
      }
      pDpy += 320;			// ���������� - �����������      
    }
  }
//  else {				// s1 == marg, right vector
//    if (pDpy >= (uint8_t *)(LCD_MEM_START+LCDWAH+320*LCDWAV) &&
//        pDpy <= (uint8_t *)(LCD_MEM_START+LCDWAH+320*(LCDWAV+200))) {
//      uint8_t pix = *pDpy;  pix ^= (pix ^ bright<<2) & 0x03<<2;  *pDpy = pix;
//    }
//  }
}  

/*!*****************************************************************************
 @brief		Position1 Marker draw
 @details	�������� ��� ���������� ������ ������� ����� ������ 1
 @param		On - ���/����
 @return	
 @note		
 */
void PosChan1_draw(bool On) {
  int32_t pos = Chan1Ctrl.SigPos / 2U - 256;
#ifdef INVPOS_USE
  if (Chan1Ctrl.Inv) pos = -pos;
#endif
  if (!On) {
    if (pos < -100)
      DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV + 199),
		   SS_MKDN, 0x03, 0x00000000);
    else if (pos >= -100 && pos <= 100)
      DpySpec_draw(DPYPOS(DPYWAH - 4, DPYWAV + 100 - pos - 4),
		   SS_MKLT, 0x03, 0x00000000);
    else	// pos > 100
      DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV - 8),
		   SS_MKUP, 0x03, 0x00000000);
  }
  else {	// On
    if (pos < -100)
    DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV + 199),
		 SS_MKDN, 0x03, 0x02020000);  
  else if (pos >= -100 && pos <= 100)
    DpySpec_draw(DPYPOS(DPYWAH - 4, DPYWAV + 100 - pos - 4),
		 SS_MKLT, 0x03, 0x02020000);
  else		// pos > 100
    DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV - 8),
		 SS_MKUP, 0x03, 0x02020000);
  }
}

/*!*****************************************************************************
 @brief		Position2 Marker draw
 @details	�������� ��� ���������� ������ ������� ����� ������ 2
 @param		On - ���/����
 @return	
 @note		
 */
void PosChan2_draw(bool On) {
  int32_t pos = Chan2Ctrl.SigPos / 2U - 256;
#ifdef INVPOS_USE
  if (Chan2Ctrl.Inv) pos = -pos;
#endif
  if (!On) {
    if (pos < -100)
      DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV + 199),
		   SS_MKDN, 0x0c, 0x00000000);  
    else if (pos >= -100 && pos <= 100)
      DpySpec_draw(DPYPOS(DPYWAH - 4, DPYWAV + 100 - pos - 4),
		   SS_MKLT, 0x0c, 0x00000000);
    else	// pos > 100
      DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV - 8),
		   SS_MKUP, 0x0C, 0x00000000);
  }
  else {	// On
    if (pos < -100)
    DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV + 199),
		 SS_MKDN, 0x0C, 0x08080000);  
  else if (pos >= -100 && pos <= 100)
    DpySpec_draw(DPYPOS(DPYWAH - 4, DPYWAV + 100 - pos - 4),
		 SS_MKLT, 0x0C, 0x08080000);
  else	// pos > 100
    DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV - 8),
		 SS_MKUP, 0x0C, 0x08080000);
  }
}

/*!*****************************************************************************
 @brief		Trigger Level draw
 @details	���������� ������ ������ ������������� (����� ��� ����)
 @param		On - ���/����
 */
void TrigLev_draw(bool On) {
  if (GenCtrl.Menu) return;
  
  int32_t lev = TrigCtrl.Level / 2U - 256;
  int32_t pos = 0;
  if (TrigCtrl.Sour == 1) pos = Chan1Ctrl.SigPos / 2 - 256;
  if (TrigCtrl.Sour == 2) pos = Chan2Ctrl.SigPos / 2 - 256;
  lev += pos;
//  Num_draw(lev);
  
  if (!On) {		// !On
    if (lev < -100)
      DpySpec_draw(DPYPOS(DPYWAH + 300 + 1, DPYWAV + 199),
		   SS_MKDN, 0x10, 0x00000000);  
    else if (lev >= -100 && lev <= 100)
      DpySpec_draw(DPYPOS(DPYWAH + 300 - 3, DPYWAV + 100 - lev - 4),
		   SS_MKRT, 0x10, 0x00000000);
    else		// lev > 100
      DpySpec_draw(DPYPOS(DPYWAH + 300 + 1, DPYWAV - 8),
		   SS_MKUP, 0x10, 0x00000000);
  }
  else {		// On
    if (lev < -100)
    DpySpec_draw(DPYPOS(DPYWAH + 300 + 1, DPYWAV + 199),
		 SS_MKDN, 0x10, 0x10100000);  
  else if (lev >= -100 && lev <= 100)
    DpySpec_draw(DPYPOS(DPYWAH + 300 - 3, DPYWAV + 100 - lev - 4),
		 SS_MKRT, 0x10, 0x10100000);
  else			// lev > 100
    DpySpec_draw(DPYPOS(DPYWAH + 300 + 1, DPYWAV - 8),
		 SS_MKUP, 0x10, 0x10100000);
  }
}


/*!*****************************************************************************
 @brief		Pretrigger Marker draw
 @details	�������� ��� ���������� ������ ������� �������������
 @param		On - ���/����
 @return	
 @note		
 */
void Pret_draw(bool On) {
  int32_t pret = (SweepCtrl.Pret & 0x1F) << (MemCtrl.SizeNum + 5); // ����������
  int32_t pos = SweepCtrl.TimePos;
  int32_t offset = pret - pos;
  if (!On) {
    if (offset < 0)
      DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV - 8),
		   SS_MKRT, 0x0F, 0x00000000);  
    else if (offset >= 0 && offset <= 300)
      DpySpec_draw(DPYPOS(DPYWAH + offset - 3, DPYWAV - 5),
		   SS_MKDN, 0x0F, 0x00000000);
    else	// offset > 300
      DpySpec_draw(DPYPOS(DPYWAH + 300, DPYWAV - 8),
		   SS_MKLT, 0x0F, 0x00000000);
  }
  else {	// On
    if (offset < 0)
    DpySpec_draw(DPYPOS(DPYWAH - 7, DPYWAV - 8),
		 SS_MKRT, 0x0F, 0x0A0A0000);  
  else if (offset >= 0 && offset <= 300)
    DpySpec_draw(DPYPOS(DPYWAH+offset - 3, DPYWAV - 5),
		 SS_MKDN, 0x0F, 0x0A0A0000);
  else	// offset > 300
    DpySpec_draw(DPYPOS(DPYWAH + 300, DPYWAV - 8),
		 SS_MKLT, 0x0F, 0x0A0A0000);
  }
}

/*!*****************************************************************************
 @brief		
 @details	������������ ������� ����� �������� ����
 @return	
 */
void Curs_redraw(void) {
  if (CursCtrl.On) Curs_draw(true);
}

/*!*****************************************************************************
 @details	���������� (�������) �������
 @param		On - ���/����
 @note		
 */
void Curs_draw(bool On) {
  if (CursCtrl.CX1 >= SweepCtrl.TimePos &&
      CursCtrl.CX1 <= SweepCtrl.TimePos + (DispCtrl.Wide ? 300 : 250)) {
    DpyLineVert_draw(DPYPOS(DPYWAH - SweepCtrl.TimePos + CursCtrl.CX1, DPYWAV),
			200, 0x00668000 | On << 7);
  }
  if (CursCtrl.CX2 >= SweepCtrl.TimePos &&
      CursCtrl.CX2 <= SweepCtrl.TimePos + (DispCtrl.Wide ? 300 : 250)) {
    DpyLineVert_draw(DPYPOS(DPYWAH - SweepCtrl.TimePos + CursCtrl.CX2, DPYWAV),
			200, 0x003C8000 | On << 7);
  }
  if (CursCtrl.CY1 >= 128 - 100 && CursCtrl.CY1 <= 128 + 100) {
    DpyLineHorz_draw(DPYPOS(DPYWAH, DPYWAV + (228 - CursCtrl.CY1)),
			(DispCtrl.Wide ? 300 : 250), 0x00668000 | On << 7);
  }
  if (CursCtrl.CY2 >= 128 - 100 && CursCtrl.CY2 <= 128 + 100) {
    DpyLineHorz_draw(DPYPOS(DPYWAH, DPYWAV + (228 - CursCtrl.CY2)),
			(DispCtrl.Wide ? 300 : 250), 0x003C8000 | On << 7);
  }

}

/*!*****************************************************************************
 @brief		Signal Memory clear
 @details	�������� ������ ��������
 @param		
 @return	
 @note		
 */
void Sig_clear(void) {
  uint16_t *pSig1 = SigChan1.Buf16K;
  uint16_t *pSig2 = SigChan2.Buf16K;
  for (uint32_t i = 16384; i--; ) {
    *pSig1++ = 0;
    *pSig2++ = 0;
  }
}

/*!*****************************************************************************
 @brief		Channels 2|1 cos|sin load for test
 @details	��������� ������ ������� ������� � ���������
 @return	
 @note		
 */
void SigChanAC_load(void) {
  uint16_t *pSigChan1 = SigChan1.Buf16K;
  uint16_t *pSigChan2 = SigChan2.Buf16K;
  for (uint32_t i = 16384; i--; ) {
    *pSigChan1++ = (uint8_t)(128 + 75 * cos(2 * 3.1415926 * i / 128)) << 8;
    *pSigChan2++ = (uint8_t)(128 + 75 * sin(2 * 3.1415926 * i / 128)) << 8;
  }
}

/*!*****************************************************************************
 @brief		Channels 2|1 random noise load
 @details	��������� ������ ������� ���������� �������� � ��������� �����
 @return	
 @note		
 */
void SigChanDC_load(void) {
  uint16_t *pSigChan1 = SigChan1.Buf16K;
  uint16_t *pSigChan2 = SigChan2.Buf16K;
  for (uint32_t i = 16384; i--; ) {
    uint16_t temp = rand();
    *pSigChan1++ = 0x7A7A
		 + ((temp + (temp >> 2) + (temp >> 4) + (temp >> 6)) & 0x0707);
    temp = rand();
    *pSigChan2++ = 0x7A7A
		 + ((temp + (temp >> 2) + (temp >> 4) + (temp >> 6)) & 0x0707);
  }
}

/*!*****************************************************************************
 @brief		Signals dots both or one channel read-average from DotBuf to Buf
 @details	���������� � ��������� ����� �� ������ ����� � ����� �������
 @return	
 @note		
 */
void SigDots_rdavr(void) {
  FrameCnt++;				// ��������� ������� ������ � ���������� �������
  if (!FrameCnt) FrameCnt--;		// ���� ���� ������������, �������� �� ���������
  uint32_t cnt = FrameCnt;		// ������� ������ � ���������� �������
  uint32_t clog = 0;			// �������� �������� ������������ ������
  while (cnt >>= 1) clog++;
  clog--;				// ��� 1-�� ����� ��� ���������� (>>0)
  uint32_t aver = AcquCtrl.Aver >> 2;	// ��� ����������
  if (clog < aver) aver = clog;
  
/* �������� � ������ 16-������� ������� ������� (� ��������, �� � ������!) */  
  uint16_t *pSigChan1 = SigChan1.Buf16K
		      + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
  uint16_t *pSigChan2 = SigChan2.Buf16K
		      + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
  uint32_t temp_dot;
  uint32_t temp_mem;
    
/* ���������� ���������� ������ */
  for (uint32_t i = SweepCtrl.Pret << MemCtrl.SizeNum + 5; i--; ) {
    temp_dot = (uint32_t)*pDotBuf++;	// ��������� ��� ������ (00002211)
    if (pDotBuf == DotBuf + 16384) pDotBuf = DotBuf;	// ���������� ���������
    if (Chan1Ctrl.On) {
      temp_mem = *pSigChan1 << 16;	// ��������� � ������� ������� (iiff0000)
      temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
      temp_mem += ((temp_dot & 0x00FF) << 24) >> aver;	// �������� ����� ������
      *pSigChan1++ = temp_mem >> 16;	// ��������� ������� �������
    }
    if (Chan2Ctrl.On) {
      temp_mem = *pSigChan2 << 16;	// ��������� � ������� ������� (iiff0000)
      temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
      temp_mem += ((temp_dot & 0xFF00) << 16) >> aver;	// �������� ����� ������
      *pSigChan2++ = temp_mem >> 16;	// ��������� ������� �������
    }
  }  
}



/*!*****************************************************************************
 @brief		Signals both, one, neither channels read-average from PL to MCU
 @details	���������� � ��������� ������� �� ���� � ��
 @return	
 @note		
 */
void SigChans_rdavr(void) {
  FrameCnt++;			// ��������� ������� ������ � ���������� �������
  if (!FrameCnt) FrameCnt--;	// ���� ���� ������������, �������� �� ���������
  uint32_t cnt = FrameCnt;		// ������� ������ � ���������� �������
  uint32_t clog = 0;			// �������� �������� ������������ ������
  while (cnt >>= 1) clog++;
  clog--;				// ��� 1-�� ����� ��� ���������� (>>0)
  uint32_t aver = AcquCtrl.Aver >> 2;	// ��� ����������
  if (clog < aver) aver = clog;

/* �������� � ������ 16-������� ������� ������� (� ��������, �� � ������!) */  
  uint16_t *pSigChan1 = SigChan1.Buf16K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
  uint16_t *pSigChan2 = SigChan2.Buf16K + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;

// �������������� ��������� �� ���������� ���������
/*  
  if (Interp.Tcur > Interp.Tmts >> 16) {
    DpyCharPad_draw(DPYPOS(DPYWAH + 300 - 2 * 8 - 2, 1), '>', 0xf3f30000);
    pSigChan1 += 1; 
    pSigChan2 += 1; 
  }
  else DpyCharPad_draw(DPYPOS(DPYWAH + 300 - 2 * 8 - 2, 1), '<', 0xf3f30000);
  // Num_draw(Interp.Tcur);
 */
  
  uint32_t temp_pld;
  uint32_t temp_mem;
    
/* ���������� ���������� ������ */
  for (uint32_t i = 1024 << MemCtrl.SizeNum; i--; ) {
    temp_pld = (uint32_t)PL->MINT;	// ��������� ��� ������ (00002211)
    if (Chan1Ctrl.On) {
      temp_mem = *pSigChan1 << 16;	// ��������� � ������� ������� (iiff0000)
      temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
      temp_mem += ((temp_pld & 0x00FF) << 24) >> aver;	// �������� ����� ������
      *pSigChan1++ = temp_mem >> 16;	// ��������� ������� �������
    }
    if (Chan2Ctrl.On) {
      temp_mem = *pSigChan2 << 16;	// ��������� � ������� ������� (iiff0000)
      temp_mem -= temp_mem >> aver;	// ��������� �� �������� ���������� (0iiff000)
      temp_mem += ((temp_pld & 0xFF00) << 16) >> aver;	// �������� ����� ������
      *pSigChan2++ = temp_mem >> 16;	// ��������� ������� �������
    }
  }
}

/*!*****************************************************************************
 @brief		Signals Buffer clear
 @details	�������� ������ ��������
 @return	
 @note		
 */
void SigChans_clear(void) {
// �������� � ������ 16-������� ������� ������� (� ��������, �� � ������!)  
  uint32_t offset = (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
  uint16_t *pSigChan1 = SigChan1.Buf16K + offset;
  uint16_t *pSigChan2 = SigChan2.Buf16K + offset;
// �������� ������
  for (uint32_t i = 1024 << MemCtrl.SizeNum; i--; ) {
    *pSigChan1++ = 0;
    *pSigChan2++ = 0;
  }
}

/*!*****************************************************************************
 @brief		Memory Bar draw
 @details	���������� ������ ������ ��������
 @return	
 @note		����� ������ 128 ����� (� 8 ��� ������ ������ 1K)
 */
void MemBar_draw(void) {
  DpyLineHorz_draw(DPYPOS(DPYWAH + 125 - 64, 6), 128, 0x00FFFF40);
  DpyLineVert_draw(DPYPOS(DPYWAH + 125 - 64, 4), 5, 0x00FFFF40);
  DpyLineVert_draw(DPYPOS(DPYWAH + 125 + 64, 4), 5, 0x00FFFF40);  
}

/*!*****************************************************************************
 @brief		Memory Bar Pretrigger draw
 @details	���������� ������� ����������� �� ������ ������
 @return	
 @note		
 */
void MemBarPret_draw(bool On) {
  int32_t pret = SweepCtrl.Pret << 2;	// ��� ����� 4 �����
  if (!On) {				// �������
    DpySpec_draw(DPYPOS(DPYWAH + 125 - 64 + pret - 3, 0),
		 SS_MKSM, 0x0F, 0x00000000);  
  }
  else {				// ����������
    DpySpec_draw(DPYPOS(DPYWAH + 125 - 64 + pret - 3, 0),
		 SS_MKSM, 0x0F, 0x0A0A0000);
  }
}

/*!*****************************************************************************
 @brief		Memory Bar Position draw
 @details	���������� ������� ������ �� ������ ������
 @return	
 @note		
 */
void MemBarPos_draw(bool On) {
  int32_t pos = SweepCtrl.TimePos >> MemCtrl.SizeNum + 3;
  // int32_t size = DispCtrl.Wide ? 75 : 62;
  int32_t size = 300 >> MemCtrl.SizeNum + 3; 
  // int32_t color = On ? 0x00FFFFCC : 0x00FFFF00;		// �������� CC
  int32_t color = On ? 0x00FFFF0A : 0x00FFFF00;		// ��� ��� ������ 0F
  DpyLineHorz_draw(DPYPOS(DPYWAH + 125 - 64 + pos, 5), size, color);
  DpyLineHorz_draw(DPYPOS(DPYWAH + 125 - 64 + pos, 7), size, color);
}

/*!*****************************************************************************
 @brief		Mathematics execute
 @details	��������� �������������� ������� 
 @return	
 @note		
 */
void Math_exe(void) {
#ifdef MATH_USE
  DpyWork_clear(MASK_MAT);  
  if (!MathCtrl.On) return;
  if (MathCtrl.Fun == MATH_SUM) Sum_draw(true);
  else if (MathCtrl.Fun == MATH_MULT) Mult_draw(true);
  else if (MathCtrl.Fun == MATH_FFT) {
    FFT_calc();
    FFT_draw(true);
  }
#endif
}

/*!*****************************************************************************
 @brief		Summa draw
 @details	���������� ����� ������� 
 @return	
 @note		
 */
void Sum_draw(bool bright) {
  if (DispCtrl.Vect)	SumVect_draw(bright);
  else			SumDots_draw(bright);
}

/*!*****************************************************************************
 @brief		Summa Dots draw
 @details	���������� ����� ����� ��������, ����������� �� ������� � ������
 @param		bright - ������� 1, 0 (����)
 @return	
 @note		lmarg, rmarg - ������� ��������� �������
 */
void SumDots_draw(bool bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  int32_t lmarg = (SigCtrl.SigBeg > SweepCtrl.TimePos) ?
                   SigCtrl.SigBeg - SweepCtrl.TimePos : 0;
  int32_t rmarg = (SigCtrl.SigEnd < SweepCtrl.TimePos + width) ?
                   SigCtrl.SigEnd - SweepCtrl.TimePos : width;
  if (lmarg >= width || rmarg < 0) return;
  uint16_t *pSig1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum 
		 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pSig2 = SigChan2.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum 
		 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pLim1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
/* ������� ��������� ������ ������� */
  if (pSig1 >= pLim1) {
    pSig1 -= (1024 << MemCtrl.SizeNum);
    pSig2 -= (1024 << MemCtrl.SizeNum);
  }
  volatile uint8_t *pDpy;
  for (uint32_t i = lmarg; i < rmarg; i++) {
    int16_t temp1 = (*pSig1++) >> 8;	// ������� (�����) �����
    int16_t temp2 = (*pSig2++) >> 8;	// ������� (�����) �����
    if (pSig1 >= pLim1) {
      pSig1 -= (1024 << MemCtrl.SizeNum);
      pSig2 -= (1024 << MemCtrl.SizeNum);
    }
#ifdef INVPOS_USE
    if (Chan1Ctrl.Inv) temp1 = 0x100 - temp1;
    if (Chan2Ctrl.Inv) temp2 = 0x100 - temp2;   
#else
    if (Chan1Ctrl.Inv) temp1 = (Chan1Ctrl.SigPos) - temp1 - 256 - Chan1Ctrl.DispPos;
    if (Chan2Ctrl.Inv) temp2 = (Chan2Ctrl.SigPos) - temp2 - 256 - Chan2Ctrl.DispPos;    
#endif
    temp1 = (Chan1Ctrl.DispPos / 2U + temp1);
    temp2 = (Chan2Ctrl.DispPos / 2U + temp2);
    
    pDpy = (uint8_t *)(DPYBUF_BASE + DPYWAH + i 
	 + 320 * (DPYWAV + 228 - (temp1 + temp2 - 128)));
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) { 
      uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 4) & 0x10;  *pDpy = pix;
    }
  }
}

/*!*****************************************************************************
 @brief		Summa Vectors draw
 @details	���������� ����� ����� ��������, ����������� �� ������� � ������
 @param		bright - ������� 1, 0 (����)
 @return	
 @note		lmarg, rmarg - ������� ��������� �������
 */
void SumVect_draw(bool bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  int32_t lmarg = (SigCtrl.SigBeg > SweepCtrl.TimePos) ?
                   SigCtrl.SigBeg - SweepCtrl.TimePos : 0;
  int32_t rmarg = (SigCtrl.SigEnd < SweepCtrl.TimePos + width) ?
                   SigCtrl.SigEnd - SweepCtrl.TimePos : width;
  if (lmarg >= width || rmarg < 0) return;
  uint16_t *pSig1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
                 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pSig2 = SigChan2.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
                 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pLim1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
/* ������� ��������� ������ ������� */
  if (pSig1 >= pLim1) {
    pSig1 -= (1024 << MemCtrl.SizeNum);
    pSig2 -= (1024 << MemCtrl.SizeNum);
  }
  uint32_t t1p, t2p, t1n, t2n;		// previous & next samples two channels
/* ���� ����� ������ �������� � ��������� */
  for (int32_t i = lmarg; i < rmarg; i++) {
    t1p = (*pSig1++) >> 8;		// integer part, begin
    t2p = (*pSig2++) >> 8;
    if (pSig1 >= pLim1) {
      pSig1 -= (1024 << MemCtrl.SizeNum);
      pSig2 -= (1024 << MemCtrl.SizeNum);
    }
    t1n = (*pSig1) >> 8;		// integer part, end
    t2n = (*pSig2) >> 8;
#ifdef INVPOS_USE
    if (Chan1Ctrl.Inv) {
      t1p = 0x100 - t1p;
      t1n = 0x100 - t1n;
    }
    if (Chan2Ctrl.Inv) {
      t2p = 0x100 - t2p;
      t2n = 0x100 - t2n;
    }
#else
    if (Chan1Ctrl.Inv) {
      t1p = (Chan1Ctrl.SigPos) - t1p - 256 - Chan1Ctrl.DispPos;
      t1n = (Chan1Ctrl.SigPos) - t1n - 256 - Chan1Ctrl.DispPos;
    }
    if (Chan2Ctrl.Inv) {
      t2p = (Chan2Ctrl.SigPos) - t2p - 256 - Chan2Ctrl.DispPos;
      t2n = (Chan2Ctrl.SigPos) - t2n - 256 - Chan2Ctrl.DispPos;
    }
#endif
    t1p += Chan1Ctrl.DispPos / 2U;
    t1n += Chan1Ctrl.DispPos / 2U;
    t2p += Chan2Ctrl.DispPos / 2U;
    t2n += Chan2Ctrl.DispPos / 2U;
    int32_t s1, s2, brk;
    s1 = t1p + t2p - 128;
    s2 = t1n + t2n - 128;
#ifdef STRA_VECT
    brk = (s1 == s2) ? s1 : ((s1 > s2) ? (s1 - 1) : (s1 + 1));
#else
    brk = (t1p + t2p + t1n + t2n - 256) >> 1;
#endif   
    VectMath_draw(s1, brk, s2, i, bright);
  }
}

/*!*****************************************************************************
 @brief		Multiply draw
 @details	���������� ������������ ������� 
 @return	
 @note		
 */
void Mult_draw(bool bright) {
  if (DispCtrl.Vect)	MultVect_draw(bright);
  else			MultDots_draw(bright);
}

/*!*****************************************************************************
 @brief		Multiply Dots draw
 @details	���������� ����� ������������ ��������
 @param		bright - �������
 @return	
 @note		lmarg, rmarg - ������� ��������� �������
 */
void MultDots_draw(bool bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  int32_t lmarg = (SigCtrl.SigBeg > SweepCtrl.TimePos) ?
                   SigCtrl.SigBeg - SweepCtrl.TimePos : 0;
  int32_t rmarg = (SigCtrl.SigEnd < SweepCtrl.TimePos + width) ?
                   SigCtrl.SigEnd - SweepCtrl.TimePos : width;
  if (lmarg >= width || rmarg < 0) return;
  uint16_t *pSig1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum 
		 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pSig2 = SigChan2.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum 
		 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pLim1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
/* ������� ��������� ������ ������� */
  if (pSig1 >= pLim1) {
    pSig1 -= (1024 << MemCtrl.SizeNum);
    pSig2 -= (1024 << MemCtrl.SizeNum);
  }
  volatile uint8_t *pDpy;
  for (uint32_t i = lmarg; i < rmarg; i++) {
    int16_t temp1 = ((*pSig1++) >> 8) - 128;	// ������� (�����) �����
    int16_t temp2 = ((*pSig2++) >> 8) - 128;	// ������� (�����) �����
    if (pSig1 >= pLim1) {
      pSig1 -= (1024 << MemCtrl.SizeNum);
      pSig2 -= (1024 << MemCtrl.SizeNum);
    }
    temp1 = temp1 - (Chan1Ctrl.SigPos / 2U - 256);
    temp2 = temp2 - (Chan2Ctrl.SigPos / 2U - 256);
    int16_t res = (temp1 * temp2) / 64 + 128;

    pDpy = (uint8_t *)(DPYBUF_BASE + DPYWAH + i 
	 + 320 * (DPYWAV + 228 - res));
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) { 
      uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 4) & 0x10;  *pDpy = pix;
    }
  }
}

/*!*****************************************************************************
 @brief		Multiply Vectors draw 
 */
void MultVect_draw(bool bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  int32_t lmarg = (SigCtrl.SigBeg > SweepCtrl.TimePos) ?
                   SigCtrl.SigBeg - SweepCtrl.TimePos : 0;
  int32_t rmarg = (SigCtrl.SigEnd < SweepCtrl.TimePos + width) ?
                   SigCtrl.SigEnd - SweepCtrl.TimePos : width;
  if (lmarg >= width || rmarg < 0) return;
  uint16_t *pSig1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
                 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pSig2 = SigChan2.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
                 + SweepCtrl.TimePos
		 + lmarg + SigCtrl.SigInx;
  uint16_t *pLim1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
/* ������� ��������� ������ ������� */
  if (pSig1 >= pLim1) {
    pSig1 -= (1024 << MemCtrl.SizeNum);
    pSig2 -= (1024 << MemCtrl.SizeNum);
  }

/* ���� ����� ������ �������� � ��������� */
  for (int32_t i = lmarg; i < rmarg; i++) {
    int16_t t1p = ((*pSig1++) >> 8) - 128;	// integer part Ch1, previous
    int16_t t2p = ((*pSig2++) >> 8) - 128;	// integer part Ch2, previous
    if (pSig1 >= pLim1) {
      pSig1 -= (1024 << MemCtrl.SizeNum);
      pSig2 -= (1024 << MemCtrl.SizeNum);
    }
    int16_t t1n = ((*pSig1) >> 8) - 128;	// integer part Ch1, next
    int16_t t2n = ((*pSig2) >> 8) - 128;	// integer part Ch2, next
    
    t1p -= Chan1Ctrl.SigPos / 2U - 256;
    t2p -= Chan2Ctrl.SigPos / 2U - 256;

    
    t1n -= Chan1Ctrl.SigPos / 2U - 256;
    t2n -= Chan2Ctrl.SigPos / 2U - 256;

    int32_t s1 = (t1p * t2p) / 64 + 128;
    int32_t s2 = (t1n * t2n) / 64 + 128;
    int32_t brk = (s1 == s2) ? s1 : ((s1 > s2) ? (s1 - 1) : (s1 + 1));
  
    VectMath_draw(s1, brk, s2, i, bright);
  }
}


/*__ ��������� ������� ________________________________________________________*/

/*!*****************************************************************************
 @brief		Move Dot from FPGA to Dot Buffer
 @details	���������� ������� ��� �� ���� � ����� �����
 @return	
 @note		pDot ��������� �� ��������� ���������� �����
 */
void Sweep_start(void) {
  if (SweepCtrl.Mode == 2) {		// ���� ����� �����������
    SweepCtrl.Stop = 1;			// ����������
    StSp_disp();			// ��������
  }
  else PL->STAT = PL_START_ACQUST;	// ����� ������ �����
}

#if false
/*!*****************************************************************************
 @brief		Move Dot from FPGA to Dot Buffer
 @details	���������� ������� ��� �� ���� � ����� �����
 @return	
 @note		pDot ��������� �� ��������� ���������� �����
 */
void Dot_move(void) {
  pDot++;
  if (pDotBuf >= DotBuf + 16384) pDotBuf = DotBuf;
  *pDotBuf = PL->SBREG;
}
#endif

/*!*****************************************************************************
 @brief		One Math Vector draw
 @details	���������� ������ (� ���� �������� ��������)
 @param		s1, brk, s2
 @param		dpos - ������� ������ ������� �� �����������
 @param		bright - ������� 1, 0 (����)
 @return	
 @note		
 */
void VectMath_draw(int32_t s1, int32_t brk, int32_t s2, 
		uint32_t dpos, bool bright)
{
//  if (SigCtrl.SigNum == FRAME_SPARSE && (!(s1) || !(s2))) return;
  if (SigCtrl.SigNum == FRAME_SPARSE && (s1 < 8 || s2 < 8)) return;

  uint32_t size;			// ������ �������
  uint8_t *pDpy = (uint8_t *)(DPYBUF_BASE + DPYWAH + dpos + 320 * (DPYWAV + 228 - s1));
/* �� ����� ������� �� �������� */
  if (s1 < brk) {			// up vector			
    size = brk - s1;
    for (uint32_t j = size; j--; ) {
      pDpy -= 320;			// ����������� - ����������
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy; pix ^= (pix ^ bright << 4) & 0x10; *pDpy = pix;
      }
    }
  }
  else if (s1 > brk) {		// down vector
    size = s1 - brk;
    for (uint32_t j = size; j--; ) {
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy; pix ^= (pix ^ bright << 4) & 0x10; *pDpy = pix;
      }
      pDpy += 320;			// ���������� - �����������
    }
  }
  else {				// s1 == brk, right vector
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
      uint8_t pix = *pDpy; pix ^= (pix ^ bright << 4) & 0x10; *pDpy = pix;
    }
  }
/* ����� �� ��������� ��� */
  pDpy++;
/* �� �������� �� ������ ������� */    
  if (brk < s2) {			// up vector  
    size = s2 - brk;
    for (uint32_t j = size; j--; ) {
      pDpy -= 320;			// ����������� - ����������    
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy; pix ^= (pix ^ bright << 4) & 0x10; *pDpy = pix;
      }
    }
  }
  else if (brk > s2) {		// down vector
    size = brk - s2;
    for (uint32_t j = size; j--; ) {
      if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) {
        uint8_t pix = *pDpy; pix ^= (pix ^ bright << 4) & 0x10; *pDpy = pix;
      }
      pDpy += 320;			// ���������� - �����������      
    }
  }
}


/*!*****************************************************************************
 @brief		Measure parameters of signal
 @details	�������� ��������� ������� �� ����� ������
 @return	
 @note		����������� � ������� ����� �����
 @note		�������� �������� 0...1023 ����������� � 2 ����,
		� ��� �������� ���������� ������ 256.
		� ����� ����� ������� ����������� 128,
		� ��� �������� ������������ �� 256.
 */
void SigPar_meas(void) {
  if (!MeasCtrl.On) return;
  // if (CursCtrl.On) return;

  uint8_t Meas1Txt[10];
  uint8_t Meas2Txt[10];
  
// �������� ������ (�� ���������)
  NumWrong_conv(Meas1Txt);
  NumWrong_conv(Meas2Txt);

/* 1. ����� �����������, ������������ � ������� �������� */

  uint16_t *pSig = (MeasCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
		 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;

  uint32_t	min = 255 << 8;
  uint32_t	max = 0 << 0;
  uint32_t	mean = 0 << 0;
  
  for (uint32_t i = 1024 << MemCtrl.SizeNum; i--; ) {
    uint32_t temp = *pSig++;		// ��������� �����, ������� �� ��������� 
    if (temp < min) min = temp;		// ����� �������
    if (temp > max) max = temp;		// ����� ��������
    mean += temp;			// �����������
  }
  mean >>= 9 + MemCtrl.SizeNum;		// �������� �� ����� ����������
  // Num_draw(min >> 8);
  // Num_draw(max >> 8);  
  // Num_draw(mean >> 8);

/*
  ���� ������� ��� �������� - �� �������, ��������� ��������� ����� ��������
  ��� �������� � ��������� ����� ��������� ������ ������� ��� ��������
  if ((min >> 8) == 0 || (min >> 8) == 0xFF)
  if ((max >> 8) == 0 || (max >> 8) == 0xFF)
 */
  if ((min >> 8) != 0 && (max >> 8) != 0xFF)
  {
/* ��������� ���������� ����� ������������ */  

/* 2. ��������� �������, ��������, ������ ��� �������, ���� ����� */

    if ((MeasCtrl.Par1 >> 2) >= PAR_MIN ||
        (MeasCtrl.Par2 >> 2) >= PAR_MIN)
    {

      uint32_t volt = (MeasCtrl.Sour ? Chan2Ctrl.VoltNum : Chan1Ctrl.VoltNum) - 6
                    + (MeasCtrl.Sour ? Chan2Ctrl.Prb : Chan1Ctrl.Prb) * 3 + 7;
      uint32_t spos = MeasCtrl.Sour ? Chan2Ctrl.SigPos : Chan1Ctrl.SigPos;

      switch (MeasCtrl.Par1 >> 2) {
      case PAR_MIN:
        Num2Volt_conv((min >> 8) + 128 - (spos >> 1), volt, Meas1Txt);
        break;
      case PAR_MAX:
        Num2Volt_conv((max >> 8) + 128 - (spos >> 1), volt, Meas1Txt);
        break;
      case PAR_AMP:
        Num2Volt_conv((max - min) >> 8, volt, Meas1Txt);
        break;
      case PAR_AVR:
        Num2Volt_conv((mean >> 8) + 128 - (spos >> 1), volt, Meas1Txt);
        break;  
      }

      switch (MeasCtrl.Par2 >> 2) {
      case PAR_MIN:
        Num2Volt_conv((min >> 8) + 128 - (spos >> 1), volt, Meas2Txt);
        break;
      case PAR_MAX:
        Num2Volt_conv((max >> 8) + 128 - (spos >> 1), volt, Meas2Txt);
        break;
      case PAR_AMP:
        Num2Volt_conv((max - min) >> 8, volt, Meas2Txt);
        break;
      case PAR_AVR:
        Num2Volt_conv((mean >> 8) + 128 - (spos >> 1), volt, Meas2Txt);
        break;  
      }
    }

/* 3. ����� ������������ ������� � �������� �������, ������ � �������
      ���� ����� */

    if (((MeasCtrl.Par1 >> 2) <= PAR_WIP
     || (MeasCtrl.Par2 >> 2) <= PAR_WIP)
     && ((max - min) >> 8) > 8)
    {
// ����� ��������
      uint32_t mid = (max + min) / 2;
    
// ��������� ������� ���������� � ������    
      uint16_t *pSig = (MeasCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
		     + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
		     
// ��������� �� ����� ������� �������, �� 1 ������ 
      uint16_t *pEnd = (MeasCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
                     + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);

      bool stlo = false;		// ������ � ������ ����� ���� ������
      bool find = false;		// ������� ������
 
// ������ ������ �� ��������� ������� ������� (+- 4?)
      while (pSig < pEnd) {
	if (*pSig < mid - 4 || *pSig > mid + 4) {
	  if (*pSig < mid - 4) stlo = true;
	  find = true;
	  break;
	}
	pSig++;
      }
// ���� ������ �������, ����������...
      if (find) {
// ����� ������ ������� ����� �������� ����� ������� �� ������� ����
        find = false;
        if (stlo) {			// ������ �����
          while (pSig < pEnd) {
	    if (*pSig > mid) {
	      find = true;
	      break;
	    }
	    pSig++;
	  }
	}
	else {				// ������ ����
	  while (pSig < pEnd) {
	    if (*pSig < mid) {
	      find = true;
	      break;
	    }
	    pSig++;
	  }
	}
// ��������� ����� ������� ��������
	uint16_t *T1 = pSig;
// ������������� �� ��������� �������
	pSig++;
	pSig++;
	pSig++;
// ���� ���� ����������, ������ ������...
	if (pSig > pEnd) find = false;

// ���� ������ ������� ������, ����������...
	if (find) {
// ������ ������ ������� ����� ��������
	  find = false;
	  if (stlo) {			// ������ ����
	    while (pSig < pEnd) {
	      if (*pSig < mid) {
	        find = true;
		break;
	      }
	      pSig++;
	    }
	  }
	  else {			// ������ �����
	    while (pSig < pEnd) {
	      if (*pSig > mid) {
	        find = true;
		break;
	      }
	      pSig++;
	    }
	  }
// ��������� ����� ������� ��������
          uint16_t *T2 = pSig;
// ������������� �� ��������� �������
	  pSig++;
	  pSig++;
	  pSig++;
// ���� ���� ����������, ������ ������...
	  if (pSig > pEnd) find = false;

// ���� ������ ������� ������, ����������...
          if (find) {
// ������ ������ ������� ����� ��������
            find = false;
	    if (stlo) {			// ������ �����
	      while (pSig < pEnd) {
	        if (*pSig > mid) {
		  find = true;
		  break;
		}
		pSig++;
	      }
	    }
	    else {			// ������ ����
	      while (pSig < pEnd) {
	        if (*pSig < mid) {
		  find = true;
		  break;
		}
		pSig++;
	      }
	    }
// ���� ������ ������� ������, ����� ������ ���������...
	    if (find) {
	      uint16_t *T3 = pSig;
	      // Num_draw(T3 - T1);

              switch (MeasCtrl.Par1 >> 2) {
              case PAR_TIM:
                Num2Time_conv(T3 - T1, Meas1Txt);
                break;
	      case PAR_FRQ:
	        Num2Freq_conv(T3 - T1, Meas1Txt);
		break;
              case PAR_WIN:
                Num2Time_conv(stlo ? (T3 - T2) : (T2 - T1), Meas1Txt);
                break;
              case PAR_WIP:
                Num2Time_conv(stlo ? (T2 - T1) : (T3 - T2), Meas1Txt);
                break;
              }
      
              switch (MeasCtrl.Par2 >> 2) {
              case PAR_TIM:
                Num2Time_conv(T3 - T1, Meas2Txt);
                break;
	      case PAR_FRQ:
	        Num2Freq_conv(T3 - T1, Meas2Txt);
		break;
              case PAR_WIN:
                Num2Time_conv(stlo ? (T3 - T2) : (T2 - T1), Meas2Txt);
                break;
              case PAR_WIP:
                Num2Time_conv(stlo ? (T2 - T1) : (T3 - T2), Meas2Txt);
                break;
              }
      
	    }			// find T3
	  }			// find T2
	}			// find T1
      }				// find signal
    }				// meas Period, Frequense, Width

/* 4. ����� ������������ ����� */

    if (((MeasCtrl.Par1 >> 2) == PAR_TFA
     || (MeasCtrl.Par2 >> 2) == PAR_TFA)
     && ((max - min) >> 8) > 8)
    {
// ��������� �� ������ ������� �������      
      uint16_t *pSig = (MeasCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
		     + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
// ��������� �� ����� ������� �������, �� 1 ������ 
      uint16_t *pEnd = (MeasCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
                     + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
// ������ 0.1, 0.9
      uint16_t trlo = min + (max - min) / 10;
      uint16_t trhi = max - (max - min) / 10;
      // Num_draw(trlo >> 8);
      // Num_draw(trhi >> 8);

      bool find = false;	// ��������� (�������) �������
// ������ ������ ��� �������
      while (pSig < pEnd) {
	if (*pSig > trhi) {
	  find = true;
	  break;
	}
	pSig++;
      }
// ���� ������ ��� �������, ����������...
      if (find) {
// ����� ������� ����� �����, ������ �����
        find = false;
	while (pSig < pEnd) {
	  if (*pSig < trhi) {
	    find = true;
	    break;
	  }
	  pSig++;
	}
// ���� ������ ������� ������, ����������...
	if (find) {
// ��������� ����� ������� ��������
	  uint16_t *T1 = pSig;
	  pSig++;
// ����� ������ ������� ����� ������ �����, ����� �����
	  find = false;
	  while (pSig < pEnd) {
	    if (*pSig < trlo) {
	      find = true;
	      break;
	    }
	    pSig++;
	  }
// ���� ������ ������� ������, ����������...
          if (find) {
// ��������� ����� ������� ��������
            uint16_t *T2 = pSig;
	    // Num_draw(T2 - T1);

// ������� ������������ �����
            if ((MeasCtrl.Par1 >> 2) == PAR_TFA)
              Num2Time_conv(T2 - T1, Meas1Txt);
            if ((MeasCtrl.Par2 >> 2) == PAR_TFA)
              Num2Time_conv(T2 - T1, Meas2Txt);

	  }			// find T2
	}			// find T1
      }				// find signal
    }				// meas Tfa

/* 5. ����� ������������ ������ */

    if (((MeasCtrl.Par1 >> 2) == PAR_TRI
     || (MeasCtrl.Par2 >> 2) == PAR_TRI)
     && ((max - min) >> 8) > 8)
    {
// ��������� �� ������ ������� �������      
      uint16_t *pSig = (MeasCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
		     + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
// ��������� �� ����� ������� �������, �� 1 ������ 
      uint16_t *pEnd = (MeasCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
                     + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
// ������ 0.1, 0.9
      uint16_t trlo = min + (max - min) / 10;
      uint16_t trhi = max - (max - min) / 10;
      // Num_draw(trlo >> 8);
      // Num_draw(trhi >> 8);

      bool find = false;	// ��������� (�������) �������
// ������ ������ ��� �������
      while (pSig < pEnd) {
	if (*pSig < trlo) {
	  find = true;
	  break;
	}
	pSig++;
      }
// ���� ������ ��� �������, ����������...
      if (find) {
// ����� ������� ����� �����, ������ ������
        find = false;
	while (pSig < pEnd) {
	  if (*pSig > trlo) {
	    find = true;
	    break;
	  }
	  pSig++;
	}
// ���� ������ ������� ������, ����������...
	if (find) {
// ��������� ����� ������� ��������
	  uint16_t *T1 = pSig;
	  pSig++;
// ����� ������ ������� ����� ������ �����, ����� ������
	  find = false;
	  while (pSig < pEnd) {
	    if (*pSig > trhi) {
	      find = true;
	      break;
	    }
	    pSig++;
	  }
// ���� ������ ������� ������, ����������...
          if (find) {
// ��������� ����� ������� ��������
            uint16_t *T2 = pSig;
	    // Num_draw(T2 - T1);

// ������� ������������ ������
            if ((MeasCtrl.Par1 >> 2) == PAR_TRI)
              Num2Time_conv(T2 - T1, Meas1Txt);
            if ((MeasCtrl.Par2 >> 2) == PAR_TRI)
              Num2Time_conv(T2 - T1, Meas2Txt);

	  }			// find T2
	}			// find T1
      }				// find signal
    }				// meas Tfa
    
  }				// ������ � �������� ���

/* 6. ���������� ���������� ��������� */

  DpyStringPad_draw(DPYPOS(DPYVALH, DPYVAL1V), Meas1Txt, 0xE2E20000, true);
  DpyStringPad_draw(DPYPOS(DPYVALH, DPYVAL2V), Meas2Txt, 0xE2E20000, true);
}

/*!*****************************************************************************
 @brief		Number Wrong
 @details	��������� ��������� �������, �������� "?"
 @param		*pBuf - ��������� �� ����� ���������� (9 �������� + \0)
 @note		
 */
void NumWrong_conv(uint8_t *pBuf) {
  *(uint32_t *)pBuf = 0x20202020;
  *(uint32_t *)(pBuf + 4) = 0x20202020;
  *(uint16_t *)(pBuf + 8) = 0x003F;
}

/*!*****************************************************************************
 @brief		Number to Volt
 @details	������������� ����� � ������
 @param		Num - �����
 @param		Volt - �/���, ���������� �������
 @param		*pBuf - ��������� �� ����� ���������� (9 �������� + \0)
 @note		
 */
void Num2Volt_conv(int32_t Num, uint32_t Volt, uint8_t *pBuf) {
  *(uint32_t *)pBuf = 0x20202020;		// "____xxxxx"x
  *(uint32_t *)(pBuf + 4) = 0x20202020;		// "________x"x
  
  if (Num < 0) {
    *pBuf = '-';
    Num = -Num;
  }
  else *pBuf = '+';
  
  uint32_t com = 4 - Volt % 9 / 3;		// comma pos
  *(pBuf + com - 1) = '0';			// "0_______x"x
  *(pBuf + com) = '.';				// "0.______x"x
  for (uint32_t i = com + 1; i < 6; i++)
    *(pBuf + i) = '0';				// "0.000___x"x
  *(pBuf + 6) = "k m\xB5"[Volt / 9];		// "0.000___x"x
  *(pBuf + 7) = 'V';				// "0.000_V_x"x
  *(pBuf + 8) = ' ';				// "0.000_V__"x 
  *(pBuf + 9) = '\0';				// "0.000_V__"\0
  
  static const uint32_t mag[] = {40, 20, 8};			// �-� ��������� ����������

  Num *= mag[Volt % 3];

  pBuf += 5;					// ��������� ����� � ������
  while (Num) {
    *pBuf-- = Num % 10 + '0';
    if (*pBuf == '.') pBuf--;
    Num /= 10;
  }
}

/*!*****************************************************************************
 @brief		Number to Time
 @details	������������� ����� �� �����
 @param		Num - �����
 @param		*pBuf - ��������� �� ����� ���������� (9 �������� + \0)
 @note		
 */
void Num2Time_conv(int32_t Num, uint8_t *pBuf) {
  *(uint32_t *)pBuf = 0x20202020;			// "    xxxxx"x
  *(uint32_t *)(pBuf + 4) = 0x20202020;			// "        x"x

  bool less = (Num < 2);
  
  uint32_t tcom = 5 - (SweepCtrl.TimeNum + 1) % 9 / 3;	// comma pos
  *(pBuf + tcom - 1) = '0';				// "__0_____x"x
  *(pBuf + tcom) = '.';					// "__0.____x"x
  for (uint32_t i = tcom + 1; i < 7; i++)
    *(pBuf + i) = '0';					// "__0.000_x"x
  *(pBuf + 7) = " m\xB5np"[(SweepCtrl.TimeNum + 1) / 9];// "______0mx"x
  *(pBuf + 8) = 's';					// "______0ms"x
  *(pBuf + 9) = '\0';					// "______0ms"\0

  static const uint32_t mag[] = {40, 20, 8};			// �-� ��������� ����������

  Num *= mag[(SweepCtrl.TimeNum + 1) % 3];

  pBuf += 6;					// ��������� ����� � ������
  while (Num) {
    *pBuf-- = Num % 10 + '0';
    if (*pBuf == '.') pBuf--;
    Num /= 10;
  }
  
  if (less) {
    while (*pBuf != ' ') *pBuf--;
    *pBuf = '<';
  }
}

/*!*****************************************************************************
 @brief		Number to Frequence
 @details	������������� ����� � �������
 @param		Num - �����
 @param		*pBuf - ��������� �� ����� ���������� (9 �������� + \0)
 @note		
 */
void Num2Freq_conv(int32_t Num, uint8_t *pBuf) {
  if (!Num) return;				// �� ������ �� 0
  *(uint32_t *)pBuf = 0x20202020;		// "    xxxxx"x
  *(uint32_t *)(pBuf + 4) = 0x20202020;		// "        x"x
  
  uint32_t fcom = 1 + (SweepCtrl.TimeNum + 8) % 9 / 3;		// comma pos
  uint32_t fmul = 1 + (SweepCtrl.TimeNum + 8) / 9;		// mult index
  Num = (500000000 >> (2 - (SweepCtrl.TimeNum + 2) % 3)) / Num;
  while (!(Num / 100000000)) {		// ���� ����� ��� �������� �����
    fcom--;				// ��������� ������� �����
    if (!fcom) {			// ���� ������� �� ����
      fcom = 3;				// ��������� ������� �� ������� 3
      fmul--;				// �������� ������ ���������
    }
    Num *= 10;				// ��������� �����
  }					// ������ ����� ������� � ������ ����
  *(pBuf + fcom) = '.';
  *(pBuf + 6) = "\xB5m kMG"[fmul];
  *(pBuf + 7) = 'H';
  *(pBuf + 8) = 'z';
  *(pBuf + 9) = '\0';
  pBuf += 5;
  Num /= 10000;				// �������� 5 �������� ����
    
  while (Num) {
    *pBuf-- = Num % 10 + '0';
    if (*pBuf == '.') pBuf--;
    Num /= 10;
  }
}

/*!*****************************************************************************
 @brief		XY draw
 @details	���������� ���� � ������ XY
 @param		���
 @note		
 */
void XYDots_draw(bool bright) {
  uint16_t *pSig1 = SigChan1.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
  uint16_t *pSig2 = SigChan2.Buf16K
                 + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum;
//  uint16_t *pLim1 = SigChan1.Buf16K
//                 + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);

  uint32_t width = DispCtrl.Wide ? 300 : 250;
  
  volatile uint8_t *pDpy;
/* �� ����� ����� ����� ��������� ����� �� ���� ������� */
  for (uint32_t i = 1024 << MemCtrl.SizeNum; i--; ) {
    int16_t temp1 = (*pSig1++) >> 8;	// ������� (�����) �����
    int16_t temp2 = (*pSig2++) >> 8;	// ������� (�����) �����
    
/* �������������, ���� ����� */
    if (Chan1Ctrl.Inv) temp1 = 0x100 - temp1;
    if (Chan2Ctrl.Inv) temp2 = 0x100 - temp2;   

/* �������� �������� */
    temp1 = (Chan1Ctrl.DispPos / 2U + temp1);
    temp2 = (Chan2Ctrl.DispPos / 2U + temp2);

/* �� ��������������� ��������� ������� ���� �� �������� */
    if (temp1 > width) break;
    
    pDpy = (uint8_t *)(DPYBUF_BASE + DPYWAH + temp1 
	 + 320 * (DPYWAV + 228 - temp2));

/* �� ������������� ��������� ������� ���� �� �������� */
    if (pDpy > DPYWAMIN && pDpy < DPYWAMAX) { 
      uint8_t pix = *pDpy;  pix ^= (pix ^ bright << 4) & 0x10;  *pDpy = pix;
    }
  }
}  



/*!*****************************************************************************
 @brief		FFT calculate 
 @note		256 ����� �������, ������� ��������� �� �����
 @verbatim
  �������� �� �������, ����������� Ruslan1 � ������������.
  ������ ������� � ��������� LRZfft.pdf.
  ������������ ������������ �� �������.
  �������������� ��������� �������������� �� ��������
  ������ � �������� ����� �����.
  sin(a + b) = sin a * cos b + cos a * sin b
  cos(a + b) = cos a * cos b - sin a * sin b
  �������������� � ������ ����� ������� ����������� �� ������� ���
  ��������� ��� (������) ����������� �� ����� �������������� �����  
 @endverbatim
 */

static float SigRe[FFT_N] __attribute((section("extram")));
static float SigIm[FFT_N] __attribute((section("extram")));

/* ������������ ������� ������������ ������������ */
static const float FFT_Att[] = {
  FFT_N / 2 * WATT_RECT,
  FFT_N / 2 * WATT_HANN,
  FFT_N / 2 * WATT_HAMM,
  FFT_N / 2 * WATT_BART,
  FFT_N / 2 * WATT_FLAT
};

void FFT_calc(void) {

  float *pSigRe;
  float *pSigIm;  
  
/* ��������� ������ ������� �������� */
  pSigRe = SigRe;		// ���������� ��������� � ������
  const float *pWind;
  switch (MathCtrl.Wind) {
    case (WIND_RECT): {			// ������������� ����
      for (uint32_t i = FFT_N; i--; )  *pSigRe++ = 1.0;
      break;
    }
    case (WIND_HANN): {			// ���� ����� (�������)
      pWind = WindHann;
      for (uint32_t i = FFT_N; i--; )  *pSigRe++ = *pWind++;
      break;       
    }
    case (WIND_HAMM): {			// ���� ��������
      pWind = WindHamm;
      for (uint32_t i = FFT_N; i--; )  *pSigRe++ = *pWind++;
      break;
    }
    case (WIND_BART): {			// ����������� ���� (��������)
      pWind = WindBart;
      for (uint32_t i = FFT_N; i--; )  *pSigRe++ = *pWind++;
      break;
    }
    case (WIND_FLAT): {		// Flat Top
      pWind = WindFlat;
      for (uint32_t i = FFT_N; i--; )  *pSigRe++ = *pWind++;
      break;
    }
  }

// ������ �������� ������� � ���������, �������� �������� � ���, ��� ��������
  int32_t pos = ((MathCtrl.Sour ? Chan2Ctrl.SigPos : Chan1Ctrl.SigPos)
	      - 512) / 2 + 128;

// ������ ��������� �� ������ ������� �������      
  uint16_t *pSig = (MathCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
		     + (1024 << MemCtrl.SizeNum) * MemCtrl.BufNum
		     + SweepCtrl.TimePos
		     + SigCtrl.SigInx;
// ������ ������ ��������� �� 1 ������ ����� ������� �������  
  uint16_t *pLim = (MathCtrl.Sour ? SigChan2.Buf16K : SigChan1.Buf16K)
                     + (1024 << MemCtrl.SizeNum) * (MemCtrl.BufNum + 1);
// ������� ��������� ������ ������
  if (pSig >= pLim)  pSig -= (1024 << MemCtrl.SizeNum);

/* ��������� � ������ ��� ������� �������
   �������� �� ������� ������� */
  pSigRe = SigRe;		// ���������� ��������� � ������
  pSigIm = SigIm;		// ���������� ��������� � ������
  for (uint32_t i = FFT_N; i--; ) {
    *pSigRe++ = (float)(((*pSig++) >> 8) - pos) * (*pSigRe);
    if (pSig >= pLim)  pSig -= (1024 << MemCtrl.SizeNum);
    *pSigIm++ = 0;
  }

/*
 ��� � ������������� �� �������:
 ������� ���� ���������� ������ ���
 ������� ���� ��������������� ���������� ������� � ������ �������
 ���������� ���� ���������� ����� ������� � ���������� �������������� ����������
 */
  uint32_t step = FFT_N;	// ��� ����� ������� �������
  for (uint32_t n = 0; n < FFT_P; n++) {  
//  while (step >= 2) {		// ������ ��� �� �������������
    uint32_t dist = step / 2;	// ���������� ����� ��������� ����� �������
    float Wre = 1.0;		// �������������� ���������
    float Wim = 0.0;
    float Ac = AC[n];
    float As = AS[n];    
  
    for (uint32_t j = 0; j < dist; j++) {	// ��� ������� ������� �����, W j_S
      for (uint32_t i = j; i < FFT_N; i += step) {	// ����� ����
					// i - ������� ������ ������� 
        uint32_t p = i + dist;		// ������� ������ �������
        float SumRe = *(SigRe + i) + *(SigRe + p);	// �����, Re
        float SumIm = *(SigIm + i) + *(SigIm + p);	// �����, Im
        float DifRe = *(SigRe + i) - *(SigRe + p);	// ��������, Re
        float DifIm = *(SigIm + i) - *(SigIm + p);	// ��������, Im
        *(SigRe + i) = SumRe;	// ��������� �� �������� �������, �� ����������
        *(SigIm + i) = SumIm;
        *(SigRe + p) = DifRe * Wre - DifIm * Wim;	// �����. ������, * W
        *(SigIm + p) = DifRe * Wim + DifIm * Wre;
      }
      // ����� �������������� ���������
      float Wtm = Wre * Ac - Wim * As;	// ����� cos � sin
      Wim = Wim * Ac + Wre * As;
      Wre = Wtm;
    }
    step /= 2;			// ����� ������
  }
  // ������������ ����������� (������� ����� ��� �� ����� ������)
  for (uint32_t i = 1; i < FFT_N - 1; i++) {
    uint32_t j = (__rbit(i)) >> (32 - FFT_P);
    if (i < j) {		// ����� �������� ������� ������������
      float TmRe = *(SigRe + j);
      float TmIm = *(SigIm + j);
      *(SigRe + j) = *(SigRe + i);
      *(SigIm + j) = *(SigIm + i);
      *(SigRe + i) = TmRe;
      *(SigIm + i) = TmIm;
    }
  }

/* ��������� ������ (���������) ������� */
/* �������� �� FFT_N � ����������� ���������� ������� ������� */

  pSigRe = SigRe;		// ���������� ��������� � ������
  pSigIm = SigIm;		// ���������� ��������� � ������
  for (uint32_t i = FFT_N; i--; ) {
     // *pSigRe = sqrt(*pSigRe * *pSigRe + *pSigIm * *pSigIm);
     *pSigRe = hypotf(*pSigRe, *pSigIm);
     *pSigRe /= FFT_Att[MathCtrl.Wind];
     pSigRe++;
     pSigIm++;
  }
  SigRe[0] /= 2;		// ���������� ������������
  
/* ��������� �������� ������ (�������� � dB)
   �������� �������������� ����� */
  pSigRe = SigRe;
  for (uint32_t i = FFT_N; i--; ) {
    *pSigRe++ = log2f(fmax(*pSigRe, 0.015625)) * 32;
  }

}

/*!*****************************************************************************
 @brief		FFT draw
 @note		
 */
void FFT_draw(bool bright) {
  uint32_t width = DispCtrl.Wide ? 300 : 250;
  float *pSigRe = SigRe;	// pointer to FFT array (module)
  int32_t s1, s2, brk;		// previous & next samples FFT, break position
/* ���� ����� ������ �������� � ��������� */
  for (int32_t i = 0; i < width; i++) {
    s1 = (int32_t)(*pSigRe++) / 2 + 128;	// integer part, begin
    s2 = (int32_t)(*pSigRe) / 2 + 128;
    // brk = (s1 == s2) ? s1 : ((s1 > s2) ? (s1 - 1) : (s1 + 1));
    brk = (s1 + s2) >> 1;
    VectMath_draw(s1, brk, s2, i, bright);
  }
}


/*! @} */

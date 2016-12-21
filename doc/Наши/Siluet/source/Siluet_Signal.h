
/*!*****************************************************************************
 @file		Siluet_Signal.h
 @author	��������� �.�.
 @date		2012.10
 @version	V0.5 
 @brief		Signal Processing functions
 @details	������� ��������� � ��������� �������
 @note		������ �������� 2 � 10 � 16384, �� 16K � ������ ������
 *******************************************************************************
 @verbatim
 2013.02
 ����� �������� ������ 16K �������� 10 �������� � ������ ������.
 ��� ����� � ������� ����� ����� ����� uint16_t �����, ����� 16K * 16 = 32 KB.
 ��� ���� ������� ����� 64 KB. 
 
 2011.11
 ������� ���� ����� ����� ��� ������� �� ��� ����������
 @endverbatim
 *******************************************************************************/

/*! @addtogroup	Signal
    @{ */
 
#ifndef SIGNAL_H		// �������� ���� ������ ���� ���
#define SIGNAL_H


/*__ ������������ ����� _______________________________________________________*/


/*__ ���������� ����������� �������� __________________________________________*/

#define MAXWGT (1 << 14)	//!< ������������ ��� ����������

#define FFT_P	10		// ������� ����������� ���
#define FFT_N	(1 << FFT_P)	// ����������� ���
#define PI 3.1415926535897932384626433832795L


/*__ ���������� ������������ __________________________________________________*/


/*__ ���������� ���� ������ ___________________________________________________*/


/*__ ���������� ���������� ____________________________________________________*/

/* ��� - ������ ������� ��������� ������� */
typedef enum {
  SWEEP_SKIP,
  ROLL,
  SCAN_PRE,
  SCAN_PST,
  FRAME_FULL,
  FRAME_SPARSE
} SIGNUM_t;

/*! ��������� ��������� �������
    ����� ������� ��������� �������
    ������ ����� � ������ (��������� �� ��������� ����� �����)
    ������� ������ � ����� ������� � ������� �������� 1 � 2 (����� �� 1 ������,
    ��� ��������� �����), ��������� � ������ ������ (�� � ������� �����)
    SigBuf[SigEnd] �� ��������! */       
typedef struct {
  SIGNUM_t SigNum;		//!< ����� ������� ��������� �������
  uint16_t SigInx;		//!< ������ ��������� ����� � ������
  uint16_t SigBeg;		//!< ������ ������ ������� � ������
  uint16_t SigEnd;		//!< ������ ����� ������� � ������
} SIGCTRL_t;

/* ��������� ��������� ������� */
// _DECL SIGCTRL_t SigCtrl _INIT({FRAME_FULL, 0, 1024});
// _DECL SIGCTRL_t SigCtrl _INIT((SIGCTRL_T){.SigNum = FRAME_FULL, .SigBeg = 0, .SigEnd = 1024});
// _DECL SIGCTRL_t SigCtrl _INIT({({FRAME_FULL, 0, 1024})});
// #define SIGINIT {FRAME_FULL, 0, 0, 511}
#define SIGINIT {FRAME_FULL, 0, 0, 1023}
_DECL SIGCTRL_t SigCtrl _INIT(SIGINIT);

/*! ��������� ������������� ������� */
typedef struct {
  uint32_t Tmts;		//!< ������� ����� trigger - second sample (<<16)
  uint32_t Tmad;		//!< ������� ���������� ���������� (<<16)
  uint16_t Tmin;		//!< ����������� ����� trigger - second sample
  uint16_t Tmax;		//!< ������������ ����� trigger - second sample  
  uint16_t Awgt;		//!< ��� ���������� �������
  uint16_t Tcur;		//!< ������� ����� trigger - second sample
} INTERP_t;

#define ITPINIT {3030 << 16, 240 << 16, 3030 - 240, 3030 + 240, 1, 3030}
_DECL INTERP_t Interp _INIT(ITPINIT);



/*!*****************************************************************************
 @brief		������ �������� ������ ���������� � ��������
 @note		��� �������� ������� ����� ��� ����������� ����� ���. �������
		[MemCtrl.BufNum][Sweep.TimePos] (0..1<<(9+MemCtrl.SizeNum))
		������� ������� - ���� ������ �������!
 */
typedef union {
  // uint16_t BufK5[32][512];
  uint16_t Buf1K[16][1024];
  uint16_t Buf2K[8][2048];
  uint16_t Buf4K[4][4096];
  uint16_t Buf8K[2][8192];
  uint16_t Buf16K[16384];
} SigBuf_t;			// integer<<8 | fractional

/* ������ �������� */
_DECL SigBuf_t SigChan1 _INIT({0});
_DECL SigBuf_t SigChan2 _INIT({0});

// _DECL SigBuf_t __attribute__((at(0x20002000))) SigChan1 _INIT({0});
// _DECL SigBuf_t __attribute__((at(0x20006000))) SigChan2 _INIT({0});

/*! ������� ������ � ���������� ������� ���������� */
_DECL uint16_t FrameCnt _INIT(0);

/* ��������� �� ���������� ������� - �� ������..., �� ������... */
// _DECL pFun_t Sig_fun;




/*__ ������� ���������� _______________________________________________________*/


/*__ ���������� ��������� ������� _____________________________________________*/
void Sweep_init(void);		// Sweep initialize
void Sweep_exe(void);		// Sweep execute
void Math_exe(void);		// Mathematics execute
void Sum_draw(bool On);		// Summa draw

void SigChans_draw(void);
void SigChans_redraw(void);
void PosChans_redraw(void);

void SigChan1_draw(uint32_t bright);
void SigChan2_draw(uint32_t bright);

void PosChan1_draw(bool On);
void PosChan2_draw(bool On);
void TrigLev_draw(bool On);

void Pret_draw(bool On);

void Curs_redraw(void);		// ������������ �������
void Curs_draw(bool On);	// ���������� (�������) �������

void Sig_clear(void);		// �������� ������ ��������
void SigChanAC_load(void);
void SigChanDC_load(void);

// void SigChans_read(void);	// ������ ������ �������� ����
void SigChans_rdavr(void);	// Read-average both channels, one or neither

void MemBar_draw(void);		// ���������� ������ ������
void MemBarPret_draw(bool On);	// ���������� ������� ����������� �� ������
void MemBarPos_draw(bool On);	// ���������� ������� ������ �� ������ ������

void SigPar_meas(void);

void XYDots_draw(bool bright);

/*__ ������ ������ ____________________________________________________________*/

//#error

#endif				// SIGNAL_H

/*! @} */

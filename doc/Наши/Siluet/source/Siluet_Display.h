
/*!*****************************************************************************
 @file		Siluet_Display.h
 @author	��������� �.�.
 @date		2012.10
 @version	V0.5
 @brief		Header for Display.c
 @details	������������ ���� ��� ������ � ��������� ����������������
 @note		������ ���� ��������� � Main.h
 *******************************************************************************/

/*! @addtogroup	Display
    @{ */
 
#ifndef DISPLAY_H			// �������� ���� ������ ���� ���
#define DISPLAY_H

/*__ ������������ ����� _______________________________________________________*/

#include "s1d13706.h"

/*__ ���������� ���� ������ ___________________________________________________*/

/*! ����������� ������� (���������� � ����� Fonts.h) */
typedef enum {
	SS_BLK, SS_GND, SS_CPAC, SS_CPDC,
	SS_MKLT, SS_MKRT, SS_MKDN, SS_MKUP,
	SS_MKSM, SS_DELT, SS_FALL, SS_RISE,
	SS_ARDN, SS_ARUP, SS_ROTR
} SSYM_t;

/* ���������������� ������������ */
#define	S_BLK	"\x10"
#define	S_GND	"\x11"
#define	S_CPAC	"\x12"
#define	S_CPDC	"\x13"
#define	S_MKLT	"\x14"
#define	S_MKRT	"\x15"
#define	S_MKDN	"\x16"
#define	S_MKUP	"\x17"
#define	S_MKSM	"\x18"
#define	S_DELT	"\x19"
#define	S_FALL	"\x1A"
#define	S_RISE	"\x1B"
#define	S_ARDN	"\x1C"
#define	S_ARUP	"\x1D"
#define S_ROTR	"\x1E"
#define S_SPSM	"\x98"		// ������ �����


/*__ ���������� ����������� �������� __________________________________________*/

// /* ������� ����� ����������� ��� � ������������ ������� MCU
//    ������ ���� �������������� ��� ����������� ���������� */
// #define DPYCTRL_BASE	((uint32_t)0x6C000000)	//!< Dysplay base address
// 
// /*! ����� ��� �� ������� ������ */
// #define	DPYBUF_BASE	(XRAM_BASE + XRAM_SIZE - DPYMEM_SIZE)
// // #define DPYMEM	DPYMEM_BASE	// ������������ ���������� ������ ���
// // #define DPYMEM	DPYBUF		// ������������ ����� ��� �� ������� ������

/* ���������� �������� �� ���������� */
#define	DPYWAH	7U		//!< �������������� ������� ������� �������
#define	DPYWAV	15U		//!< ������������ ������� ������� �������
#define DPYMAH	DPYWAH + 251	//!< �������������� ������� ������� ����
#define DPYMAV	DPYWAV		//!< ������������ ������� ������� ����
#define DPYMHH	DPYMAH + 1	//!< �������������� ������� ��������� � �������� ���� 
#define DPYMHV	DPYMAV + 9	//!< ������������ ������� ��������� ����
#define DPYMVH	DPYMAH + 1	//!< �������������� ������� ��������� ����
//
#define DPYM1AV	DPYWAV + 25	//!< ������������ ������� ������� 1 ����
#define DPYM1IV	DPYM1AV + 6	//!< ������������ ������� ������� 1 ����
#define DPYM1RV	DPYM1AV + 18	//!< ������������ ������� ��������� 1 ����
#define DPYM1VV DPYM1AV + 21	//!< ������������ ������� �������� 1 ����
//
#define DPYM2AV	DPYWAV + 25 + 35 * 1	//!< ������������ ������� ������� 2 ����
#define DPYM2IV	DPYM2AV + 6	//!< ������������ ������� ������� 2 ����
#define DPYM2RV	DPYM2AV + 18	//!< ������������ ������� ��������� 2 ����
#define DPYM2VV DPYM2AV + 21	//!< ������������ ������� �������� 2 ����
//
#define DPYM3AV	DPYWAV + 25 + 35 * 2	//!< ������������ ������� ������� 3 ����
#define DPYM3IV	DPYM3AV + 6	//!< ������������ ������� ������� 3 ����
#define DPYM3RV	DPYM3AV + 18	//!< ������������ ������� ��������� 3 ����
#define DPYM3VV DPYM3AV + 21	//!< ������������ ������� �������� 3 ����
//
#define DPYM4AV	DPYWAV + 25 + 35 * 3	//!< ������������ ������� ������� 4 ����
#define DPYM4IV	DPYM4AV + 6	//!< ������������ ������� ������� 4 ����
#define DPYM4RV	DPYM4AV + 18	//!< ������������ ������� ��������� 4 ����
#define DPYM4VV DPYM4AV + 21	//!< ������������ ������� �������� 4 ����
//
#define DPYM5AV	DPYWAV + 25 + 35 * 4	//!< ������������ ������� ������� 5 ����
#define DPYM5IV	DPYM5AV + 6	//!< ������������ ������� ������� 5 ����
#define DPYM5RV	DPYM5AV + 18	//!< ������������ ������� ��������� 5 ����
#define DPYM5VV DPYM5AV + 21	//!< ������������ ������� �������� 5 ����
//
#define DPYSAH	DPYWAH		//!< �������������� ������� ����� �������
#define DPYS1VV 219		//!< ������������ ������� ������ 1 �������
#define DPYS2VV	230		//!< ������������ ������� ������ 2 �������
//
#define DPYPARH		(320 - 8 * 14)	//!< �����. ������� ���������� 1 � 2
#define DPYPAR1V	(DPYS1VV)	//!< ����. ������� ��������� 1
#define DPYPAR2V	(DPYS2VV)	//!< ����. ������� ��������� 2
#define DPYVALH		(320 - 8 * 9)	//!< �����. ������� �������� 1 � 2
#define DPYVAL1V	(DPYS1VV)	//!< ����. ������� �������� 1
#define DPYVAL2V	(DPYS2VV)	//!< ����. ������� �������� 2


/* ������� ������ */
/* ����� � ������� ��� ������ �� ������������ */
#define WHITE_ON_BLACK_NO_SMOOTH	0xA3A2A1A0
#define WHITE_ON_BLACK			0xA7A6A5A4
#define BLACK_ON_WHITE_NO_SMOOTH	0xABAAA9A8
#define BLACK_ON_WHITE			0xAFAEADAC
// #define  WHITE_ON_DARK			0xb7b6b5b4

#define BLANK		0x00
#define BLACK		0x6A
#define DARK		0x6D
#define DIM		0x70
#define GRAY		0x73
#define SILVER		0x76
#define LIGHT		0x79
#define FROST		0x7C
#define WHITE		0x7F

#define BLACK_ON_GRAY	0x6AADAC73
#define WHITE_ON_GRAY	0x7FAFAE73
#define BLACK_ON_SILVER	0x6AB1B076
#define WHITE_ON_SILVER	0x7FB3B276

#define WHITE_ON_DARK	0x7FB1B06E

/* ������� ������ ��� ��������� ���� */
/*
#define PAL_BKG_HEAD	SILVER
#define PAL_TXT_HEAD	BLACK_ON_SILVER
#define PAL_BKG_ITEM	GRAY
#define PAL_TXT_ITEM	WHITE_ON_GRAY
#define PAL_BKG_VALUE	WHITE
#define PAL_TXT_VALUE	BLACK_ON_WHITE
#define PAL_EMB_FALL	DARK
#define PAL_EMB_RISE	LIGHT
*/

/* ����� ���� - �������� ������� (��� � ������ ����������) */
#define HEAD_BKG	0xBD
#define HEAD_TXT	0xC0B9BBBD
#define ITEM_BKG	0xBC
#define ITEM_TXT	0xFFBFBEBC
#define VOFF_BKG	ITEM_BKG
#define VOFF_TXT	0xC0B8BABC
#define VON_BKG		HEAD_BKG
#define VON_TXT		HEAD_TXT
#define HEAD_EMFA	ITEM_BKG
#define HEAD_EMRI	FROST
#define ITEM_EMFA	DARK
#define ITEM_EMRI	HEAD_BKG

/* ����� ����� ��� ������� � ������� DpyWork_clear(uint16_t mask)
   ����� ������������� ��� ���� �������� ��������
   0 - ���������� ��� */
#define	MASK_MAT	0xEFEF 
#define MASK_MATSIG	0xE0E0
#define	MASK_CURSMATSIG	0x6060


/*__ ���������� ������������ __________________________________________________*/

/* ������� �� ������� ������ ��� */
// #define EXTDPYPOS(XBeg,YBeg) (uint8_t *)(EXTDPY+(XBeg)+((YBeg)*320))

/* ��������� �� ������� � ������ ����������� ��� */
#define DPYPOS(XBeg, YBeg) \
	(uint8_t *)(DPYBUF_BASE + (XBeg) + (YBeg) * 320)

/* ��������� ������������: ������, �����, �����, ����, ������ */
#define DPY_RECT(XBeg, YBeg, XEnd, YEnd, Mask, Color)			\
	DpyRect_fill((uint8_t *)(DPYBUF_BASE + (XBeg) + (YBeg) * 320),	\
  		(XEnd) - (XBeg) + 1, (YEnd) - (YBeg) + 1, (Mask)<<8 | (Color))
#define DPY_RORECT(XBeg, YBeg, XEnd, YEnd, Mask, Color)			\
	DpyRoRect_fill((uint8_t *)(DPYBUF_BASE + (XBeg) + (YBeg) * 320),\
  		(XEnd) - (XBeg) + 1, (YEnd) - (YBeg) + 1, (Mask)<<8 | (Color))
#define DPY_LINEH(XBeg, YBeg, XEnd, Mask, Color, Patt)			\
	DpyLineHorz_draw((uint8_t *)(DPYBUF_BASE + (XBeg) + (YBeg) * 320),\
		(XEnd) - (XBeg) + 1, (Patt)<<16 | (Mask)<<8 | (Color))
#define DPY_LINEV(XBeg, YBeg, YEnd, Mask, Color, Patt)			\
	DpyLineVert_draw((uint8_t *)(DPYBUF_BASE + (XBeg) + (YBeg) * 320),\
		(YEnd) - (YBeg) + 1, (Patt)<<16 | (Mask)<<8 | (Color)) 
		
#define DPYXSIZE(XBeg, XEnd) ((XEnd) - (XBeg) + 1)
#define DPYYSIZE(YBeg, YEnd) ((YEnd) - (YBeg) + 1)


/*__ ���������� ���������� ____________________________________________________*/

/*__ �������� �������������� ������� __________________________________________*/

/* ������ � ������������ ��� */
void LcdCtrl_init(void);	// ���������������� ���������� ���
void LcdMem_test(void);		// ���� ����������� ���
void LcdMem_clear(void);	// �������� ������ ����������� ���
bool LcdVnD_check(void);	// Vertical non-Display period status

/* ���������� ����� ����������� � ������ ����������� ��� */
void DpyBuf2Mem_copy(uint32_t Offset, uint32_t Size);

/* �������� ����� ������ (������ ������ ������) */
void DpyScreen_blank(void);	// �������� ���� ����� (������ ������ ������) 
void DpyWork_blank(void);	// �������� ������� ������� (������ ������ ������)
void DpyMenu_blank(void);	// �������� ������� ���� (������ ������ ������)
void DpyExMenu_blank(void);	// �������� ������������, ����� ����
void DpyNum_blank(void);	// �������� ��������� ������������

void DpyWork_clear(uint16_t mask);	// �������� ������� ����������� (�������� � �.�.)

void DpyPalet_draw(void);	// ���������� �������
void DpyFont_draw(void);	// ���������� �����

void Manufact_draw(void);	//!< �������� ��� ������������� ("�����")
void DpyScale_draw(void);	//!< ���������� ����� � ������� �������

/* �������� ������ */
void DpyString_draw(uint8_t *pDpy, const uint8_t *pText, uint32_t palette, bool monospace);
void DpyStringPad_draw(uint8_t *pDpy, const uint8_t *pText, uint32_t palette, bool monospace);

/* ��������� ������������� */
void DpyRect_fill(uint8_t *pDpy, uint32_t XSize, uint32_t YSize, uint32_t MaskColor);
void DpyRoRect_fill(uint8_t *pDpy, uint32_t XSize, uint32_t YSize, uint32_t MaskColor);

/* ���������� ����� */
void DpyLineHorz_draw(uint8_t *pDpy, uint32_t XSize, uint32_t PattMaskColor);
void DpyLineVert_draw(uint8_t *pDpy, uint32_t YSize, uint32_t PattMaskColor);

/* ���������� ������ */
uint32_t DpyChar_draw(volatile uint8_t *pDpy, uint8_t symb, uint32_t palet);
uint32_t DpyCharPad_draw(volatile uint8_t *pDpy, uint8_t symb, uint32_t palet);
void DpySpec_draw(volatile uint8_t *pDpy, SSYM_t symb, uint8_t mask, uint32_t palet);

#endif

/*! @} */

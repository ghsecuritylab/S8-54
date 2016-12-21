
/*!*****************************************************************************
 @file		Siluet_Interface.c
 @author	��������� �.�.
 @date		2012.10 - 2013.05
 @version	V0.5
 @brief		Interface functions
 @details	User interface functions
 @note		
 *******************************************************************************
 @verbatim
 ���������� ������ ����������
   �������� ������
   �������� �� ������: KNm KCt
   KNm - ����� �������� (0..7) ��� ������ (8..31)
   KCt - ��� �������� (-128..+127) ��� ������ (-1, 1)
   �������� �� MCU: ALC - ��� ������ � ����������� aallllll
   aa - 00 - ������������� ����� (ComBusy = 0) + ��� �����������
	01 - �������������� ����������� �������� ���� �����������
	10 - ������, (ComBusy = 0), ��������� (+ ��� �����������)
	11 - ����� ������, (ComBusy = 0), �����? (+ ��� �����������)
   llllll - _t_21p (�����, �����2, �����1, �������) (Lights_n)
  
 ������ ������ [0..31]
   0     1     2     3     4     5     6     7
   V1    V2    Tim   Set   Pos1  Pos2  PosT  Level
   Chan1 Math  Chan2 [11]  Sweep [13]  Trig  [15]
   Disp  Acqu  Curs  Meas  Mem   Util  Autos StSp
   Help  F1    F2    F3    F4    F5    [30]  [31]
   
 2013.04.17
 
 ����� �������:
   FpXXX_hand - ����������� ������� ������ ����������
   MnXXX_hand - ����������� ��������� ����
   MnXXX_disp - ���������� ��������� ���� � ����
   XXX_sett - ����������� ������� � ����
   XXXSt_disp - ���������� ������� � �������
   SetXXX_hand - ���������� �������, �������� ����� ���������
   SetXXX_disp - ��������� �������, �������� ����� ���������
   SetXXX_sett - ���������� �������, �������� ������ ���������
   ExeXXX_hand - ���������� �������, �������� ������ ��������� � ���� ������ 
 
 ��������� ����� �� ��������:
 
   ���������� ������ - �������� �� ��������� �������
   
     ��������
     ������, ���������� ����
     ������ ��� ����
     
     ������, ������������� ���� (�������������� F1 - F5)
     ����������� ��������� � ����, ���������� ���������� � ����
     
       ����������� ����� ���������, ���������� ����� ���������
       ����������� ������ ��������� (� ���� ������)
     
       ����������� �������, ���������� ������� � ������� ���������
       ����������� ����� ���������
 
 @endverbatim
 *******************************************************************************/

/*! @addtogroup	Interface
    @{ */
 
/*__ ������������ ���� ________________________________________________________*/

#include "Siluet_Main.h"	// ��� ��������� ������ � ����� �����

/*__ ��������� ���� ������ ____________________________________________________*/

/*__ ����������� �������� _____________________________________________________*/

/*__ ��������� ��������� ������� ______________________________________________*/

// /* ��������� ������������ ������� ������ ���������� */

// void FpVolt1_hand(int32_t Cnt);			// Volts 1 / div
// void FpVolt2_hand(int32_t Cnt);			// Volts 2 / div
// void FpTime_hand(int32_t Cnt);			// Time / div
// void FpSet_hand(int32_t Cnt);			// Setting
// void FpPos1_hand(int32_t Cnt);			// Position 1
// void FpPos2_hand(int32_t Cnt);			// Position 2
// void FpPosT_hand(int32_t Cnt);			// Position Time
// void FpLevel_hand(int32_t Cnt);			// Trigger Level
// void FpChan1_hand(int32_t Cnt);		// Channel 1 Menu
// void FpMath_hand(int32_t Cnt);		// Mathematic Menu
// void FpChan2_hand(int32_t Cnt);		// Channel 2 Menu
// void Fp11_hand(int32_t Cnt);
// void FpSweep_hand(int32_t Cnt);		// Horizontal Sweeep Menu
// void Fp13_hand(int32_t Cnt);		// Position Time Switch
// void FpTrig_hand(int32_t Cnt);		// Trigger Menu
// void Fp15_hand(int32_t Cnt);		// (Trigger Level Switch)
// void FpDisp_hand(int32_t Cnt);		// Display Menu
// void FpAcqu_hand(int32_t Cnt);		// Acquisition Menu
// void FpCurs_hand(int32_t Cnt);		// Cursors Menu
// void FpMeas_hand(int32_t Cnt);		// Measure Menu
// void FpMem_hand(int32_t Cnt);		// Memory Menu
// void FpUtil_hand(int32_t Cnt);		// Utilities Menu
// void FpAutoset_hand(int32_t Cnt);		// Autoset
// void FpStSp_hand(int32_t Cnt);			// Start / Stop
// void FpHelp_hand(int32_t Cnt);			// Help
// void FpF1_hand(int32_t Cnt);				// F1
// void FpF2_hand(int32_t Cnt);				// F2
// void FpF3_hand(int32_t Cnt);				// F3
// void FpF4_hand(int32_t Cnt);				// F4
// void FpF5_hand(int32_t Cnt);				// F5
// void Fp30_hand(int32_t Cnt);
// void Fp31_hand(int32_t Cnt);			// (Setting Switch)

/* ��������� ������������ ��������� ����
   ��������� ����������� ��������� ���� */

void MnVoid_hand(void);
void MnVoid_disp(void);

// ������
void MnServCal_hand(void);
void MnServCal_disp(void);
void MnServCPU_hand(void);
void MnServCPU_disp(void);
void MnServPL_hand(void);
void MnServPL_disp(void);
void MnServDpy_hand(void);
void MnServDpy_disp(void);
void MnServExe_hand(void);
void MnServExe_disp(void);

// ����� 1
void MnChan1Mode_hand(void);
void MnChan1Mode_disp(void);
void MnChan1Prb_hand(void);
void MnChan1Prb_disp(void);
void MnChan1Inv_hand(void);
void MnChan1Inv_disp(void);
void MnChan1Cplg_hand(void);
void MnChan1Cplg_disp(void);
void MnChan1BWLim_hand(void);
void MnChan1BWLim_disp(void);
// void MnChan1Gnd_hand(void);
// void MnChan1Gnd_disp(void);

// ����� 2
void MnChan2Mode_hand(void);
void MnChan2Mode_disp(void);
void MnChan2Prb_hand(void);
void MnChan2Prb_disp(void);
void MnChan2Inv_hand(void);
void MnChan2Inv_disp(void);
void MnChan2Cplg_hand(void);
void MnChan2Cplg_disp(void);
void MnChan2BWLim_hand(void);
void MnChan2BWLim_disp(void);
// void MnChan2Gnd_hand(void);
// void MnChan2Gnd_disp(void);

// ����������
void MnMathMode_hand(void);
void MnMathMode_disp(void);
void MnMathFun_hand(void);
void MnMathFun_disp(void);
void MnMathSour_hand(void);
void MnMathSour_disp(void);
void MnMathWind_hand(void);
void MnMathWind_disp(void);
void MnMathOffs_hand(void);
void MnMathOffs_disp(void);

// ���������
void MnSweepMode_hand(void);
void MnSweepMode_disp(void);
void MnSweepRoll_hand(void);
void MnSweepRoll_disp(void);
void MnSweepPret_hand(void);
void MnSweepPret_disp(void);
void MnSweepXY_hand(void);
void MnSweepXY_disp(void);

// �������������
void MnTrigSour_hand(void);
void MnTrigSour_disp(void);
void MnTrigSlp_hand(void);
void MnTrigSlp_disp(void);
void MnTrigCplg_hand(void);
void MnTrigCplg_disp(void);
void MnTrigNRej_hand(void);
void MnTrigNRej_disp(void);

// �������
void MnDispHelp_hand(void);
void MnDispHelp_disp(void);
void MnDispVect_hand(void);
void MnDispVect_disp(void);
void MnDispScale_hand(void);
void MnDispScale_disp(void);
void MnDispClear_hand(void);
void MnDispClear_disp(void);

// ���� ����������
void MnAcquFilt_hand(void);	// ������ (�������� ����������)
void MnAcquFilt_disp(void);
void MnAcquPeak_hand(void);	// ������� ��������
void MnAcquPeak_disp(void);
void MnAcquAver_hand(void);	// ����������
void MnAcquAver_disp(void);
void MnAcquPers_hand(void);	// ���������� (�������������)
void MnAcquPers_disp(void);

// �������
void MnCursMode_hand(void);
void MnCursMode_disp(void);
void MnCursPara_hand(void);
void MnCursPara_disp(void);
void MnCursSel1_hand(void);
void MnCursSel1_disp(void);
void MnCursSel2_hand(void);
void MnCursSel2_disp(void);
void MnCursSelTr_hand(void);
void MnCursSelTr_disp(void);

// ���������
void MnMeasMode_hand(void);
void MnMeasMode_disp(void);
void MnMeasSour_hand(void);
void MnMeasSour_disp(void);
void MnMeasPar1_hand(void);
void MnMeasPar1_disp(void);
void MnMeasPar2_hand(void);
void MnMeasPar2_disp(void);

// ������
void MnMemSize_hand(void);
void MnMemSize_disp(void);
void MnMemNum_hand(void);
void MnMemNum_disp(void);
void MnMemSig_hand(void);
void MnMemSig_disp(void);
void MnMemSet_hand(void);
void MnMemSet_disp(void);
void MnMemExe_hand(void);
void MnMemExe_disp(void);

// �������
void MnUtilCal_hand(void);
void MnUtilCal_disp(void);
void MnUtilBal_hand(void);
void MnUtilBal_disp(void);
void MnUtilReset_hand(void);
void MnUtilReset_disp(void);
void MnUtilVers_hand(void);
void MnUtilVers_disp(void);


/* ��������� ������� ��������� �������
   ��������� ������� ��������� ������� (� �������)
   ���������� � ��������� ������������ ���� Siluet_Interface.h */

/* ��������� ������������ ������� ����� ��������� */

void SetPret_sett(void);
void SetHold_sett(void);

/* ��������� ������������ ������ ��������� (������) */

void ExeVoid_hand(void);
void ExeCalibr_hand(void);	// ����������� ������������
void ExeCalSave_hand(void);	// ��������� ���������� ����������
void ExeCPUiMem_hand(void);	
void ExeCPUeMem_hand(void);
void ExePLRecv_hand(void);
void ExePLComp_hand(void);
void ExePLWrite_hand(void);
void ExePLRead_hand(void);
void ExeDpyWhite_hand(void);
void ExeDpyBlack_hand(void);
void ExeDpyFont_hand(void);
void ExeDpyPalet_hand(void);
void ExeDpyRed_hand(void);
void ExeDpyGreen_hand(void);
void ExeDpyBlue_hand(void);
void ExeDpyDefault_hand(void);

/* ��������� ������� ������ � ������� */
// ��������� ������ � ����� �� 2-� ���
void Sig1_save(void);
void Sig2_save(void);
// ��������� ������ �� ����� �� 2-� ���
void Sig1_load(void);
void Sig2_load(void);

/* ��������� ����������� ����/����, ������� */

void StSp_disp(void);
void Autoset_disp(void);

/* ��������� ���������, ��������������� ������� */

void MenuHead_disp(void);	// ���������� ���� � ������� �������
void MenuHeadDepr_disp(void);	// ���������� ���������� ������ ����
void Help_draw(void);		// ���������� ������
void DigitBar_disp(void);
void HelpMenu_clear(void);	// �������� ����� ��� ������ ����

void DpyOffOn_draw(uint8_t *pDpy, bool On);	// �������� ���� / ���
void DpySetting_draw(uint8_t *pDpy, bool On);	// ���������� ��������� � ��������
void DpyRotor_draw(uint8_t *pDpy, bool On);	// ���������� ��������

void DpyChanGnd_draw(uint8_t *pDpy);		// �������� ����������
void DpyChanCplg_draw(uint32_t Cplg);		// �������� ����� � ������
void DpyChanPrb_draw(uint32_t Prb);		// �������� ������� � ������
uint32_t DpyVolt_draw(uint8_t *pDpy, uint32_t Num, uint32_t Color);	// Volt/div

void itoad_conv(int32_t numb, uint8_t *str);
void itoah_conv(uint32_t numb, uint8_t *str);


/*__ ��������� ���������� (� �������� ����� - ����������) _____________________*/


/* ������� ������� - ������������ � ����������� ��������� ����
   ������ ����: (��������� ���� ���������� ������ ����� ��������� �������)
   MenuServ, MenuChan1, MenuChan2, MenuSweep, MenuTrig,
   MenuDisp, MenuAcq, MenuCurs, MenuMeas, MenuMem, MenuUtil,  */
   
/* ������ ���������� �� ������� - ����������� ��������� ���� */
static const pMenu_t MenuItem_hand[][5] = {
  MnServCal_hand, MnServCPU_hand, MnServPL_hand, MnServDpy_hand, MnServExe_hand,
  MnChan1Mode_hand, MnChan1Prb_hand, MnChan1Inv_hand, MnChan1Cplg_hand, MnChan1BWLim_hand,
  MnMathMode_hand, MnMathFun_hand, MnMathSour_hand, MnMathWind_hand, MnMathOffs_hand,
  MnChan2Mode_hand, MnChan2Prb_hand, MnChan2Inv_hand, MnChan2Cplg_hand, MnChan2BWLim_hand,
  MnSweepMode_hand, MnSweepRoll_hand, MnSweepPret_hand, MnVoid_hand, MnSweepXY_hand,
  MnTrigSour_hand, MnTrigSlp_hand, MnVoid_hand, MnTrigCplg_hand, MnTrigNRej_hand,
  MnDispHelp_hand, MnDispVect_hand, MnDispScale_hand, MnVoid_hand, MnDispClear_hand,
  MnAcquFilt_hand, MnAcquPeak_hand, MnAcquAver_hand, MnAcquPers_hand, MnVoid_hand,
  MnCursMode_hand, MnCursPara_hand, MnCursSel1_hand, MnCursSel2_hand, MnCursSelTr_hand,
  MnMeasMode_hand, MnMeasSour_hand, MnMeasPar1_hand, MnMeasPar2_hand, MnVoid_hand,
  MnMemSize_hand, MnMemNum_hand, MnMemSig_hand, MnMemSet_hand, MnMemExe_hand,
  MnUtilCal_hand, MnUtilBal_hand, MnVoid_hand, MnUtilVers_hand, MnUtilReset_hand  
};

/* ������ ���������� �� ������� ��������� �������� ��������� ���� */
static const pMenu_t MenuValue_disp[][5] = {
  MnServCal_disp, MnServCPU_disp, MnServPL_disp, MnServDpy_disp, MnServExe_disp,
  MnChan1Mode_disp, MnChan1Prb_disp, MnChan1Inv_disp, MnChan1Cplg_disp, MnChan1BWLim_disp,
  MnMathMode_disp, MnMathFun_disp, MnMathSour_disp, MnMathWind_disp, MnMathOffs_disp,
  MnChan2Mode_disp, MnChan2Prb_disp, MnChan2Inv_disp, MnChan2Cplg_disp, MnChan2BWLim_disp,
  MnSweepMode_disp, MnSweepRoll_disp, MnSweepPret_disp, MnVoid_disp, MnSweepXY_disp,
  MnTrigSour_disp, MnTrigSlp_disp, MnVoid_disp, MnTrigCplg_disp, MnTrigNRej_disp,
  MnDispHelp_disp, MnDispVect_disp, MnDispScale_disp, MnVoid_disp, MnDispClear_disp, 
  MnAcquFilt_disp, MnAcquPeak_disp, MnAcquAver_disp, MnAcquPers_disp, MnVoid_disp,
  MnCursMode_disp, MnCursPara_disp, MnCursSel1_disp, MnCursSel2_disp, MnCursSelTr_disp,
  MnMeasMode_disp, MnMeasSour_disp, MnMeasPar1_disp, MnMeasPar2_disp, MnVoid_disp,
  MnMemSize_disp, MnMemNum_disp, MnMemSig_disp, MnMemSet_disp, MnMemExe_disp,
  MnUtilCal_disp, MnUtilBal_disp, MnVoid_disp, MnUtilVers_disp, MnUtilReset_disp
};

/* ������ ���������� �� ������� - ����������� ����� ��������� */
static const pSet_t SetItem_hand[] = {
  SetVoid_hand, SetPret_hand, SetHold_hand, SetAver_hand,
  SetCurs1_hand, SetCurs2_hand, SetCursTr_hand,
  SetPar1_hand, SetPar2_hand,
  SetBufNum_hand  
};

/* ������ ���������� �� ������� - ����������� ������ ��������� (������) */
static const pExe_t ExeItem_hand[] = {
  ExeVoid_hand,
  ExeCalibr_hand, ExeCalSave_hand,  
  ExeCPUiMem_hand, ExeCPUeMem_hand,
  ExePLRecv_hand, ExePLComp_hand, ExePLWrite_hand, ExePLRead_hand,
  ExeDpyWhite_hand, ExeDpyBlack_hand, ExeDpyFont_hand, ExeDpyPalet_hand,
  ExeDpyRed_hand, ExeDpyGreen_hand, ExeDpyBlue_hand, ExeDpyDefault_hand
};

/* ������ ���������� �� ������� - ����������� ������ ��������� ���� ������ */ 
static const pExe_t MemFun[] = { 
  Sig1_save, Sig2_save, Sig1_load, Sig2_load
};

/*__ ���������� ������� _______________________________________________________*/

/*!*****************************************************************************
 @brief		Front Panel Processing
 @details	��������� ��������� �� ������ ����������
 @note		
 */
void Panel_Process(void) {
/* ������ ���������� �� ����������� ������������ ������� ���������� */
  static const pPanel_t FpKey_hand[32] = {
    FpVolt1_hand, FpVolt2_hand, FpTime_hand, FpSet_hand,
    FpPos1_hand, FpPos2_hand, FpPosT_hand, FpLevel_hand,
    FpChan1_hand, FpMath_hand, FpChan2_hand, Fp11_hand,
    FpSweep_hand, Fp13_hand, FpTrig_hand, Fp15_hand,
    FpDisp_hand, FpAcqu_hand, FpCurs_hand, FpMeas_hand,
    FpMem_hand, FpUtil_hand, FpAutoset_hand, FpStSp_hand,
    FpHelp_hand, FpF1_hand, FpF2_hand, FpF3_hand,
    FpF4_hand, FpF5_hand, Fp30_hand, Fp31_hand
  };

  uint32_t KeyNum = (uint32_t)PanCtrl.RcBuf[0];
  int32_t KeyCnt = (int8_t)PanCtrl.RcBuf[1];
  
/* ������������� ������� ����������� */  
  if (KeyCnt >  2)  KeyCnt =   1 << ( KeyCnt - 1);
  if (KeyCnt < -2)  KeyCnt = -(1 << (-KeyCnt - 1));
  //  if (KeyCnt >  3) KeyCnt =   1 << ( KeyCnt - 2);
  //  if (KeyCnt < -3) KeyCnt = -(1 << (-KeyCnt - 2));
  
/* ������� ���������� �� ������ (��������) */
  FpKey_hand[KeyNum](KeyCnt);
}


/*__ ��������� ������� ________________________________________________________*/

/* ����������� ������������ ������� ����������:
   ��������
   ������, ���������� ����
   ������, ����������� ������� ����
   ������, ����������� ���������������� ������� */


//__ �������� _________________________________________________________________//

 
/*!*****************************************************************************
 @brief	
 @details	�����/��� 1
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 */
void FpVolt1_hand(int32_t Cnt) {
  if (!Chan1Ctrl.On) return;
  int32_t temp = (int32_t)Chan1Ctrl.VoltNum;
  temp += Cnt;
  if (temp < VOLT_BEG) temp = VOLT_BEG;
  if (temp > VOLT_END) temp = VOLT_END;
  Chan1Ctrl.VoltNum = temp;
  Chan1Cplg_sett();
  FpPos1_hand(0);		// ��������������� �������    
  Chan1St_disp();
  FrameCnt = 0;			// �������� ������� ������ � ���������� �������
  if (CursCtrl.On) SetCursSt_disp();
}

/*!*****************************************************************************
 @brief	
 @details	�����/��� 2
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 */
void FpVolt2_hand(int32_t Cnt) {
  if (!Chan2Ctrl.On) return;
  int32_t temp = (int32_t)Chan2Ctrl.VoltNum;
  temp += Cnt; 
  if (temp < VOLT_BEG) temp = VOLT_BEG;
  if (temp > VOLT_END) temp = VOLT_END;
  Chan2Ctrl.VoltNum = temp;
  Chan2Cplg_sett();
  FpPos2_hand(0);		// ��������������� �������
  Chan2St_disp();
  FrameCnt = 0;			// �������� ������� ������ � ���������� �������
  if (CursCtrl.On) SetCursSt_disp();
}

/*!*****************************************************************************
 @brief	
 @details	�����/���
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 */
void FpTime_hand(int32_t Cnt) {

/* ���������, ��������, ����������, �������� �����/��� */
  int32_t temp = (int32_t)SweepCtrl.TimeNum;
  temp += Cnt;
  if (temp < 0) temp = 0;
  if (temp >= TIME_CNT) temp = TIME_CNT - 1;
  SweepCtrl.TimeNum = temp;
  Time_sett();
  TimeSt_disp();
  SweepSt_disp();
  
/* ������ ���������� �� ������ ��� �� ������ (1sec/div � ���������) */
  PL_AcquBuf &= ~(PL_ACQU_FRMIE | PL_ACQU_DOTIE);
  if (temp <= TIME_DOT)	PL_AcquBuf |= PL_ACQU_DOTIE;
  else			PL_AcquBuf |= PL_ACQU_FRMIE;
  PL->ACQU = PL_AcquBuf;
  
/* ��������������� ���������� �� ������� ���������� */
  SetPret_sett();
  // Hex32_draw(PL_AcquBuf);
  
/* ������� ������� ��������� */
  // if (Chan1Ctrl.On) SigChan1_draw(0);	// clear old wave
  // if (Chan2Ctrl.On) SigChan2_draw(0);	// clear old wave
  DpyWork_clear(MASK_MATSIG);
  Sweep_init();
  FrameCnt = 0;			// �������� ������� ������ � ���������� �������
  if (CursCtrl.On) SetCursSt_disp();
}

/*!*****************************************************************************
 @brief	
 @details	���������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 */
void FpSet_hand(int32_t Cnt) {
  SetItem_hand[SetNum](Cnt);
}

/*!*****************************************************************************
 @brief		Position Channel 1
 @details	����� 1, ��������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 @verbatim
 �������� ������� ����������� � ��� ������, � ��������� 0..0x3ff (1024 ������).
 � ��� ����������� ��������� �� 2 ������� �������� (0..0xffc, � ����� 4).
 �������� ��������� ����������� � ����������� �������,
 �������� -512..+511, ��� 1 (1024 ������)
 ������ ����� �������� ������������ ��������� �������  
 �������� ��������� ������� �� 2 ��� ������������ � ��������,
 �������� -256..+255 (512 �������)
 ����� �������� ����� ����, �������� ��������� ��������������� � �������� (0).
 @endverbatim
 */
void FpPos1_hand(int32_t Cnt) {
  if (!Chan1Ctrl.On) return;
  int32_t temp;				// temporal level
  SigChan1_draw(0);			// clear signal image (old DispPos)
  PosChan1_draw(false);			// clear pos marker
  TrigLev_draw(false);
  temp = (int32_t)Chan1Ctrl.SigPos + Cnt;	// desired level
  if (temp < 0) Cnt += (0 - temp);		// min limit (0), incr Cnt
  if (temp > 1023) Cnt -= (temp - 1023);	// max limit (1023), decr Cnt
  Chan1Ctrl.SigPos += Cnt;			// add limited counter
  Chan1Ctrl.DispPos += Cnt;			// add limited counter

//  ANADAC(DAC_CHAN1, Chan1Ctrl.SigPos << 2);
  uint16_t pos = Chan1Ctrl.SigPos;
  if (Chan1Ctrl.VoltNum == VOLT_END) {	// 2mV
    if (Chan1Ctrl.Cplg == 2)
      pos += Bal1Ctrl.Ofs2DC;
    if (Chan1Ctrl.Cplg == 1)
      pos += Bal1Ctrl.Ofs2AC;
    if (Chan1Ctrl.Cplg == 0)
      pos += Bal1Ctrl.Ofs2GND;
  }
  if (Chan1Ctrl.VoltNum % 3 == 0) {	// 5mV
    if (Chan1Ctrl.Cplg == 2)
      pos += Bal1Ctrl.Ofs5DC;
    if (Chan1Ctrl.Cplg == 1)
      pos += Bal1Ctrl.Ofs5AC;
    if (Chan1Ctrl.Cplg == 0)
      pos += Bal1Ctrl.Ofs5GND;
  }
  if (Chan1Ctrl.VoltNum % 3 == 2) {	// 10mV
    if (Chan1Ctrl.Cplg == 2)
      pos += Bal1Ctrl.Ofs10DC;
    if (Chan1Ctrl.Cplg == 1)
      pos += Bal1Ctrl.Ofs10AC;
    if (Chan1Ctrl.Cplg == 0)
      pos += Bal1Ctrl.Ofs5GND;
  }
  if (Chan1Ctrl.VoltNum % 3 == 1) {	// 20mV
    if (Chan1Ctrl.Cplg == 2)
      pos += Bal1Ctrl.Ofs20DC;
    if (Chan1Ctrl.Cplg == 1)
      pos += Bal1Ctrl.Ofs20AC;
    if (Chan1Ctrl.Cplg == 0)
      pos += Bal1Ctrl.Ofs5GND;
  }
  
  ANADAC(DAC_CHAN1, pos << 2);
  //  Num_draw(pos);  
  
  SigChan1_draw(3);			// draw signal image (new DispPos)
  PosChan1_draw(true);			// draw pos marker
  TrigLev_draw(true);
}

/*!*****************************************************************************
 @brief		Position Channel 2
 @details	����� 2, ��������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpPos2_hand(int32_t Cnt) {
  if (!Chan2Ctrl.On) return;
  int32_t temp;
  SigChan2_draw(0);
  PosChan2_draw(false);
  TrigLev_draw(false);
  temp = (int32_t)Chan2Ctrl.SigPos + Cnt;
  if (temp < 0) Cnt += (0 - temp);
  if (temp > 1023) Cnt -= (temp - 1023);
  Chan2Ctrl.SigPos += Cnt;
  Chan2Ctrl.DispPos += Cnt;
  
//  ANADAC(DAC_CHAN2, Chan2Ctrl.SigPos << 2);
  uint16_t pos = Chan2Ctrl.SigPos;
  if (Chan2Ctrl.VoltNum == VOLT_END) {	// 2mV
    if (Chan2Ctrl.Cplg == 2)
      pos += Bal2Ctrl.Ofs2DC;
    if (Chan2Ctrl.Cplg == 1)
      pos += Bal2Ctrl.Ofs2AC;
    if (Chan2Ctrl.Cplg == 0)
      pos += Bal2Ctrl.Ofs2GND;
  }
  if (Chan2Ctrl.VoltNum % 3 == 0) {	// 5mV
    if (Chan2Ctrl.Cplg == 2)
      pos += Bal2Ctrl.Ofs5DC;
    if (Chan2Ctrl.Cplg == 1)
      pos += Bal2Ctrl.Ofs5AC;
    if (Chan2Ctrl.Cplg == 0)
      pos += Bal2Ctrl.Ofs5GND;
  }
  if (Chan2Ctrl.VoltNum % 3 == 2) {	// 10mV
    if (Chan2Ctrl.Cplg == 2)
      pos += Bal2Ctrl.Ofs10DC;
    if (Chan2Ctrl.Cplg == 1)
      pos += Bal2Ctrl.Ofs10AC;
    if (Chan2Ctrl.Cplg == 0)
      pos += Bal2Ctrl.Ofs5GND;
  }
  if (Chan2Ctrl.VoltNum % 3 == 1) {	// 20mV
    if (Chan2Ctrl.Cplg == 2)
      pos += Bal2Ctrl.Ofs20DC;
    if (Chan2Ctrl.Cplg == 1)
      pos += Bal2Ctrl.Ofs20AC;
    if (Chan2Ctrl.Cplg == 0)
      pos += Bal2Ctrl.Ofs5GND;
  }
 
  ANADAC(DAC_CHAN2, pos << 2);
  //  Num_draw(pos);  
  
  SigChan2_draw(3);
  PosChan2_draw(true);
  TrigLev_draw(true);
}

/*!*****************************************************************************
 @brief		Time Position
 @details	���������, �������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note	
 @verbatim
 ������� ��������� �� ������ ������
 ������� � ������ ������� ���������� ����������� ���, ����� � �������� ������
 ��� 10 �������� ���� �������� ������.
 ��� �� ��������� ������� ����������� (256 ��� ����� 0.5K)
	����� ����, ��� ����������� ����������� � ExtDpy ������
	������� ����������� �� 3.2ms, � ���. �������� ��������� 23.2ms 
 @endverbatim
 */
void FpPosT_hand(int32_t Cnt) {
//  LED_ON();			// ����, ������ ��������� ~16ms (62.5Hz)
#if false
// ������� �� ����� non-Display
//  while (DPY_VnD_check()) { };	// ����� 0
//  while (!DPY_VnD_check()) { };	// ����� 1 (������ non-Display period)
#endif
  Pret_draw(false);
  MemBarPos_draw(false);
  // if (CursCtrl.On) Curs_draw(false);
  // if (Chan1Ctrl.On) SigChan1_draw(0);
  // if (Chan2Ctrl.On) SigChan2_draw(0);
// �������� ����������� ��������, ����������, �������� */
  DpyWork_clear(MASK_CURSMATSIG);
  
//  LED_OFF();			// ����, ~2ms ��� ���� ������� (1ms+1ms)
  int32_t pos = SweepCtrl.TimePos;
  pos += Cnt;
  int32_t lmarg = 0;		// �������� ��� ��������� 0 �������
  int32_t rmarg = (1024 << MemCtrl.SizeNum) - 300;
  if (pos < lmarg) pos = lmarg;
  if (pos > rmarg) pos = rmarg;
  SweepCtrl.TimePos = pos;
  if (Chan1Ctrl.On) SigChan1_draw(3);
  if (Chan2Ctrl.On) SigChan2_draw(3);
  Pret_draw(true);
  MemBarPos_draw(true);
  if (CursCtrl.On) Curs_draw(true);
//  LED_OFF();		// ����, ~4.25ms, ������ 30.50ms (������� � ������ ����������)
}

/*!*****************************************************************************
 @brief		Trigger Level
 @details	������� �����
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpLevel_hand(int32_t Cnt) {
  TrigLev_draw(false);
  int16_t temp = TrigCtrl.Level + Cnt;
  if (temp < 0) temp = 0;
  if (temp > 1023) temp = 1023;
  TrigCtrl.Level = temp;
  TrigLev_draw(true);
//  PL->SDAC = PL_SDAC_T1LEV | (TrigCtrl.Level<<2);
//  DELAY_START(2); DELAY_WAIT();
//  PL->SDAC = PL_SDAC_T2LEV | (TrigCtrl.Level<<2);
//  DELAY_START(2); DELAY_WAIT();
//  PL->SDAC = PL_SDAC_TXLEV | (TrigCtrl.Level<<2);
  ANADAC(DAC_LEVEL, TrigCtrl.Level << 2);
}


//__ ������, ���������� ���� __________________________________________________//


/*!*****************************************************************************
 @brief		
 @details	���� ����� 1
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpChan1_hand(int32_t Cnt) {
  if (Cnt > 0) {			// ������ ������
    if (GenCtrl.Menu
        && MenuNum == MENU_CHAN1) {	// ���� ���� ����
      GenCtrl.Menu = 0;			// ��������� ���� ����
      HelpMenu_clear();      
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {				// ��� ������ ����
      GenCtrl.Menu = 1;			// �������� ���� ���� 
      MenuNum = MENU_CHAN1;
      MenuHead_disp();			// ���������� ����  
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else	MenuHeadDepr_disp();		// ������ ��������
}

#if 0
void FpChan1_hand(int32_t Cnt) {
  if (Cnt > 0) {			// ���� ������ ������
    if (GenCtrl.Menu && 
        MenuNum == MENU_CHAN1) {	// ���� ���� ���� ����
      GenCtrl.Menu = 0;			// ��������� ���� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
    }
    else {				// ��� ������ ����
      GenCtrl.Menu = 1;			// �������� ���� ����
      MenuNum = MENU_CHAN1;
      MenuHead_disp();			// ���������� ����
      DispCtrl.Wide = 0;
      Chan1Ctrl.On ^= 1;		// �������� ��������� ������ ����/���
      // MnChan1Mode_disp();
      Chan1Mode_sett();
      Chan1St_disp();			// ���������� � �������
      PosChan1_draw(Chan1Ctrl.On);	// ���������� ������
    }
    DpyScale_draw();			// ���������� �����
  }
  else MenuHeadDepr_disp();		// ������ ��������
}    
#endif
    
/*!*****************************************************************************
 @brief		
 @details	���� ��� ���
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpMath_hand(int32_t Cnt) {
  if (Cnt > 0) {			// ������ ������
    if (GenCtrl.Menu &&
        MenuNum == MENU_MATH) {
      GenCtrl.Menu = 0;			// ��������� ���� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;			// �������� ���� ����
      MenuNum = MENU_MATH;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();
}

/*!*****************************************************************************
 @brief	
 @details	���� ����� 2
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpChan2_hand(int32_t Cnt)
{
  if (Cnt > 0) {			// ������ ������
    if (GenCtrl.Menu &&
        MenuNum == MENU_CHAN2) {
      GenCtrl.Menu = 0;			// ��������� ���� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;			// �������� ���� ���� 
      MenuNum = MENU_CHAN2;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else  MenuHeadDepr_disp();		// ������ ��������
}

#if 0
void FpChan2_hand(int32_t Cnt) {
  if (Cnt > 0) {			// ���� ������ ������
    if (GenCtrl.Menu && 
        MenuNum == MENU_CHAN2) {	// ���� ���� ���� ����
      GenCtrl.Menu = 0;			// ��������� ���� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
    }
    else {				// ��� ������ ����
      GenCtrl.Menu = 1;			// �������� ���� ����
      MenuNum = MENU_CHAN2;
      MenuHead_disp();			// ���������� ����
      DispCtrl.Wide = 0;
      Chan2Ctrl.On ^= 1;		// �������� ��������� ������ ����/���
      // MnChan1Mode_disp();
      Chan2Mode_sett();
      Chan2St_disp();			// ���������� � �������
      PosChan2_draw(Chan2Ctrl.On);	// ���������� ������
    }
    DpyScale_draw();			// ���������� ���������� ��� ������� �����
  }
  else MenuHeadDepr_disp();		// ������ ��������
}    
#endif

/*!*****************************************************************************
 */
void Fp11_hand(int32_t Cnt) { }

/*!*****************************************************************************
 @brief	
 @details	���� ���������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note	
 */
void FpSweep_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
    if (GenCtrl.Menu && MenuNum == MENU_SWEEP) {
      GenCtrl.Menu = 0;				// ��������� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;				// �������� ����
      MenuNum = MENU_SWEEP;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();			// ������ ��������
}

/*!*****************************************************************************
 */
void Fp13_hand(int32_t Cnt) { }

/*!*****************************************************************************
 @brief	
 @details	���� �����
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note	
 */
void FpTrig_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
    if (GenCtrl.Menu && MenuNum == MENU_TRIG) {
      GenCtrl.Menu = 0;				// ��������� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;				// �������� ����
      MenuNum = MENU_TRIG;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();			// ������ ��������
}

/*!*****************************************************************************
 */
void Fp15_hand(int32_t Cnt) { }

/*!*****************************************************************************
 @brief	
 @details	���� �������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note	
 */
void FpDisp_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
    if (GenCtrl.Menu && MenuNum == MENU_DISP) {
      GenCtrl.Menu = 0;				// ��������� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;				// �������� ����
      MenuNum = MENU_DISP;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();			// ������ ��������
}

/*!*****************************************************************************
 @brief		
 @details	���� ���� ���
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpAcqu_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
    if (GenCtrl.Menu && MenuNum == MENU_ACQU) {
      GenCtrl.Menu = 0;				// ��������� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;				// �������� ����
      MenuNum = MENU_ACQU;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();			// ������ ��������
}

/*!*****************************************************************************
 @brief	
 @details	���� �������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note	
 */
void FpCurs_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
    if (GenCtrl.Menu && MenuNum == MENU_CURS) {
      GenCtrl.Menu = 0;				// ��������� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;				// �������� ����
      MenuNum = MENU_CURS;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();			// ������ ��������
}

/*!*****************************************************************************
 @brief	
 @details	���� �����
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note	
 */
void FpMeas_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
    if (GenCtrl.Menu && MenuNum == MENU_MEAS) {
      GenCtrl.Menu = 0;				// ��������� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;				// �������� ����
      MenuNum = MENU_MEAS;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();			// ������ ��������
}

/*!*****************************************************************************
 @brief	
 @details	���� ������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note	
 */
void FpMem_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
    if (GenCtrl.Menu && MenuNum == MENU_MEM) {
      GenCtrl.Menu = 0;				// ��������� ����
      HelpMenu_clear();
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;				// �������� ����
      MenuNum = MENU_MEM;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();			// ������ ��������
}

/*!*****************************************************************************
 @brief	
 @details	���� �������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note	
 */
void FpUtil_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
    if (GenCtrl.Menu && MenuNum == MENU_UTIL) {
      GenCtrl.Menu = 0;				// ��������� ����
      HelpMenu_clear();
      // DPY_ClearExMenu();			// � �������� �������� �����
      DispCtrl.Wide = 1;
      SigChans_redraw();
      Curs_redraw();
    }
    else {
      GenCtrl.Menu = 1;				// �������� ����
      MenuNum = MENU_UTIL;
      MenuHead_disp();
      DispCtrl.Wide = 0;
    }
    DpyScale_draw();
  }
  else MenuHeadDepr_disp();			// ������ ��������
}


//__ ������ ��� ���� __________________________________________________________//


/*!*****************************************************************************
 @brief		
 @details	���� ���
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpAutoset_hand(int32_t Cnt) {
#define LEN 8		// time lenth (LEN * 0.5 s / 25 = 160 ms)
#define DTM 8		// dead time
#define HYS 8		// hysteresis

  if (Cnt > 0 && GenCtrl.Autoset == 0) {	// Key Auto pressed, Autoset done
    GenCtrl.Autoset = 1;

/* ���������� ������, ����� ��� ���� ������� */

// ������ ������ � ������� ��������
    /// AcquCtrl.Filt = 3;
    /// AcquFilt_sett();
    AcquCtrl.Peak = 1;
    AcquPeak_sett();    
    
// ���������� ��������� �� ������
    SweepCtrl.TimeNum = TIME_DOT;
    Time_sett();

// ���������� ������ ���������� �� ���� ������ �� ������
    PL_AcquBuf &= ~(PL_ACQU_TDTIE | PL_ACQU_FRMIE | PL_ACQU_DOTIE);
    PL_AcquBuf |= PL_ACQU_DOTIE;
    PL->ACQU = PL_AcquBuf;
    SweepCtrl.Stop = 0;

    uint32_t min;
    uint32_t max;
    uint32_t rng;		// range
    
/* ������ ������ � ������ 1, ���� ������� */
    if (Chan1Ctrl.On) {
      
// ������ ����������� ������
//    Chan1Ctrl.BWLim = 1;
//    Chan1BWLim_sett();

// ���������� ����� ����� ��������, ����� �� ����������� ����
      Chan1Ctrl.VoltNum = 4;				// 20V
      Chan1Ctrl.Cplg = 1;
      Chan1Cplg_sett();

// ���������� ������� � �������� ������
      PosChan1_draw(false);
      TrigLev_draw(false); 
      Chan1Ctrl.SigPos = 512;
      Chan1Ctrl.DispPos = 0;
      FpPos1_hand(0);
      TrigLev_draw(false);      

// ����� ����� �������    
      PL->STAT = PL_START_ACQUST;

// ����� �������, ��������
      min = 255;
      max = 0;
      for (uint32_t i = DTM; i--; ) {
        while (PLIRQ_GET()) { };	// �����, ���� ��� ������� �� �����
        uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      }
      for (uint32_t i = LEN; i--; ) {
        while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
        uint_fast16_t stat = PL->STAT;		// ������ � �������� ���������
        uint32_t rint = (uint8_t)PL->RINT;	// ������ ����� 1 
        if (rint < min) min = rint;
        if (rint > max) max = rint;
      }
      
// ������� ���������� ����������
      rng = max - min;
      if (rng > 100) { }				// 20V
      else if (rng > 50) Chan1Ctrl.VoltNum = 5;		// 10V
      else if (rng > 20) Chan1Ctrl.VoltNum = 6;		// 5V
      else {
      
// ���������� �-� � 10 ��� ��������������
        Chan1Ctrl.VoltNum = 7;				// 2V
	Chan1Cplg_sett();
	min = 255;
	max = 0;
        for (uint32_t i = DTM; i--; ) {
          while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
          uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
        }
        for (uint32_t i = LEN; i--; ) {
          while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
          uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
          uint32_t rint = (uint8_t)PL->RINT;	// ������ ����� 1 
          if (rint < min) min = rint;
          if (rint > max) max = rint;
        }

// ������� ���������� ����������
        rng = max - min;
        if (rng > 100) { }				// 2V
	else if (rng > 50) Chan1Ctrl.VoltNum = 8;	// 1V
	else if (rng > 20) Chan1Ctrl.VoltNum = 9;	// 0.5V
	else {

// ���������� �-� � 10 ��� ��������������
          Chan1Ctrl.VoltNum = 10;			// 0.2V
	  Chan1Cplg_sett();
	  min = 255;
	  max = 0;
          for (uint32_t i = DTM; i--; ) {
            while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
            uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
          }
          for (uint32_t i = LEN; i--; ) {
            while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
            uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
            uint32_t rint = (uint8_t)PL->RINT;	// ������ ����� 1 
            if (rint < min) min = rint;
            if (rint > max) max = rint;
          }

// ������� ���������� ����������
          rng = max - min;
          if (rng > 100) { }				// 0.2V
	  else if (rng > 50) Chan1Ctrl.VoltNum = 11;	// 0.1V
	  else if (rng > 20) Chan1Ctrl.VoltNum = 12;	// 50mV
	  else {

// ���������� �-� � 10 ��� ��������������
            Chan1Ctrl.VoltNum = 13;			// 20mV
	    Chan1Cplg_sett();
	    min = 255;
	    max = 0;
            for (uint32_t i = DTM; i--; ) {
              while (PLIRQ_GET()) { };	// �����, ���� ��� ������� �� �����
              uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
            }
    
            for (uint32_t i = LEN; i--; ) {
              while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
              uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
              uint32_t rint = (uint8_t)PL->RINT;	// ������ ����� 1 
              if (rint < min) min = rint;
              if (rint > max) max = rint;
            }  

// ������� ���������� ����������
            rng = max - min;
            if (rng > 100) { }				// 20mV
	    else if (rng > 50) Chan1Ctrl.VoltNum = 14;	// 10mV
	    else if (rng > 20) Chan1Ctrl.VoltNum = 15;	// 5mV
	    else Chan1Ctrl.VoltNum = 16;		// 2mV

          }	// 20mV
	}	// 0.2V
      }		// 2V
      
// ���� �������� ��� ������, ��������� �-� (����� ������ ���������������)
      if (Chan2Ctrl.On) {
        if (Chan1Ctrl.VoltNum != 16)
          Chan1Ctrl.VoltNum--;      
        PosChan1_draw(false);
	Chan1Ctrl.SigPos += 100;
      }
      
    Chan1Cplg_sett();
    FpPos1_hand(0);
    TrigLev_draw(false);		// ������� ������    
    }		// Chan 1

/* ������ ������ � ������ 2, ���� ������� */
    if (Chan2Ctrl.On) {
      
// ������ ����������� ������
//    Chan1Ctrl.BWLim = 1;
//    Chan1BWLim_sett();

// ���������� ����� ����� ��������, ����� �� ����������� ����
      Chan2Ctrl.VoltNum = 4;				// 20V
      Chan2Ctrl.Cplg = 1;
      Chan2Cplg_sett();

// ���������� ������� � �������� ������
      PosChan2_draw(false);
      Chan2Ctrl.SigPos = 512;
      Chan2Ctrl.DispPos = 0;
      FpPos2_hand(0);
      TrigLev_draw(false);      

// ����� ����� �������    
      PL->STAT = PL_START_ACQUST;

// ����� �������, ��������
      min = 255;
      max = 0;
      for (uint32_t i = DTM; i--; ) {
        while (PLIRQ_GET()) { };	// �����, ���� ��� ������� �� �����
        uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      }
      for (uint32_t i = LEN; i--; ) {
        while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
        uint_fast16_t stat = PL->STAT;		// ������ � �������� ���������
        uint32_t rint = (uint8_t)(PL->RINT >> 8);	// ������ ����� 2 
        if (rint < min) min = rint;
        if (rint > max) max = rint;
      }
      
// ������� ���������� ����������
      rng = max - min;
      if (rng > 100) { }				// 20V
      else if (rng > 50) Chan2Ctrl.VoltNum = 5;		// 10V
      else if (rng > 20) Chan2Ctrl.VoltNum = 6;		// 5V
      else {
      
// ���������� �-� � 10 ��� ��������������
        Chan2Ctrl.VoltNum = 7;				// 2V
	Chan2Cplg_sett();
	min = 255;
	max = 0;
        for (uint32_t i = DTM; i--; ) {
          while (PLIRQ_GET()) { };	// �����, ���� ��� ������� �� �����
          uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
        }
        for (uint32_t i = LEN; i--; ) {
          while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
          uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
          uint32_t rint = (uint8_t)(PL->RINT >> 8);	// ������ ����� 2 
          if (rint < min) min = rint;
          if (rint > max) max = rint;
        }

// ������� ���������� ����������
        rng = max - min;
        if (rng > 100) { }				// 2V
	else if (rng > 50) Chan2Ctrl.VoltNum = 8;	// 1V
	else if (rng > 20) Chan2Ctrl.VoltNum = 9;	// 0.5V
	else {

// ���������� �-� � 10 ��� ��������������
          Chan2Ctrl.VoltNum = 10;			// 0.2V
	  Chan2Cplg_sett();
	  min = 255;
	  max = 0;
          for (uint32_t i = DTM; i--; ) {
            while (PLIRQ_GET()) { };	// �����, ���� ��� ������� �� �����
            uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
          }
          for (uint32_t i = LEN; i--; ) {
            while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
            uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
            uint32_t rint = (uint8_t)(PL->RINT >> 8);	// ������ ����� 2 
            if (rint < min) min = rint;
            if (rint > max) max = rint;
          }

// ������� ���������� ����������
          rng = max - min;
          if (rng > 100) { }				// 0.2V
	  else if (rng > 50) Chan2Ctrl.VoltNum = 11;	// 0.1V
	  else if (rng > 20) Chan2Ctrl.VoltNum = 12;	// 50mV
	  else {

// ���������� �-� � 10 ��� ��������������
            Chan2Ctrl.VoltNum = 13;			// 20mV
	    Chan2Cplg_sett();
	    min = 255;
	    max = 0;
            for (uint32_t i = DTM; i--; ) {
              while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
              uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
            }
            for (uint32_t i = LEN; i--; ) {
              while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
              uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
              uint32_t rint = (uint8_t)(PL->RINT >> 8);	// ������ ����� 2 
              if (rint < min) min = rint;
              if (rint > max) max = rint;
            }

// ������� ���������� ����������
            rng = max - min;
            if (rng > 100) { }				// 20mV
	    else if (rng > 50) Chan2Ctrl.VoltNum = 14;	// 10mV
	    else if (rng > 20) Chan2Ctrl.VoltNum = 15;	// 5mV
	    else Chan2Ctrl.VoltNum = 16;		// 2mV

          }	// 20mV
	}	// 0.2V
      }		// 2V
      
// ���� �������� ��� ������, ��������� �-� (����� ������ ���������������)
      if (Chan1Ctrl.On) {
        if (Chan2Ctrl.VoltNum != 16)
          Chan2Ctrl.VoltNum--;      
        PosChan2_draw(false);
	Chan2Ctrl.SigPos -= 100;
      }
          
    Chan2Cplg_sett();
    FpPos2_hand(0);
    TrigLev_draw(false);
    }		// Chan 2

/* ���������� ������������� �� ����� �������� ������� */

    TrigLev_draw(false);
    TrigCtrl.Level = 512;
    ANADAC(DAC_LEVEL, TrigCtrl.Level << 2);
    
    if (Chan2Ctrl.VoltNum < Chan1Ctrl.VoltNum) {
      TrigCtrl.Sour = 2;
    }
    else TrigCtrl.Sour = 1;
    TrigSour_sett();
    TrigSt_disp();
    TrigLev_draw(true);
    
/* ���������� �����/��� */

    // SweepCtrl.TimeNum = 15;
    // Time_sett();

// ����� �������� �������� �������
    min = 255;
    max = 0;
    for (uint32_t i = DTM; i--; ) {
       while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
       uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }

    if (TrigCtrl.Sour == 1) {
      for (uint32_t i = LEN; i--; ) {
        while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
        uint_fast16_t stat = PL->STAT;		// ������ � �������� ���������
        uint32_t rint = (uint8_t)PL->RINT;	// ������ ����� 1 
        if (rint < min) min = rint;
        if (rint > max) max = rint;
      }
    }
    
    if (TrigCtrl.Sour == 2) {
      for (uint32_t i = LEN; i--; ) {
        while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
        uint_fast16_t stat = PL->STAT;		// ������ � �������� ���������
        uint32_t rint = (uint8_t)(PL->RINT >> 8);	// ������ ����� 2 
        if (rint < min) min = rint;
        if (rint > max) max = rint;
      }
    }
    
    uint32_t mid = (max + min) / 2;
    // Num_draw(mid);

// ������ ������ � ������� ��������
    AcquCtrl.Filt = 0;
    AcquFilt_sett();    
    AcquCtrl.Peak = 0;
    AcquPeak_sett();
    
// ���������� ������ ���������� �� ���� ������ ������
    PL_AcquBuf &= ~(PL_ACQU_TDTIE | PL_ACQU_FRMIE | PL_ACQU_DOTIE);
    PL_AcquBuf |= PL_ACQU_FRMIE;
    PL->ACQU = PL_AcquBuf;
    
// ���������� ������ ������ 0.5K (�� �����! ������ ������� 512 �������)
    // MemCtrl.SizeNum = 0;		// 0.5K
    // MemSizeBuf_disp();
    // MemSize_sett();
    
// ���������� ��������� �� ������, 0.1 us, ����� ������� �� ������� �����
// 0.1 us * (512 / 25) = 2.048 us
    SweepCtrl.TimeNum = 26;
    Time_sett();    

// ����� ����� �������, ������� ���������� �����    
    PL->STAT = PL_START_ACQUST;
      
    while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
    uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������

    bool     sthi = false;		// ������ ���� ��������
    uint32_t edge = 0;			// ���������� ��������� ����� ��������
    
// �������� � ������ 1
    if (TrigCtrl.Sour == 1) {   
      uint32_t rint = (uint8_t)(PL->MINT);	// ��������� ��������� ������� � �����
      if (rint < mid - HYS) sthi = 0;
      if (rint > mid + HYS) sthi = 1;     
      for (uint32_t i = 511; i--; ) {
        rint = (uint8_t)PL->MINT;
        if ((rint < mid - HYS && sthi) || (rint > mid + HYS && !sthi)) {
          edge++;
          sthi ^= 1;
	}
      }
    }

// �������� � ������ 2
    if (TrigCtrl.Sour == 2) {   
      uint32_t rint = (uint8_t)(PL->MINT >> 8);	// ��������� ��������� ������� � �����
      if (rint < mid - HYS) sthi = 0;
      if (rint > mid + HYS) sthi = 1;     
      for (uint32_t i = 511; i--; ) {
        rint = (uint8_t)(PL->MINT >> 8);
        if ((rint < mid - HYS && sthi) || (rint > mid + HYS && !sthi)) {
          edge++;
          sthi ^= 1;
        }
      }
    }
    
    if (edge > 200) SweepCtrl.TimeNum = 31;
    else if (edge > 80) SweepCtrl.TimeNum = 30;
    else if (edge > 40) SweepCtrl.TimeNum = 29;
    else if (edge > 20) SweepCtrl.TimeNum = 28;
    else if (edge > 8) SweepCtrl.TimeNum = 27;
    else if (edge > 4) SweepCtrl.TimeNum = 26;
    else
    {
      
// ���������� ��������� 10us
      SweepCtrl.TimeNum = 20;
      Time_sett();    

// ����� ����� �������, ������� ���������� �����    
      PL->STAT = PL_START_ACQUST;
      
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������

      edge = 0;				// ���������� ��������� ����� ��������
    
// �������� � ������ 1
      if (TrigCtrl.Sour == 1) {
        uint32_t rint = (uint8_t)PL->MINT;	// ��������� ��������� ������� � �����
        if (rint < mid - HYS) sthi = 0;
        if (rint > mid + HYS) sthi = 1;
        for (uint32_t i = 511; i--; ) {
          rint = (uint8_t)PL->MINT;
          if ((rint < mid - HYS && sthi) || (rint > mid + HYS && !sthi)) {
            edge++;
            sthi ^= 1;
          }
        }
      }

// �������� � ������ 2
      if (TrigCtrl.Sour == 2) {
        uint32_t rint = (uint8_t)(PL->MINT >> 8);	// ��������� ��������� ������� � �����
        if (rint < mid - HYS) sthi = 0;
        if (rint > mid + HYS) sthi = 1;
        for (uint32_t i = 511; i--; ) {
          rint = (uint8_t)(PL->MINT >> 8);
          if ((rint < mid - HYS && sthi) || (rint > mid + HYS && !sthi)) {
            edge++;
            sthi ^= 1;
          }
        }
      }
      
      if (edge > 200) SweepCtrl.TimeNum = 25;
      else if (edge > 80) SweepCtrl.TimeNum = 24;
      else if (edge > 40) SweepCtrl.TimeNum = 23;
      else if (edge > 20) SweepCtrl.TimeNum = 22;
      else if (edge > 8) SweepCtrl.TimeNum = 21;
      else if (edge > 4) SweepCtrl.TimeNum = 20;
      else
      {
      
// ���������� ��������� 1ms
        SweepCtrl.TimeNum = 14;
        Time_sett();    

// ����� ����� �������, ������� ���������� �����    
        PL->STAT = PL_START_ACQUST;
      
        while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
        uint_fast16_t stat = PL->STAT;		// ������ � �������� ���������

        edge = 0;				// ���������� ��������� ����� ��������
    
// �������� � ������ 1
        if (TrigCtrl.Sour == 1) {
          uint32_t rint = (uint8_t)PL->MINT;	// ��������� ��������� ������� � �����
          if (rint < mid - HYS) sthi = 0;
          if (rint > mid + HYS) sthi = 1;
          for (uint32_t i = 511; i--; ) {
            rint = (uint8_t)PL->MINT;
            if ((rint < mid - HYS && sthi) || (rint > mid + HYS && !sthi)) {
              edge++;
              sthi ^= 1;
            }
          }
        }
	
// �������� � ������ 2
        if (TrigCtrl.Sour == 2) {
          uint32_t rint = (uint8_t)(PL->MINT >> 8);	// ��������� ��������� ������� � �����
          if (rint < mid - HYS) sthi = 0;
          if (rint > mid + HYS) sthi = 1;
          for (uint32_t i = 511; i--; ) {
            rint = (uint8_t)(PL->MINT >> 8);
            if ((rint < mid - HYS && sthi) || (rint > mid + HYS && !sthi)) {
              edge++;
              sthi ^= 1;
            }
          }
        }
      
        if (edge > 200) SweepCtrl.TimeNum = 19;
        else if (edge > 80) SweepCtrl.TimeNum = 18;
        else if (edge > 40) SweepCtrl.TimeNum = 17;
        else if (edge > 20) SweepCtrl.TimeNum = 16;
        else if (edge > 8) SweepCtrl.TimeNum = 15;
        else if (edge > 4) SweepCtrl.TimeNum = 14;
        else
	{

// ���������� ��������� 0.1s
          SweepCtrl.TimeNum = 8;
          Time_sett();

// ����� ����� �������, ������� ���������� �����    
          PL->STAT = PL_START_ACQUST;
      
          while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
          uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������

          edge = 0;				// ���������� ��������� ����� ��������
    
// �������� � ������ 1
          if (TrigCtrl.Sour == 1) {
            uint32_t rint = (uint8_t)PL->MINT;		// ��������� ��������� ������� � �����
            if (rint < mid - HYS) sthi = 0;
            if (rint > mid + HYS) sthi = 1;
            for (uint32_t i = 511; i--; ) {
              rint = (uint8_t)PL->MINT;
              if ((rint < mid - HYS && sthi) || (rint > mid + HYS && !sthi)) {
                edge++;
                sthi ^= 1;
              }
            }
          }

// �������� � ������ 2
          if (TrigCtrl.Sour == 2) {
            uint32_t rint = (uint8_t)(PL->MINT >> 8);	// ��������� ��������� ������� � �����
            if (rint < mid - HYS) sthi = 0;
            if (rint > mid + HYS) sthi = 1;
            for (uint32_t i = 511; i--; ) {
              rint = (uint8_t)(PL->MINT >> 8);
              if ((rint < mid - HYS && sthi) || (rint > mid + HYS && !sthi)) {
                edge++;
                sthi ^= 1;
              }
            }
          }
      
          if (edge > 200) SweepCtrl.TimeNum = 13;
          else if (edge > 80) SweepCtrl.TimeNum = 12;
          else if (edge > 40) SweepCtrl.TimeNum = 11;
          else if (edge > 20) SweepCtrl.TimeNum = 10;
          else if (edge > 8) SweepCtrl.TimeNum = 9;
          else if (edge > 4) SweepCtrl.TimeNum = 8;
          else SweepCtrl.TimeNum = 7;

	}	// < 14
      }		// < 20
    }		// < 26
    
    //  Num_draw(edge);
    Time_sett();
    
/* ������������ ���������� ������ ������ */    

// ���������� �������    
    // PosChan1_draw(Chan1Ctrl.On);
    // PosChan2_draw(Chan2Ctrl.On);
    
// ���������� � �������    
    Chan1St_disp();
    Chan2St_disp();
    TimeSt_disp(); 
    
// ������������ ������ ���������� �� ��������� �������������

    PL_AcquBuf |= PL_ACQU_TDTIE;
    PL->ACQU = PL_AcquBuf;
  }

  Autoset_disp();
  GenCtrl.Autoset = 0;
  
  DpyWork_clear(MASK_MATSIG);
  Sweep_init();  
  // PL->STAT = PL_START_ACQUST;
  
// ������������ �������������

  if (PL->STAT & PL_STAT_TRIGDET)	// ���� ���� �������������
    PanCtrl.TxBuf &= ~(1 << 4);		// ������ ���� �������������
  else
    PanCtrl.TxBuf |=  (1 << 4);		// �������� ���� �������������
  PanCtrl.TxBuf |= 0x40;
  USART3->DR = PanCtrl.TxBuf;		// ������� � ������
  
}

/*!*****************************************************************************
 @brief		
 @details	����/����
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpStSp_hand(int32_t Cnt) {
  if (Cnt > 0) {			// Key Stop pressed
    SweepCtrl.Stop ^= 1;
    StSp_disp();			// display
    if (!SweepCtrl.Stop) {
      Sweep_init();
      if (SweepCtrl.Roll) DpyWork_clear(MASK_MATSIG);
    }
  }
}

/*!*****************************************************************************
 @brief		
 @details	������ / ���� / ������
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		Menu = 0; -> Menu = 1; -> Menu = 1;
		Help = 0; -> Help = 0; -> Help = 1;
 */
void FpHelp_hand(int32_t Cnt) {
  if (Cnt > 0) {				// ������ ������
// � ��������� ���� ������� ����� ��������� ������
    if (MenuNum == MENU_SERV && !SweepCtrl.Stop) return;
    if (!GenCtrl.Menu) {			// ���� ���� ���
      GenCtrl.Menu = 1;				// ������������ ����
      if (MenuNum == MENU_SERV)  DpyScreen_blank();
      MenuHead_disp();				// ���������� ����
      DispCtrl.Wide = 0;
      DpyScale_draw();
    }
    else {					// ���� ����
      if (DispCtrl.HelpEna && !GenCtrl.Help) {	// ���� ������ ���������, �� �� ��������
        GenCtrl.Help = 1;			// �������� ����� ������      
	Help_draw();				// �������� ������
      }
      else {					// ������ ���������, ��� ��� ��������
        GenCtrl.Menu = 0;
	GenCtrl.Help = 0;
        if (MenuNum == MENU_SERV)  DpyScreen_blank();
        HelpMenu_clear();
        DispCtrl.Wide = 1;
	DpyScale_draw();			// ���������� �����
        SigChans_redraw();
	Curs_redraw();
      }
    }
  }
  else {					// ������ ��������
    {
      MenuHeadDepr_disp();			// ���������� ���������� ������
    }
  }
}


//__ ������, ������������� ���� _______________________________________________//


/*!*****************************************************************************
 @brief		
 @details	F1
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpF1_hand(int32_t Cnt) {
  if (GenCtrl.Menu) {
    if (Cnt > 0) {
      if (MenuNum == MENU_SERV) {
        MenuHead_disp();
	MenuHeadDepr_disp();
      }
      DPY_LINEH(DPYMAH + 1, DPYM1AV,      318, 0xff, ITEM_EMFA, 0xff);
      DPY_LINEH(DPYMAH + 1, DPYM1AV + 34, 318, 0xff, ITEM_EMRI, 0xff);
      MenuItem_hand[MenuNum][0]();
    }
    else {
      DPY_LINEH(DPYMAH + 1, DPYM1AV,      318, 0xff, ITEM_EMRI, 0xff);
      DPY_LINEH(DPYMAH + 1, DPYM1AV + 34, 318, 0xff, ITEM_EMFA, 0xff);
    }
  }
}

/*!*****************************************************************************
 @brief		
 @details	F2
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpF2_hand(int32_t Cnt) {
  if (GenCtrl.Menu) {
    if (Cnt > 0) {
      if (MenuNum == MENU_SERV) {
        MenuHead_disp();
	MenuHeadDepr_disp();
      }
      DPY_LINEH(DPYMAH + 1, DPYM2AV,      318, 0xff, ITEM_EMFA, 0xff);
      DPY_LINEH(DPYMAH + 1, DPYM2AV + 34, 318, 0xff, ITEM_EMRI, 0xff);
      MenuItem_hand[MenuNum][1]();
    }
    else {
      DPY_LINEH(DPYMAH + 1, DPYM2AV,      318, 0xff, ITEM_EMRI, 0xff);
      DPY_LINEH(DPYMAH + 1, DPYM2AV + 34, 318, 0xff, ITEM_EMFA, 0xff);
    }
  }
}

/*!*****************************************************************************
 @brief		
 @details	F3
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpF3_hand(int32_t Cnt) {
  if (GenCtrl.Menu) {
    if (Cnt > 0) {
      if (MenuNum == MENU_SERV) {
        MenuHead_disp();
	MenuHeadDepr_disp();
      }
      DPY_LINEH(DPYMAH + 1, DPYM3AV,      318, 0xff, ITEM_EMFA, 0xff);
      DPY_LINEH(DPYMAH + 1, DPYM3AV + 34, 318, 0xff, ITEM_EMRI, 0xff);
      MenuItem_hand[MenuNum][2]();
    }
    else {
      DPY_LINEH(DPYMAH + 1, DPYM3AV,      318, 0xff, ITEM_EMRI, 0xff);
      DPY_LINEH(DPYMAH + 1, DPYM3AV + 34, 318, 0xff, ITEM_EMFA, 0xff);
    }
  }
}

/*!*****************************************************************************
 @brief		
 @details	F4
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpF4_hand(int32_t Cnt) {
  if (GenCtrl.Menu) {
    if (Cnt > 0) {
      if (MenuNum == MENU_SERV) {
        MenuHead_disp();
	MenuHeadDepr_disp();
      }
      DPY_LINEH(DPYMAH + 1, DPYM4AV,      318, 0xff, ITEM_EMFA, 0xff);
      DPY_LINEH(DPYMAH + 1, DPYM4AV + 34, 318, 0xff, ITEM_EMRI, 0xff);
      MenuItem_hand[MenuNum][3]();
    }
    else {
      DPY_LINEH(DPYMAH + 1, DPYM4AV,      318, 0xff, ITEM_EMRI, 0xff);
      DPY_LINEH(DPYMAH + 1, DPYM4AV + 34, 318, 0xff, ITEM_EMFA, 0xff);
    }
  }
}

#if false
/*!*****************************************************************************
 @brief		
 @details	F5
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpF5_hand(int32_t Cnt) {
  if (GenCtrl.Menu) {
    if (Cnt > 0) {
      if (!GenCtrl.Lock) {    
        DPY_LINEH(DPYMAH + 1, DPYM5AV,      318, 0xff, ITEM_EMFA, 0xff);
        DPY_LINEH(DPYMAH + 1, DPYM5AV + 34, 318, 0xff, ITEM_EMRI, 0xff);
// ��� ������ ������ ������� ������ ���������
	if (MenuNum == MENU_SERV) {
	  DPY_LINEH(DPYMAH + 1, DPYM5AV,      318, 0xFF, ITEM_EMFA, 0xFF);
	  DPY_LINEH(DPYMAH + 1, DPYM5AV + 34, 318, 0xFF, ITEM_EMRI, 0xFF);
	}
      }
      MenuItem_hand[MenuNum][4](); 
    }
    else {
      if (!GenCtrl.Lock) {
        DPY_LINEH(DPYMAH + 1, DPYM5AV,      318, 0xff, ITEM_EMRI, 0xff);
        DPY_LINEH(DPYMAH + 1, DPYM5AV + 34, 318, 0xff, ITEM_EMFA, 0xff);
      }
    }
  }
}
#endif

/*!*****************************************************************************
 @brief		
 @details	F5
 @param		Cnt - ���������� ������� ����������-����������
 @return	
 @note		
 */
void FpF5_hand(int32_t Cnt) {
  if (GenCtrl.Menu) {
    if (Cnt > 0) {
      if (!GenCtrl.Lock) {    
        DPY_LINEH(DPYMAH + 1, DPYM5AV,      318, 0xff, ITEM_EMFA, 0xff);
        DPY_LINEH(DPYMAH + 1, DPYM5AV + 34, 318, 0xff, ITEM_EMRI, 0xff);
// ��� ������ ������ ������� ������ ���������
	if (MenuNum == MENU_SERV) {
	  DPY_LINEH(DPYMAH + 1, DPYM5AV,      318, 0xFF, ITEM_EMFA, 0xFF);
	  DPY_LINEH(DPYMAH + 1, DPYM5AV + 34, 318, 0xFF, ITEM_EMRI, 0xFF);
	}
      }
      MenuItem_hand[MenuNum][4](); 
    }
    else {
      if (!GenCtrl.Lock) {
        DPY_LINEH(DPYMAH + 1, DPYM5AV,      318, 0xff, ITEM_EMRI, 0xff);
        DPY_LINEH(DPYMAH + 1, DPYM5AV + 34, 318, 0xff, ITEM_EMFA, 0xff);
      }
    }
  }
}

/*!*****************************************************************************
 */
void Fp30_hand(int32_t Cnt) { }

/*!*****************************************************************************
 */
void Fp31_hand(int32_t Cnt) { }


//__ ����������� ��������� ����, ���������� ���������� ���� ___________________//


/*!*****************************************************************************
 @brief		
 @details	������ ���������� �������� ����
 @note		
 */
void MnVoid_hand(void) { }

/*!*****************************************************************************
 @brief		
 @details	������ ������� ��������� �������� ����
 @note		
 */
void MnVoid_disp(void) { }


//* ������� ���� ������ *//

/*!*****************************************************************************
 @brief		
 @details	������, ����������, ���������� � ����
 */
void MnServCal_hand(void) {
  uint_fast8_t num = ServCtrl.CalNum;
  num++;
  if (num >= 2) num = 0;
  ServCtrl.CalNum = num;
  ExeNum = (EXE_t)(EXE_CALIBR + num);	// �������� ����� ������� "���������"
  MnServCal_disp();
}

/*!*****************************************************************************
 @brief		
 @details	������, ����������, ��������� � ����
 */
void MnServCal_disp(void) {
  static const uint8_t *Caltext[] = {" ������", "���������"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 1, DPYM1VV);
  uint_fast8_t numb = ServCtrl.CalNum;
  DpyRect_fill(pDpy, 58, 10, 0xff<<8 | VOFF_BKG);
  DpyString_draw(pDpy, Caltext[numb], VOFF_TXT, 0); 
}

/*!*****************************************************************************
 @brief		
 @details	������, ������� ����������, ���������� � ����
 */
void MnServCPU_hand(void) { 
  uint32_t numb = ServCtrl.CPUNum;
  numb++;
  if (numb >= 2) numb = 0;
  ServCtrl.CPUNum = numb;
  ExeNum = (EXE_t)(EXE_CPUIMEM + numb);	// �������� ����� ������� "���������"
  GenCtrl.Lock = 0;
  MnServCPU_disp();
}

/*!*****************************************************************************
 @brief		
 @details	������, ������� ����������, ��������� � ����
 */
void MnServCPU_disp(void) {
  static const uint8_t *CPUtext[2] = {"����� ���", "����� ���"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 1, DPYM2VV);
  uint32_t numb = ServCtrl.CPUNum;
  DpyRect_fill(pDpy, 58, 10, 0xff<<8 | VOFF_BKG);
//  DpyRoRect_fill(pDpy+9*mode, 40, 14, 0xff<<8|VON_BKG);
  DpyString_draw(pDpy, CPUtext[numb], VOFF_TXT, 0);
}

/*!*****************************************************************************
 @brief		
 @details	������, ������� ����, ���������� � ����
 */
void MnServPL_hand(void) { 
  uint32_t numb = ServCtrl.PLNum;
  numb++;
  if (numb >= 4)  numb = 0;
  ServCtrl.PLNum = numb;
  ExeNum = (EXE_t)(EXE_PLRECV + numb);	// �������� ����� ������� "���������"
  GenCtrl.Lock = 0;
  MnServPL_disp();
}

/*!*****************************************************************************
 @brief		
 @details	������, ������� ����, ��������� � ����
 */
void MnServPL_disp(void) {
  static const uint8_t *PLtext[4] = {
    " �������", "����� ���", "\x98\x98��������", "����� ���"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 1,DPYM3VV);
  uint32_t numb = ServCtrl.PLNum;
  DpyRect_fill(pDpy, 58, 10, 0xff<<8 | VOFF_BKG);
//  DpyRoRect_fill(pDpy+9*mode, 40, 14, 0xff<<8|VON_BKG);
  DpyString_draw(pDpy, PLtext[numb], VOFF_TXT, 0);
}

/*!*****************************************************************************
 @brief		
 @details	������, ������� ���, ���������� � ����
 */
void MnServDpy_hand(void) {
  uint32_t numb = ServCtrl.DpyNum;
  numb++;
  if (numb >= 8)  numb = 0;
  ServCtrl.DpyNum = numb;
  ExeNum = (EXE_t)(EXE_DPYWHITE + numb);		// �������� ����� ������� "���������"
  if (numb != 8)  GenCtrl.Lock = 1;
  else		  GenCtrl.Lock = 0; 
  MnServDpy_disp();
}

/*!*****************************************************************************
 @brief		
 @details	������, ������� ���, ��������� � ����
 */
void MnServDpy_disp(void) {
  static const uint8_t *LCDtext[] = {
    "  �����", " \x98������", "  �����", " �������",
    " �������", " �������", "  �����", "\x98���������"
    };
  uint8_t *pDpy = DPYPOS(DPYMHH + 1, DPYM4VV);
  uint32_t numb = ServCtrl.DpyNum;
  DpyRect_fill(pDpy, 58, 10, 0xff<<8 | VOFF_BKG);
//  DpyRoRect_fill(pDpy+9*mode, 40, 14, 0xff<<8|VON_BKG);
  DpyString_draw(pDpy, LCDtext[numb], VOFF_TXT, 0);
}

/*!*****************************************************************************
 @details	������, ������� ���������, ���������� � ����
 */
void MnServExe_hand(void) {
  ExeItem_hand[ExeNum]();
}

/*!*****************************************************************************
 @details	������, ������� ���������, ��������� � ����
 */
void MnServExe_disp(void) { }


//* ����� 1 *//

/*!*****************************************************************************
 @details	����� 1, �����, ����������
 @note		���� <-> ���
 */
void MnChan1Mode_hand(void) {
  Chan1Ctrl.On ^= 1;
  MnChan1Mode_disp();
  Chan1Mode_sett();
  Chan1St_disp();		// ���������� � �������
  PosChan1_draw(Chan1Ctrl.On);	// ���������� ������
  CursMeasSt_disp();		// ��������/������� ��������� �� ��������
  SetCursSt_disp();		// ��������/������� ��������� ���������
}

/*!*****************************************************************************
 @details	����� 1, �����, ��������� � ����
 @note		���� <-> ���
 */
void MnChan1Mode_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM1RV), Chan1Ctrl.On);
}

/*!*****************************************************************************
 @details	����� 1, �������, ����������
 @note		
 */
void MnChan1Prb_hand(void) {
  INC_MAX(Chan1Ctrl.Prb, 3);
  MnChan1Prb_disp();
  Chan1St_disp();		// ���������� � �������
  if (CursCtrl.On) SetCursSt_disp();  
}

/*!*****************************************************************************
 @details	����� 1, �������, ��������� � ����
 @note		
 */
void MnChan1Prb_disp(void) {
  DpyChanPrb_draw((uint32_t)Chan1Ctrl.Prb);
}

/*!*****************************************************************************
 @details	����� 1, ��������, ����������
 @note		
 */
void MnChan1Inv_hand(void) {
  if (Chan1Ctrl.On) {
    SigChan1_draw(0);
    PosChan1_draw(0);
  }
  Chan1Ctrl.Inv ^= 1;
  MnChan1Inv_disp();
  Chan1St_disp();
  if (Chan1Ctrl.On) {
    SigChan1_draw(3);
    PosChan1_draw(1);
  }
}

/*!*****************************************************************************
 @details	����� 1, ��������, ��������� � ����
 @note		
 */
void MnChan1Inv_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM3RV), Chan1Ctrl.Inv);
}

/*!*****************************************************************************
 @details	����� 1, �����, ����������
 @note		
 */
void MnChan1Cplg_hand(void) {
  INC_MAX(Chan1Ctrl.Cplg, 2);
  MnChan1Cplg_disp();
  Chan1Cplg_sett();
  FpPos1_hand(0);		// ��������������� �������
  Chan1St_disp();		// ���������� � �������
}

/*!*****************************************************************************
 @details	����� 1, �����, ��������� � ����
 @note		
 */
void MnChan1Cplg_disp(void) {
  DpyChanCplg_draw(Chan1Ctrl.Cplg);
}

/*!*****************************************************************************
 @details	����� 1, ����������� ������, ����������
 @note		
 */
void MnChan1BWLim_hand(void) {
  Chan1Ctrl.BWLim ^= 1;
  MnChan1BWLim_disp();
  Chan1BWLim_sett();
  Chan1St_disp();			// ���������� � �������
}

/*!*****************************************************************************
 @details	����� 1, ����������� ������, ��������� � ����
 @note		
 */
void MnChan1BWLim_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM5RV), Chan1Ctrl.BWLim);
}

#if 0
/*!*****************************************************************************
 @details	����� 1, ����������, ����������
 @note		
 */
void MnChan1Gnd_hand(void) {
  Chan1Ctrl.Gnd ^= 1;
//  MnChan1Gnd_disp();
  Chan1Gnd_sett();
  Chan1St_disp();			// ���������� � �������
}

/*!*****************************************************************************
 @details	����� 1, ����������, ��������� � ����
 @note		
 */
void MnChan1Gnd_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM5RV), Chan1Ctrl.Gnd);
}
#endif

//* ����� 2 *//

/*!*****************************************************************************
 @details	����� 2, �����, ����������
 @note		���� <-> ���
 */
void MnChan2Mode_hand(void) {
  Chan2Ctrl.On ^= 1;
  MnChan2Mode_disp();
  Chan2Mode_sett();
  Chan2St_disp();		// ���������� � �������
  PosChan2_draw(Chan2Ctrl.On);	// ���������� ������
  CursMeasSt_disp();		// ��������/������� ��������� �� ��������
  SetCursSt_disp();		// ��������/������� ��������� ���������
}

/*!*****************************************************************************
 @details	����� 2, �����, ��������� � ����
 @note		���� <-> ���
 */
void MnChan2Mode_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM1RV), Chan2Ctrl.On);
}

/*!*****************************************************************************
 @details	����� 2, �������, ����������
 @note		
 */
void MnChan2Prb_hand(void) {
  INC_MAX(Chan2Ctrl.Prb, 3);
  MnChan2Prb_disp();
  Chan2St_disp();
}

/*!*****************************************************************************
 @details	����� 2, �������, ��������� � ����
 @note		
 */
void MnChan2Prb_disp(void) {
  DpyChanPrb_draw((uint32_t)Chan2Ctrl.Prb);
  if (CursCtrl.On) SetCursSt_disp();
}

/*!*****************************************************************************
 @details	����� 2, ��������, ����������
 @note		
 */
void MnChan2Inv_hand(void) {
  if (Chan2Ctrl.On) {
    SigChan2_draw(0);
    PosChan2_draw(0);
  }
  Chan2Ctrl.Inv ^= 1;
  MnChan2Inv_disp();
  Chan2St_disp();
  if (Chan2Ctrl.On) {
    SigChan2_draw(3);
    PosChan2_draw(1);
  }
}

/*!*****************************************************************************
 @details	����� 2, ��������, ��������� � ����
 @note		
 */
void MnChan2Inv_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM3RV), Chan2Ctrl.Inv);
}

/*!*****************************************************************************
 @details	����� 2, �����, ����������
 @note		
 */
void MnChan2Cplg_hand(void) {
  INC_MAX(Chan2Ctrl.Cplg, 2);
  MnChan2Cplg_disp();
  Chan2Cplg_sett();
  FpPos2_hand(0);		// ��������������� �������
  Chan2St_disp();		// ���������� � �������
}

/*!*****************************************************************************
 @details	����� 2, �����, ��������� � ����
 @note		
 */
void MnChan2Cplg_disp(void) {
  DpyChanCplg_draw(Chan2Ctrl.Cplg);
}

/*!*****************************************************************************
 @details	����� 2, ����������� ������, ����������
 @note		
 */
void MnChan2BWLim_hand(void) {
  Chan2Ctrl.BWLim ^= 1;
  MnChan2BWLim_disp();
  Chan2BWLim_sett();
  Chan2St_disp();			// ���������� � �������
}

/*!*****************************************************************************
 @details	����� 2, ����������� ������, ��������� � ����
 @note		
 */
void MnChan2BWLim_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM5RV), Chan2Ctrl.BWLim);
}

#if 0
/*!*****************************************************************************
 @details	����� 2, ����������, ����������
 @note		
 */
void MnChan2Gnd_hand(void) {
  Chan2Ctrl.Gnd ^= 1;
//  MnChan2Gnd_disp();
  Chan2Gnd_sett();
  Chan2St_disp();
}

/*!*****************************************************************************
 @details	����� 2, ����������, ��������� � ����
 @note		
 */
void MnChan2Gnd_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM5RV), Chan2Ctrl.Gnd);
}
#endif

//__ ������� ��������� � ����, ����� ��� ���� ������� __//

#if 0
/*!*****************************************************************************
 @brief		Channel Ground Draw
 @details	���������� ���������� � ����
 @param		pDpy - ��������� � ������ ���������
 @param		Gnd - ����������
 @note	
 */
void DpyChanGnd_draw(uint8_t *pDpy) {
  static const uint8_t *GndTxt = "��������";
  DpyRoRect_fill(pDpy + 1, 55, 14, 0xFF << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 2, GndTxt, VON_TXT, 0);
}
#endif

/*!*****************************************************************************
 @brief		Channel Probe draw
 @details	���������� � ���� �������
 @param		*pDpy
 @param		Prb
 @note	
 */
void DpyChanPrb_draw(uint32_t Prb) {
  static const uint8_t *PrbTxt[4] = {"1/100", "\x98\x98""1/10", " 1/1", " 10x"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM2RV);
  DpyRect_fill(pDpy, 58, 14, 0xFF << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 8 * Prb, 33, 14, 0xFF<<8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 1 + 8 * Prb, PrbTxt[Prb], VON_TXT, 0);
}

/*!*****************************************************************************
 @brief		Channel Coupling Draw
 @details	���������� � ���� ����� � ������
 @param		pDpy - ��������� � ������ ���������
 @param		Cplg - ��� �����
 @note	
 */
void DpyChanCplg_draw(uint32_t Cplg) {
  static const uint8_t *CplgTxt[] = {"������", "\x98�����", " \x98����"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM4RV);
  DpyRect_fill(pDpy, 58, 14, 0xFF << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 6 * Cplg, 42, 14, 0xFF << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 1 + 6 * Cplg, CplgTxt[Cplg], VON_TXT, 0);
}


//* �������������� ��������� *//

/*!*****************************************************************************
 @details	����������, �����, ����������
 */
void MnMathMode_hand(void) {
  MathCtrl.On ^= 1;		// �������� ���������
  DpyWork_clear(MASK_MAT);
  MnMathMode_disp();
  Math_exe();
}

/*!*****************************************************************************
 @details	����������, �����, ���������
 */
void MnMathMode_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM1RV), MathCtrl.On);  
  MathSt_disp();			// ��������� ���������
}
 

/*!*****************************************************************************
 @details	����������, �������, ����������
 */
void MnMathFun_hand(void) {
  INC_MAX(MathCtrl.Fun, 2);		// ��������� ����� �������
  MnMathFun_disp();
  MnMathSour_disp();
  MnMathWind_disp();
  Math_exe();
}

/*!*****************************************************************************
 @details	����������, �������, ��������� � ����
 */
void MnMathFun_disp(void) {
  static const uint8_t *FunTxt[3] = {"�����", "\x98�����", "������"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 4, DPYM2RV);
  uint32_t fun = MathCtrl.Fun;  
  DpyRect_fill(pDpy, 56, 14, 0xFF << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 6 * fun, 40, 14, 0xFF << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 1 + 6 * fun, FunTxt[fun], VON_TXT, 0);
}

/*!*****************************************************************************
 @details	����������, ��������, ����������
 @note		���������� ��� ������� "������"
 */
void MnMathSour_hand(void)
{
  if (MathCtrl.Fun == MATH_FFT) {
    MathCtrl.Sour ^= 1;
    MnMathSour_disp();
    Math_exe();
  }
}

/*!*****************************************************************************
 @details	����������, ��������, ��������� � ����
 @note		������������ ��� ������� "������"
 */
void MnMathSour_disp(void) {
  uint8_t *pDpy = DPYPOS(DPYMHH + 6, DPYM3RV);
  DpyRect_fill(pDpy, 52, 14, 0xFF << 8 | VOFF_BKG);
  if (MathCtrl.Fun == 2) {
    static const uint8_t *SourTxt[2] = {"�����\x98""1", "�����\x98""2"};
    DpyRoRect_fill(pDpy, 48, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 320 * 3 + 4, SourTxt[MathCtrl.Sour], VON_TXT, 0);
  }
}

/*!*****************************************************************************
 @details	����������, ���� ���, ����������
 */
void MnMathWind_hand(void)
{
  if (MathCtrl.Fun == MATH_FFT) {
    INC_MAX(MathCtrl.Wind, 4);
    MnMathWind_disp();
    Math_exe();
  }
}

/*!*****************************************************************************
 @details	����������, ���� ���, ��������� � ����
 */
void MnMathWind_disp(void)
{
  uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM4RV);
  DpyRect_fill(pDpy, 58, 14, 0xFF << 8 | VOFF_BKG);
  if (MathCtrl.Fun == 2) {
    static const uint8_t *WindTxt[] = 
      {"�������", "�������", "�������", "��������", "��. ����"};
    DpyRoRect_fill(pDpy, 56, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 320 * 3 + 4, WindTxt[MathCtrl.Wind], VON_TXT, 0);
  }
}

/*!*****************************************************************************
 @details	����������, ��������, ����������
 */
void MnMathOffs_hand(void) { }

/*!*****************************************************************************
 @details	����������, ��������, ��������� � ����
 */
void MnMathOffs_disp(void) { }


//* ��������� *//

/*!*****************************************************************************
 @details	���������, �����, ����������
 @note		
 */
void MnSweepMode_hand(void) {
  uint32_t temp = SweepCtrl.Mode;
  temp++;
  if (temp > 2) temp = 0;
  SweepCtrl.Mode = temp;
  MnSweepMode_disp();
  SweepMode_sett();
  SweepSt_disp();
  if (temp == 2) SweepCtrl.Stop = 1;
  else {
    SweepCtrl.Stop = 0;
    PL->STAT = PL_START_ACQUST; }
  StSp_disp();
}

/*!*****************************************************************************
 @details	���������, �����, ��������� � ����
 @note		
 */
void MnSweepMode_disp(void) {
  static const uint8_t *ModeTxt[3] = {" ����", "\x98\x98����", "������"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 1, DPYM1RV);
  uint32_t mode = SweepCtrl.Mode;
  DpyRect_fill(pDpy, 58, 14, 0xFF << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 9 * mode, 40, 14, 0xFF << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 1 + 9 * mode, ModeTxt[mode], VON_TXT, 0);  
}

/*!
 *******************************************************************************
 * @details	���������, ���������, ����������
 * @note	
 */
void MnSweepRoll_hand(void) {
  SweepCtrl.Roll ^= 1;
  MnSweepRoll_disp();
  SweepRoll_sett();
  SweepSt_disp();
  Sweep_init();
  DpyWork_clear(MASK_MATSIG);
}

/*!*****************************************************************************
 @details	���������, ���������, ��������� � ����
 @note	
 */
void MnSweepRoll_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM2RV), SweepCtrl.Roll);
}

/*!*****************************************************************************
 @details	���������, ����������, ����������
 @note	
 */
void MnSweepPret_hand(void) {
// ������ ������� ����� ���������
  if (SetNum != SET_PRET) SetNum = SET_PRET;
  else	SetNum = SET_VOID;
  MnSweepPret_disp();
}

/*!*****************************************************************************
 @details	���������, ����������, ��������� � ����
 @note	
 */
void MnSweepPret_disp(void) {
  bool OffOn = false;			// ��� ���������
  if (SetNum == SET_PRET)  OffOn = true;
  DpySetting_draw(DPYPOS(DPYMHH + 2, DPYM3RV), OffOn);
}

/*!*****************************************************************************
 @details	���������, X-Y, ����������
 @note	
 */
void MnSweepXY_hand(void) {
  SweepCtrl.XY ^= 1;
  MnSweepXY_disp();
// �������� ���� � ����������� X(Ch1)-Y(Ch2)
}

/*!*****************************************************************************
 @details	���������, X-Y, ��������� � ����
 @note	
 */
void MnSweepXY_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM5RV), SweepCtrl.XY);
}

//* ������������� *//

/*!*****************************************************************************
 @details	�������������, ��������, ����������
 @note	
 */
void MnTrigSour_hand(void) {
  uint32_t sour = TrigCtrl.Sour;
  sour++;  if (sour > 3) sour = 0;
  TrigCtrl.Sour = sour;
  MnTrigSour_disp();
  TrigSour_sett();
  TrigSt_disp();
}

/*!*****************************************************************************
 @details	�������������, ��������, ��������� � ����
 @note	
 */
void MnTrigSour_disp(void) {
  static const uint8_t *SrcTxt[4] = {"����", "���1", "���2", "����"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 1, DPYM1RV);
  uint32_t sour = TrigCtrl.Sour;
  DpyRect_fill(pDpy, 58, 14, 0xff << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 10 * sour, 28, 14, 0xff << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 1 + 10 * sour, SrcTxt[sour], VON_TXT, 0);    
}

/*!*****************************************************************************
 @details	�������������, �������, ����������
 @note	
 */
void MnTrigSlp_hand(void) {
  TrigCtrl.Rise ^= 1;
  MnTrigSlp_disp();
  TrigSlp_sett();
  TrigSt_disp();
}

/*!*****************************************************************************
 @details	�������������, �������, ��������� � ����
 @note	
 */
void MnTrigSlp_disp(void) {
  uint8_t *pDpy = DPYPOS(DPYMHH + 1, DPYM2RV);
  DpyRect_fill(pDpy, 58, 14, 0xff << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 1 + 28 * TrigCtrl.Rise, 28, 14, 0xff << 8 | VON_BKG);  
  if (!TrigCtrl.Rise) {
    DpySpec_draw(pDpy + 320 * 3 + 10, SS_FALL, 0xff, VON_TXT);
    DpySpec_draw(pDpy + 320 * 3 + 40, SS_RISE, 0xff, VOFF_TXT);
  }
  else {
    DpySpec_draw(pDpy + 320 * 3 + 10, SS_FALL, 0xff, VOFF_TXT);
    DpySpec_draw(pDpy + 320 * 3 + 40, SS_RISE, 0xff, VON_TXT);
  }
}

/*!*****************************************************************************
 @details	�������������, �����, ����������
 @note	
 */
void MnTrigCplg_hand(void) {
  uint32_t cplg = TrigCtrl.Cplg;
  cplg++;  if (cplg > 3) cplg = 0;
  TrigCtrl.Cplg = cplg;
  MnTrigCplg_disp();
  TrigCplg_sett();
  TrigSt_disp();
}

/*!*****************************************************************************
 @details	�������������, �����, ��������� � ����
 @note	
 */
void MnTrigCplg_disp(void) {
  static const uint8_t *CplgTxt[4] = {
    " \x98\x98��", "\x98\x98����", "�����", " \x98\x98��"
  };
  uint8_t *pDpy = DPYPOS(DPYMHH + 1, DPYM4RV);
  uint32_t cplg = TrigCtrl.Cplg;
  DpyRect_fill(pDpy, 58, 14, 0xff << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 8 * cplg, 34, 14, 0xff << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 1 + 8 * cplg, CplgTxt[cplg], VON_TXT, 0);    
}

/*!*****************************************************************************
 @details	�������������, ��������������, ����������
 @note	
 */
void MnTrigNRej_hand(void) {
  TrigCtrl.NRej ^= 1;
  MnTrigNRej_disp();
  TrigNRej_sett();
}

/*!*****************************************************************************
 @details	�������������, ��������������, ��������� � ����
 @note	
 */
void MnTrigNRej_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM5RV), TrigCtrl.NRej);
}

//* ������� *//

/*!*****************************************************************************
 @details	�������, ������, ����������
 @note	
 */
void MnDispHelp_hand(void) {
  DispCtrl.HelpEna ^= 1;
  MnDispHelp_disp();
}

/*!*****************************************************************************
 @details	�������, ������, ��������� � ����
 @note	
 */
void MnDispHelp_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM1RV), DispCtrl.HelpEna);
}

/*!*****************************************************************************
 @details	�������, ����� �����/�������, ����������
 @note	
 */
void MnDispVect_hand(void) {
  SigChan1_draw(0);
  SigChan2_draw(0);
  DispCtrl.Vect ^= 1;
  MnDispVect_disp();
//  SigChan1_draw(3);
//  SigChan2_draw(3);
  SigChans_redraw();
}

/*!*****************************************************************************
 @details	�������, ����� �����/�������, ��������� � ����
 @note	
 */
void MnDispVect_disp(void) {
  static const uint8_t *VectTxt[2] = {" �����", "�������"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 1, DPYM2RV);
  DpyRect_fill(pDpy, 58, 14, 0xff << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 12 * DispCtrl.Vect, 46, 14, 0xff << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 12 * DispCtrl.Vect + 1, 
	VectTxt[DispCtrl.Vect], VON_TXT, 0);
}

/*!*****************************************************************************
 @details	�������, �����, ����������
 @note	
 */
void MnDispScale_hand(void) {
  INC_MAX(DispCtrl.Scale, 3);
  MnDispScale_disp();
  DpyScale_draw();  
}

/*!*****************************************************************************
 @details	�������, �����, ��������� � ����
 @note		0-Frame, 1-Cross(+Frame), 2-Grid(+Frame), 3-Cross+Grid(+Frame)
 */
void MnDispScale_disp(void) {
  static const uint8_t *ScaleText[4] = {"�����", "�����", "�����", " ���"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM3RV);
  DpyRect_fill(pDpy, 58, 14, 0xFF << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 8 * DispCtrl.Scale, 33, 14, 0xFF << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 1 + 8 * DispCtrl.Scale, 
		ScaleText[DispCtrl.Scale], VON_TXT, 0);
}

/*!*****************************************************************************
 @details	�������, ��������, ����������
 @note
 */
void MnDispClear_hand(void) {
  DpyWork_clear(MASK_MATSIG);
}

/*!*****************************************************************************
 @details	�������, ��������, ���������
 @note
 */
void MnDispClear_disp(void) { }


//* ���� ���������� *//

/*!*****************************************************************************
 @details	������ (�������� ����������), ����������
 @note	
 */
void MnAcquFilt_hand(void) {
  INC_MAX(AcquCtrl.Filt, 3);
  MnAcquFilt_disp();
  AcquFilt_sett();
}

/*!*****************************************************************************
 @details	������ (�������� ����������), ���������
 @note	
 */
void MnAcquFilt_disp(void) {
  static const uint8_t *FiltText[4] = {
	"����",
	"2\x98\x98���",
	"4\x98\x98���",
	"8\x98\x98���"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM1RV);
  DpyRect_fill(pDpy, 58, 14, 0xFF << 8 | VOFF_BKG);
  DpyRoRect_fill(pDpy + 8 * AcquCtrl.Filt, 33, 14, 0xFF << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 1 + 8 * AcquCtrl.Filt,
		FiltText[AcquCtrl.Filt], VON_TXT, 0);
}

/*!*****************************************************************************
 @details	������� ��������, ����������
 @note	
 */
void MnAcquPeak_hand(void) {
  AcquCtrl.Peak ^= 1;
  MnAcquPeak_disp();
  AcquPeak_sett();
}

/*!*****************************************************************************
 @details	������� ��������, ���������
 @note	
 */
void MnAcquPeak_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM2RV), AcquCtrl.Peak);
}

/*!*****************************************************************************
 @details	����������, ����������
 @note	
 */
void MnAcquAver_hand(void) {
// ������ ������� ����� ���������
  if (SetNum != SET_AVER) SetNum = SET_AVER;
  else			  SetNum = SET_VOID;
  MnAcquAver_disp();
}

/*!*****************************************************************************
 @details	����������, ��������� � ���� (������, ����� ���� ���� ��������)
 @note	
 */
void MnAcquAver_disp(void) {
  if (MenuNum == MENU_ACQU && GenCtrl.Menu) {
    uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM3RV);  
    bool On = false;			// ��� ���������
    if (SetNum == SET_AVER) On = true;
    DpyRotor_draw(pDpy, On);

    static const uint8_t *AverTxt[13] = {
      "1/1", "1/2", "1/4", "1/8", "1/16",
      "1/32", "1/64", "1/128", "1/256",
      "1/512", "1/1024", "1/2048", "1/4096"
    };

    // DpyRect_fill(pDpy, 58, 14, 0xff<<8|VOFF_BKG);
    DpyRoRect_fill(pDpy + 17, 40, 14, 0xff<<8 | VON_BKG);
    DpyString_draw(pDpy + 18 + 320 * 3, AverTxt[AcquCtrl.Aver >> 2], VON_TXT, 0);
  }
}

/*!*****************************************************************************
 @details	���������� (�������������), ����������
 @note	
 */
void MnAcquPers_hand(void)
{
  AcquCtrl.Pers ^= 1;
  MnAcquPers_disp();
}

/*!*****************************************************************************
 @details	���������� (�������������), ���������
 @note	
 */
void MnAcquPers_disp(void)
{
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM4RV), AcquCtrl.Pers);
}


//* ������� *//

/*!*****************************************************************************
 @details	
 @note		
 */
void MnCursMode_hand(void) {
  SET_t static SetCurs = SET_VOID;	// ����� ������� ��������� ��������
  CursCtrl.On ^= 1;
  MnCursMode_disp();		// ������������ � ����
  if (!CursCtrl.On) {
    SetCurs = SetNum;		// ��������� ����� ������� ��������� ��������
    SetNum = SET_VOID;		// ������ ������� ���������
  }
  else {
    MeasCtrl.On = 0;
    SetNum = SetCurs;		// ������������ ����� ������� ��������� ��������
  }  
  MnCursSel1_disp();
  MnCursSel2_disp();
  MnCursSelTr_disp();
  
  Curs_draw(CursCtrl.On);	// ���������� �� ������
  CursMeasSt_disp();		// ������������ � �������
  SetCursSt_disp();		// ��������/������� ��������� ���������
}

/*!*****************************************************************************
 @details	
 @note		
 */
void MnCursMode_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM1RV), CursCtrl.On);
}

/*!*****************************************************************************
 @details	
 @note		
 */
void MnCursPara_hand(void) {
  CursCtrl.xY ^= 1;
  MnCursPara_disp();
  CursMeasSt_disp();		// ������������ � �������
  SetCursSt_disp();		// ��������/������� ��������� ���������  
}

/*!*****************************************************************************
 @details	
 @note		
 */
void MnCursPara_disp(void) {
  static const uint8_t *MeasTxt[] = {"\x98\x98"S_DELT"X", "\x98\x98"S_DELT"Y"};
  uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM2RV);
  if (!CursCtrl.xY) {
    DpyRoRect_fill(pDpy, 28, 14, 0xff << 8 | VON_BKG);
    DpyString_draw(pDpy + 320 * 3 + 1, MeasTxt[0], VON_TXT, 0);
    DpyRect_fill(pDpy + 28, 28, 14, 0xff<<8 | VOFF_BKG);
    DpyString_draw(pDpy + 320 * 3 + 31, MeasTxt[1], VOFF_TXT, 0);
  }
  else {
    DpyRect_fill(pDpy, 28, 14, 0xff<<8 | VOFF_BKG);
    DpyString_draw(pDpy + 320 * 3 + 1, MeasTxt[0], VOFF_TXT, 0);
    DpyRoRect_fill(pDpy + 28, 28, 14, 0xff << 8 | VON_BKG);
    DpyString_draw(pDpy + 320 * 3 + 31, MeasTxt[1], VON_TXT, 0);
  }
}

/*!*****************************************************************************
 @details	������� ������ ������
 @note		
 */
void MnCursSel1_hand(void) {
  SetNum = SET_CURS1;
  MnCursSel1_disp();
  MnCursSel2_disp();
  MnCursSelTr_disp();
}

/*!*****************************************************************************
 @details	
 @note		
 */
void MnCursSel1_disp(void) {
  bool On = false;			// ��� ���������
  if (SetNum == SET_CURS1) On = true;
  DpySetting_draw(DPYPOS(DPYMHH + 2, DPYM3RV), On);  
}

/*!*****************************************************************************
 @details	������� ������ ������
 @note		
 */
void MnCursSel2_hand(void) {
  SetNum = SET_CURS2;
  MnCursSel1_disp();
  MnCursSel2_disp();
  MnCursSelTr_disp();
}

/*!*****************************************************************************
 @details	
 @note		
 */
void MnCursSel2_disp(void) {
  bool On = false;
  if (SetNum == SET_CURS2) On = true;
  DpySetting_draw(DPYPOS(DPYMHH + 2, DPYM4RV), On);
}

/*!*****************************************************************************
 @details	������� ��� ������� (��������)
 @note		
 */
void MnCursSelTr_hand(void) {
  SetNum = SET_CURSTR;
  MnCursSel1_disp();
  MnCursSel2_disp();
  MnCursSelTr_disp();
}

/*!*****************************************************************************
 @details	
 @note		
 */
void MnCursSelTr_disp(void) {
  bool On = false;
  if (SetNum == SET_CURSTR) On = true;
  DpySetting_draw(DPYPOS(DPYMHH + 2, DPYM5RV), On);
}

/*!*****************************************************************************
 @details	
 @note		
 */
void CursMeasSt_disp(void) {
  if (MeasCtrl.On) return;
  if (!CursCtrl.On) 
    DPY_RECT(DPYPARH, DPYPAR1V,
	     319,     DPYPAR2V + 9, 0xFF, BLANK);
  else {
    if (!CursCtrl.xY) {
      DpyStringPad_draw(DPYPOS(DPYPARH, DPYPAR1V),
			"  " S_DELT "X=", 0x80800000, true);
      DpyStringPad_draw(DPYPOS(DPYPARH, DPYPAR2V),
			"1/" S_DELT "X=", 0x80800000, true);
    }
    else {
      if (!Chan1Ctrl.On)
        DPY_RECT(DPYPARH, DPYPAR1V,
		 319,     DPYPAR1V + 9, 0xFF, BLANK);
      else
        DpyStringPad_draw(DPYPOS(DPYPARH, DPYPAR1V),
			" 1" S_DELT "Y=", 0x80800000, true);
      if (!Chan2Ctrl.On)
        DPY_RECT(DPYPARH, DPYPAR2V,
		 319,     DPYPAR2V + 9, 0xFF, BLANK);
      else DpyStringPad_draw(DPYPOS(DPYPARH, DPYPAR2V),
			" 2" S_DELT "Y=", 0x80800000, true);
    }			
  }  
}


//* ��������� *//

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMeasMode_hand(void) {
  MeasCtrl.On ^= 1;
  if (MeasCtrl.On) {
// ��������� � �������� �������
    CursCtrl.On = 0;
    Curs_draw(0);
// ������� ������� ���������� ��������� �� ��������
    if (SetNum == SET_CURS1
     || SetNum == SET_CURS2
     || SetNum == SET_CURSTR)
      SetNum = SET_VOID;
  }
  MnMeasMode_disp();
  SigPar_meas();  
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMeasMode_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM1RV), MeasCtrl.On);
  MeasPar1St_disp();
  MeasPar2St_disp();
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMeasSour_hand(void) {
  MeasCtrl.Sour ^= 1;
  MnMeasSour_disp();
  SigPar_meas();
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMeasSour_disp(void) {
  static const uint8_t *SourTxt[] = {"���1", "���2"};
  uint8_t *pDpy = DPYPOS(DPYMHH, DPYM2RV);
  DpyRect_fill(pDpy, 60, 14, 0xFF << 8 | VOFF_BKG);
  if (!MeasCtrl.Sour) {
    DpyRoRect_fill(pDpy + 2, 28, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 3 + 320 * 3, SourTxt[0], VON_TXT, false);
    DpyString_draw(pDpy + 3 + 56 - 28 + 320 * 3, SourTxt[1], VOFF_TXT, false);
  }
  else {
    DpyString_draw(pDpy + 3 + 320 * 3, SourTxt[0], VOFF_TXT, false);
    DpyRoRect_fill(pDpy + 2 + 56 - 28, 28, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 3 + 56 - 28 + 320 * 3, SourTxt[1], VON_TXT, false);
  }
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMeasPar1_hand(void) {
// ������ ������� ����� ���������
  if (SetNum != SET_PAR1) SetNum = SET_PAR1;
  else			  SetNum = SET_VOID;
  MnMeasPar1_disp();
  MnMeasPar2_disp();
  SigPar_meas();
}

static const uint8_t *ParTxt[] = {
  "������", " ����.",
  "���� -", "���� +",
  "��.���", "��.���",
  "�����.", "�����.",
  "������", "�����."
};

static const uint8_t *ParStTxt[] = {
  "   T=", "   F=",
  "  T-=", "  T+=",
  "T���=", "T���=",
  "V���=", "V���=",
  "V���=", "V���="
};

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMeasPar1_disp(void) {
  if (MenuNum == MENU_MEAS && GenCtrl.Menu) {
    uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM3RV);  
    bool On = false;			// ��� ���������
    if (SetNum == SET_PAR1) On = true;
    DpyRotor_draw(pDpy, On);

    DpyRoRect_fill(pDpy + 16, 42, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 18 + 320 * 3, ParTxt[MeasCtrl.Par1 >> 2], VON_TXT, false);
  }
  MeasPar1St_disp();
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMeasPar2_hand(void) {
// ������ ������� ����� ���������
  if (SetNum != SET_PAR2) SetNum = SET_PAR2;
  else			  SetNum = SET_VOID;
  MnMeasPar1_disp();
  MnMeasPar2_disp();
  SigPar_meas();
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMeasPar2_disp(void) {
  if (MenuNum == MENU_MEAS && GenCtrl.Menu) {
    uint8_t *pDpy = DPYPOS(DPYMHH + 2, DPYM4RV);  
    bool On = false;			// ��� ���������
    if (SetNum == SET_PAR2) On = true;
    DpyRotor_draw(pDpy, On);

    DpyRoRect_fill(pDpy + 16, 42, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 18 + 320 * 3, ParTxt[MeasCtrl.Par2 >> 2], VON_TXT, false);
  }
  MeasPar2St_disp();
}


/*!*****************************************************************************
 @brief		Measurement Parameter 1 display in Status
 @details	
 @note		
 */
void MeasPar1St_disp(void) {
  if (CursCtrl.On) return;	// �� �������, ���� ���� �������
  if (!MeasCtrl.On) 
    DPY_RECT(DPYSAH + 200, DPYS1VV,
	     319,          DPYS1VV + 10, 0xFF, BLANK);
  else {
    DpyStringPad_draw(DPYPOS(DPYSAH + 200, DPYS1VV),
			ParStTxt[MeasCtrl.Par1 >> 2], 0xE2E20000, true); 
  }  
}

/*!*****************************************************************************
 @brief		Measurement Parameter 2 display in Status
 @details	
 @note		
 */
void MeasPar2St_disp(void) {
  if (CursCtrl.On) return;	// �� �������, ���� ���� �������
  if (!MeasCtrl.On) 
    DPY_RECT(DPYSAH + 200, DPYS2VV,
	     319,          DPYS2VV + 10, 0xFF, BLANK);
  else {
    DpyStringPad_draw(DPYPOS(DPYSAH + 200, DPYS2VV),
			ParStTxt[MeasCtrl.Par2 >> 2], 0xE2E20000, true); 
  }  
}

//* ������ *//

/*!*****************************************************************************
 @details	������, ������, ����������
 @note	
 */
void MnMemSize_hand(void) {
// �������� ������ ��������
  Sig_clear();

// �������� ����������� ����������, �������� */
  DpyWork_clear(MASK_CURSMATSIG);

  // Pret_draw(false);			// ������� ������ ��������� �����������
  MemBarPos_draw(false);		// ������� ������� �� ������ ������
  // if (Chan1Ctrl.On) SigChan1_draw(0);	// �������� ������ ����������� ������� 1
  // if (Chan2Ctrl.On) SigChan2_draw(0);	// �������� ������ ����������� ������� 2
  // if (CursCtrl.On) Curs_draw(false);	// ������� �������

// ��������� �������� �������, �������� ������ ������, �������� ������� 
  int32_t ofs = (SweepCtrl.Pret << MemCtrl.SizeNum + 5) - SweepCtrl.TimePos;
  // INC_MAX(MemCtrl.SizeNum, 5);
  // if (!MemCtrl.SizeNum) MemCtrl.SizeNum = 1;	// ���������� 0.5K
  INC_MAX(MemCtrl.SizeNum, 4);
  int32_t pos = (SweepCtrl.Pret << MemCtrl.SizeNum + 5) - ofs;

// ���������� ������� ��������� ������
  int32_t lmarg = 0;
  int32_t rmarg = (1024 << MemCtrl.SizeNum) - 300;
  if (pos < lmarg) pos = lmarg;
  if (pos > rmarg) pos = rmarg;
  SweepCtrl.TimePos = pos;

// ���������� �������
  if (CursCtrl.On) {
    SetCursTr_hand(0);
    Curs_draw(true);	// ���������� �������  
  }

// �������� ����� ������ �� ������ ����
  MemCtrl.BufNum = 0;
  
  // SigChans_redraw();		// ������������ ������
  
  MnMemSize_disp();
  MnMemNum_disp();
  MemSizeBuf_disp();		// �������� � ���������
  // Pret_draw(true);		// ���������� ����� ��������� �����������
  MemBarPos_draw(true);		// ���������� ������� �� ������ ������

  MemSize_sett();  
  SetPret_sett();		// ������ ���������� � ����
  // SetPret_hand(0);	// �������� (���������� � ����������) ��������� �����������
  // PL->STAT = PL_START_ACQUST;		// Start new frame
  Sweep_init();

}

  static const uint8_t *MemSizeTxt[] = {
    // "0.5K",
    " 1K ",
    " 2K ",
    " 4K ",
    " 8K ",
    "\x98\x98""16K"
  };

  static const uint8_t *MemNumTxt[] = {
    " 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8",
    " 9", "10", "11", "12", "13", "14", "15", "16",
    "17", "18", "19", "20", "21", "22", "23", "24",
    "25", "26", "27", "28", "29", "30", "31", "32"
  };
  
/*!*****************************************************************************
 @details	������, ������, ��������� � ����� ����
 @note	
 */
void MnMemSize_disp(void)
{
  uint8_t *pDpy = DPYPOS(DPYMHH, DPYM1RV);
  DpyRect_fill(pDpy, 60, 14, 0xFF << 8 | VOFF_BKG);  
  DpyRoRect_fill(pDpy + 3 * (5 - MemCtrl.SizeNum), 30 + 6 * MemCtrl.SizeNum,
      14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 18 + 320 * 3, MemSizeTxt[MemCtrl.SizeNum], VON_TXT, 0); 
}

/*!*****************************************************************************
 @details	������, ������, ��������� � ������ ���������
 @note	
 */
void MemSizeBuf_disp(void)
{
  uint8_t *pDpy = DPYPOS(DPYWAH + 200, 1);
  DpyStringPad_draw(pDpy, MemSizeTxt[MemCtrl.SizeNum], 0x0A0A0000, false);
  // DpyStringPad_draw(pDpy + 24, MemNumTxt[MemCtrl.BufNum], 0x1F1F0000, false);
}

/*!*****************************************************************************
 @brief		
 @details	
 @param		
 @return	
 @note		
 */
void MnMemNum_hand(void) {
  if (SetNum != SET_BUFNUM) SetNum = SET_BUFNUM;
  else			    SetNum = SET_VOID;
  MnMemNum_disp();  
}



/*!*****************************************************************************
 @brief		
 @details	
 @param		
 @return	
 @note		
 */
void MnMemNum_disp(void) {
  if (MenuNum == MENU_MEM && GenCtrl.Menu) {
    uint8_t *pDpy = DPYPOS(DPYMHH, DPYM2RV);
    bool On = false;
    if (SetNum == SET_BUFNUM) On = true;
    DpyRotor_draw(pDpy + 2, On);
    
    // DpyRect_fill(pDpy, 60, 14, 0xFF << 8 | VOFF_BKG);
    DpyRoRect_fill(pDpy + 36, 20, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 39 + 320 * 3, MemNumTxt[MemCtrl.BufNum], VON_TXT, 0);
  }
}
  


/*!*****************************************************************************
 @brief		
 @details	������� ������� ���������� ��� �������� �������
 @note		
 */
void MnMemSig_hand(void) {
  uint32_t num = MemItem;
  num++;
  if (num > SIG2LOAD) num = 0;
  MemItem = (MEMEXE_t)num;
  MnMemSig_disp();
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMemSig_disp(void) {
  static const uint8_t *MemFunTxt[] = {
    "����. 1", "����. 2", "����. 1", "����. 2"
  };
  uint8_t *pDpy = DPYPOS(DPYMHH, DPYM3RV);
  DpyRoRect_fill(pDpy + 4, 52, 14, 0xFF << 8 | VON_BKG);
  DpyString_draw(pDpy + 8 + 3 * 320, MemFunTxt[MemItem], VON_TXT, 0);
  
  pDpy = DPYPOS(DPYMHH, DPYM5RV);  
  DpyRect_fill(pDpy, 60, 14, 0xFF << 8 | VOFF_BKG);
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMemSet_hand(void) {

}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMemSet_disp(void) {

}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMemExe_hand(void) {
  uint8_t *pDpy = DPYPOS(DPYMHH, DPYM5RV);  
  DpyRect_fill(pDpy, 60, 14, 0xFF << 8 | VOFF_BKG);
  MemFun[MemItem]();
  DpyString_draw(pDpy + 2 + 3 * 320,
	"���������", VOFF_TXT, false);
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnMemExe_disp(void) {

}

/*!*****************************************************************************
 @brief		
 @details	��������� ���������� �������
 @note		
 */
void Sig1_save(void) {
  uint8_t *pSigCh1 = (uint8_t *)SigChan1.Buf16K;
  uint8_t *pSigCh2 = (uint8_t *)SigChan2.Buf16K;
  SweepCtrl.Stop = 1;
  SFMSect_erase(SFMSIG1);		// ������� ������ 64 ��
  for (uint32_t i = 128; i--; ) {	// 128 ������� �� 256 ������
    SFMPage_progr(pSigCh1 + 256 * i, SFMSIG1 + 256 * i, 256);
  }
  for (uint32_t i = 128; i--; ) {	// 128 ������� �� 256 ������
    SFMPage_progr(pSigCh2 + 256 * i, SFMSIG1 + 0x8000 + 256 * i, 256);  
  }
  SweepCtrl.Stop = 0;
}

/*!*****************************************************************************
 @brief		
 @details	��������� ���������� �������
 @note		
 */
void Sig2_save(void) {
  uint8_t *pSigCh1 = (uint8_t *)SigChan1.Buf16K;
  uint8_t *pSigCh2 = (uint8_t *)SigChan2.Buf16K;
  SweepCtrl.Stop = 1;
  SFMSect_erase(SFMSIG2);		// ������� ������ 64 ��
  for (uint32_t i = 128; i--; ) {	// 128 ������� �� 256 ������
    SFMPage_progr(pSigCh1 + 256 * i, SFMSIG2 + 256 * i, 256);
  }
  for (uint32_t i = 128; i--; ) {	// 128 ������� �� 256 ������
    SFMPage_progr(pSigCh2 + 256 * i, SFMSIG2 + 0x8000 + 256 * i, 256);  
  }
  SweepCtrl.Stop = 0;
}

/*!*****************************************************************************
 @brief		
 @details	��������� �������� �������
 @note		
 */
void Sig1_load(void) {
  uint8_t *pSigCh1 = (uint8_t *)SigChan1.Buf16K;
  uint8_t *pSigCh2 = (uint8_t *)SigChan2.Buf16K;
  SweepCtrl.Stop = 1;
  StSp_disp();
  SFMRead_start(SFMSIG1);
  for (uint32_t i = 1 << 15; i--; ) {	// ������ 32 ��
    *pSigCh1++ = SFMByte_read();
  }
  SFMRead_stop();
  SFMRead_start(SFMSIG1 + 0x8000);
  for (uint32_t i = 1 << 15; i--; ) {	// ������ 32 ��
    *pSigCh2++ = SFMByte_read();
  }
  SFMRead_stop();
  // DpyWork_clear(MASK_MATHSIG);
  SigChans_redraw();
  // Math_exe();
  SigPar_meas();			// ��������� (���� ����)
}

/*!*****************************************************************************
 @brief		
 @details	��������� �������� �������
 @note		
 */
void Sig2_load(void) {
  uint8_t *pSigCh1 = (uint8_t *)SigChan1.Buf16K;
  uint8_t *pSigCh2 = (uint8_t *)SigChan2.Buf16K;
  SweepCtrl.Stop = 1;
  StSp_disp();
  SFMRead_start(SFMSIG2);
  for (uint32_t i = 1 << 15; i--; ) {	// ������ 32 ��
    *pSigCh1++ = SFMByte_read();
  }
  SFMRead_stop();
  SFMRead_start(SFMSIG2 + 0x8000);
  for (uint32_t i = 1 << 15; i--; ) {	// ������ 32 ��
    *pSigCh2++ = SFMByte_read();
  }
  SFMRead_stop();
  // DpyWork_clear(MASK_MATHSIG);
  SigChans_redraw();
  // Math_exe();
  SigPar_meas();			// ��������� (���� ����)
}



//* ������� *//

/*!*****************************************************************************
 @brief		
 @details	���������� �������� / ��������� (���������� ����������)
 @note		��� 0 � ����� ��� ������ ���������� �������� ����������
 */
void MnUtilCal_hand(void) {
  GenCtrl.FPCal ^= 1;
  if (GenCtrl.FPCal) PanCtrl.TxBuf |=  0x01;
  else		     PanCtrl.TxBuf &= ~0x01;
  PanCtrl.TxBuf |= 0x40;
  USART3->DR = PanCtrl.TxBuf;
  MnUtilCal_disp();
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnUtilCal_disp(void) {
  DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM1RV), GenCtrl.FPCal);
}

/*!*****************************************************************************
 @brief		Balance
 @details	
 @note		�� ���������� 2mV...20mV �������� DC, AC.
		���������� �������� �� 2mV, � �� ���� ���������.
		�������� ����������, ������ �� ����������.
		�������� ������ ������� � 2 ����, ������� ����������� ��������
		������� �� �������� �� ���������� ����������
 \attention	��������� GenCtrl.Bal ��� ������
 */
void MnUtilBal_hand(void) {
#define WGT 64		// average weight
#define DTM 8		// dead time

  MnUtilBal_disp();
///  osMutexRelease(MutDpy_id);
///  osSignalSet(Main_id, 1);  		// ������ �� ���������
  
// ��������� ������, ���� �� �������  
  if (!GenCtrl.Bal) {
// �������� ������, ���� ��� ���
    GenCtrl.Bal = true;
// �������� ��� ������
    Chan1Ctrl.On = true;
    Chan2Ctrl.On = true;
    Chan1Mode_sett();
    Chan2Mode_sett();
    
// ������ ����������� ������
    Chan1Ctrl.BWLim = 1;
    Chan2Ctrl.BWLim = 1;
    Chan1BWLim_sett();
    Chan2BWLim_sett();
    
/* ���������� ������� � �������� ������ */    
    PosChan1_draw(false);
    PosChan2_draw(false);
    Chan1Ctrl.SigPos = 512;
    Chan2Ctrl.SigPos = 512;
    Chan1Ctrl.DispPos = 0;
    Chan2Ctrl.DispPos = 0;
    ANADAC(DAC_CHAN1, Chan1Ctrl.SigPos << 2);
    ANADAC(DAC_CHAN2, Chan2Ctrl.SigPos << 2);
    PosChan1_draw(true);
    PosChan2_draw(true);

// ������ ������    
    AcquCtrl.Filt = 3;
    AcquFilt_sett();

// ���������� ��������� �� ������    
    SweepCtrl.TimeNum = TIME_DOT;
    Time_sett();
    
// ���������� ������ ���������� �� ���� ������ �� ������
    PL_AcquBuf &= ~(PL_ACQU_TDTIE | PL_ACQU_FRMIE | PL_ACQU_DOTIE);
    PL_AcquBuf |= PL_ACQU_DOTIE;
    PL->ACQU = PL_AcquBuf;
    SweepCtrl.Stop = 0;

/* 1. ������ 2mV, GND */
    Chan1Ctrl.VoltNum = VOLT_END;	// ������ 2mV
    Chan2Ctrl.VoltNum = VOLT_END;
    Chan1Ctrl.Cplg = 0;			// ������ ����������
    Chan2Ctrl.Cplg = 0;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
    
// ����� ����� ������� 
    PL->STAT = PL_START_ACQUST;

/* �������������� ��������� ����� */
    uint32_t ofs1 = 0, ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
    
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs2GND = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs2GND = 256 - ofs2 / (WGT / 2);

/* 2. ������ 2mV, AC */
    Chan1Ctrl.VoltNum = VOLT_END;	// ������ 2mV
    Chan2Ctrl.VoltNum = VOLT_END;
    Chan1Ctrl.Cplg = 1;			// ������ ����� �� ����������� ����
    Chan2Ctrl.Cplg = 1;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
    
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
    
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs2AC = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs2AC = 256 - ofs2 / (WGT / 2);
    // Num_draw(Bal1Ctrl.Ofs2AC);
    
/* 3. ������ 2mV, DC */
    Chan1Ctrl.Cplg = 2;			// ������ ����� �� ����������� ����
    Chan2Ctrl.Cplg = 2;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
  
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
    
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs2DC = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs2DC = 256 - ofs2 / (WGT / 2);
    
/* 4. ������ 5mV, GND */
    Chan1Ctrl.VoltNum = VOLT_END - 1;	// ������ 5mV
    Chan2Ctrl.VoltNum = VOLT_END - 1;
    Chan1Ctrl.Cplg = 0;			// ������ ����������
    Chan2Ctrl.Cplg = 0;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
  
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }

    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs5GND = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs5GND = 256 - ofs2 / (WGT / 2);

/* 5. ������ 5mV, AC */
    Chan1Ctrl.VoltNum = VOLT_END - 1;	// ������ 5mV
    Chan2Ctrl.VoltNum = VOLT_END - 1;
    Chan1Ctrl.Cplg = 1;			// ������ ����� �� ����������� ����
    Chan2Ctrl.Cplg = 1;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
    
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
    
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs5AC = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs5AC = 256 - ofs2 / (WGT / 2);
    
/* 6. ������ 5mV, DC */
    Chan1Ctrl.Cplg = 2;			// ������ ����� �� ����������� ����
    Chan2Ctrl.Cplg = 2;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
  
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
    
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs5DC = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs5DC = 256 - ofs2 / (WGT / 2);

/* 7. ������ 10mV, AC */
    Chan1Ctrl.VoltNum = VOLT_END - 2;	// ������ 10mV
    Chan2Ctrl.VoltNum = VOLT_END - 2;
    Chan1Ctrl.Cplg = 1;			// ������ ����� �� ����������� ����
    Chan2Ctrl.Cplg = 1;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();

  
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
    
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs10AC = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs10AC = 256 - ofs2 / (WGT / 2);

/* 8. ������ 10mV, DC */
    Chan1Ctrl.Cplg = 2;			// ������ ����� �� ����������� ����
    Chan2Ctrl.Cplg = 2;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
  
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
   
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs10DC = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs10DC = 256 - ofs2 / (WGT / 2);

/* 9. ������ 20mV, AC */
    Chan1Ctrl.VoltNum = VOLT_END - 3;	// ������ 20mV
    Chan2Ctrl.VoltNum = VOLT_END - 3;
    Chan1Ctrl.Cplg = 1;			// ������ ����� �� ����������� ����
    Chan2Ctrl.Cplg = 1;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
  
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
    
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs20AC = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs20AC = 256 - ofs2 / (WGT / 2);
    
/* 10. ������ 20mV, DC */
    Chan1Ctrl.Cplg = 2;			// ������ ����� �� ����������� ����
    Chan2Ctrl.Cplg = 2;    
    Chan1Cplg_sett();			// ���������� V/div � �����
    Chan2Cplg_sett();
  
/* �������������� ��������� ����� */
    ofs1 = 0;
    ofs2 = 0;
    for (uint32_t i = DTM; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
    }
    
    for (uint32_t i = WGT; i--; ) {
      while (PLIRQ_GET()) { };		// �����, ���� ��� ������� �� �����
      uint_fast16_t stat = PL->STAT;	// ������ � �������� ���������
      uint32_t rint = PL->RINT;
      ofs1 += (uint8_t)rint;
      ofs2 += (uint8_t)(rint >> 8);
    }

/* ��������� � ��������� �������� */
    // Num_draw(ofs1 / WGT);
    Bal1Ctrl.Ofs20DC = 256 - ofs1 / (WGT / 2);
    Bal2Ctrl.Ofs20DC = 256 - ofs2 / (WGT / 2);

/* X. ��������� �� flash */
    SFMPage_write((uint8_t *)&Bal1Ctrl.Ofs20DC, SFMBAL1, 10);
    SFMPage_write((uint8_t *)&Bal2Ctrl.Ofs20DC, SFMBAL2, 10);    

/* ������ ����� ������������ */
    GenCtrl.Bal = false;

/* ����� ������� */
    Signature = 0x00000000;	// ������� ��������� � Backup RAM
    NVIC_SystemReset(); 
  }
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnUtilBal_disp(void) {
  // DpyOffOn_draw(DPYPOS(DPYMHH + 2, DPYM2RV), GenCtrl.Bal);
  DpyString_draw(DPYPOS(DPYMHH + 2, DPYM2RV), "���.(1���)", VOFF_TXT, false);
}


/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnUtilVers_hand(void) {

}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void MnUtilVers_disp(void) {
  uint8_t *pDpy = DPYPOS(DPYMHH + 20, DPYM4RV);
  DpyRoRect_fill(pDpy, 24, 14, 0xFF << 8 | VON_BKG);
  DpyString_draw(pDpy + 320 * 3 + 4, VERSION, VON_TXT, false);
}

/*!*****************************************************************************
 \brief		Menu Utilities Reset
 */
void MnUtilReset_hand(void) {
  Signature = 0x00000000;	// ������� ��������� � Backup RAM
  NVIC_SystemReset();
}

void MnUtilReset_disp(void) {
  uint8_t *pDpy = DPYPOS(DPYMHH + 4, DPYM5RV + 3);
  DpyString_draw(pDpy, "��������", ITEM_TXT, false);
}


/* ########################################################################### */

//__ ����������� ����� ���������, ���������� ����� ��������� __________________//


/*!*****************************************************************************
 @details	������ ������� ����� ���������, ����������
 @note	
 */
void SetVoid_hand(int32_t Cnt) { }

/*!*****************************************************************************
 @details	���������� ����������, ����������
 @note		���������� ���������� �������� �� 32 ��� ����� 1K �������
		��� ������� ������ ������ ����������, ����� ���� 32-2 �������  
 */
void SetPret_hand(int32_t Cnt) {
  Pret_draw(false);
  MemBarPret_draw(false);
  int16_t pret = (int16_t)SweepCtrl.Pret;
//  int32_t offs = pret - SweepCtrl.TimePos;	// �������� �������
  // pret += Cnt << 4;
  pret += Cnt;
  int16_t lmarg = 1;		// ����� ������ 1/32 ������
  int16_t rmarg = 31;		// ������ ������ 31/31 ������

  if (pret < lmarg) pret = lmarg;
  if (pret > rmarg) pret = rmarg;
  SweepCtrl.Pret = pret;
//  SweepCtrl.TimePos = (pret << MemCtrl.SizeNum) - offs;	// ����� �������
  Pret_draw(true);
  MemBarPret_draw(true);
  SetPret_sett();
  // Sweep_init();
}

/*!*****************************************************************************
 @details	���������� ������������, ����������
 @note	
 */
void SetHold_hand(int32_t Cnt) { }


/*!*****************************************************************************
 @details	���������� ����������, ����������
 @note	
 */
void SetAver_hand(int32_t Cnt) {
  int32_t aver = (int32_t)AcquCtrl.Aver;
  aver += Cnt;				// ��� ��������!
  if (aver < 0) aver = 0;
  if (aver > 12 << 2) aver = 12 << 2;
  AcquCtrl.Aver = aver;
  MnAcquAver_disp();			// �������� �-� ���������� � ����
}

/*!*****************************************************************************
 @brief		
 @details	���������� ������ 1
 @note		�� ������� �������������� �������, �� ���������� - �������
 */
void SetCurs1_hand(int32_t Cnt) {
/* ������� ������ ������ */
  Curs_draw(false);
/* ������ �� X */
  if (!CursCtrl.xY) {		// x
    int32_t curs = CursCtrl.CX1;
    curs += Cnt;
    if (curs < 0) curs = 0;
    if (curs > (1024 << MemCtrl.SizeNum) - (DispCtrl.Wide ? 0 : 50))
      curs = (1024 << MemCtrl.SizeNum) - (DispCtrl.Wide ? 1 : 51);
    CursCtrl.CX1 = curs;
/* �������� ����������� ��������, ���� ����� */
    if (curs < SweepCtrl.TimePos) {
      Pret_draw(false);
      MemBarPos_draw(false);
      if (Chan1Ctrl.On) SigChan1_draw(0);
      if (Chan2Ctrl.On) SigChan2_draw(0);
      SweepCtrl.TimePos = curs;
      if (Chan1Ctrl.On) SigChan1_draw(3);
      if (Chan2Ctrl.On) SigChan2_draw(3);
      Pret_draw(true);
      MemBarPos_draw(true);
    }
    if (curs > SweepCtrl.TimePos + (DispCtrl.Wide ? 300 : 250)) {
      Pret_draw(false);
      MemBarPos_draw(false);
      if (Chan1Ctrl.On) SigChan1_draw(0);
      if (Chan2Ctrl.On) SigChan2_draw(0);
      SweepCtrl.TimePos = curs - (DispCtrl.Wide ? 300 : 250);
      if (Chan1Ctrl.On) SigChan1_draw(3);
      if (Chan2Ctrl.On) SigChan2_draw(3);
      Pret_draw(true);
      MemBarPos_draw(true);
    }
  }
/* ������ �� Y */
  else {
    int32_t curs = CursCtrl.CY1;
    curs += Cnt;
    if (curs < 28) curs = 28;
    if (curs > 228) curs = 228;
    CursCtrl.CY1 = curs;
  }
/* ���������� ����� ������ */
  Curs_draw(true);
  SetCursSt_disp();
}

/*!*****************************************************************************
 @brief		
 @details	���������� ������ 2
 @note		�� ������� �������������� �������, �� ���������� - �������
 */
void SetCurs2_hand(int32_t Cnt) {
/* ������� ������ ������ */
  Curs_draw(false);
/* ������ �� X */
  if (!CursCtrl.xY) {		// x
    int32_t curs = CursCtrl.CX2;
    curs += Cnt;
    if (curs < 0) curs = 0;
    if (curs > (1024 << MemCtrl.SizeNum) - (DispCtrl.Wide ? 0 : 50))
      curs = (1024 << MemCtrl.SizeNum) - (DispCtrl.Wide ? 1 : 51);
    CursCtrl.CX2 = curs;
/* �������� ����������� ��������, ���� ����� */
    if (curs < SweepCtrl.TimePos) {
      Pret_draw(false);
      MemBarPos_draw(false);
      if (Chan1Ctrl.On) SigChan1_draw(0);
      if (Chan2Ctrl.On) SigChan2_draw(0);
      SweepCtrl.TimePos = curs;
      if (Chan1Ctrl.On) SigChan1_draw(3);
      if (Chan2Ctrl.On) SigChan2_draw(3);
      Pret_draw(true);
      MemBarPos_draw(true);
    }
    if (curs > SweepCtrl.TimePos + (DispCtrl.Wide ? 300 : 250)) {
      Pret_draw(false);
      MemBarPos_draw(false);
      if (Chan1Ctrl.On) SigChan1_draw(0);
      if (Chan2Ctrl.On) SigChan2_draw(0);
      SweepCtrl.TimePos = curs - (DispCtrl.Wide ? 300 : 250);
      if (Chan1Ctrl.On) SigChan1_draw(3);
      if (Chan2Ctrl.On) SigChan2_draw(3);
      Pret_draw(true);
      MemBarPos_draw(true);
    }
  }
/* ������ �� Y */
  else {
    int32_t curs = CursCtrl.CY2;
    curs += Cnt;
    if (curs < 28) curs = 28;
    if (curs > 228) curs = 228;
    CursCtrl.CY2 = curs;
  }
/* ���������� ����� ������ */
  Curs_draw(true);
  SetCursSt_disp();
}

/*!*****************************************************************************
 @brief		
 @details	���������� ������� 1 � 2
 @note		�� ������� �������������� �������, �� ���������� - �������
 */
void SetCursTr_hand(int32_t Cnt) {
/* ������� ������ ������� */
  Curs_draw(false);
/* ������ �� X */
  if (!CursCtrl.xY) {		// x
    int32_t curs1 = CursCtrl.CX1;
    int32_t curs2 = CursCtrl.CX2;
    curs1 += Cnt;
    curs2 += Cnt;
    if (curs1 < 0) curs1 = 0;
    if (curs2 < 0) curs2 = 0;
    if (curs1 > (1024 << MemCtrl.SizeNum) - (DispCtrl.Wide ? 0 : 50))
        curs1 = (1024 << MemCtrl.SizeNum) - (DispCtrl.Wide ? 1 : 51);
    if (curs2 > (1024 << MemCtrl.SizeNum) - (DispCtrl.Wide ? 0 : 50))
        curs2 = (1024 << MemCtrl.SizeNum) - (DispCtrl.Wide ? 1 : 51);
    CursCtrl.CX1 = curs1;
    CursCtrl.CX2 = curs2;
/* �������� ����������� ��������, ���� ����� */
    if (curs1 < SweepCtrl.TimePos || curs2 < SweepCtrl.TimePos) {
      Pret_draw(false);
      MemBarPos_draw(false);
      if (Chan1Ctrl.On) SigChan1_draw(0);
      if (Chan2Ctrl.On) SigChan2_draw(0);
      SweepCtrl.TimePos = curs1 < curs2 ? curs1 : curs2;
      if (Chan1Ctrl.On) SigChan1_draw(3);
      if (Chan2Ctrl.On) SigChan2_draw(3);
      Pret_draw(true);
      MemBarPos_draw(true);
    }
    if (curs1 > SweepCtrl.TimePos + (DispCtrl.Wide ? 300 : 250) ||
        curs2 > SweepCtrl.TimePos + (DispCtrl.Wide ? 300 : 250)) {
      Pret_draw(false);
      MemBarPos_draw(false);
      if (Chan1Ctrl.On) SigChan1_draw(0);
      if (Chan2Ctrl.On) SigChan2_draw(0);
      SweepCtrl.TimePos = curs1 > curs2 ? 
	curs1 - (DispCtrl.Wide ? 300 : 250) : curs2 - (DispCtrl.Wide ? 300 : 250);
      if (Chan1Ctrl.On) SigChan1_draw(3);
      if (Chan2Ctrl.On) SigChan2_draw(3);
      Pret_draw(true);
      MemBarPos_draw(true);
    }
  }
/* ������ �� Y */
  else {
    int32_t curs1 = CursCtrl.CY1;
    int32_t curs2 = CursCtrl.CY2;
    curs1 += Cnt;
    curs2 += Cnt;
    if (curs1 < 28) curs1 = 28;
    if (curs2 < 28) curs2 = 28;
    if (curs1 > 228) curs1 = 228;
    if (curs2 > 228) curs2 = 228;
    CursCtrl.CY1 = curs1;
    CursCtrl.CY2 = curs2;
  }
/* ���������� ����� ������� */
  Curs_draw(true);
  SetCursSt_disp();
}

/*!*****************************************************************************
 @brief		
 @details	��������/������� ���������� ��������� � �������
 @note		
 */
void SetCursSt_disp(void) {
  if (!CursCtrl.On) return;
  uint8_t txt1[10];						// "012345678"9
  uint8_t txt2[10];						// "012345678"9
  uint8_t *ptxt1 = txt1;		// ��������� �� ������ � ������
  uint8_t *ptxt2 = txt2;		// ��������� �� ������ � ������
  *(uint32_t *)ptxt1 = 0x20202020;				// "____xxxxx"x
  *(uint32_t *)ptxt2 = 0x20202020;
  *(uint32_t *)(ptxt1 + 4) = 0x20202020;			// "________x"x
  *(uint32_t *)(ptxt2 + 4) = 0x20202020;
  *(uint16_t *)(ptxt1 + 8) = 0x0020;				// "_________"\0
  *(uint16_t *)(ptxt2 + 8) = 0x0020;				// "_________"\0
  
  uint32_t mag[] = {40, 20, 8};		// ����������� ��������� ����������  
  
  if (!CursCtrl.xY) {
/* dT */
    uint32_t tcom = 5 - (SweepCtrl.TimeNum + 1) % 9 / 3;	// comma pos
    *(ptxt1 + tcom - 1) = '0';					// "__0_____x"x
    *(ptxt1 + tcom) = '.';					// "__0.____x"x
    for (uint32_t i = tcom + 1; i < 7; i++)
      *(ptxt1 + i) = '0';					// "__0.000_x"x
    *(ptxt1 + 7) = " m\xB5np"[(SweepCtrl.TimeNum + 1) / 9];	// "______0mx"x
    *(ptxt1 + 8) = 's';						// "______0ms"x
    *(ptxt1 + 9) = '\0';					// "______0ms"\0

    *(ptxt2 + 7) = 'H';
    *(ptxt2 + 8) = 'z';
    *(ptxt2 + 9) = '\0';    
    
    int32_t tdel = CursCtrl.CX1 - CursCtrl.CX2;
    if (tdel < 0) tdel = -tdel;
    tdel *= mag[(SweepCtrl.TimeNum + 1) % 3];
    
    ptxt1 += 6;				// ��������� ����� � ������
    while (tdel) {
      *ptxt1-- = tdel % 10 + '0';
      if (*ptxt1 == '.') ptxt1--;
      tdel /= 10;
    }
/* 1/dT */
    uint32_t fcom = 1 + (SweepCtrl.TimeNum + 8) % 9 / 3;	// comma pos
    uint32_t fmul = 1 + (SweepCtrl.TimeNum + 8) / 9;		// mult index
    int32_t fdel = CursCtrl.CX1 - CursCtrl.CX2;
    if (fdel < 0) fdel = -fdel;
    if (!fdel) {
      fdel++;			// ������ ������� �� 0 (������� ��������)
      *(ptxt2 + 6) = '?';
    }
    else {
      fdel = (500000000 >> (2 - (SweepCtrl.TimeNum + 2) % 3)) / fdel;
      while (!(fdel / 100000000)) {	// ���� ����� ��� �������� �����
        fcom--;				// ��������� ������� �����
        if (!fcom) {			// ���� ������� �� ����
          fcom = 3;			// ��������� ������� �� ������� 3
	  fmul--;			// �������� ������ ���������
        }
        fdel *= 10;			// ��������� �����
      }					// ������ ����� ������� � ������ ����
      *(ptxt2 + fcom) = '.';
      *(ptxt2 + 6) = "\xB5m kMG"[fmul];
      ptxt2 += 5;
      fdel /= 10000;			// �������� 5 �������� ����
    
      while (fdel) {
        *ptxt2-- = fdel % 10 + '0';
        if (*ptxt2 == '.') ptxt2--;
        fdel /= 10;
      }
    }
  }

  else {
  
    if (Chan1Ctrl.On) {
      uint32_t num =  (Chan1Ctrl.VoltNum - 6 + Chan1Ctrl.Prb * 3) + 7;
      uint32_t com = 4 - num % 9 / 3;				// comma pos
      *(ptxt1 + com - 1) = '0';					// "0_______x"x
      *(ptxt1 + com) = '.';					// "0.______x"x
      for (uint32_t i = com + 1; i < 6; i++)
        *(ptxt1 + i) = '0';					// "0.000___x"x
      *(ptxt1 + 6) = "k m\xB5"[num / 9];			// "0.000___x"x
      *(ptxt1 + 7) = 'V';					// "0.000_V_x"x
      *(ptxt1 + 8) = ' ';					// "0.000_V__"x 
      *(ptxt1 + 9) = '\0';					// "0.000_V__"\0

      int32_t del = CursCtrl.CY1 - CursCtrl.CY2;
      if (del < 0) del = -del;
      del *= mag[num % 3];

      ptxt1 += 5;			// ��������� ����� � ������
      while (del) {
        *ptxt1-- = del % 10 + '0';
	if (*ptxt1 == '.') ptxt1--;
	del /= 10;
      }
    }
    
    if (Chan2Ctrl.On) {
      uint32_t num =  (Chan2Ctrl.VoltNum - 6 + Chan2Ctrl.Prb * 3) + 7;      
      uint32_t com = 4 - num % 9 / 3;				// comma pos
      *(ptxt2 + com - 1) = '0';					// "0_______x"x
      *(ptxt2 + com) = '.';					// "0.______x"x
      for (uint32_t i = com + 1; i < 6; i++)
        *(ptxt2 + i) = '0';					// "0.000___x"x
      *(ptxt2 + 6) = "k m\xB5"[num / 9];			// "0.000___x"x
      *(ptxt2 + 7) = 'V';					// "0.000_V_x"x
      *(ptxt2 + 8) = ' ';					// "0.000_V__"x
      *(ptxt2 + 9) = '\0';					// "0.000_V__"\0

      int32_t del = CursCtrl.CY1 - CursCtrl.CY2;
      if (del < 0) del = -del;
      del *= mag[num % 3];

      ptxt2 += 5;			// ��������� ����� � ������
      while (del) {
        *ptxt2-- = del % 10 + '0';
	if (*ptxt2 == '.') ptxt2--;
	del /= 10;
      }
    }
    
  }
  DpyStringPad_draw(DPYPOS(DPYVALH, DPYVAL1V), txt1, 0x80800000, true);
  DpyStringPad_draw(DPYPOS(DPYVALH, DPYVAL2V), txt2, 0x80800000, true);
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void SetPar1_hand(int32_t Cnt) {
  int32_t par = (int32_t)MeasCtrl.Par1;
  par += Cnt;				// �������� ��������!
  if (par < 0) par = 0;
  if (par > PAR_AVR << 2) par = PAR_AVR << 2;
  MeasCtrl.Par1 = par;
  MnMeasPar1_disp();			// �������� �������� � ����
  MeasPar1St_disp();			// �������� �������� � �������
  SigPar_meas();
}

/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void SetPar2_hand(int32_t Cnt) {
  int32_t par = (int32_t)MeasCtrl.Par2;
  par += Cnt;				// �������� ��������!
  if (par < 0) par = 0;
  if (par > PAR_AVR << 2) par = PAR_AVR << 2;
  MeasCtrl.Par2 = par;
  MnMeasPar2_disp();			// �������� �������� � ����
  MeasPar2St_disp();			// �������� �������� � �������
  SigPar_meas();
} 

 
/*!*****************************************************************************
 @brief		
 @details	
 @note		
 */
void SetBufNum_hand(int32_t Cnt)
{
  static int32_t cnt;
  cnt += Cnt;
  int32_t num = MemCtrl.BufNum;
  if (cnt > +4) { num++; cnt = 0; }
  if (cnt < -4) { num--; cnt = 0; }
  if (MemCtrl.SizeNum == 0) { if (num < 0) num = 31; if (num > 31) num = 0; }
  if (MemCtrl.SizeNum == 1) { if (num < 0) num = 15; if (num > 15) num = 0; }
  if (MemCtrl.SizeNum == 2) { if (num < 0) num = 7; if (num > 7) num = 0; }
  if (MemCtrl.SizeNum == 3) { if (num < 0) num = 3; if (num > 3) num = 0; }
  if (MemCtrl.SizeNum == 4) { if (num < 0) num = 1; if (num > 1) num = 0; }
  if (MemCtrl.SizeNum >= 5) num = 0;
  MemCtrl.BufNum = num;
  MnMemNum_disp();
  DpyWork_clear(MASK_MATSIG);
  SigChans_redraw();
  Math_exe();
  SigPar_meas();
}
 

//__ ����������� ������ ��������� (� ���� ������) _____________________________//


/*!*****************************************************************************
 @details	������ ������� ���������, ����������
 @note	
 */
void ExeVoid_hand(void) { }

/*!*****************************************************************************
 @brief		Calibrate execute
 @details	��������� ���������� �������������
 @note
 */
void ExeCalibr_hand(void) {
  uint32_t tmts = SFMWord_read(SFMINTERP);
  if (~tmts) {
    Interp.Tmts = tmts;
    Interp.Tmad = SFMWord_read(SFMINTERP + 4);
  }
/* ������ ������ �����, �� ������, �� ������ 1, ����� �� �� */
  // PL_TrigBuf |= PL_TRIG_NORM;
  // PL->TRIG = PL_TrigBuf;
  Chan2Ctrl.On = 0;			// ��������� ����� 2
  PL->TRIG = PL_TRIG_DIV | PL_TRIG_NORM | PL_TRIG_RISE
	   | PL_TRIG_HYST | PL_TRIG_AC | PL_TRIG_CH1;
  SetNum = SET_AVER;		// ���������� �������
  ServCtrl.Calibr = 1;		// �������� ����������� ��������
  SweepCtrl.Stop = 0;		// ������ ���� 
}

/*!*****************************************************************************
 @brief		Calibrate Save execute
 @details	��������� ���������� ���������� �������������
 @note		�������� ��� ����� (8 ������) �� �������� SFMINTERP
 */
void ExeCalSave_hand(void) {
  SFMPage_write((uint8_t *)&Interp.Tmts, SFMINTERP, 8);
  ServCtrl.Calibr = 0;			// ��������� �����������
  DpyNum_blank();			// �������� ����
  SetNum = SET_VOID;			// ������ ����� ����������
}

/*!*****************************************************************************
 @details	
 @note		
 */
void ExeCPUiMem_hand(void) { }

/*!*****************************************************************************
 @details	
 @note		
 */
void ExeCPUeMem_hand(void) { }


/*!*****************************************************************************
 @details	������� ��� �� RS-232
 @note		������ 4 ����� ��������������� ��� �������� ������� ����
 */
void ExePLRecv_hand(void)
{
  NVIC_DisableIRQ(USART2_IRQn);
  uint8_t *dat = (uint8_t *)(XRAM_BASE + 4);	// ��������� �� ����� � ������
  uint8_t *dpy = (uint8_t *)(DPYMEM_BASE);	// ��������� �� ����� � ���
  uint32_t cnt = 0;			// ������� ��� ����������� �� 256x240 ������
  CodeCnt = 0;				// ���������� ������� ������
  WDELAY_START(8000000);		// 8 sec
  // TimerTicks = 8000;			// 8 sec
  // while (TimerTicks) {
  while (!(WDELAY_CHECK)) {
    if (USART2->SR & USART_SR_RXNE) {
      uint8_t temp = USART2->DR;
      *dat++ = temp;
      *dpy++ = temp;
      cnt++;
      CodeCnt++;
      if ((cnt & 0x000000FF) == 0) {
        dpy += (320 - 256);
        // TimerTicks = 8000;
	WDELAY_RESTART();
      }	
      if ((cnt > 256U * 240U)) {
        dpy = (uint8_t *)(DPYMEM_BASE);
	cnt = 0;
      }
    }
  }
  Num_draw(CodeCnt);
  *(uint32_t *)(XRAM_BASE) = CodeCnt;	// �������� ������ ���� 
}

/*!*****************************************************************************
 @details	��������� ��������� ��������� �� RS-232 ���� � ���� � ������
 @note	
 */
void ExePLComp_hand(void) {
  NVIC_DisableIRQ(USART2_IRQn);
  uint8_t *dat = (uint8_t *)(XRAM_BASE + 4);	// ��������� �� ����� � ������
  uint8_t *dpy = (uint8_t *)(DPYMEM_BASE);	// ��������� �� ����� � ���
  uint32_t cnt = 0;			// ������� ��� ����������� 256x240 ������
  CodeCnt = 0;				// ���������� ������� ������
  WDELAY_START(8000000);		// 8 sec
  // TimerTicks = 8000;			// 8 sec
  // while (TimerTicks) {
  while (!(WDELAY_CHECK)) {
    if (USART2->SR & USART_SR_RXNE) {
      uint8_t temp = USART2->DR;
      if (*dat++ == temp)  *dpy++ = 0xCC;
      else  *dpy++ = 0xC3;
      cnt++;
      CodeCnt++;
      if ((cnt & 0x000000FF) == 0) {
        dpy += (320 - 256);
        // TimerTicks = 8000;
        WDELAY_RESTART();
      }	
      if ((cnt > 256U * 240U)) {
        dpy = (uint8_t *)(DPYMEM_BASE);
        cnt = 0;
      }
    }
  }
  Num_draw(CodeCnt);
}

/*!*****************************************************************************
 @details	�������� ��� � ���������������� ������
 @note		������ 4 ����� ���� - ������
 @note		��������� ������ ����������� � ����� ���������� ��������
 */
void ExePLWrite_hand(void) {
  if (!CodeCnt)  return;			// ���� ���� ���, ����
  uint8_t *dat = (uint8_t *)(XRAM_BASE);	// ��������� �� ����� � ���
  uint8_t *dpy = (uint8_t *)(DPYMEM_BASE);	// ��������� �� ����� � ���
  uint32_t adr = SFMCODE_BASE;		// ����� ���������������� ������
  uint32_t cnt = 0;			// ������� ��� ����������� 256x240 ������

  for (uint32_t i = 4; i > 0; i--) {
    SFMSect_erase(adr);			// ������� 4 ������� (262144 �����)
    adr += (1 << 16);			// +65536
  }
  uint32_t pages = (CodeCnt + 4) / 256;	// ���������� ������ �������
  uint32_t bytes = (CodeCnt + 4) % 256;	// ���������� ���������� ������
  adr = SFMCODE_BASE;
  for (uint32_t i = pages; i > 0; i--) {
    SFMPage_progr(dat, adr, 256);
    dat += 256;
    adr += 256;  
    for (uint32_t j = 256; j > 0; j--) {
      *dpy++ = 0xCF;			// ������
      cnt++;
      if ((cnt & 0x000000FF) == 0) {
        dpy += (320 - 256);
      }
      if ((cnt > 256U * 240U)) {
        dpy = (uint8_t *)(DPYMEM_BASE);
	cnt = 0;
      }
    }
  }
  SFMPage_progr(dat, adr, bytes);	// ����������������� �������
  for (uint32_t j = bytes; j > 0; j--) {
    *dpy++ = 0xcf;
    cnt++;
    if ((cnt & 0x000000FF) == 0) {
      dpy += (320 - 256);
    }
    if ((cnt > 256U * 240U)) {
      dpy = (uint8_t *)(DPYMEM_BASE);
      cnt = 0;
    }
  }    
  
  Num_draw(adr + bytes);		// �������� ���������� ������
  WDELAY_START(4000000);
  // TimerTicks = 4000;			// 4 sec
  // while (TimerTicks);			// ��������
  WDELAY_WAIT();
}

/*!*****************************************************************************
 @details	��������� � �������� ��� �� ���������������� ������
 @note		
 */
void ExePLRead_hand(void) {
  if (!CodeCnt) return;			// ���� ���� ���, ����
  uint8_t *dat = (uint8_t *)(XRAM_BASE);	// ��������� �� ����� � ���
  uint8_t *dpy = (uint8_t *)(DPYMEM_BASE);	// ��������� �� ����� � ���
  uint32_t adr = SFMCODE_BASE;
  uint32_t cnt = 0;			// ������� ��� ����������� 256x240 ������

  SFMRead_start(adr);
  for (uint32_t i = CodeCnt + 4; i > 0; i--) {
    if (*dat++ == SFMByte_read()) *dpy++ = 0xFC;	// ��������� (�������)
    else  *dpy++ = 0xF3;				// �� ��������� (����������)
    cnt++;
    if ((cnt & 0x000000FF) == 0) { dpy += (320 - 256); }
    if ((cnt > 256U * 240U)) { dpy = (uint8_t *)(DPYMEM_BASE); cnt = 0; }
  }
  SFMRead_stop();
  
  WDELAY_START(4000000);
  // TimerTicks = 4000;
  // while (TimerTicks);
  WDELAY_WAIT();
}

/*!*****************************************************************************
 @details	��������� ����� ����� ������
 @note	
 */
void ExeDpyWhite_hand(void) {
  DPY_RECT(0, 0, 319, 239, 0xFF, WHITE);
//  Gen.Lock = 1;			// ������������� ������ ����������
}

/*!*****************************************************************************
 @details	��������� ����� ������ ������
 @note	
 */
void ExeDpyBlack_hand(void) {
  DPY_RECT(0, 0, 319, 239, 0xFF, BLACK);
//  Gen.Lock = 1;
}

/*!*****************************************************************************
 @details	���������� ��� ������� �� ������
 @note	
 */
void ExeDpyFont_hand(void) {
  DpyScreen_blank();
  DigitBar_disp();
  DpyFont_draw();
}

/*!*****************************************************************************
 @details	���������� ��� ������� �� ������
 @note	
 */
void ExeDpyPalet_hand(void) {
  DpyScreen_blank();
  DigitBar_disp();
  DpyPalet_draw();
}

/*!*****************************************************************************
 @details	��������� ����� ������� ������
 @note	
 */
void ExeDpyRed_hand(void) {
  DPY_RECT(0, 0, 319, 239, 0xFF, 0xC3);
//  Gen.Lock = 1;		// ������������� ������ ����������
}

/*!*****************************************************************************
 @details	��������� ����� ������� ������
 @note	
 */
void ExeDpyGreen_hand(void) {
  DPY_RECT(0, 0, 319, 239, 0xFF, 0xCC);
//  Gen.Lock = 1;			// ������������� ������ ����������
}

/*!*****************************************************************************
 @details	��������� ����� ����� ������
 @note	
 */
void ExeDpyBlue_hand(void) {
  DPY_RECT(0, 0, 319, 239, 0xFF, 0xF0);
//  Gen.Lock = 1;		// ������������� ������ ����������
}

/*!*****************************************************************************
 @details	������������ �����
 @note	
 */
void ExeDpyDefault_hand(void) {
    DpyScreen_blank();
    DpyScale_draw();
    MenuHead_disp();
    MenuHeadDepr_disp();    
//    Gen.Lock = 0;	// �������������� ������ ����������
}


//__ ����������� �������, ���������� ������� � ������� ��������� ______________//

/* ������� ����� Volt/div ��� ��������� � AnaReg */
static const uint8_t VoltDivReg[] = {
  0x56,					// (4)	20 V/div
  0x66,					// (5)	10 V/div
  0x46,					// (6)	 5 V/div
  0x52,					// (7)	 2 V/div
  0x62,					// (8)	 1 V/div
  0x42,					// (9)	0.5 V/div
  0x54,					// (10)	0.2 V/div *
  0x64,					// (11)	0.1 V/div
  0x44,					// (12)	50 mV/div
  0x50,					// (13)	20 mV/div
  0x60,					// (14)	10 mV/div
  0x40,					// (15)	5 mV/div
  0x00					// (16)	2 mV/div
};
  
//* ����� 1 *//

/*!*****************************************************************************
 @details	����� 1, �����, ����������
 @note	
 */
void Chan1Mode_sett(void) {
  if (Chan1Ctrl.On) SigChan1_draw(3);
  else              SigChan1_draw(0);
  if (Chan1Ctrl.On) PL_VoltBuf |= PL_VOLT_S1EN;
  else              PL_VoltBuf &= ~PL_VOLT_S1EN;
  PL->VOLT = PL_VoltBuf;
}

/*!*****************************************************************************
 @details	����� 1, ����������� ������, ����������
 @note	
 */
void Chan1BWLim_sett(void) {
  AnaRegBuf &= ~(1 << 7);
  AnaRegBuf |= Chan1Ctrl.BWLim << 7;
  AnaReg_send();
}

/* ������ 1 + 2, ��������� � ���� ��������� */

/*!*****************************************************************************
 @details	����� 1, �����, ����������
 @note		
 */
void Chan1Cplg_sett(void) {
  AnaRegBuf &= ~0x00000076;	// ������ ���� Volt/div
  AnaRegBuf |= VoltDivReg[Chan1Ctrl.VoltNum - VOLT_BEG];
  if (!Chan1Ctrl.Cplg) {	// ����������
    AnaRegBuf |= 0x00000030;	// ���������� ����
  }
  AnaRegBuf &= ~(1 << 3);	// �������� ��� �����
  AnaRegBuf |= !!(Chan1Ctrl.Cplg & 0x02) << 3;	// 01 - AC, 10 - DC

  AnaReg_send();		// ������� �����
}

/*!*****************************************************************************
 @details	����� 1, ��������� � �������
 @note		���������� �����, �����������, ����� � ����������� ���������
 */
void Chan1St_disp(void) {
  if (Chan1Ctrl.On) PanCtrl.TxBuf &= ~(1 << 1);	// ������ ����
  else	PanCtrl.TxBuf |= (1 << 1);		// �������� ����
  PanCtrl.TxBuf |= 0x40;
  USART3->DR = PanCtrl.TxBuf;

  if (Chan1Ctrl.On) {
    DpyRect_fill(DPYPOS(DPYSAH, DPYS1VV - 1), 9, 10, 0x0000FF02);
    DpyChar_draw(DPYPOS(DPYSAH + 1, DPYS1VV), '1', 0x00000202);
    uint32_t spaces = DpyVolt_draw(DPYPOS(DPYSAH + 12, DPYS1VV),
        Chan1Ctrl.VoltNum - 6 + Chan1Ctrl.Prb * 3, 0x02020000);
    // Num_draw(spaces);
    SSYM_t CplgSym[] = {SS_GND, SS_CPAC, SS_CPDC};
    DpySpec_draw(DPYPOS(DPYSAH + 12 + 8 * spaces, DPYS1VV),
      CplgSym[Chan1Ctrl.Cplg], 0x03, 0x02020000);
//    if (Chan1Ctrl.Gnd) ssym = SS_GND;
//    else if (!Chan1Ctrl.Cplg) ssym = SS_CPAC;
//      else ssym = SS_CPDC;
//    DpySpec_draw(DPYPOS(DPYSAH + 12 + 8 * spaces, DPYS1VV), ssym, 0x03, 0x03030000);
    if (Chan1Ctrl.Inv) {
      DpySpec_draw(DPYPOS(DPYSAH + 12 + 40, DPYS1VV), SS_ARDN, 0x03, 0x02020000);
    }    
  }
  else
    DPY_RECT(DPYSAH, DPYS1VV - 1, DPYSAH + 60, DPYS1VV + 9, 0xFF, BLANK);
}

//* ����� 2 *//

/*!*****************************************************************************
 @details	����� 2, �����, ����������
 @note	
 */
void Chan2Mode_sett(void) {
  if (Chan2Ctrl.On)  SigChan2_draw(3);
  else               SigChan2_draw(0);
  if (Chan2Ctrl.On) PL_VoltBuf |=  PL_VOLT_S2EN;
  else              PL_VoltBuf &= ~PL_VOLT_S2EN;
  PL->VOLT = PL_VoltBuf;
}

/*!*****************************************************************************
 @details	����� 2, ����������� ������, ����������
 @note	
 */
void Chan2BWLim_sett(void) {
  AnaRegBuf &= ~(1 << 8);
  AnaRegBuf |= Chan2Ctrl.BWLim << 8;
  AnaReg_send();
}

/*!*****************************************************************************
 @details	����� 2, �����, ����������
 @note	
 */
void Chan2Cplg_sett(void) {
  AnaRegBuf &= ~0x00007600;	// ������ ���� Volt/div
  AnaRegBuf |= VoltDivReg[Chan2Ctrl.VoltNum - VOLT_BEG] << 8;
  if (!Chan2Ctrl.Cplg) {	// ���� ���� ����������,
    AnaRegBuf |= 0x00003000;	// ���������� ����
  }
  AnaRegBuf &= ~(1 << 3 + 8);
  AnaRegBuf |= !!(Chan2Ctrl.Cplg & 0x02) << 3 + 8;	// 01 - AC, 10 - DC
  
  AnaReg_send();		// ������� �����
}

/*!*****************************************************************************
 @details	����� 2, ��������� � �������
 @note		���������� �����, �����������, ����� � ����������� ���������
 */
void Chan2St_disp(void) {
  if (Chan2Ctrl.On) PanCtrl.TxBuf &= ~(1 << 3);	// ������ ����
  else PanCtrl.TxBuf |= (1 << 3);		// �������� ����
  PanCtrl.TxBuf |= 0x40;
  USART3->DR = PanCtrl.TxBuf;
  
  if (Chan2Ctrl.On) {
    DpyRect_fill(DPYPOS(DPYSAH, DPYS2VV - 1), 9, 10, 0x0000FF08);
    DpyChar_draw(DPYPOS(DPYSAH + 1, DPYS2VV), '2', 0x00000808);
    uint32_t spaces = DpyVolt_draw(DPYPOS(DPYSAH + 12, DPYS2VV),
        Chan2Ctrl.VoltNum - 6 + Chan2Ctrl.Prb * 3, 0x08080000);
    // Num_draw(spaces);
    SSYM_t CplgSym[] = {SS_GND, SS_CPAC, SS_CPDC};
    DpySpec_draw(DPYPOS(DPYSAH + 12 + 8 * spaces, DPYS2VV),
      CplgSym[Chan2Ctrl.Cplg], 0x0C, 0x08080000);
    
//    if (Chan2Ctrl.Gnd) ssym = SS_GND;
//    else if (!Chan2Ctrl.Cplg) ssym = SS_CPAC;
//      else ssym = SS_CPDC;
//    DpySpec_draw(DPYPOS(DPYSAH + 12 + 8 * spaces, DPYS2VV), ssym, 0x0c, 0x0c0c0000);
    if (Chan2Ctrl.Inv) {
      DpySpec_draw(DPYPOS(DPYSAH + 12 + 40, DPYS2VV), SS_ARDN, 0x0C, 0x08080000);
    }      
  }
  else
    DPY_RECT(DPYSAH, DPYS2VV - 1, DPYSAH + 60, DPYS2VV + 9, 0xFF, BLANK);
}

//* �������������� ��������� *//

/*!*****************************************************************************
 @details	���. ���, ���������
 @note		�������� ��� ����� ���������
 */
void MathSt_disp(void) {
  if (MathCtrl.On) PanCtrl.TxBuf &= ~(1 << 2);	// ������ ����
  else             PanCtrl.TxBuf |=  (1 << 2);	// �������� ����
  PanCtrl.TxBuf |= 0x40;
  USART3->DR = PanCtrl.TxBuf;
}

//* ��������� *//

/*!*****************************************************************************
 @details	�����/���, ����������
 @note		�������� ���� ������ � ����
 @note		(2^31 * 4 ns > 8.5 s) * 25 > 200 s/div
 @note		������� 50 s/div
 @verbatim
  0  -  50 s/div
  26 - 100 ns/div	250 MSps, 4 ns sample
  27 -  50 ns/div	TimeItp = 2
  ...
  35 - 0.1 ns/div	TimeItp = 1000
 @endverbatim
 */
void Time_sett(void) {
  static const uint32_t PL_TimeDiv[] = {
  500000000 - 2,			//  0   50 s/div (2 s/dot)
  200000000 - 2,			//  1   20 s/div (0.8 s/dot)
  100000000 - 2,			//  2   10 s/div (0.4 s/dot)
   50000000 - 2,			//  3    5 s/div (0.2 s/dot)
   20000000 - 2,			//  4    2 s/div (80 ms/dot)
   10000000 - 2,			//  5    1 s/div (40 ms/dot)
    5000000 - 2,			//  6  0.5 s/div (20 ms/dot)
    2000000 - 2,			//  7  0.2 s/div (8 ms/dot)
    1000000 - 2,			//  8  0.1 s/div (4 ms/dot)
     500000 - 2,			//  9  50 ms/div (2 ms/dot)
     200000 - 2,			// 10  20 ms/div (0.8 ms/dot)
     100000 - 2,			// 11  10 ms/div (0.4 ms/dot)
      50000 - 2,			// 12   5 ms/div (0.2 ms/dot)
      20000 - 2,			// 13   2 ms/div (80 us/dot)
      10000 - 2,			// 14   1 ms/div (40 us/dot)
       5000 - 2,			// 15 0.5 ms/div (20 us/dot) *
       2000 - 2,			// 16 0.2 ms/div (8 us/dot)
       1000 - 2,			// 17 0.1 ms/div (4 us/dot)
        500 - 2,			// 18  50 us/div (2 us/dot)
        200 - 2,			// 19  20 us/div (0.8 us/dot)
        100 - 2,			// 20  10 us/div (0.4 us/dot)
         50 - 2,			// 21   5 us/div (0.2 us/dot)
         20 - 2,			// 22   2 us/div (80 ns/dot)
         10 - 2,			// 23   1 us/div (40 ns/dot)
          5 - 2,			// 24 0.5 us/div (20 ns/dot)
          2 - 2,			// 25 0.2 us/div (8 ns/dot)
  };
  static const uint16_t TimeItp_table[] = {
              1,			// 26 0.1 us/div (4 ns/dot)
              2,			// 27  50 ns/div (Random sample)
              5,			// 28  20 ns/div
             10,			// 29  10 ns/div
             20,			// 30   5 ns/div
             50,			// 31   2 ns/div
            100,			// 32   1 ns/div
            200,			// 33 0.5 ns/div
            500,			// 34 0.2 ns/div
           1000				// 35 0.1 ns/div
  };
  
  if (SweepCtrl.TimeNum < 26) {
    PL->TIML = (uint16_t)PL_TimeDiv[SweepCtrl.TimeNum];
    PL->TIMH = (uint16_t)(PL_TimeDiv[SweepCtrl.TimeNum] >> 16);
    SweepCtrl.TimeItp = 1;
  }
  else {
    PL->TIML = 0;
    PL->TIMH = PL_TIMH_LDP;
    SweepCtrl.TimeItp = TimeItp_table[SweepCtrl.TimeNum - 26];
  }

#ifdef TRIGDIV_USE
/* ������ �������� �� ������� ���������� */
  if (SweepCtrl.TimeNum < 27)
    PL_TrigBuf &= ~PL_TRIG_DIV;		// ������ �������� �� 4
  else
    PL_TrigBuf |= PL_TRIG_DIV;		// ������ �������� �� 4  
  PL->TRIG = PL_TrigBuf;
#endif
}

/*!*****************************************************************************
 @details	�����/���, ��������� � �������
 */
void TimeSt_disp(void) {
  static const uint8_t *TimeTxt[] =
  { "  50s", "  20s", "  10s",
    "   5s", "   2s", "   1s",
    " 0.5s", " 0.2s", " 0.1s",    
    " 50ms", " 20ms", " 10ms",
    "  5ms", "  2ms", "  1ms",
    "0.5ms", "0.2ms", "0.1ms",
    " 50\xB5s", " 20\xB5s", " 10\xB5s",
    "  5\xB5s", "  2\xB5s", "  1\xB5s",
    "0.5\xB5s", "0.2\xB5s", "0.1\xB5s",
    " 50ns", " 20ns", " 10ns",
    "  5ns", "  2ns", "  1ns",                            
    "0.5ns", "0.2ns", "0.1ns" };
  DpyStringPad_draw(DPYPOS(DPYSAH + 72, DPYS2VV), 
		TimeTxt[SweepCtrl.TimeNum], 0x0A0A0000, true);
}

/*!*****************************************************************************
 @details	���������, �����, ����������
 */
void SweepMode_sett(void) {
  if (SweepCtrl.Mode) PL_TrigBuf |=  PL_TRIG_NORM;	// Norm, Single
  else		      PL_TrigBuf &= ~PL_TRIG_NORM;	// Auto
  PL->TRIG = PL_TrigBuf;
}

/*!*****************************************************************************
 @details	���������, �����������, ����������
 */
void SweepRoll_sett(void) { }

/*!*****************************************************************************
 @details	���������, �����, ��������� � �������
 */
void SweepSt_disp(void) {
  static const uint8_t *ModeTxt[4] = {" ����  ", " ����  ", "������ ", "�������"};
  uint32_t mode = SweepCtrl.Mode;
  if (SweepCtrl.Roll && SweepCtrl.TimeNum <= TIME_DOT) mode = 3;
  DpyStringPad_draw(DPYPOS(DPYSAH + 72, DPYS1VV), ModeTxt[mode], 0x0A0A0000, 1);
}

//* ������������� *//

/*!*****************************************************************************
 @details	�������������, ��������, ����������
 */
void TrigSour_sett(void) {
  static const uint8_t TrigSett[4] = {0x01, 0x00, 0x02, 0x01};
  AnaRegBuf &= ~(3 << 22);
  AnaRegBuf |= (TrigSett[TrigCtrl.Sour]) << 22;	// Ext, Ch1, Ch2, Ext
  AnaReg_send();			// ������� �����    
}

/*!*****************************************************************************
 @details	�������������, ��������, ��������� � �������
 */
void TrigSt_disp(void) {
  static const uint8_t *SrcTxt[4] = {"����", "���1", "���2", "����"};
  DpyStringPad_draw(DPYPOS(DPYSAH + 132, DPYS1VV), 
		    SrcTxt[TrigCtrl.Sour], 0x0A0A0000, true);
  DpyRect_fill(DPYPOS(DPYSAH + 132, DPYS2VV), 32, 8, 0xFF<<8 | BLANK);
  DpySpec_draw(DPYPOS(DPYSAH + 136, DPYS2VV), 
	      (SSYM_t)(SS_FALL + TrigCtrl.Rise), 0xFF, 0x0A0A0000);
  uint8_t *pDpy = DPYPOS(DPYSAH + 148, DPYS2VV);
  switch (TrigCtrl.Cplg) {
  case 0:
    DpyString_draw(pDpy, "��", 0x0A0A0000, true);
    break;
  case 1:
  default:  
    DpySpec_draw(pDpy + 4, SS_CPDC, 0xFF, 0x0A0A0000);
    break;
  case 2:
    DpySpec_draw(pDpy + 4, SS_CPAC, 0xFF, 0x0A0A0000);      
    break;
  case 3:
    DpyString_draw(pDpy, "��", 0x0A0A0000, true);
  }
}

/*!*****************************************************************************
 @details	�������������, �������, ����������
 */
void TrigSlp_sett(void) {
  if (TrigCtrl.Rise) PL_TrigBuf |=  PL_TRIG_RISE;	// Rise
  else		     PL_TrigBuf &= ~PL_TRIG_RISE;	// Fall
  PL->TRIG = PL_TrigBuf;
}

/*!*****************************************************************************
 @details	�������������, �����, ����������
 */
void TrigCplg_sett(void) {
  AnaRegBuf &= ~(1 << 15);
  AnaRegBuf |= (!(bool)TrigCtrl.Cplg) << 15;	// LF, DC, AC, HF
  AnaReg_send();			// ������� �����  
}

/*!*****************************************************************************
 @details	�������������, ��������������, ����������
 */
void TrigNRej_sett(void) {
// �������� ������ ��� (���������������� � ����)
  if (TrigCtrl.NRej) PL_TrigBuf |=  (PL_TRIG_HYST);
  else		     PL_TrigBuf &= ~(PL_TRIG_HYST); 
  PL->TRIG = PL_TrigBuf;
}

//* ������ *//

/*!*****************************************************************************
 @details	������, �����, ����������
 \note		���� ������ ������ � ���� ���������� � 0.5K 
 */
void MemSize_sett(void) {
  PL_AcquBuf &= ~PL_ACQU_MEM;
  PL_AcquBuf |= (MemCtrl.SizeNum + 1) << 8;
  PL->ACQU = PL_AcquBuf;
}

//* ���� ���������� *//

/*!*****************************************************************************
 @details	������, ����������
 */
void AcquFilt_sett(void) {
  PL_AcquBuf &= ~PL_ACQU_FILT;
  PL_AcquBuf |= AcquCtrl.Filt;
  PL->ACQU = PL_AcquBuf;
}

/*!*****************************************************************************
 @details	������� ��������, ����������
 */
void AcquPeak_sett(void) {
  PL_AcquBuf &= ~PL_ACQU_PEAK;
  PL_AcquBuf |= AcquCtrl.Peak << 2;
  PL->ACQU = PL_AcquBuf;
}

/*!*****************************************************************************
 @details	����/���� ���������
 */
void StSp_disp(void) {
  static const uint8_t *StopText[2] = {"    ", "����"};
  // DpyStringPad_draw(DPYPOS(DPYMHH, 1), StopText[SweepCtrl.Stop], 0xf3f30000, 0);
  DpyStringPad_draw(DPYPOS(DPYWAH + 300 - (3 * 7 + 5), 1),
		StopText[SweepCtrl.Stop], 0xF3F30000, 0);

// �������� ���������� �����
//  static const uint8_t *TestText = "Test" S_ROTR "A";
//  DpyString_draw(DPYPOS(DPYWAH, 2), TestText, 0xF3F30000, 0);
}

/*!*****************************************************************************
 @details	������� ���������
 */
void Autoset_disp(void) { }


//__ ����������� ����� ��������� ______________________________________________//

/*!*****************************************************************************
 @details	��������� ����������� � ����
 @note		�������� ������� ���� �� �����, � ���� ��� �� ������������
 */
void SetPret_sett(void) {
  uint16_t pret = SweepCtrl.Pret << MemCtrl.SizeNum + 5;
//  if (SweepCtrl.TimeNum >= 26) pret -= 16;	// ���������� �� 16 ����� �����
  PL->PRET = pret;
  // Num_draw(pret);
}

/*!*****************************************************************************
 @details	��������� ������������ � ����
 */
void SetHold_sett(void) { }


/*!*****************************************************************************
 @brief		Volt/Div draw
 @details	���������� ������ � �������
 @param		pDpy
 @param		Num
 @param		Color
 @return	���������� ���������� ��������
 @note		������ ������ ��� ������� �����	
 */
uint32_t DpyVolt_draw(uint8_t *pDpy, uint32_t Num, uint32_t Color) {
  static const uint8_t *VoltTxt[] = {
    " 500V ", " 200V ", " 100V ",		// 1/100
    "  50V ", "  20V ", "  10V ",		// 1/10
    "   5V ", "   2V ", "   1V ",
    " 0.5V ", " 0.2V ", " 0.1V ",
    " 50mV ", " 20mV ", " 10mV ",
    "  5mV ", "  2mV ", "  1mV ",
    " .5mV ", " .2mV ", " .1mV "		// x10
  };
  DpyStringPad_draw(pDpy, VoltTxt[Num], Color, 1);
  uint32_t Spaces = 0;
  const uint8_t *ptr = VoltTxt[Num] + 1;	// ������ ������ ����������
  while (*ptr++ == ' ') Spaces++;
  return Spaces;
}


/*__ �������������� ������� ____________________________________________________*/


/*!*****************************************************************************
 @brief		Number draw
 @details	���������� ����� (32-������� ����������) � ��������� ����
 @param		number
 @return	
 @note	
 */
void Num_draw(int32_t number) {
  if (!ServCtrl.Numb) return;
  uint8_t TextBuf[12];			// ��������� ����� ��� ��������� ������
  itoad_conv(number, TextBuf);
  // uint8_t TextBuf[12] = "123456789AB";	// ������ ��� ��������
  // DpyStringPad_draw(DPYPOS(DPYWAH+1,1), TextBuf, 0xf3f30000, 1);
  DpyStringPad_draw(DPYPOS(DPYWAH + 300 - 11 * 8 - 2, 1), TextBuf, 0xF3F30000, 1);
  // DpyStringPad_draw(DPYPOS(DPYWAH, 1), TextBuf, 0xF3F30000, true);
}

/*!*****************************************************************************
 @brief		Hexadecimal 32-bit variable draw
 @details	���������� 32-������� ���������� � 16-������ ���� � ��������� ����
 @param		var - ����������
 @return	
 @note	
 */
void Hex32_draw(uint32_t var) {
  if (!ServCtrl.Numb) return;		// ����� �� ������� ����� 
  uint8_t TextBuf[11];			// ��������� ����� ��� ��������� ������
  uint8_t *pText = &TextBuf[10];
  *pText-- = 0;
  for (uint32_t i = 8; i--; ) {
    uint8_t dig = (var & 0xf);
    dig += (dig < 10)? 0x30 : 0x37;
    *pText-- = dig;
    var >>= 4;
  }
  *pText-- = 'x';
  *pText = '0';
  DpyStringPad_draw(DPYPOS(DPYWAH + 300 - 10 * 8 - 2, 1), TextBuf, 0xf3f30000, 1);
}

/*!*****************************************************************************
 @brief		Dump draw
 @details	���������� ���������� ������ (32-������� ����������)
 @param		mem - ��������� �� ����������
 @return	
 @note	
 */
void Dump_draw(uint8_t *mem) {
  if (!ServCtrl.Dump) return;
/* ��������� ����� */
  uint8_t TextBuf[38] = {"0xMMMMMMMM: HHHHHHHHHHHHHHHH TTTTTTTT"}; 
  itoah_conv((uint32_t)mem, TextBuf + 2);
  uint8_t *pTxt = TextBuf + 12;
  for (int32_t i = 8; i > 0; i--) {
    uint8_t dig = (*mem & 0xf0)>>4;
    *pTxt++ = dig + ((dig < 10)? 0x30 : 0x37);
    dig = *(mem++) & 0x0f; 
    *pTxt++ = dig + ((dig < 10)? 0x30 : 0x37);
  }
  pTxt++;
  mem -= 8;
  for (int32_t i = 8; i > 0; i--) {
    *pTxt++ = *mem++;
  }
  DpyStringPad_draw(DPYPOS(DPYWAH + 1, 1), TextBuf, 0xf3f30000, 1);
}

/*!*****************************************************************************
 @brief		Draw Menu
 @details	���������� ���� (��������� ����, ��������� ���������, ��������) 
 @return	
 @note
 */
void MenuHead_disp(void) {
/* ��������� ���� [MenuNum]
   ������ ����:
   MenuServ, MenuChan1, MenuMath, MenuChan2, MenuSweep, MenuTrig,
   MenuDisp, MenuAcq, MenuCurs, MenuMeas, MenuMem, MenuUtil */
  static const uint8_t *MenuHead[] = {
    " \x98\x98������",
    " ����� 1", " ���. ���", " ����� 2", "���������", "  �����",
    "\x98\x98�������", "\x98���� ���", "\x98\x98�������", "���������",
    " \x98\x98������", "\x98\x98�������"
  }; 

/* ��������� ��������� ���� [MenuNum][FNum(0:4)] */
  static const uint8_t *MenuItemHead[][5] = {
    "����������", "\x98���� ���", "\x98��� ����", "\x98���� ���", "\x98���������",
    "  �����", " \x98�������", "\x98\x98��������", "  \x98�����", "���.������",
    "  �����", " \x98�������", " ��������", S_SPSM"���� ���", S_SPSM S_SPSM"��������",
    "  �����", " \x98�������", "\x98\x98��������", "  \x98�����", "���.������",
    "  �����", "\x98���������", " \x98�������", "", "   X-Y",
    " ��������", " \x98�������", "", "  \x98�����", "���������",
    " \x98������", "  \x98�����", "  \x98�����", "", " ��������", 
    "  ������", "���\x98������", " ������-�", " ������-�", "",
    "  �����", " ��������", " ������ 1", " ������ 2", "\x98\x98���� 1_2",
    "  �����", " ��������", S_SPSM"��������1", S_SPSM"��������2", "",
    "  \x98�����", "����� ���", "  ������", "\x98���������", "\x98���������",
    "����������", "���-�"S_SPSM"����", "", "  ������", "  �����"
  };
  
  DPY_RECT(DPYMAH, DPYMAV,      319, DPYMAV +  24, 0xFF, HEAD_BKG);
  DPY_RECT(DPYMAH, DPYMAV + 25, 319, DPYMAV + 200, 0xFF, ITEM_BKG);

  DPY_LINEH(DPYMAH + 1, DPYMAV +  1, 318, 0xff, HEAD_EMFA, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYMAV + 24, 318, 0xff, HEAD_EMRI, 0xFF);

  DPY_LINEH(DPYMAH + 1, DPYM1AV,      318, 0xff, ITEM_EMRI, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM1AV + 34, 318, 0xff, ITEM_EMFA, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM2AV,      318, 0xff, ITEM_EMRI, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM2AV + 34, 318, 0xff, ITEM_EMFA, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM3AV,      318, 0xff, ITEM_EMRI, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM3AV + 34, 318, 0xff, ITEM_EMFA, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM4AV,      318, 0xff, ITEM_EMRI, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM4AV + 34, 318, 0xff, ITEM_EMFA, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM5AV,      318, 0xff, ITEM_EMRI, 0xFF);
  DPY_LINEH(DPYMAH + 1, DPYM5AV + 34, 318, 0xff, ITEM_EMFA, 0xFF);

  DpyString_draw(DPYPOS(DPYMHH,DPYMHV), MenuHead[MenuNum], HEAD_TXT, 0); 

  DpyString_draw(DPYPOS(DPYMHH,DPYM1IV), MenuItemHead[MenuNum][0], ITEM_TXT, 0);
  DpyString_draw(DPYPOS(DPYMHH,DPYM2IV), MenuItemHead[MenuNum][1], ITEM_TXT, 0);
  DpyString_draw(DPYPOS(DPYMHH,DPYM3IV), MenuItemHead[MenuNum][2], ITEM_TXT, 0);
  DpyString_draw(DPYPOS(DPYMHH,DPYM4IV), MenuItemHead[MenuNum][3], ITEM_TXT, 0);
  DpyString_draw(DPYPOS(DPYMHH,DPYM5IV), MenuItemHead[MenuNum][4], ITEM_TXT, 0);

  MenuValue_disp[MenuNum][0]();
  MenuValue_disp[MenuNum][1]();
  MenuValue_disp[MenuNum][2]();
  MenuValue_disp[MenuNum][3]();
  MenuValue_disp[MenuNum][4]();  
}

/*!*****************************************************************************
 @brief		Menu Head Depress
 @details	���������� ���������� ������ ����
 @return	
 @note		
 */
void MenuHeadDepr_disp(void) {
  if (GenCtrl.Menu) {
    DPY_LINEH(DPYMAH + 1, DPYMAV +  1, 318, 0xff, HEAD_EMRI, 0xFF);
    DPY_LINEH(DPYMAH + 1, DPYMAV + 24, 318, 0xff, HEAD_EMFA, 0xFF);
  }
}

/*!*****************************************************************************
 @brief		Draw Help
 @details	���������� ������
 @return	
 @note		
 */
void Help_draw(void) {
  DPY_RECT(DPYWAH, DPYWAV, DPYWAH + 250, DPYWAV + 200, 0xFF, HEAD_BKG);
}

/*!*****************************************************************************
 @brief		Clear Help MENU
 @details	�������� ������ ����, ���� ��� ��������
 @return	
 @note		������������ ��� ����� � ����
 */
void HelpMenu_clear(void) {
  if (DispCtrl.HelpEna) {		// ���� ���� ������ ����
//    Gen.Help = 0;
    // DPY_ClearScreen();		// �������� ���� �����
    //		����� ����� ������������ ������ ���������
    DpyWork_blank();
  }
  // else
  DpyMenu_blank();			// �������� ������ ����
  TrigLev_draw(true);
}

/*!*****************************************************************************
 @brief		Off/On Draw
 @details	���������� ���� / ��� (�� ����)
 @param		pDpy - ��������� �� ������ ����������
 @param		OffOn - 1 ���, 0 ����
 @return	
 @note	
 */
void DpyOffOn_draw(uint8_t *pDpy, bool On) {
  static const uint8_t *OffTxt = "����";
  static const uint8_t *OnTxt  = "\x98���";
  if (!On) {
    DpyRoRect_fill(pDpy, 28, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 320 * 3 + 1, OffTxt, VON_TXT, 0);
    DpyRect_fill(pDpy + 28, 28, 14, 0xFF << 8 | VOFF_BKG);
    DpyString_draw(pDpy + 320 * 3 + 31, OnTxt, VOFF_TXT, 0);
  }
  else {
    DpyRect_fill(pDpy, 28, 14, 0xFF << 8 | VOFF_BKG);
    DpyString_draw(pDpy + 320 * 3 + 1, OffTxt, VOFF_TXT, 0);
    DpyRoRect_fill(pDpy + 28, 28, 14, 0xFF << 8 | VON_BKG);
    DpyString_draw(pDpy + 320 * 3 + 31, OnTxt, VON_TXT, 0);
  }
}

/*!*****************************************************************************
 @brief		SETTING & Rotor Draw
 @details	���������� ��������� (_)
 @param		pDpy - ��������� �� ������ ����������
 @param		On - 1 ���, 0 ����
 @return	
 @note	
 */
void DpySetting_draw(uint8_t *pDpy, bool On) {
  static const uint8_t *Set = "�������";
  DpyString_draw(pDpy + 320 * 3, Set, VOFF_TXT, false);
  if (On)  DpyRoRect_fill(pDpy + 43, 14, 14, 0xFF << 8 | VON_BKG);
  else DpyRect_fill(pDpy + 43, 14, 14, 0xFF << 8 | VOFF_BKG);
  DpySpec_draw(pDpy + 46 + 320 * 1, SS_ROTR, 0xFF, VON_TXT);     
}

/*!*****************************************************************************
 @brief		Rotor Draw
 @details	���������� (_)
 @param		pDpy - ��������� �� ������ ����������
 @param		OffOn
 @return	
 @note	
 */
void DpyRotor_draw(uint8_t *pDpy, bool On) {
  if (On)  DpyRoRect_fill(pDpy, 14, 14, 0xFF << 8 | VON_BKG);
  else	   DpyRect_fill  (pDpy, 14, 14, 0xFF << 8 | VOFF_BKG);
  DpySpec_draw(pDpy + 3 + 320 * 1, SS_ROTR, 0xFF, VON_TXT);     
}

/*!*****************************************************************************
 @brief		Vertical Digits Bar Display
 @details	
 @return	
 @note	
 */
void DigitBar_disp(void) {
  DpyString_draw(DPYPOS(10, 4 + 15 *  0), "00", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  1), "10", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  2), "20", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  3), "30", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  4), "40", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  5), "50", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  6), "60", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  7), "70", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  8), "80", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 *  9), "90", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 * 10), "A0", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 * 11), "B0", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 * 12), "C0", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 * 13), "D0", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 * 14), "E0", WHITE_ON_BLACK, 1);
  DpyString_draw(DPYPOS(10, 4 + 15 * 15), "F0", WHITE_ON_BLACK, 1);
}

/*!*****************************************************************************
 @brief		32-bit Integer with sign convert to ASCII decimal
 @details	32-������� ����� �� ������ ������������� � ������ \n
 @details	������ ������: " ... 0", " ...+1", " ...-32767", "-2147483647"
 @param		numb - �����
 @param		str - ��������� �� ������-����� (12 ������)
 @return	
 */
void itoad_conv(int32_t numb, uint8_t *str) {
  *(uint32_t *)(str)   = 0x20202020;
  *(uint32_t *)(str + 4) = 0x20202020;    
  *(uint32_t *)(str + 8) = 0x00302020;
  str += 10;
  uint8_t  sign = '+';
  if (!numb) return;
  if (numb < 0) { numb = -numb; sign = '-'; }
  do { *str-- = numb % 10 + '0'; } while (numb /= 10);
  *str = sign;
}

/*!*****************************************************************************
 @brief		32-bit Integer convert to ASCII hexadecimal
 @details	32-������� ����������� ����� ������������� � ������
 @param		numb - �����
 @param		str - ��������� �� ������-�����
 @return	
 */
void itoah_conv(uint32_t numb, uint8_t *str) {
  for (int32_t i = 8; i > 0; i--) {
    uint8_t dig = (numb & 0xF0000000)>>28;
    dig += (dig < 10)? 0x30 : 0x37;
    *str++ = dig;
    numb <<= 4;
  }
}




/*! @} */

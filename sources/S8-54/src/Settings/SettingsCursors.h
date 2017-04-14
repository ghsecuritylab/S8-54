#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Settings
 *  @{
 *  @defgroup SettingsCursors Settings Cursors
 *  @{
 */

#define CURSORS_SHOW_FREQ   (set.cursors.showFreq)
#define CURS_MOVE_PERCENTS  (set.cursors.movement == CursMovement_Percents)

#define CURS_SOURCE         (set.cursors.source)
#define CURS_SOURCE_A       (CURS_SOURCE == A)
#define CURS_SOURCE_B       (CURS_SOURCE == B)

#define CURsU_CNTRL_CH(ch)  (set.cursors.cntrlU[ch])
#define CURsU_CNTRL         (CURsU_CNTRL_CH(CURS_SOURCE))
#define CURsU_CNTRL_1       (CURsU_CNTRL == CursCntrl_1)
#define CURsU_CNTRL_2       (CURsU_CNTRL == CursCntrl_2)
#define CURsU_CNTRL_1_2     (CURsU_CNTRL == CursCntrl_1_2)
#define CURsU_DISABLED      (CURsU_CNTRL == CursCntrl_Disable)
#define CURsU_ENABLED       (!CURsU_DISABLED)

#define CURsT_CNTRL_CH(ch)  (set.cursors.cntrlT[ch])
#define CURsT_CNTRL         (CURsT_CNTRL_CH(CURS_SOURCE))
#define CURsT_CNTRL_1       (CURsT_CNTRL == CursCntrl_1)
#define CURsT_CNTRL_2       (CURsT_CNTRL == CursCntrl_2)
#define CURsT_CNTRL_1_2     (CURsT_CNTRL == CursCntrl_1_2)
#define CURsT_DISABLED      (CURsT_CNTRL == CursCntrl_Disable)
#define CURsT_ENABLED       (!CURsT_DISABLED)

#define CURsU_POS(ch, num)  (set.cursors.posCurU[ch][num])
#define CURsT_POS(ch, num)  (set.cursors.posCurT[ch][num])

#define dUperc(ch)          (set.cursors.deltaU100percents[ch])
#define dTperc(ch)          (set.cursors.deltaT100percents[ch])

#define CURS_ACTIVE         (set.cursors.active)
#define CURS_ACTIVE_U       (CURS_ACTIVE == CursActive_U)
#define CURS_ACTIVE_T       (CURS_ACTIVE == CursActive_T)

#define CURS_LOOK_U(numCur) (set.cursors.lookMode[numCur] == CursLookMode_Voltage)
#define CURS_LOOK_T(numCur) (set.cursors.lookMode[numCur] == CursLookMode_Time)
#define CURS_LOOK_BOTH(numCur) (set.cursors.lookMode[numCur] == CursLookMode_Both)


 /// �������� ������� ������� ����������
float sCursors_GetCursPosU(Channel ch, int numCur);
/// ���������� true,���� ����� �������� �������
bool  sCursors_NecessaryDrawCursors(void);
/// �������� ������ ������� ����������
const char* sCursors_GetCursVoltage(Channel source, int numCur, char buffer[20]);
/// �������� ������ ������� �������
const char* sCursors_GetCursorTime(Channel source, int numCur, char buffer[20]);
/// �������� ������ ��������� �������� ����������
const char* sCursors_GetCursorPercentsU(Channel source, char buffer[20]);
/// �������� ������ ��������� �������� �������
const char* sCursors_GetCursorPercentsT(Channel source, char buffer[20]);

/** @}  @}
 */

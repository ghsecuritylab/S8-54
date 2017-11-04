#pragma once
#include "MenuItems.h"
#include "Panel/Controls.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Menu
 *  @{
 *  @defgroup MenuFunctions Menu Functions
 *  @brief ��������������� ������� ��� ������ � ����
 *  @{
 */

/// ���������� true, ���� ������� ���� item �������� �������, �.�. ����� ���� �����
bool ItemIsAcitve(const void *item);
/// ���������� ��� �������� ���� �� ������ address
TypeItem TypeMenuItem(const void *address);
/// ���������� ��� ��������� �������� ����
TypeItem TypeOpenedItem(void);
/// ���������� ����� ��������� �������� ����
void *OpenedItem(void);
/// ���������� ����� �������� �������� ���� (�������, ��� �������, �������� �������, ������ �������� ���� ������ ���������
void *CurrentItem(void);
/// ���������� true, ���� ������� ������� �������� � ������ namePage ������
bool CurrentItemIsOpened(NamePage namePage);
/// �������/��������� ������� ����� ��������
void SetCurrentItem(const void *item,               ///< ����� ��������, ���������� �������� ����� ����������/�����
                    bool active                     ///< true - ������� ������� �������, false - ��������� ������� �������. � ���� ������ ������� ���������� ��������� ��������
                    );
/// ���������� ����� ��������, �������� ����������� ������� �� ������ item
Page *Keeper(const void *item);

NamePage GetNameOpenedPage(void);

bool ChangeOpenedItem(void *item, int delta);
/// ��������� ��� ����������� �������� Governor, GovernorColor ��� Choice �� ������ item � ����������� �� ����� delta
void ChangeItem(void *item, int delta);
/// ���������� ������ � �������� ��������� �������� Choice ��� NamePage �� ������ item
int HeightOpenedItem(void *item);
/// ���������� �������� �������� �� ������ item, ��� ��� �������� �� ������� �������
const char *TitleItem(void *item);
/// ���������� true, ���� button - �������������� ������� [1..5]
bool IsFunctionalButton(PanelButton button);
/// ������� �������� ������� ����
void CloseOpenedItem(void);
/// �������/������� ������� ���� �� ������ item
void OpenItem(const void *item, bool open);
/// ���������� true, ���� ������� ���� �� ������ item ������
bool ItemIsOpened(const void *item);

Page *PagePointerFromName(NamePage namePage);

bool IsPageSB(const void *item);

void CallFuncOnPressButton(void *button);

/** @}
 */

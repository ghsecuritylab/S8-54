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
/// ���������� ������� �������� �������� ������� page
int8 PosCurrentItem(const Page *page);
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
/// ���������� ��� �������� ������ �������� choice � ������� i ��� ��� �������� � �������� ���� ���������
const char *NameSubItem(Choice *choice, int i);

/// ���������� ������ � �������� ��������� �������� Choice ��� NamePage �� ������ item
int HeightOpenedItem(void *item);
/// ���������� �������� �������� �� ������ item, ��� ��� �������� �� ������� �������
const char *TitleItem(void *item);
/// ���������� ������� ������� �������� �������� �� ������ page �� ������. ���� ������� ����������� 0, ��� ����� 0, ���� ������� ����������� 1, ��� ����� 5 � �.�.
int PosItemOnTop(Page *page);
/// ���������� true, ���� button - �������������� ������� [1..5]
bool IsFunctionalButton(PanelButton button);
/// ������� �������� ������� ����
void CloseOpenedItem(void);
/// �������/������� ������� ���� �� ������ item
void OpenItem(const void *item, bool open);
/// ���������� true, ���� ������� ���� �� ������ item ������
bool ItemIsOpened(const void *item);

void ChangeSubPage(const Page *page, int delta);
/// �������� ������� ��������� ������� ������ ��� ������ numItem �������� page
void ShortPressOnPageItem(Page *page, int numItem);

Page *PagePointerFromName(NamePage namePage);

bool IsPageSB(const void *item);

void CallFuncOnPressButton(void *button);

/** @}
 */

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

/// ���������� ���������� ��������� ������ � �������� �� ������ choice
int Choice_NumSubItems(Choice *choice);
/// ���������� true, ���� ������� ���� item �������� �������, �.�. ����� ���� �����
bool ItemIsAcitve(const void *item);
/// ���������� ���������� ��������� � �������� �� ������ page
int NumItemsInPage(const Page * const page);
/// ���������� ����� ������� ���������� �������� �� ������ page
int NumCurrentSubPage(Page *page);
/// D��������� ����� ���������� � �������� �� ������ page
int NumSubPages(const Page *page);
/// ���������� ��� �������� ���� �� ������ address
TypeItem TypeMenuItem(const void *address);
/// ���������� ��� ��������� �������� ����
TypeItem TypeOpenedItem(void);
/// ���������� ����� ��������� �������� ����
void *OpenedItem(void);
/// ���������� ����� �������� �������� ���� (�������, ��� �������, �������� �������, ������ �������� ���� ������ ���������
void *CurrentItem(void);
/// ���������� ����� �������� ���� �������� ��������
void *Item(const Page *page,                        ///< ��������, ������� ������� ����� ������
            int numElement                          ///< ���������� ����� ��������, ������� ����� ������
            );
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
/// ���������� ��� �������� page
NamePage GetNamePage(const Page *page);

NamePage GetNameOpenedPage(void);

bool ChangeOpenedItem(void *item, int delta);
/// ��������� ��� ����������� �������� Governor, GovernorColor ��� Choice �� ������ item � ����������� �� ����� delta
void ChangeItem(void *item, int delta);
/// ���������� ��� �������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
const char *NameCurrentSubItem(Choice *choice);
/// ���������� ��� �������� ������ �������� choice � ������� i ��� ��� �������� � �������� ���� ���������
const char *NameSubItem(Choice *choice, int i);
/// ���������� ��� ���������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
const char *NameNextSubItem(Choice *choice);

const char *NamePrevSubItem(Choice *choice);
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

SButton* SmallButonFromPage(Page *page, int numButton);

void CallFuncOnPressButton(void *button);

void CallFuncOnDrawButton(Button *button, int x, int y);

/** @}
 */

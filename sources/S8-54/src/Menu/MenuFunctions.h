#pragma once

#include "MenuItems.h"
#include "Panel/Controls.h"


int Choice_NumSubItems(Choice *choice);                         // ���������� ���������� ��������� ������ � �������� �� ������ choice.

bool            ItemIsAcitve(void *item);                       // ���������� true, ���� ������� ���� item �������� �������, �.�. ����� ���� �����.
int             NumItemsInPage(const Page * const page);        // ���������� ���������� ��������� � �������� �� ������ page.
int             NumCurrentSubPage(Page *page);                  // ���������� ����� ������� ���������� �������� �� ������ page.
int             NumSubPages(const Page *page);                  // D��������� ����� ���������� � �������� �� ������ page.
TypeItem        TypeMenuItem(const void *address);              // ���������� ��� �������� ���� �� ������ address.
TypeItem        TypeOpenedItem(void);                           // ���������� ��� ��������� �������� ����.
void*           OpenedItem(void);                               // ���������� ����� ��������� �������� ����.
void*           CurrentItem(void);                              // ���������� ����� �������� �������� ���� (�������, ��� �������, �������� �������, ������ �������� ���� ������ ���������.
void*           Item                                            // ���������� ����� �������� ���� �������� ��������.
                     (const Page *page,                         // ��������, ������� ������� ����� ������
                     int numElement                             // ���������� ����� ��������, ������� ����� ������
                     );
bool            CurrentItemIsOpened(NamePage namePage);         // ���������� true, ���� ������� ������� �������� � ������ namePage ������.
int8            PosCurrentItem(const Page *page);               // ���������� ������� �������� �������� ������� page.
void            SetCurrentItem                                  // �������/��������� ������� ����� ��������.
                                (const void *item,              // ����� ��������, ���������� �������� ����� ����������/�����
                                bool active                     // true - ������� ������� �������, false - ��������� ������� �������. � ���� ������ ������� ���������� ��������� ��������
                                );
Page*           Keeper(const void *item);                       // ���������� ����� ��������, �������� ����������� ������� �� ������ item.
NamePage        GetNamePage(const Page *page);                  // ���������� ��� �������� page.
NamePage        GetNameOpenedPage(void);
void            OpenPageAndSetItCurrent(NamePage namePage);
bool            ChangeOpenedItem(void *item, int delta);
void            ChangeItem(void *item, int delta);              // ��������� ��� ����������� �������� Governor, GovernorColor ��� Choice �� ������ item � ����������� �� ����� delta
const char*     NameCurrentSubItem(Choice *choice);             // ���������� ��� �������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������.
const char*     NameSubItem(Choice *choice, int i);             // ���������� ��� �������� ������ �������� choice � ������� i ��� ��� �������� � �������� ���� ���������.
const char*     NameNextSubItem(Choice *choice);                // ���������� ��� ���������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������.
const char*     NamePrevSubItem(Choice *choice);
int             HeightOpenedItem(void *item);                   // ���������� ������ � �������� ��������� �������� Choice ��� NamePage �� ������ item.
const char*     TitleItem(void *item);                          // ���������� �������� �������� �� ������ item, ��� ��� �������� �� ������� �������.
int             PosItemOnTop(Page *page);                       // ���������� ������� ������� �������� �������� �� ������ page �� ������. ���� ������� ����������� 0, ��� ����� 0, ���� ������� ����������� 1, ��� ����� 5 � �.�.
bool            IsFunctionalButton(PanelButton button);         // ���������� true, ���� button - �������������� ������� [1..5].
void            CloseOpenedItem(void);                          // ������� �������� ������� ����.
void            OpenItem(const void *item, bool open);          // �������/������� ������� ���� �� ������ item.
bool            ItemIsOpened(void *item);                       // ���������� true, ���� ������� ���� �� ������ item ������.
void            ChangeSubPage(const Page *page, int delta);
void            PrintStatePage(Page *page);
void            ShortPressOnPageItem(Page *page, int numItem);  // �������� ������� ��������� ������� ������ ��� ������ numItem �������� page;
Page*           PagePointerFromName(NamePage namePage);
bool            IsPageSB(const void *item);
SmallButton*    SmallButonFromPage(Page *page, int numButton);
void            CallFuncOnPressButton(void *button);
void            CallFuncOnDrawButton(Button *button, int x, int y);

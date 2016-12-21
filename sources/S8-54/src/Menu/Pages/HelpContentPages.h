#pragma once


typedef enum
{
    TypePage_Content,       // �� ���� �������� ����������� ������ �� ������ ��������
    TypePage_Description    // �� ���� �������� ��� ������, ������ ��������
} TypePageHelp;


#define MAX_PAGES 3


typedef struct  
{
    TypePageHelp    type;
    void*           parent;             // ����� ������������ ��������
    char*           title[2];           // �������� ��������
    void*           pages[MAX_PAGES];   // ������ �������� ������ ��������� ������� � ������ TypePage_Content
    char*           content[2];         // ����� ���������� �������� � ������ TypePage_Description
} PageHelp;

extern const PageHelp helpMenu;

static const PageHelp helpMenuCommon =
{
    TypePage_Description,
    (void*)&helpMenu,
    {
        "����� �������� ��������� ����",
        "General description of the principles of the menu"
    },
    {0},
    {
        "������ �� ������ ���������� ����� ��� ���� ������� - ��������, ������������� ����� 0.5 ��� � �������, ������������� ����� 0.5 ���. "
        "���� ������������ ����� ����������� ��������� ���������. "
        "������� �������� ���� ����������� �������� ���� ������� �������� ������ ����. "
        "�� ���� ��������� ������� �������� ������� ���������������� ������ � ������� ������� ����� �� ������ �� ������ ����������:\n"
        "\"�������\" - �������\n"
        "\"����� 1\" - ����� 1\n"
        "\"����� 2\" - ����� 2\n"
        "\"�����.\" - �����\n"
        "\"����E����\" - ����\n"
        "\"�������\" - �������\n"
        "\"������\" - ������\n"
        "\"���������\" - �����\n"
        "\"������\" - ������\n"
        "\"������\" - ������\n"
        "� ������ �������� ������� �������� ������� ��������� ��������������� ���������"
        ,
        ""
    }
};

static const PageHelp helpMenuControls =
{
    TypePage_Description,
    (void*)&helpMenu,
    {
        "�������� ������� �����������",
        "Description of the controls"
    },
    {0},
    {
        "",
        ""
    }
};

extern const PageHelp helpMain;

static const PageHelp helpSCPI =
{
    TypePage_Description,
    (void*)&helpMain,
    {
        "������ � SCPI",
        "Working with SCPI"
    },
    {0},
    {
        "",
        ""
    }
};

const PageHelp helpMenu =
{
    TypePage_Content,
    (void*)&helpMain,
    {
        "������ � ����",
        "Working with menus"
    },
    {
        (void*)&helpMenuCommon,
        (void*)&helpMenuControls
    }
};

const PageHelp helpMain =
{
    TypePage_Content,
    0,
    {
        "������",
        "HELP"
    },
    {
        (void*)&helpMenu,
        (void*)&helpSCPI
    }
};

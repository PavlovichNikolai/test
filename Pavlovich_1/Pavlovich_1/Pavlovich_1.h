
// Pavlovich_1.h : ������� ���� ��������� ��� ���������� Pavlovich_1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CPavlovich_1App:
// � ���������� ������� ������ ��. Pavlovich_1.cpp
//

class CPavlovich_1App : public CWinAppEx
{
public:
	CPavlovich_1App();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPavlovich_1App theApp;

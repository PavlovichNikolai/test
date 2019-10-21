
// Pavlovich_1.h : главный файл заголовка для приложения Pavlovich_1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CPavlovich_1App:
// О реализации данного класса см. Pavlovich_1.cpp
//

class CPavlovich_1App : public CWinAppEx
{
public:
	CPavlovich_1App();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPavlovich_1App theApp;

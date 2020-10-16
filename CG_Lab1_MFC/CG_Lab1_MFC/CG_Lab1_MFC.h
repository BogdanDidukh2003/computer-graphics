
// CG_Lab1_MFC.h : main header file for the CG_Lab1_MFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCGLab1MFCApp:
// See CG_Lab1_MFC.cpp for the implementation of this class
//

class CCGLab1MFCApp : public CWinAppEx
{
public:
	CCGLab1MFCApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCGLab1MFCApp theApp;

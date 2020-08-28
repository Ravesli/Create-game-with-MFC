
// SameGame.h : main header file for the SameGame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSameGameApp:
// See SameGame.cpp for the implementation of this class
//

class CSameGameApp : public CWinApp
{
public:
	CSameGameApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSameGameApp theApp;

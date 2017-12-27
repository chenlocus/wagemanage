// wagemanage.h : wagemanage 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h” 
#endif

#include "resource.h"       // 主符号


// CwagemanageApp:
// 有关此类的实现，请参阅 wagemanage.cpp
//

class CwagemanageApp : public CWinApp
{
public:
	CwagemanageApp();


// 重写
public:
	virtual BOOL InitInstance();
	CDialog * m_pMiddle;

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnProjectInput();
	afx_msg void OnFileNew();
};

extern CwagemanageApp theApp;

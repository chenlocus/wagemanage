// wagemanage.h : wagemanage Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CwagemanageApp:
// �йش����ʵ�֣������ wagemanage.cpp
//

class CwagemanageApp : public CWinApp
{
public:
	CwagemanageApp();


// ��д
public:
	virtual BOOL InitInstance();
	CDialog * m_pMiddle;

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnProjectInput();
	afx_msg void OnFileNew();
};

extern CwagemanageApp theApp;

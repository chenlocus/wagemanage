// MainFrm.h : CMainFrame ��Ľӿ�
//
#include "wrkldstatDlg.h"
#include "wagestaDlg.h"

#pragma once
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	CWageStaDlg  * pWageStaDlg;
	CWrkldStatDlg *pWrkldStatDlg;

public:
	afx_msg void OnWorkloadInput();
	afx_msg void OnGrczmxb();
	afx_msg void OnTotalWage();
	afx_msg void OnTypeInput();
	afx_msg void OnNameInput();
	afx_msg void OnProjectInput();
	afx_msg void OnDepartinfo();
	afx_msg void OnHisdataSave();
	afx_msg void OnHisdataClear();
};



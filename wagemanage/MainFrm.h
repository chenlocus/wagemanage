// MainFrm.h : CMainFrame 类的接口
//
#include "wrkldstatDlg.h"
#include "wagestaDlg.h"

#pragma once
class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// 生成的消息映射函数
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



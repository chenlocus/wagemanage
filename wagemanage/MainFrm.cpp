// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "wagemanage.h"
#include "WorkLoadDlg.h"
#include "MainFrm.h"
#include ".\mainfrm.h"
#include "nameinputdlg.h"
#include "subworkpricedlg.h"
#include "TypeInputDlg.h"
#include "departmentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_WORKLOAD_INPUT, OnWorkloadInput)
	ON_COMMAND(ID_GRCZMXB, OnGrczmxb)
	ON_COMMAND(ID_TOTAL_WAGE, OnTotalWage)
	ON_COMMAND(ID_TYPE_INPUT, OnTypeInput)
	ON_COMMAND(ID_NAME_INPUT, OnNameInput)
	ON_COMMAND(ID_PROJECT_INPUT, OnProjectInput)
	ON_COMMAND(ID_DEPARTINFO, OnDepartinfo)
	ON_COMMAND(ID_HISDATA_SAVE, OnHisdataSave)
	ON_COMMAND(ID_HISDATA_CLEAR, OnHisdataClear)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	pWageStaDlg =NULL;
	pWrkldStatDlg=NULL;
}

CMainFrame::~CMainFrame()
{
	delete pWageStaDlg;
	delete pWrkldStatDlg;
	pWageStaDlg =NULL;
	pWrkldStatDlg=NULL;

}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	// TODO: 如果不需要工具栏可停靠，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序


void CMainFrame::OnWorkloadInput()
{
	// TODO: 在此添加命令处理程序代码
	CWorkLoadDlg dlg;
	dlg.DoModal();

}

void CMainFrame::OnGrczmxb()
{
	if (NULL==pWrkldStatDlg)
	{
		pWrkldStatDlg= new CWrkldStatDlg(this);
		pWrkldStatDlg->Create(IDD_TOTAL_PRDUCTION_DLG);
	}
	pWrkldStatDlg->ShowWindow(SW_NORMAL);
}

void CMainFrame::OnTotalWage()
{
	// TODO: 在此添加命令处理程序代码
	if (NULL ==pWageStaDlg)
	{
		pWageStaDlg =new CWageStaDlg(this);
		pWageStaDlg->Create(IDD_WAGE_TOTAL_DLG);
	}
	pWageStaDlg->ShowWindow(SW_NORMAL);

}

void CMainFrame::OnTypeInput()
{
	// TODO: 在此添加命令处理程序代码
	CSubworkPriceDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnNameInput()
{
	// TODO: 在此添加命令处理程序代码
	CNameInputDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnProjectInput()
{
	// TODO: 在此添加命令处理程序代码
	CTypeInputDlg dlg;
	dlg.DoModal();

}

void CMainFrame::OnDepartinfo()
{
	// TODO: 在此添加命令处理程序代码
	CDepartmentDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnHisdataSave()
{
	// TODO: 在此添加命令处理程序代码
	char cPath[MAX_PATH];
	CString szPath("");
	CString strOldFile;
	CString strNewFile;
	CString strDate;
	::GetModuleFileName(NULL, cPath, MAX_PATH);
	szPath = cPath;
	int pos = szPath.ReverseFind('\\');
	szPath = szPath.Left(pos+1);
	strOldFile.Format("%swage_manage.mdb", szPath);

	CTime timeTmp=CTime::GetCurrentTime();
	strDate=timeTmp.Format("%Y");
	szPath +="history\\";
	strNewFile.Format("%swage_manage%s.mdb",szPath,strDate);
	CopyFile(strOldFile,strNewFile,0);
	CString strMessage;
	strMessage.Format("历史数据已经保存为%s",strNewFile);
	AfxMessageBox(strMessage);

}

void CMainFrame::OnHisdataClear()
{
	// TODO: 在此添加命令处理程序代码
	char cPath[MAX_PATH];
	CString szPath("");
	CString strOldFile;
	CString strNewFile;
	CString strDate;
	::GetModuleFileName(NULL, cPath, MAX_PATH);
	szPath = cPath;
	int pos = szPath.ReverseFind('\\');
	szPath = szPath.Left(pos+1);
	strOldFile.Format("%swage_manage.mdb", szPath);
	DeleteFile(strOldFile);
	
	strNewFile.Format("%sempty_wage_manage.mdb", szPath);
	CopyFile(strNewFile,strOldFile,0);
	AfxMessageBox("当前数据已经清空！");


}

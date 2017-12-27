// wagemanageView.cpp : CwagemanageView 类的实现
//

#include "stdafx.h"
#include "wagemanage.h"

#include "wagemanageDoc.h"
#include "wagemanageView.h"
#include ".\wagestadlg.h"
#include ".\wrkldstatdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwagemanageView

IMPLEMENT_DYNCREATE(CwagemanageView, CView)

BEGIN_MESSAGE_MAP(CwagemanageView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CwagemanageView 构造/析构

CwagemanageView::CwagemanageView()
{
	// TODO: 在此处添加构造代码

}

CwagemanageView::~CwagemanageView()
{
}

BOOL CwagemanageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CwagemanageView 绘制

void CwagemanageView::OnDraw(CDC* pDC)
{
	CwagemanageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CwagemanageApp* app=(CwagemanageApp*)AfxGetApp();
	CRect rectClient;
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int	cw=tm.tmMaxCharWidth;
	int	ch=tm.tmHeight;
	bool bl=pDC->IsPrinting();
	if(bl)//pDC->IsPrinting()
	{
		pDC->SetMapMode(MM_TEXT);
		SIZE CurOrg;
		CurOrg.cx=0;
		CurOrg.cy=0;

		//打印区域的宽度和高度
		SIZE CurRegion;
		CurRegion.cx=0;//m_psd.ptPaperSize.x-
		CurRegion.cy=0;//m_psd.ptPaperSize.y-
		pDC->HIMETRICtoDP(&CurOrg);
		pDC->HIMETRICtoDP(&CurRegion);
		CurRegion.cx=pDC->GetDeviceCaps(HORZRES)-CurRegion.cx;
		CurRegion.cy=pDC->GetDeviceCaps(VERTRES)-CurRegion.cy;
		CString s;
		CString strTemp;
		CRect rect;
		rect.SetRect(CurOrg.cx,CurOrg.cy,CurRegion.cx,CurRegion.cy);
		CRgn rgn;
		rgn.CreateRectRgnIndirect(&rect);
		CBrush Brugreen;
		Brugreen.CreateSolidBrush(RGB(0,0,0));
		pDC->FrameRgn(&rgn,&Brugreen,5,5);
		rgn.DeleteObject();
		LOGFONT lf;
		::GetObject(GetCurrentObject(pDC->GetSafeHdc(),OBJ_FONT),sizeof(LOGFONT),&lf);
		lf.lfHeight=ch*20/16;
		lf.lfWidth=cw*26/25;
		lf.lfWeight=FW_BLACK;

		CFont ft,*pOldFont;
		ft.CreateFontIndirect(&lf);
		pOldFont=pDC->SelectObject(&ft);
		
		if (app->m_pMiddle->IsKindOf(RUNTIME_CLASS(CWageStaDlg)))
		{
			CWageStaDlg *pDlg = (CWageStaDlg*)(app->m_pMiddle);
			char* chr = s.GetBuffer(20);
			//app->m_pMiddle->m_cMonth.GetWindowText(chr,20);
			//s=chr;
			////size=pDC->GetOutputTabbedTextExtent(s,0,NULL);
			//size=pDC->GetOutputTextExtent(s);
			pDC->SetTextAlign(TA_CENTER);
			strTemp = "月个人总工资报表";

			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+50,strTemp);


			pDC->SetTextAlign(TA_LEFT);
			pDC->SelectObject(pOldFont);
			ft.DeleteObject();
			CString strMonth=pDlg->m_date.Format("%Y-%m");
			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+200,strMonth);

			CHeaderCtrl*   pHeaderCtrl   = pDlg->m_list.GetHeaderCtrl();//m_list是你的列表控件； 
			int nColumnCount  =  pHeaderCtrl->GetItemCount();   //microsoft的bug

		    
			int interval_x =CurRegion.cx/nColumnCount;
			
			int interval_y =110;

			

			/*for (int iCol=1;iCol<nColumnCount;iCol++)
			{
				HDITEM pCol;
				pHeaderCtrl->GetItem(iCol,&pCol);
				strTemp =pCol.pszText;
				pDC->TextOut(CurOrg.cx+100+interval_x*iCol,CurOrg.cy/2+300,pCol.pszText);
			}*/
			
			//打印标题栏
			for (int j=0;j<nColumnCount;j++)
			{
				strTemp = pDlg->strCaption.GetAt(j);
				pDC->TextOut(CurOrg.cx+100+interval_x*j,CurOrg.cy/2+380,strTemp);

			}
			pDC->MoveTo(CurOrg.cx+90,CurOrg.cy/2+370);
			pDC->LineTo(CurOrg.cx+interval_x*nColumnCount-30,CurOrg.cy/2+370);

			//打印内容
			for (int i =1; i<pDlg->m_list.GetItemCount()+1;i++)
			{
				for (int j=0;j<nColumnCount;j++)
				{
					strTemp = pDlg->m_list.GetItemText(i-1,j);
					pDC->TextOut(CurOrg.cx+100+interval_x*j,CurOrg.cy/2+380+i*interval_y,strTemp);

				}
				pDC->MoveTo(CurOrg.cx+90,CurOrg.cy/2+370+i*interval_y);
				pDC->LineTo(CurOrg.cx+interval_x*nColumnCount-30,CurOrg.cy/2+370+i*interval_y);
			}
			//最后一横
			pDC->MoveTo(CurOrg.cx+90,CurOrg.cy/2+370+i*interval_y);
			pDC->LineTo(CurOrg.cx+interval_x*nColumnCount-30,CurOrg.cy/2+370+i*interval_y);
			
			int temp =interval_y*(pDlg->m_list.GetItemCount()+1);
			for (int j=0; j<nColumnCount;j++)
			{
				pDC->MoveTo(CurOrg.cx+90+interval_x*j,CurOrg.cy/2+370);
				pDC->LineTo(CurOrg.cx+90+interval_x*j,CurOrg.cy/2+370+temp);
			}
			//最后一竖
			pDC->MoveTo(CurOrg.cx+interval_x*nColumnCount-30,CurOrg.cy/2+370);
			pDC->LineTo(CurOrg.cx+interval_x*nColumnCount-30,CurOrg.cy/2+370+temp);

		}

		if (app->m_pMiddle->IsKindOf(RUNTIME_CLASS(CWrkldStatDlg)))
		{
			CWrkldStatDlg *pDlg = (CWrkldStatDlg*)(app->m_pMiddle);
			char* chr = s.GetBuffer(20);
			//app->m_pMiddle->m_cMonth.GetWindowText(chr,20);
			//s=chr;
			////size=pDC->GetOutputTabbedTextExtent(s,0,NULL);
			//size=pDC->GetOutputTextExtent(s);
			pDC->SetTextAlign(TA_CENTER);
			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+50,"月个人产值明细表");

			pDC->SelectObject(pOldFont);
			ft.DeleteObject();
			CString strType;
			pDlg->m_type.GetLBText(pDlg->m_type.GetCurSel(),strType);
			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+180,_T("项目编号： ")+strType);
			CString strMonth=pDlg->m_date.Format("%Y-%m");
			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+250,strMonth);

			//CHeaderCtrl*   pHeaderCtrl   = pDlg->m_list.GetHeaderCtrl();//m_list是你的列表控件； 
			//int nColumnCount  =  pHeaderCtrl->GetItemCount();   //microsoft的bug
			pDC->SetTextAlign(TA_LEFT);
			int interval_x1 =CurOrg.cx+100;
			int interval_x2 =CurOrg.cx+100+400;
			int interval_x3 =CurRegion.cx-400;
			int interval_x_internal;
			int start_y = CurOrg.cy/2+400;
			int interval_y =110;

			CString strTemp;
			
			//打印标题栏
			pDC->TextOut(interval_x1,start_y,_T("姓名"));
			pDC->TextOut(interval_x2,start_y,_T("单个工序工作量"));
			pDC->TextOut(interval_x3,start_y,_T("工分累计"));
			
			

			pDC->MoveTo(interval_x1-20,start_y-20);
			pDC->LineTo(CurRegion.cx-30,start_y-20);
			
			int iCount = pDlg->m_list.GetItemCount();
			//打印内容
			for (int i =0; i<iCount-1;i++)
			{
				interval_x_internal = interval_x2;
				//print name 
				strTemp = pDlg->m_list.GetItemText(i,0);
				pDC->TextOut(interval_x1,start_y+(i+1)*interval_y,strTemp);
				
				//print working load information
				for (int j=0;j<pDlg->m_strCaption.GetCount();j++)
				{
					strTemp = pDlg->m_list.GetItemText(i,j+1);
					if (atoi(strTemp)!=0)
					{
						strTemp = pDlg->m_strCaption.GetAt(j)+" "+strTemp;
						pDC->TextOut(interval_x_internal+10,start_y+(i+1)*interval_y,strTemp);
						interval_x_internal = interval_x_internal+450+10;
					}

				}
				//print total information
				strTemp = pDlg->m_list.GetItemText(i,pDlg->m_strCaption.GetCount()+1);
				pDC->TextOut(interval_x3,start_y+(i+1)*interval_y,strTemp);

				pDC->MoveTo(interval_x1-20,start_y-20+i*interval_y);
				pDC->LineTo(CurRegion.cx-30,start_y-20+i*interval_y);
				
				
			}

			pDC->MoveTo(interval_x1-20,start_y-20+(iCount-1)*interval_y);
			pDC->LineTo(CurRegion.cx-30,start_y-20+(iCount-1)*interval_y);

			//最后一横
			pDC->MoveTo(interval_x1-20,start_y-20+iCount*interval_y);
			pDC->LineTo(CurRegion.cx-30,start_y-20+iCount*interval_y);

			int interval_y_internal = start_y+(iCount+1)*interval_y;
			//打印累计信息
			pDC->TextOut(interval_x1,start_y+(i+1)*interval_y,_T("工分累计信息："));
			for(int iCol =0;iCol<pDlg->m_strCaption.GetCount();iCol++)
			{
				strTemp = pDlg->m_list.GetItemText(iCount-1,iCol+1);
				if (atoi(strTemp)!=0)
				{
					strTemp = pDlg->m_strCaption.GetAt(iCol)+" "+strTemp;
					pDC->TextOut(interval_x1,interval_y_internal,strTemp);
					interval_y_internal +=interval_y;

				}
			}
			//print the final total information
			strTemp = _T("总计  ")+pDlg->m_list.GetItemText(iCount-1,pDlg->m_strCaption.GetCount()+1);
			pDC->TextOut(interval_x1,interval_y_internal,strTemp);
	


			
			int temp =interval_y*(pDlg->m_list.GetItemCount()+1);

			pDC->MoveTo(interval_x1-20,start_y-20);
			pDC->LineTo(interval_x1-20,start_y-20+iCount*interval_y);

			pDC->MoveTo(interval_x2-20,start_y-20);
			pDC->LineTo(interval_x2-20,start_y-20+iCount*interval_y);

			pDC->MoveTo(interval_x3-20,start_y-20);
			pDC->LineTo(interval_x3-20,start_y-20+iCount*interval_y);
			
			//最后一竖
			pDC->MoveTo(CurRegion.cx-30,start_y-20);
			pDC->LineTo(CurRegion.cx-30,start_y-20+iCount*interval_y);
			

		}
	}
	app->m_pMainWnd->SetWindowText("某服饰工资管理系统");
}


// CwagemanageView 打印

BOOL CwagemanageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CwagemanageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CwagemanageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CwagemanageView 诊断

#ifdef _DEBUG
void CwagemanageView::AssertValid() const
{
	CView::AssertValid();
}

void CwagemanageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CwagemanageDoc* CwagemanageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CwagemanageDoc)));
	return (CwagemanageDoc*)m_pDocument;
}
#endif //_DEBUG


// CwagemanageView 消息处理程序

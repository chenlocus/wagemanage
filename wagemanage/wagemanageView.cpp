// wagemanageView.cpp : CwagemanageView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CwagemanageView ����/����

CwagemanageView::CwagemanageView()
{
	// TODO: �ڴ˴���ӹ������

}

CwagemanageView::~CwagemanageView()
{
}

BOOL CwagemanageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CwagemanageView ����

void CwagemanageView::OnDraw(CDC* pDC)
{
	CwagemanageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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

		//��ӡ����Ŀ�Ⱥ͸߶�
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
			strTemp = "�¸����ܹ��ʱ���";

			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+50,strTemp);


			pDC->SetTextAlign(TA_LEFT);
			pDC->SelectObject(pOldFont);
			ft.DeleteObject();
			CString strMonth=pDlg->m_date.Format("%Y-%m");
			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+200,strMonth);

			CHeaderCtrl*   pHeaderCtrl   = pDlg->m_list.GetHeaderCtrl();//m_list������б�ؼ��� 
			int nColumnCount  =  pHeaderCtrl->GetItemCount();   //microsoft��bug

		    
			int interval_x =CurRegion.cx/nColumnCount;
			
			int interval_y =110;

			

			/*for (int iCol=1;iCol<nColumnCount;iCol++)
			{
				HDITEM pCol;
				pHeaderCtrl->GetItem(iCol,&pCol);
				strTemp =pCol.pszText;
				pDC->TextOut(CurOrg.cx+100+interval_x*iCol,CurOrg.cy/2+300,pCol.pszText);
			}*/
			
			//��ӡ������
			for (int j=0;j<nColumnCount;j++)
			{
				strTemp = pDlg->strCaption.GetAt(j);
				pDC->TextOut(CurOrg.cx+100+interval_x*j,CurOrg.cy/2+380,strTemp);

			}
			pDC->MoveTo(CurOrg.cx+90,CurOrg.cy/2+370);
			pDC->LineTo(CurOrg.cx+interval_x*nColumnCount-30,CurOrg.cy/2+370);

			//��ӡ����
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
			//���һ��
			pDC->MoveTo(CurOrg.cx+90,CurOrg.cy/2+370+i*interval_y);
			pDC->LineTo(CurOrg.cx+interval_x*nColumnCount-30,CurOrg.cy/2+370+i*interval_y);
			
			int temp =interval_y*(pDlg->m_list.GetItemCount()+1);
			for (int j=0; j<nColumnCount;j++)
			{
				pDC->MoveTo(CurOrg.cx+90+interval_x*j,CurOrg.cy/2+370);
				pDC->LineTo(CurOrg.cx+90+interval_x*j,CurOrg.cy/2+370+temp);
			}
			//���һ��
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
			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+50,"�¸��˲�ֵ��ϸ��");

			pDC->SelectObject(pOldFont);
			ft.DeleteObject();
			CString strType;
			pDlg->m_type.GetLBText(pDlg->m_type.GetCurSel(),strType);
			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+180,_T("��Ŀ��ţ� ")+strType);
			CString strMonth=pDlg->m_date.Format("%Y-%m");
			pDC->TextOut((CurOrg.cx+CurRegion.cx)/2,CurOrg.cy/2+250,strMonth);

			//CHeaderCtrl*   pHeaderCtrl   = pDlg->m_list.GetHeaderCtrl();//m_list������б�ؼ��� 
			//int nColumnCount  =  pHeaderCtrl->GetItemCount();   //microsoft��bug
			pDC->SetTextAlign(TA_LEFT);
			int interval_x1 =CurOrg.cx+100;
			int interval_x2 =CurOrg.cx+100+400;
			int interval_x3 =CurRegion.cx-400;
			int interval_x_internal;
			int start_y = CurOrg.cy/2+400;
			int interval_y =110;

			CString strTemp;
			
			//��ӡ������
			pDC->TextOut(interval_x1,start_y,_T("����"));
			pDC->TextOut(interval_x2,start_y,_T("������������"));
			pDC->TextOut(interval_x3,start_y,_T("�����ۼ�"));
			
			

			pDC->MoveTo(interval_x1-20,start_y-20);
			pDC->LineTo(CurRegion.cx-30,start_y-20);
			
			int iCount = pDlg->m_list.GetItemCount();
			//��ӡ����
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

			//���һ��
			pDC->MoveTo(interval_x1-20,start_y-20+iCount*interval_y);
			pDC->LineTo(CurRegion.cx-30,start_y-20+iCount*interval_y);

			int interval_y_internal = start_y+(iCount+1)*interval_y;
			//��ӡ�ۼ���Ϣ
			pDC->TextOut(interval_x1,start_y+(i+1)*interval_y,_T("�����ۼ���Ϣ��"));
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
			strTemp = _T("�ܼ�  ")+pDlg->m_list.GetItemText(iCount-1,pDlg->m_strCaption.GetCount()+1);
			pDC->TextOut(interval_x1,interval_y_internal,strTemp);
	


			
			int temp =interval_y*(pDlg->m_list.GetItemCount()+1);

			pDC->MoveTo(interval_x1-20,start_y-20);
			pDC->LineTo(interval_x1-20,start_y-20+iCount*interval_y);

			pDC->MoveTo(interval_x2-20,start_y-20);
			pDC->LineTo(interval_x2-20,start_y-20+iCount*interval_y);

			pDC->MoveTo(interval_x3-20,start_y-20);
			pDC->LineTo(interval_x3-20,start_y-20+iCount*interval_y);
			
			//���һ��
			pDC->MoveTo(CurRegion.cx-30,start_y-20);
			pDC->LineTo(CurRegion.cx-30,start_y-20+iCount*interval_y);
			

		}
	}
	app->m_pMainWnd->SetWindowText("ĳ���ι��ʹ���ϵͳ");
}


// CwagemanageView ��ӡ

BOOL CwagemanageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CwagemanageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CwagemanageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CwagemanageView ���

#ifdef _DEBUG
void CwagemanageView::AssertValid() const
{
	CView::AssertValid();
}

void CwagemanageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CwagemanageDoc* CwagemanageView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CwagemanageDoc)));
	return (CwagemanageDoc*)m_pDocument;
}
#endif //_DEBUG


// CwagemanageView ��Ϣ�������

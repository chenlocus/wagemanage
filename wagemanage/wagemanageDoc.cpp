// wagemanageDoc.cpp :  CwagemanageDoc ���ʵ��
//

#include "stdafx.h"
#include "wagemanage.h"

#include "wagemanageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwagemanageDoc

IMPLEMENT_DYNCREATE(CwagemanageDoc, CDocument)

BEGIN_MESSAGE_MAP(CwagemanageDoc, CDocument)
END_MESSAGE_MAP()


// CwagemanageDoc ����/����

CwagemanageDoc::CwagemanageDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CwagemanageDoc::~CwagemanageDoc()
{
}

BOOL CwagemanageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CwagemanageDoc ���л�

void CwagemanageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CwagemanageDoc ���

#ifdef _DEBUG
void CwagemanageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CwagemanageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CwagemanageDoc ����

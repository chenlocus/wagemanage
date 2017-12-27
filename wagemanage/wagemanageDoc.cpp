// wagemanageDoc.cpp :  CwagemanageDoc 类的实现
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


// CwagemanageDoc 构造/析构

CwagemanageDoc::CwagemanageDoc()
{
	// TODO: 在此添加一次性构造代码

}

CwagemanageDoc::~CwagemanageDoc()
{
}

BOOL CwagemanageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CwagemanageDoc 序列化

void CwagemanageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CwagemanageDoc 诊断

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


// CwagemanageDoc 命令

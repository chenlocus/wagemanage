// wagemanageView.h : CwagemanageView ��Ľӿ�
//


#pragma once


class CwagemanageView : public CView
{
protected: // �������л�����
	CwagemanageView();
	DECLARE_DYNCREATE(CwagemanageView)

// ����
public:
	CwagemanageDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CwagemanageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // wagemanageView.cpp �ĵ��԰汾
inline CwagemanageDoc* CwagemanageView::GetDocument() const
   { return reinterpret_cast<CwagemanageDoc*>(m_pDocument); }
#endif


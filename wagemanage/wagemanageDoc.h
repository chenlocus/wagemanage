// wagemanageDoc.h :  CwagemanageDoc ��Ľӿ�
//


#pragma once

class CwagemanageDoc : public CDocument
{
protected: // �������л�����
	CwagemanageDoc();
	DECLARE_DYNCREATE(CwagemanageDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CwagemanageDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};



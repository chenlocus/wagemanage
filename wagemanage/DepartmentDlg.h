#pragma once
#include "wagedealAgt.h"
#include "afxwin.h"

// CDepartmentDlg �Ի���

class CDepartmentDlg : public CDialog
{
	DECLARE_DYNAMIC(CDepartmentDlg)

public:
	CDepartmentDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDepartmentDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DEPARTMENT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CWagedealAgt m_wagedealagt;
	DECLARE_MESSAGE_MAP()
public:
	// ��������
	CString m_name;
	// ���Ӳ���
	CListBox m_addlist;
	// �Ѿ��еĲ���
	CListBox m_list;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedModify();
};

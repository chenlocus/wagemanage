#pragma once
#include "afxwin.h"
#include "wagedealAgt.h"


// CEmployInfoEditDlg �Ի���

class CEmployInfoEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CEmployInfoEditDlg)

public:
	CEmployInfoEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEmployInfoEditDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_MODIFY_EMPLOY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CComboBox m_departlist;
	CWagedealAgt * m_wagedealagt;
	CString m_Department;
private:
	CString strEmployeeInfo;
	CString strOldDepartment;
	CString strOldName;

public:
	void SetEmplyeeInfo(CString strInfo,CWagedealAgt *pDatabase);
	afx_msg void OnBnClickedOk();
};

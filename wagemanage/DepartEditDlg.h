#pragma once


// CDepartEditDlg �Ի���

class CDepartEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CDepartEditDlg)

public:
	CDepartEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CDepartEditDlg(CString &);
	virtual ~CDepartEditDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DEPARTEDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_oldname;
	CString m_newname;
	afx_msg void OnBnClickedOk();
};

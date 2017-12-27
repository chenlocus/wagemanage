#pragma once


// CDepartEditDlg 对话框

class CDepartEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CDepartEditDlg)

public:
	CDepartEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	CDepartEditDlg(CString &);
	virtual ~CDepartEditDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DEPARTEDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_oldname;
	CString m_newname;
	afx_msg void OnBnClickedOk();
};

#pragma once


// CBankLoginDlg 对话框

class CBankLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBankLoginDlg)

public:
	CBankLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBankLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDBANK_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegister();
	virtual BOOL OnInitDialog();

	bool checkDialogValueValid();

	friend std::string loginCardDlg();	// 登录 返回账号
	afx_msg void OnBnClickedLogin();
protected:
	CString cardAccount;
	CString cardPassword;
};

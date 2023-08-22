#pragma once


// CBankRegisterDlg 对话框

class CBankRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBankRegisterDlg)

public:
	CBankRegisterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBankRegisterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDBANK_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	friend std::string registerCardDlg();	// 注册 返回账号
	afx_msg void OnBnClickedOk();
	bool checkDialogValueValid();
protected:
	CString userName;
	CString userID;
	CString userPhoneNumber;
	CString cardAccount;
	CString cardPassword;
	float cardBalance;
	INT userGenderRadio;
};

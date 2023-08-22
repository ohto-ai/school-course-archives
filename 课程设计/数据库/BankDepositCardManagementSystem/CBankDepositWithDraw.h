#pragma once


// CBankDepositWithDraw 对话框

class CBankDepositWithDraw : public CDialogEx
{
	DECLARE_DYNAMIC(CBankDepositWithDraw)

public:
	CBankDepositWithDraw(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBankDepositWithDraw();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDBANK_DEPOSIT_WITHDRAW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDwDeposit();
	afx_msg void OnBnClickedDwWhitdraw();
	afx_msg void OnBnClickedDodw();
	float changeBalance;
};

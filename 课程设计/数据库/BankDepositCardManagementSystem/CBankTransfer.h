#pragma once


// CBankTransfer 对话框

class CBankTransfer : public CDialogEx
{
	DECLARE_DYNAMIC(CBankTransfer)

public:
	CBankTransfer(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBankTransfer();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDBANK_TRANSFER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedTransferin();
	afx_msg void OnBnClickedTransferout();
	afx_msg void OnBnClickedDotransfer();
	float transferAmount;
};

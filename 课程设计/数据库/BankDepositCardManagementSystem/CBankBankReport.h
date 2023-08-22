#pragma once


// CBankBankReport 对话框

class CBankBankReport : public CDialogEx
{
	DECLARE_DYNAMIC(CBankBankReport)

public:
	CBankBankReport(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBankBankReport();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDBANK_BANKREPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBankReportUpdate();
	float reportResult;
};

#pragma once


// CBankUserReport 对话框

class CBankUserReport : public CDialogEx
{
	DECLARE_DYNAMIC(CBankUserReport)

public:
	CBankUserReport(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBankUserReport();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDBANK_USERREPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnUserReportUpdate();
	float reportResult;
};

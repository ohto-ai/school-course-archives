#pragma once


// CBankHistory 对话框

class CBankHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CBankHistory)

public:
	CBankHistory(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBankHistory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDBANK_HISTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQueryhistory();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDatebeginEnable();
	afx_msg void OnBnClickedDateendEnable();
};

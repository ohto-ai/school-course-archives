#pragma once


// CBankCardConfig 对话框

class CBankCardConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CBankCardConfig)

public:
	CBankCardConfig(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBankCardConfig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDBANK_CARDCONFIG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDocancel();
	virtual BOOL OnInitDialog();
};


// CBankDepositCardManagementSystemDlg.h: 头文件
//

#pragma once


// CBankDepositCardManagementSystemDlg 对话框
class CBankDepositCardManagementSystemDlg : public CDialogEx
{
// 构造
public:
	CBankDepositCardManagementSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BANKDEPOSITCARDMANAGEMENTSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	enum NAVIGATION_TAB_VALUE: size_t
	{
		TAB_DEPOSIT_WITHDRAW	// 存取款
		, TAB_TRANSFER			// 汇款转账
		, TAB_HISTORY			// 历史记录
		, TAB_CARDCONFIG		// 储蓄卡设置
		, TAB_USER_REPORT		// 用户报表
		, TAB_BANK_REPORT		// 银行报表
	};


	CBankDepositWithDraw tabDepositWithDraw;
	CBankTransfer tabTransfer;
	CBankHistory tabHistory;
	CBankCardConfig tabCardConfig;
	CBankUserReport tabUserReport;
	CBankBankReport tabBankReport;


	CTabCtrl navigatTab;
public:
	afx_msg void OnTcnSelchangeNavigationTab(NMHDR* pNMHDR, LRESULT* pResult);
};

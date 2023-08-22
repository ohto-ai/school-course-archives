
// CBankDepositCardManagementSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankDepositCardManagementSystemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBankDepositCardManagementSystemDlg 对话框



CBankDepositCardManagementSystemDlg::CBankDepositCardManagementSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BANKDEPOSITCARDMANAGEMENTSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	thatboy::PublicMemory::cardAccount = _T("");
	thatboy::PublicMemory::userName = _T("");
	thatboy::PublicMemory::cardBalance = 0.0f;
}

void CBankDepositCardManagementSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCBANK_NAVIGATION_TAB, navigatTab);
}

BEGIN_MESSAGE_MAP(CBankDepositCardManagementSystemDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDCBANK_NAVIGATION_TAB, &CBankDepositCardManagementSystemDlg::OnTcnSelchangeNavigationTab)
END_MESSAGE_MAP()


// CBankDepositCardManagementSystemDlg 消息处理程序

BOOL CBankDepositCardManagementSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 登录
	thatboy::PublicMemory::cardAccount = loginCardDlg().c_str();
	if (thatboy::PublicMemory::cardAccount.IsEmpty()) {
		EndDialog(IDCANCEL);
		return FALSE;
	}

	// 更新用户信息

	thatboy::CallBack::updateUserInfo = [&] {
		if (thatboy::Bank::queryCardState(thatboy::PublicMemory::cardAccount.GetString()) == "Cancellation")
		{
			EndDialog(IDOK);
			return;
		}
		thatboy::PublicMemory::userName = thatboy::Bank::queryUserName(thatboy::PublicMemory::cardAccount.GetString()).c_str();
		thatboy::PublicMemory::userGender = thatboy::Bank::queryUserGender(thatboy::PublicMemory::cardAccount.GetString()) == "Male";
		std::stringstream sstream(thatboy::Bank::queryCardBalance(thatboy::PublicMemory::cardAccount.GetString()));
		sstream >> thatboy::PublicMemory::cardBalance;
		// 顶部信息
		CString topInfo;
		topInfo.Format("%s %s[%s] - 余额 ￥%.2f", thatboy::PublicMemory::userName.GetString(), thatboy::PublicMemory::userGender ? "先生" : "女士", thatboy::PublicMemory::cardAccount.GetString(), thatboy::PublicMemory::cardBalance);
		SetDlgItemText(IDCBANK_TOPINFO, topInfo.GetString());
	};

	thatboy::CallBack::updateUserInfo();
	
	navigatTab.InsertItem(TAB_DEPOSIT_WITHDRAW, "存取款");
	navigatTab.InsertItem(TAB_TRANSFER, "转账汇款");
	navigatTab.InsertItem(TAB_HISTORY, "历史记录");
	navigatTab.InsertItem(TAB_CARDCONFIG, "储蓄卡设置");
	navigatTab.InsertItem(TAB_USER_REPORT, "用户报表");
	navigatTab.InsertItem(TAB_BANK_REPORT, "银行报表");

	tabDepositWithDraw.Create(IDDBANK_DEPOSIT_WITHDRAW, &navigatTab);
	tabTransfer.Create(IDDBANK_TRANSFER, &navigatTab);
	tabHistory.Create(IDDBANK_HISTORY, &navigatTab);
	tabCardConfig.Create(IDDBANK_CARDCONFIG, &navigatTab);
	tabUserReport.Create(IDDBANK_USERREPORT, &navigatTab);
	tabBankReport.Create(IDDBANK_BANKREPORT, &navigatTab);

	CRect rc;
	navigatTab.GetClientRect(rc);
	rc.top += 1;
	rc.bottom -= 21;
	rc.left += 1;
	rc.right -= 1;

	tabDepositWithDraw.MoveWindow(rc);
	tabTransfer.MoveWindow(rc);
	tabHistory.MoveWindow(rc);
	tabCardConfig.MoveWindow(rc);
	tabUserReport.MoveWindow(rc);
	tabBankReport.MoveWindow(rc);

	tabDepositWithDraw.ShowWindow(SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBankDepositCardManagementSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBankDepositCardManagementSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBankDepositCardManagementSystemDlg::OnTcnSelchangeNavigationTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 隐藏全部
	tabDepositWithDraw.ShowWindow(SW_HIDE);
	tabTransfer.ShowWindow(SW_HIDE);
	tabHistory.ShowWindow(SW_HIDE);
	tabCardConfig.ShowWindow(SW_HIDE);
	tabUserReport.ShowWindow(SW_HIDE);
	tabBankReport.ShowWindow(SW_HIDE);


	switch (navigatTab.GetCurSel())
	{
	case TAB_DEPOSIT_WITHDRAW:
		tabDepositWithDraw.ShowWindow(SW_SHOW);
		break;
	case TAB_TRANSFER:
		tabTransfer.ShowWindow(SW_SHOW);
		break;
	case TAB_HISTORY:
		tabHistory.ShowWindow(SW_SHOW);
		break;
	case TAB_CARDCONFIG:
		tabCardConfig.ShowWindow(SW_SHOW);
		break;
	case TAB_USER_REPORT:
		tabUserReport.ShowWindow(SW_SHOW);
		break;
	case TAB_BANK_REPORT:
		tabBankReport.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}


	*pResult = 0;
}

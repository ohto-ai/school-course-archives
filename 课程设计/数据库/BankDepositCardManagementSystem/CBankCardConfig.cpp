// CBankCardConfig.cpp: 实现文件
//

#include "pch.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankCardConfig.h"
#include "afxdialogex.h"


// CBankCardConfig 对话框

IMPLEMENT_DYNAMIC(CBankCardConfig, CDialogEx)

CBankCardConfig::CBankCardConfig(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDBANK_CARDCONFIG, pParent)
{

}

CBankCardConfig::~CBankCardConfig()
{
}

void CBankCardConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBankCardConfig, CDialogEx)
	ON_BN_CLICKED(IDCBANK_DOCANCEL, &CBankCardConfig::OnBnClickedDocancel)
END_MESSAGE_MAP()


// CBankCardConfig 消息处理程序


void CBankCardConfig::OnBnClickedDocancel()
{
	CString password;
	GetDlgItemText(IDCBANK_CONFIG_PASSWORD, password);
	if (thatboy::Bank::verifyPassword(thatboy::PublicMemory::cardAccount.GetString(), password.GetString()))
	{
		CString balance;
		balance.Format("余额已取出￥%.2f，账号已注销！", thatboy::PublicMemory::cardBalance);
		thatboy::Bank::cancelAccount(thatboy::PublicMemory::cardAccount.GetString());
		MessageBox(balance);;
	}
	else
	{
		MessageBox("账号密码验证失败！", "失败");
	}
	thatboy::CallBack::updateUserInfo();
}

BOOL CBankCardConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDCBANK_CONFIG_ACCOUNT, thatboy::PublicMemory::cardAccount.GetString());
	((CEdit*)GetDlgItem(IDCBANK_CONFIG_PASSWORD))->SetLimitText(6);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

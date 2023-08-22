// CBankDepositWithDraw.cpp: 实现文件
//

#include "pch.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankDepositWithDraw.h"
#include "afxdialogex.h"


// CBankDepositWithDraw 对话框

IMPLEMENT_DYNAMIC(CBankDepositWithDraw, CDialogEx)

CBankDepositWithDraw::CBankDepositWithDraw(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDBANK_DEPOSIT_WITHDRAW, pParent)
	, changeBalance(0)
{

}

CBankDepositWithDraw::~CBankDepositWithDraw()
{
}

void CBankDepositWithDraw::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDCBANK_DW_AMOUNT, changeBalance);
}


BEGIN_MESSAGE_MAP(CBankDepositWithDraw, CDialogEx)
	ON_BN_CLICKED(IDCBANK_DW_DEPOSIT, &CBankDepositWithDraw::OnBnClickedDwDeposit)
	ON_BN_CLICKED(IDCBANK_DW_WHITDRAW, &CBankDepositWithDraw::OnBnClickedDwWhitdraw)
	ON_BN_CLICKED(IDCBANK_DODW, &CBankDepositWithDraw::OnBnClickedDodw)
END_MESSAGE_MAP()


// CBankDepositWithDraw 消息处理程序


BOOL CBankDepositWithDraw::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDCBANK_DW_ACCOUNT, thatboy::PublicMemory::cardAccount.GetString());

	((CEdit*)GetDlgItem(IDCBANK_DW_PASSWORD))->SetLimitText(6);
	CheckRadioButton(IDCBANK_DW_DEPOSIT, IDCBANK_DW_WHITDRAW, IDCBANK_DW_DEPOSIT);
	SetDlgItemText(IDCBANK_DW_AMOUNT, "0");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CBankDepositWithDraw::OnBnClickedDwDeposit()
{
	SetDlgItemText(IDCBANK_DODW, "完成存款");
}


void CBankDepositWithDraw::OnBnClickedDwWhitdraw()
{
	SetDlgItemText(IDCBANK_DODW, "完成取款");
}


void CBankDepositWithDraw::OnBnClickedDodw()
{
	CString password;
	UpdateData();
	GetDlgItemText(IDCBANK_DW_PASSWORD, password);

	if (!thatboy::Bank::verifyPassword(thatboy::PublicMemory::cardAccount.GetString(), password.GetString()))
	{
		MessageBox("密码验证失败！", "错误");
		return;
	}
	else if (!thatboy::Bank::depositAndWithdraw(thatboy::PublicMemory::cardAccount.GetString()
		, (GetCheckedRadioButton(IDCBANK_DW_DEPOSIT, IDCBANK_DW_WHITDRAW) == IDCBANK_DW_DEPOSIT ? changeBalance : -changeBalance)))
	{
		MessageBox("存取款失败！", "错误");
	}
	else
	{
		MessageBox("存取款成功！", "成功");
		SetDlgItemText(IDCBANK_DW_PASSWORD, "");
		SetDlgItemText(IDCBANK_DW_AMOUNT, "0");
	}

	thatboy::CallBack::updateUserInfo();
}

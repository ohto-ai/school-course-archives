// CBankTransfer.cpp: 实现文件
//

#include "pch.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankTransfer.h"
#include "afxdialogex.h"


// CBankTransfer 对话框

IMPLEMENT_DYNAMIC(CBankTransfer, CDialogEx)

CBankTransfer::CBankTransfer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDBANK_TRANSFER, pParent)
	, transferAmount(0)
{

}

CBankTransfer::~CBankTransfer()
{
}

void CBankTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDCBANK_TRANSFERAMOUNT, transferAmount);
}


BEGIN_MESSAGE_MAP(CBankTransfer, CDialogEx)
	ON_BN_CLICKED(IDCBANK_TRANSFERIN, &CBankTransfer::OnBnClickedTransferin)
	ON_BN_CLICKED(IDCBANK_TRANSFEROUT, &CBankTransfer::OnBnClickedTransferout)
	ON_BN_CLICKED(IDCBANK_DOTRANSFER, &CBankTransfer::OnBnClickedDotransfer)
END_MESSAGE_MAP()


// CBankTransfer 消息处理程序


BOOL CBankTransfer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDCBANK_TRANSFER_THISACCOUNT, thatboy::PublicMemory::cardAccount.GetString());

	CheckRadioButton(IDCBANK_TRANSFEROUT, IDCBANK_TRANSFERIN, IDCBANK_TRANSFEROUT);
	((CEdit*)GetDlgItem(IDCBANK_TRANSFER_THISPASSWORD))->SetLimitText(6);
	((CEdit*)GetDlgItem(IDCBANK_TRANSFER_THATPASSWORD))->SetLimitText(6);
	((CComboBox*)GetDlgItem(IDCBANK_TRANSFER_THATACCOUNT))->LimitText(18);
	SetDlgItemText(IDCBANK_TRANSFERAMOUNT, "0");


	auto result = thatboy::Bank::enumNormalAccount();
	for (auto account : result)
		((CComboBox*)GetDlgItem(IDCBANK_TRANSFER_THATACCOUNT))->AddString(account[0]);
	((CComboBox*)GetDlgItem(IDCBANK_TRANSFER_THATACCOUNT))->DeleteString(((CComboBox*)GetDlgItem(IDCBANK_TRANSFER_THATACCOUNT))->FindString(0, thatboy::PublicMemory::cardAccount.GetString()));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CBankTransfer::OnBnClickedTransferin()
{
	GetDlgItem(IDCBANK_TRANSFER_THISPASSWORD)->EnableWindow(FALSE);
	GetDlgItem(IDCBANK_TRANSFER_THATPASSWORD)->EnableWindow(TRUE);
}


void CBankTransfer::OnBnClickedTransferout()
{
	GetDlgItem(IDCBANK_TRANSFER_THISPASSWORD)->EnableWindow(TRUE);
	GetDlgItem(IDCBANK_TRANSFER_THATPASSWORD)->EnableWindow(FALSE);
}


void CBankTransfer::OnBnClickedDotransfer()
{
	CString thatAccount;
	CString password;
	UpdateData();
	GetDlgItemText(
		GetCheckedRadioButton(IDCBANK_TRANSFEROUT, IDCBANK_TRANSFERIN) == IDCBANK_TRANSFEROUT 
		? IDCBANK_TRANSFER_THISPASSWORD : IDCBANK_TRANSFER_THATPASSWORD, password);
	GetDlgItemText(IDCBANK_TRANSFER_THATACCOUNT, thatAccount);

	if (GetCheckedRadioButton(IDCBANK_TRANSFEROUT, IDCBANK_TRANSFERIN) == IDCBANK_TRANSFEROUT?
		!thatboy::Bank::verifyPassword(thatboy::PublicMemory::cardAccount.GetString(), password.GetString())
		: !thatboy::Bank::verifyPassword(thatAccount.GetString(), password.GetString())
		)
	{
		MessageBox("密码验证失败！", "错误");
		return;
	}
	else if (!thatboy::Bank::transfer(thatboy::PublicMemory::cardAccount.GetString()
		, thatAccount.GetString()
		, (GetCheckedRadioButton(IDCBANK_TRANSFEROUT, IDCBANK_TRANSFERIN) == IDCBANK_TRANSFEROUT ? -transferAmount : transferAmount)))
	{
		MessageBox("转账失败！", "错误");
	}
	else
	{
		MessageBox("转账成功！", "成功");
		SetDlgItemText(IDCBANK_TRANSFER_THISPASSWORD, "");
		SetDlgItemText(IDCBANK_TRANSFER_THATPASSWORD, "");
		SetDlgItemText(IDCBANK_TRANSFERAMOUNT, "0");
	}

	thatboy::CallBack::updateUserInfo();
}

// CBankLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankLoginDlg.h"
#include "afxdialogex.h"


// CBankLoginDlg 对话框

IMPLEMENT_DYNAMIC(CBankLoginDlg, CDialogEx)

CBankLoginDlg::CBankLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDBANK_LOGIN, pParent)
	, cardAccount(_T(""))
	, cardPassword(_T(""))
{

}

CBankLoginDlg::~CBankLoginDlg()
{
}

void CBankLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDCBANK_LOGIN_ACCOUNT, cardAccount);
	DDX_Text(pDX, IDCBANK_LOGIN_PASSWORD, cardPassword);
}


BEGIN_MESSAGE_MAP(CBankLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDBANK_REGISTER, &CBankLoginDlg::OnBnClickedRegister)
	ON_BN_CLICKED(IDOK, &CBankLoginDlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CBankLoginDlg 消息处理程序


void CBankLoginDlg::OnBnClickedRegister()
{
	ShowWindow(SW_HIDE);
	SetDlgItemText(IDCBANK_LOGIN_ACCOUNT, registerCardDlg().c_str());
	ShowWindow(SW_SHOW);
}


BOOL CBankLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CComboBox*)GetDlgItem(IDCBANK_LOGIN_ACCOUNT))->LimitText(18);
	((CEdit*)GetDlgItem(IDCBANK_LOGIN_PASSWORD))->SetLimitText(6);

	auto result = thatboy::Bank::enumNormalAccount();
	for (auto account : result)
		((CComboBox*)GetDlgItem(IDCBANK_LOGIN_ACCOUNT))->AddString(account[0]);

	return FALSE;
}

bool CBankLoginDlg::checkDialogValueValid()
{
	UpdateData();
	if (cardAccount.IsEmpty())
		MessageBox("账户不可为空！", "错误");
	else if (cardPassword.GetLength() != 6)
		MessageBox("密码长度必须为6位！", "错误");
	else if (!thatboy::Bank::verifyPassword(cardAccount.GetString(), cardPassword.GetString()))
		MessageBox("用户名或密码验证失败，请检查后重试！", "错误");
	else
	{
		//MessageBox("验证成功");
		return true;
	}
	return false;
}

std::string loginCardDlg()
{
	CBankLoginDlg dlg;
	if (IDOK == dlg.DoModal())
		return dlg.cardAccount.GetString();
	else
		return "";
}


void CBankLoginDlg::OnBnClickedLogin()
{
	if(checkDialogValueValid())
		CDialogEx::OnOK();
}

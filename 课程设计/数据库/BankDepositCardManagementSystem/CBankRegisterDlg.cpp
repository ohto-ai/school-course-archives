// CBankRegisterDlg.cpp: 实现文件
//

#include "pch.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankRegisterDlg.h"
#include "afxdialogex.h"


// CBankRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CBankRegisterDlg, CDialogEx)

CBankRegisterDlg::CBankRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDBANK_REGISTER, pParent)
	, userName(_T(""))
	, userGenderRadio(IDCBANK_REG_MALE)
	, userID(_T(""))
	, userPhoneNumber(_T(""))
	, cardAccount(_T(""))
	, cardPassword(_T(""))
	, cardBalance(0)
{}

CBankRegisterDlg::~CBankRegisterDlg()
{
}

void CBankRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDCBANK_REG_USERNAME, userName);
	DDX_Text(pDX, IDCBANK_REG_USERID, userID);
	DDX_Text(pDX, IDCBANK_REG_PHONENUMBER, userPhoneNumber);
	DDX_Text(pDX, IDCBANK_REG_ACCOUNT, cardAccount);
	DDX_Text(pDX, IDCBANK_REG_PASSWORD, cardPassword);
	DDX_Text(pDX, IDCBANK_REG_ACCOUNTAMOUNT, cardBalance);
	DDX_Radio(pDX, IDCBANK_REG_MALE, userGenderRadio);
}


BEGIN_MESSAGE_MAP(CBankRegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBankRegisterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBankRegisterDlg 消息处理程序


BOOL CBankRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化
	CheckRadioButton(IDCBANK_REG_MALE, IDCBANK_REG_FEMALE, IDCBANK_REG_MALE);
	((CEdit*)GetDlgItem(IDCBANK_REG_USERNAME))->SetLimitText(20);
	((CEdit*)GetDlgItem(IDCBANK_REG_PASSWORD))->SetLimitText(6);
	((CEdit*)GetDlgItem(IDCBANK_REG_PASSWORD_REPEAT))->SetLimitText(6);
	((CEdit*)GetDlgItem(IDCBANK_REG_PHONENUMBER))->SetLimitText(11);
	((CEdit*)GetDlgItem(IDCBANK_REG_USERID))->SetLimitText(18);

	// 申请账号
	SetDlgItemText(IDCBANK_REG_ACCOUNT, thatboy::Bank::applyAccountNumber().c_str());

	return FALSE;
}

std::string registerCardDlg()
{
	CBankRegisterDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (thatboy::Bank::createAccount(
			dlg.cardAccount.GetString()
			, dlg.cardPassword.GetString()
			, dlg.cardBalance
			, dlg.userName.GetString()
			, dlg.userGenderRadio == 0
			, dlg.userPhoneNumber.GetString()
			, dlg.userID.GetString()
		))
		{
			::MessageBox(nullptr, ("注册成功！请保存好您的账号和密码！[" + dlg.cardAccount + "]").GetString(), "成功", MB_OK);
			return dlg.cardAccount.GetString();
		}
		else
		{
			::MessageBox(nullptr, "注册失败，请重新尝试！", "失败", MB_OK);
			return "";
		}
		
	}
	else
	{
		return "";
	}
}

void CBankRegisterDlg::OnBnClickedOk()
{
	if (checkDialogValueValid())
		CDialogEx::OnOK();
}


bool CBankRegisterDlg::checkDialogValueValid()
{
	UpdateData();
	CString cardPasswordRepead;
	GetDlgItemText(IDCBANK_REG_PASSWORD_REPEAT, cardPasswordRepead);
	if (userName.IsEmpty())
		MessageBox("姓名不可为空！", "错误");
	else if (userID.GetLength() != 18)
		MessageBox("身份证号长度必须为18位！", "错误");
	else if (userPhoneNumber.GetLength() != 11)
		MessageBox("预留手机号长度必须为11位！", "错误");
	else if (cardPassword.GetLength() != 6)
		MessageBox("密码长度必须为6位！", "错误");
	else if (cardPassword != cardPasswordRepead)
		MessageBox("两次密码必须一致！", "错误");
	else if (cardBalance <=0)
		MessageBox("开户金额必须大于0元！", "错误");
	else
		return true;
	return false;
}

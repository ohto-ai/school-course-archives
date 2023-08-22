// CBankHistory.cpp: 实现文件
//

#include "pch.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankHistory.h"
#include "afxdialogex.h"


// CBankHistory 对话框

IMPLEMENT_DYNAMIC(CBankHistory, CDialogEx)

CBankHistory::CBankHistory(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDBANK_HISTORY, pParent)
{

}

CBankHistory::~CBankHistory()
{
}

void CBankHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBankHistory, CDialogEx)
	ON_BN_CLICKED(IDCBANK_QUERYHISTORY, &CBankHistory::OnBnClickedQueryhistory)
	ON_BN_CLICKED(IDCBANK_DATEBEGIN_ENABLE, &CBankHistory::OnBnClickedDatebeginEnable)
	ON_BN_CLICKED(IDCBANK_DATEEND_ENABLE, &CBankHistory::OnBnClickedDateendEnable)
END_MESSAGE_MAP()


// CBankHistory 消息处理程序


void CBankHistory::OnBnClickedQueryhistory()
{
	CTime timeBegin, timeEnd;
	((CDateTimeCtrl*)GetDlgItem(IDCBANK_DATEBEGIN))->GetTime(timeBegin);
	((CDateTimeCtrl*)GetDlgItem(IDCBANK_DATEEND))->GetTime(timeEnd);

	CString begStr, endStr;

	begStr = IsDlgButtonChecked(IDCBANK_DATEBEGIN_ENABLE) == BST_CHECKED ? timeBegin.Format("%Y-%m-%d 0:0:0") : "";
	endStr = IsDlgButtonChecked(IDCBANK_DATEEND_ENABLE) == BST_CHECKED ? timeEnd.Format("%Y-%m-%d 0:0:0") : "";

	auto result = thatboy::Bank::queryHistoryEvent(thatboy::PublicMemory::cardAccount.GetString(), begStr.GetString(), endStr.GetString());


	auto& Report = *(CListCtrl*)GetDlgItem(IDCBANK_HISTORYLIST);
	while (Report.DeleteColumn(Report.GetHeaderCtrl()->GetItemCount() - 1));
	Report.DeleteAllItems();
	result.forEachField([&Report](thatboy::MySQLField field)
		{
			Report.InsertColumn(Report.GetHeaderCtrl()->GetItemCount(), field.getName(), 0, 140);
		});
	for (auto row : result)
	{
		auto thisItem = Report.GetItemCount();
		Report.InsertItem(thisItem, row[0]);
		for (int i = 1; i < Report.GetHeaderCtrl()->GetItemCount(); i++)
			Report.SetItemText(thisItem, i, row[i]);
	}
}


BOOL CBankHistory::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CDateTimeCtrl*)GetDlgItem(IDCBANK_DATEBEGIN))->SetFormat("yyyy-MM-dd");
	((CDateTimeCtrl*)GetDlgItem(IDCBANK_DATEEND))->SetFormat("yyyy-MM-dd");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CBankHistory::OnBnClickedDatebeginEnable()
{
	GetDlgItem(IDCBANK_DATEBEGIN)->EnableWindow(IsDlgButtonChecked(IDCBANK_DATEBEGIN_ENABLE) == BST_CHECKED);
}


void CBankHistory::OnBnClickedDateendEnable()
{
	GetDlgItem(IDCBANK_DATEEND)->EnableWindow(IsDlgButtonChecked(IDCBANK_DATEEND_ENABLE) == BST_CHECKED);
}

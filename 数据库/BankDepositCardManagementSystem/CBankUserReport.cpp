// CBankUserReport.cpp: 实现文件
//

#include "pch.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankUserReport.h"
#include "afxdialogex.h"


// CBankUserReport 对话框

IMPLEMENT_DYNAMIC(CBankUserReport, CDialogEx)

CBankUserReport::CBankUserReport(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDBANK_USERREPORT, pParent)
	, reportResult(0)
{

}

CBankUserReport::~CBankUserReport()
{
}

void CBankUserReport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDCBANK_USERREPORT_RESULT, reportResult);
}


BEGIN_MESSAGE_MAP(CBankUserReport, CDialogEx)
	ON_CBN_SELCHANGE(IDCBANK_USERREPORT_TYPE, &CBankUserReport::OnUserReportUpdate)
	ON_CBN_SELCHANGE(IDCBANK_USERREPORT_DATE, &CBankUserReport::OnUserReportUpdate)
END_MESSAGE_MAP()


// CBankUserReport 消息处理程序


BOOL CBankUserReport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CComboBox*)GetDlgItem(IDCBANK_USERREPORT_DATE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDCBANK_USERREPORT_TYPE))->SetCurSel(0);
	SetDlgItemText(IDCBANK_USERREPORT_RESULT, "0");
	OnUserReportUpdate();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CBankUserReport::OnUserReportUpdate()
{
	auto result = thatboy::Bank::queryUserReport(thatboy::PublicMemory::cardAccount.GetString(), reportResult, ((CComboBox*)GetDlgItem(IDCBANK_USERREPORT_DATE))->GetCurSel(), ((CComboBox*)GetDlgItem(IDCBANK_USERREPORT_TYPE))->GetCurSel());


	auto& Report = *(CListCtrl*)GetDlgItem(IDCBANK_REPORTLIST);
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
	UpdateData(FALSE);


}

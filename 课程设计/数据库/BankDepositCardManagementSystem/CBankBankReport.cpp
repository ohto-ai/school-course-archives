// CBankBankReport.cpp: 实现文件
//

#include "pch.h"
#include "BankDepositCardManagementSystem.h"
#include "CBankBankReport.h"
#include "afxdialogex.h"


// CBankBankReport 对话框

IMPLEMENT_DYNAMIC(CBankBankReport, CDialogEx)

CBankBankReport::CBankBankReport(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDBANK_BANKREPORT, pParent)
	, reportResult(0)
{

}

CBankBankReport::~CBankBankReport()
{
}

void CBankBankReport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDCBANK_BANKREPORT_RESULT, reportResult);
}


BEGIN_MESSAGE_MAP(CBankBankReport, CDialogEx)
	ON_CBN_SELCHANGE(IDCBANK_BANKREPORT_DATE, &CBankBankReport::OnBankReportUpdate)
	ON_CBN_SELCHANGE(IDCBANK_BANKREPORT_TYPE, &CBankBankReport::OnBankReportUpdate)
END_MESSAGE_MAP()


// CBankBankReport 消息处理程序


BOOL CBankBankReport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CComboBox*)GetDlgItem(IDCBANK_BANKREPORT_DATE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDCBANK_BANKREPORT_TYPE))->SetCurSel(0);
	SetDlgItemText(IDCBANK_BANKREPORT_RESULT, "0");

	OnBankReportUpdate();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CBankBankReport::OnBankReportUpdate()
{
	auto result = thatboy::Bank::queryBankReport(reportResult, ((CComboBox*)GetDlgItem(IDCBANK_BANKREPORT_DATE))->GetCurSel(), ((CComboBox*)GetDlgItem(IDCBANK_BANKREPORT_TYPE))->GetCurSel());


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

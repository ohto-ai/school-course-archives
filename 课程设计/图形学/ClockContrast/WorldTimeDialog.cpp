// WorldTimeDialog.cpp: 实现文件
//

#include "pch.h"
#include "ClockContrast.h"
#include "WorldTimeDialog.h"
#include "afxdialogex.h"

#define IDT_FRESH_WORLD_TIME_IMAGE 0X21 
// WorldTimeDialog 对话框

IMPLEMENT_DYNAMIC(WorldTimeDialog, CDialog)



WorldTimeDialog::WorldTimeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORLD_TIME, pParent)
{

}

WorldTimeDialog::~WorldTimeDialog()
{
}

void WorldTimeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WorldTimeDialog, CDialog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// WorldTimeDialog 消息处理程序


BOOL WorldTimeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	Tip.Create(this);
	Tip.AddTool(GetDlgItem(IDC_WORLD_TIME_IMAGE), TEXT("别看了，这些地方我都没去过。"));
	Tip.SetDelayTime(200);
	Tip.Activate(TRUE); 
	Tip.SetTipBkColor(RGB(0, 0, 0));
	Tip.SetTipTextColor(RGB(0, 122, 204));

	TipFont.CreatePointFont(200, TEXT("等线"));
	Tip.SetFont(&TipFont);

	LoadImageFromResource(&WorldTimeImage, IDB_WORLD_TIME_BMP, _T("PNG"));
	WorldTimeImageCtrlDC = GetDlgItem(IDC_WORLD_TIME_IMAGE)->GetDC();
	GetDlgItem(IDC_WORLD_TIME_IMAGE)->GetClientRect(&WorldTimeImageCtrlRect);

	Font.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("楷体"));
	Pen.CreatePen(PS_SOLID, 2, RGB(50, 80, 255));
	Brush.CreateSolidBrush(RGB(200, 200, 255));

	WorldTimeImageCtrlDC->SelectObject(&Pen);
	WorldTimeImageCtrlDC->SelectObject(&Font);
	WorldTimeImageCtrlDC->SelectObject(&Brush);
	WorldTimeImageCtrlDC->SetTextColor(RGB(10, 10, 10));
	WorldTimeImageCtrlDC->SetBkMode(TRANSPARENT);

	// 初始化城市
	CityVector.clear();
	CityVector.push_back(WorldCityTimeInfo(TEXT("北京"), CPoint(886, 261), 8));
	CityVector.push_back(WorldCityTimeInfo(TEXT("伦敦"), CPoint(478, 200), 0));
	CityVector.push_back(WorldCityTimeInfo(TEXT("莫斯科"), CPoint(704, 223), 3));
	CityVector.push_back(WorldCityTimeInfo(TEXT("新德里"), CPoint(814, 309), 6));
	CityVector.push_back(WorldCityTimeInfo(TEXT("华盛顿"), CPoint(215, 256), -4));
	CityVector.push_back(WorldCityTimeInfo(TEXT("巴西利亚"), CPoint(316, 460), -3));
	CityVector.push_back(WorldCityTimeInfo(TEXT("开普敦"), CPoint(547, 523), +2));
	CityVector.push_back(WorldCityTimeInfo(TEXT("圣地亚哥"), CPoint(229, 545), -3));


	SetTimer(IDT_FRESH_WORLD_TIME_IMAGE, 100, nullptr);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL WorldTimeDialog::LoadImageFromResource(ATL::CImage* pImage, UINT nResID, LPCTSTR lpTyp)
{
	if (pImage == NULL)return false;

	pImage->Destroy();

	// 查找资源
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL)return false;

	// 加载资源
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// 锁定内存中的指定资源
	LPVOID lpVoid = ::LockResource(hImgData);

	LPSTREAM pStream = NULL;
	DWORD dwSize = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// 解除内存中的指定资源
	::GlobalUnlock(hNew);

	// 从指定内存创建流对象
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if (ht != S_OK)
	{
		GlobalFree(hNew);
	}
	else
	{
		// 加载图片
		pImage->Load(pStream);

		GlobalFree(hNew);
	}
	// 释放资源
	::FreeResource(hImgData);
	return true;
}


void WorldTimeDialog::OnTimer(UINT_PTR nIDEvent)
{
	static auto DrawWorldTimeInfo = [&]()
	{
		for (auto& city : CityVector)
		{
			WorldTimeImageCtrlDC->Rectangle(city.CityPosition.x - 2, city.CityPosition.y - 2, city.CityPosition.x + 146, city.CityPosition.y + 42);
			WorldTimeImageCtrlDC->TextOut(city.CityPosition.x, city.CityPosition.y, city.CityName);
			WorldTimeImageCtrlDC->TextOut(city.CityPosition.x, city.CityPosition.y + 20, city.TimeString);
		}
	};
	switch (nIDEvent)
	{
	case IDT_FRESH_WORLD_TIME_IMAGE:	// 刷新图像
		WorldCityTimeInfo::UpdateAllCityTime();													// 更新时间
		WorldTimeImage.BitBlt(WorldTimeImageCtrlDC->m_hDC, WorldTimeImageCtrlRect.TopLeft());	// 贴背景
		DrawWorldTimeInfo();																	// 绘制信息
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL WorldTimeDialog::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_MOUSEMOVE)
		Tip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}


void WorldTimeDialog::OnDestroy()
{
	CDialogEx::OnDestroy();
	KillTimer(IDT_FRESH_WORLD_TIME_IMAGE);	// 关闭定时器
	Font.DeleteObject();
	Brush.DeleteObject();
	Pen.DeleteObject();
}

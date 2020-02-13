
// ClockContrastDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ClockContrast.h"
#include "ClockContrastDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDT_FRESH_CLOCK 0X2C
// CClockContrastDlg 对话框



CClockContrastDlg::CClockContrastDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLOCKCONTRAST_DIALOG, pParent)
{
	DlgIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClockContrastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClockContrastDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW_WORLD_TIME, &CClockContrastDlg::OnBnClickedShowWorldTime)
	ON_BN_CLICKED(IDC_RETURN, &CClockContrastDlg::OnBnClickedReturn)
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_PLANE_IMG, &CClockContrastDlg::OnStnClickedPlaneImg)
	ON_STN_CLICKED(IDC_MEAT_IMG, &CClockContrastDlg::OnStnClickedMeatImg)
	ON_STN_CLICKED(IDC_AUTHOR_IMG, &CClockContrastDlg::OnStnClickedAuthorImg)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CClockContrastDlg 消息处理程序

BOOL CClockContrastDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(DlgIcon, TRUE);			// 设置大图标
	SetIcon(DlgIcon, FALSE);		// 设置小图标

	// 设置背景颜色
	SetBackgroundColor(BKColor);


	// 添加城市
	CityVector.push_back(CityTimeInfo(TEXT("北京"), 8));
	CityVector.push_back(CityTimeInfo(TEXT("伦敦"), 0));
	CityVector.push_back(CityTimeInfo(TEXT("莫斯科"), 3));
	CityVector.push_back(CityTimeInfo(TEXT("华盛顿"), -4));
	
	// 获取时钟DC
	ClockCtrlpDC[0] = GetDlgItem(IDC_CLOCK_0)->GetDC();
	ClockCtrlpDC[1] = GetDlgItem(IDC_CLOCK_1)->GetDC();
	ClockCtrlpDC[2] = GetDlgItem(IDC_CLOCK_2)->GetDC();
	ClockCtrlpDC[3] = GetDlgItem(IDC_CLOCK_3)->GetDC();
	// 获取时钟区域
	GetDlgItem(IDC_CLOCK_0)->GetClientRect(ClockClientRect + 0);
	GetDlgItem(IDC_CLOCK_1)->GetClientRect(ClockClientRect + 1);
	GetDlgItem(IDC_CLOCK_2)->GetClientRect(ClockClientRect + 2);
	GetDlgItem(IDC_CLOCK_3)->GetClientRect(ClockClientRect + 3);


	// 加载精灵图
	Plane.Load(TEXT("PIC"), TEXT("PLANE"), 8, 8);
	Meat.Load(TEXT("PIC"), TEXT("MEAT"), 8, 1);
	Author.Load(TEXT("PIC"), TEXT("THATBOY"));
	// 精灵图DC及矩形
	PlaneCtrlpDC = GetDlgItem(IDC_PLANE_IMG)->GetDC();
	GetDlgItem(IDC_PLANE_IMG)->GetClientRect(&PlaneCtrlRect);
	MeatCtrlpDC = GetDlgItem(IDC_MEAT_IMG)->GetDC();
	GetDlgItem(IDC_MEAT_IMG)->GetClientRect(&MeatCtrlRect);
	AuthorCtrlpDC = GetDlgItem(IDC_AUTHOR_IMG)->GetDC();
	GetDlgItem(IDC_AUTHOR_IMG)->GetClientRect(&AuthorCtrlRect);
	// 缩放精灵图到控件大小
	Plane.Zoom(PlaneCtrlRect.Width(), PlaneCtrlRect.Height());
	Meat.Zoom(MeatCtrlRect.Width(), MeatCtrlRect.Height());
	Author.Zoom(AuthorCtrlRect.Width(), AuthorCtrlRect.Height());
	// 创建浮动提示框
	Tip.Create(this);
	// 创建缓冲区
	for (size_t i = 0; i < ClockNumber; i++)
	{
		ClockBuffDC[i].CreateCompatibleDC(ClockCtrlpDC[i]);
		ClockBuffImage[i].CreateCompatibleBitmap(ClockCtrlpDC[i], ClockClientRect[i].Width(), ClockClientRect[i].Height());
		ClockBuffDC[i].SelectObject(ClockBuffImage + i);
		//ClockBuffDC[i].SetBkMode(TRANSPARENT);
		ClockBuffDC[i].FillSolidRect(ClockClientRect + i, BKColor);
	}
	// 获得时钟中心
	ClockCenterPoint[0] = ClockClientRect[0].CenterPoint();
	ClockCenterPoint[1] = ClockClientRect[1].CenterPoint();
	ClockCenterPoint[2] = ClockClientRect[2].CenterPoint();
	ClockCenterPoint[3] = ClockClientRect[3].CenterPoint();
	// 获得表盘轮廓矩形
	DialCircleInsideRect[0] = DialCircleOutsideRect[0] = ClockClientRect[0];
	DialCircleInsideRect[1] = DialCircleOutsideRect[1] = ClockClientRect[1];
	DialCircleInsideRect[2] = DialCircleOutsideRect[2] = ClockClientRect[2];
	DialCircleInsideRect[3] = DialCircleOutsideRect[3] = ClockClientRect[3];
	// 设置内侧轮廓
	for (auto& rect : DialCircleInsideRect)
	{
		rect.left += BorderWidth;
		rect.top += BorderWidth;
		rect.right -= BorderWidth;
		rect.bottom -= BorderWidth;
	}

	// 中心圈
	for (size_t i = 0; i < ClockNumber; i++)
		CentralCircleRect[i].SetRect(ClockCenterPoint[i].x - CentralCircleRadius, ClockCenterPoint[i].y - CentralCircleRadius,
									 ClockCenterPoint[i].x + CentralCircleRadius, ClockCenterPoint[i].y + CentralCircleRadius);

	// 表盘文字位置
	int DialStrWidth = 180;
	int DialStrHeight = 60;
	for (size_t i = 0; i < ClockNumber; i++)
		DialStrRect[i].SetRect(ClockCenterPoint[i].x - DialStrWidth / 2, ClockCenterPoint[i].y - DialStrHeight / 2,
							   ClockCenterPoint[i].x + DialStrWidth / 2, ClockCenterPoint[i].y + DialStrHeight / 2);

	// 设置表盘文字
	DialString[0] = TEXT("数学是火，点亮物理的灯。");
	DialString[1] = TEXT("物理是灯，照亮化学的路。");
	DialString[2] = TEXT("化学是路，通向生物的坑。");
	DialString[3] = TEXT("生物是坑，埋葬了理科生。");
	// 添加浮动提示框
	Tip.AddTool(GetDlgItem(IDC_PLANE_IMG), TEXT("鼠标移开，别点我。"));
	Tip.AddTool(GetDlgItem(IDC_MEAT_IMG), TEXT("时区查询"));
	Tip.AddTool(GetDlgItem(IDC_AUTHOR_IMG), TEXT("作者数嵌172 朱广锋（that boy）"));
	Tip.AddTool(GetDlgItem(IDC_RETURN), TEXT("官人慢走~"));
	Tip.AddTool(GetDlgItem(IDC_SHOW_WORLD_TIME), TEXT("一起去旅行？"));
	Tip.AddTool(GetDlgItem(IDC_CLOCK_0), TEXT("广告位招租"));
	Tip.AddTool(GetDlgItem(IDC_CLOCK_1), TEXT("有意者联系"));
	Tip.AddTool(GetDlgItem(IDC_CLOCK_2), TEXT("点击小飞机"));
	Tip.AddTool(GetDlgItem(IDC_CLOCK_3), TEXT("给我发信息"));

	// 设置缓冲区属性
	for (size_t i = 0; i < ClockNumber; i++)
	{
		ClockBuffDC[i].SetBkMode(TRANSPARENT);		// 设置透明
		ClockBuffDC[i].SetTextColor(RGB(50, 50, 50));// 设置字体颜色
	}

	// 设置指针长度和宽度、表盘轮廓宽度、中心圈宽度
	HandHourLength = static_cast<int>(ClockClientRect->Width() / 2 * 0.6);
	HandMinuteLength = static_cast<int>(ClockClientRect->Width() / 2 * 0.75);
	HandSecondLength = static_cast<int>(ClockClientRect->Width() / 2 * 0.9);
	HandHourWidth = 3;
	HandMinuteWidth = 2;
	HandSecondWidth = 1;
	DialCircleOutsideWidth = 0;
	DialCircleInsideWidth = 3;
	CentralCircleWidth = 2;

	// 设置刻度长度和宽度
	for (size_t i = 0; i < 12; ++i)
	{
		ClockScaleWidth[i] = 2;
		ClockScaleLength[i] = 8;
	}
	ClockScaleWidth[0] = ClockScaleWidth[3] = ClockScaleWidth[6] = ClockScaleWidth[9] = 4;
	ClockScaleLength[0] = ClockScaleLength[3] = ClockScaleLength[6] = ClockScaleLength[9] = 12;

	// 计算刻度位置
	for (size_t i = 0; i < 12; ++i)
	{
		ClockScaleBeg[i].x = static_cast<int>((ClockClientRect->Width() / 2 - BorderWidth - ClockScaleLength[i]) * sin((i / 12.0) * 2 * PI) + ClockCenterPoint[0].x);
		ClockScaleBeg[i].y = static_cast<int>((ClockClientRect->Width() / 2 - BorderWidth - ClockScaleLength[i]) * (-cos((i / 12.0) * 2 * PI)) + ClockCenterPoint[0].y);
		ClockScaleEnd[i].x = static_cast<int>((ClockClientRect->Width() / 2 - BorderWidth) * sin((i / 12.0) * 2 * PI) + ClockCenterPoint[0].x);
		ClockScaleEnd[i].y = static_cast<int>((ClockClientRect->Width() / 2 - BorderWidth) * (-cos((i / 12.0) * 2 * PI)) + ClockCenterPoint[0].y);
	}


	// 指针颜色
	HandHourPen.CreatePen(PS_SOLID, HandHourWidth, RGB(200, 0, 0));
	HandMinutePen.CreatePen(PS_SOLID, HandMinuteWidth, RGB(0, 0, 0));
	HandSecondPen.CreatePen(PS_SOLID, HandSecondWidth, RGB(255, 80, 0));
	// 刻度线颜色
	for(size_t i=0;i<12;++i)
		ClockScalePen[i].CreatePen(PS_SOLID, ClockScaleWidth[i], RGB(0, 0, 0));	
	// 表盘颜色
	DialCircleOutsidePen.CreatePen(PS_SOLID, DialCircleOutsideWidth, RGB(0, 0, 0));
	DialCircleInsidePen.CreatePen(PS_SOLID, DialCircleInsideWidth, RGB(0, 124, 204));
	DialCircleOutsideBrush.CreateSolidBrush(RGB(40, 40, 40));
	DialCircleInsideBrush.CreateSolidBrush(RGB(220, 220, 220));
	// 中心圈颜色
	CentralCirclePen.CreatePen(PS_SOLID, CentralCircleWidth, RGB(190, 190, 90));
	CentralCircleBrush.CreateSolidBrush(RGB(10, 10, 10));
	// 浮动提示框颜色
	Tip.SetTipBkColor(RGB(240, 240, 240));
	Tip.SetTipTextColor(RGB(0, 122, 204));
	// 创建字体
	DialStringFont.CreatePointFont(180, TEXT("华文行楷"));
	CityStringFont.CreatePointFont(140, TEXT("华文琥珀"));
	ButtonStringFont.CreatePointFont(120, TEXT("华文行楷"));
	TipFont.CreatePointFont(140, TEXT("华文行楷"));
	// 设置字体
	GetDlgItem(IDC_TIME_0)->SetFont(&CityStringFont);
	GetDlgItem(IDC_TIME_1)->SetFont(&CityStringFont);
	GetDlgItem(IDC_TIME_2)->SetFont(&CityStringFont);
	GetDlgItem(IDC_TIME_3)->SetFont(&CityStringFont);
	GetDlgItem(IDC_SHOW_WORLD_TIME)->SetFont(&ButtonStringFont);
	GetDlgItem(IDC_RETURN)->SetFont(&ButtonStringFont);
	Tip.SetFont(&TipFont);

	// 设置浮动提示框延时并开启
	Tip.SetDelayTime(200);
	Tip.Activate(TRUE);
	// 开启定时器
	SetTimer(IDT_FRESH_CLOCK, 50, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClockContrastDlg::OnPaint()
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
		dc.DrawIcon(x, y, DlgIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClockContrastDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(DlgIcon);
}

void CClockContrastDlg::OnBnClickedShowWorldTime()
{
	ShowWindow(FALSE);
	WorldTimeDialog dlg;
	dlg.DoModal();

	ShowWindow(TRUE);
}

void CClockContrastDlg::OnBnClickedReturn()
{	
	CDialog::OnOK();
}


void CClockContrastDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case IDT_FRESH_CLOCK:
		CityTimeInfo::UpdateAllCityTime(true);
		DrawClock();
		BitBlt(PlaneCtrlpDC->m_hDC, 0, 0, PlaneCtrlRect.Width(), PlaneCtrlRect.Height(), GetImageHDC((IMAGE*)(&Plane.NextFrame())), 0, 0, SRCCOPY);
		BitBlt(MeatCtrlpDC->m_hDC, 0, 0, MeatCtrlRect.Width(), MeatCtrlRect.Height(), GetImageHDC((IMAGE*)(&Meat.NextFrame())), 0, 0, SRCCOPY);
		BitBlt(AuthorCtrlpDC->m_hDC, 0, 0, AuthorCtrlRect.Width(), AuthorCtrlRect.Height(), GetImageHDC((IMAGE*)(&Author.NextFrame())), 0, 0, SRCCOPY);
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CClockContrastDlg::DrawClock()
{
	for (size_t i = 0; i < ClockNumber; i++)
	{
		// 指针终点
		CPoint HandHourEnd;
		CPoint HandMinuteEnd;
		CPoint HandSecondEnd;

		// 计算指针终点
		HandHourEnd.x = static_cast<int>(HandHourLength * sin(((CityVector[i].Time.GetHour() % 12) * 60 + CityVector[i].Time.GetMinute()) / 720.0 * 2 * PI) + ClockCenterPoint[i].x);
		HandHourEnd.y = static_cast<int>(HandHourLength * (-cos(((CityVector[i].Time.GetHour() % 12) * 60 + CityVector[i].Time.GetMinute()) / 720.0 * 2 * PI)) + ClockCenterPoint[i].y);

		HandMinuteEnd.x = static_cast<int>(HandMinuteLength * sin((CityVector[i].Time.GetMinute() * 60 + CityVector[i].Time.GetSecond()) / 3600.0 * 2 * PI) + ClockCenterPoint[i].x);
		HandMinuteEnd.y = static_cast<int>(HandMinuteLength * (-cos((CityVector[i].Time.GetMinute() * 60 + CityVector[i].Time.GetSecond()) / 3600.0 * 2 * PI)) + ClockCenterPoint[i].y);

		HandSecondEnd.x = static_cast<int>(HandSecondLength * sin((CityVector[i].Time.GetSecond()) / 60.0 * 2 * PI) + ClockCenterPoint[i].x);
		HandSecondEnd.y = static_cast<int>(HandSecondLength * (-cos((CityVector[i].Time.GetSecond()) / 60.0 * 2 * PI)) + ClockCenterPoint[i].y);
			
		// 表盘
		ClockBuffDC[i].SelectObject(DialCircleOutsidePen);
		ClockBuffDC[i].SelectObject(DialCircleOutsideBrush);
		ClockBuffDC[i].Ellipse(DialCircleOutsideRect + i);

		ClockBuffDC[i].SelectObject(DialCircleInsidePen);
		ClockBuffDC[i].SelectObject(DialCircleInsideBrush);
		ClockBuffDC[i].Ellipse(DialCircleInsideRect + i);

		// 文字
		ClockBuffDC[i].SelectObject(DialStringFont);
		ClockBuffDC[i].DrawText(DialString[i], DialStrRect + i, DT_CENTER | DT_VCENTER| DT_WORDBREAK);

		// 刻度
		for (size_t j = 0; j < 12; ++j)
		{
			ClockBuffDC[i].SelectObject(ClockScalePen[j]);
			ClockBuffDC[i].MoveTo(ClockScaleBeg[j]);
			ClockBuffDC[i].LineTo(ClockScaleEnd[j]);
		}
		
		// 时针
		ClockBuffDC[i].SelectObject(HandHourPen);
		ClockBuffDC[i].MoveTo(ClockClientRect[i].CenterPoint());
		ClockBuffDC[i].LineTo(HandHourEnd);
		// 分针
		ClockBuffDC[i].SelectObject(HandMinutePen);
		ClockBuffDC[i].MoveTo(ClockClientRect[i].CenterPoint());
		ClockBuffDC[i].LineTo(HandMinuteEnd);
		// 秒针
		ClockBuffDC[i].SelectObject(HandSecondPen);
		ClockBuffDC[i].MoveTo(ClockClientRect[i].CenterPoint());
		ClockBuffDC[i].LineTo(HandSecondEnd);
		// 中心圈
		ClockBuffDC[i].SelectObject(CentralCirclePen);
		ClockBuffDC[i].SelectObject(CentralCircleBrush);
		ClockBuffDC[i].Ellipse(CentralCircleRect + i);

	}
	// 双缓冲贴图
	for (size_t i = 0; i < ClockNumber; i++)
		ClockCtrlpDC[i]->BitBlt(0, 0, ClockClientRect[i].Width(), ClockClientRect[i].Height(), ClockBuffDC + i, 0, 0, SRCCOPY);
	// 更新文字
	SetDlgItemText(IDC_TIME_0, CityVector[0].TimeString);
	SetDlgItemText(IDC_TIME_1, CityVector[0].TimeString);
	SetDlgItemText(IDC_TIME_2, CityVector[0].TimeString);
	SetDlgItemText(IDC_TIME_3, CityVector[0].TimeString);
}

void CClockContrastDlg::OnStnClickedPlaneImg()
{
	ShellExecute(0, NULL, _T("mailto:zhuguangfeng.thatboy@gmail.com"), NULL, NULL, SW_NORMAL);
}


BOOL CClockContrastDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_MOUSEMOVE)
		Tip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CClockContrastDlg::OnStnClickedMeatImg()
{
	ShellExecute(0, NULL, _T("http://www.24timemap.com/"), NULL, NULL, SW_NORMAL);
}


void CClockContrastDlg::OnStnClickedAuthorImg()
{
	ShellExecute(0, NULL, _T("https://thatboy.visualstudio.com/"), NULL, NULL, SW_NORMAL);
}


void CClockContrastDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// 释放资源
	TipFont.DeleteObject();

	for (auto& bmp : ClockBuffImage)
		bmp.DeleteObject();
	for (auto& dc : ClockBuffDC)
		dc.DeleteDC();
	for (auto& pen : ClockScalePen)
		pen.DeleteObject();

	DialStringFont.DeleteObject();
	CityStringFont.DeleteObject();
	ButtonStringFont.DeleteObject();

	DialCircleOutsideBrush.DeleteObject();
	DialCircleInsideBrush.DeleteObject();
	CentralCircleBrush.DeleteObject();

	HandHourPen.DeleteObject();
	HandMinutePen.DeleteObject();
	HandSecondPen.DeleteObject();
	DialCircleOutsidePen.DeleteObject();
	DialCircleInsidePen.DeleteObject();
	CentralCirclePen.DeleteObject();
}

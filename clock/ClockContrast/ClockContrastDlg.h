
// ClockContrastDlg.h: 头文件
//

#pragma once

#include "WorldTimeDialog.h"
#include "CityTimeInfo.h"

// CClockContrastDlg 对话框
class CClockContrastDlg : public CDialogEx
{
// 构造
public:
	CClockContrastDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLOCKCONTRAST_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


public:
	static constexpr size_t ClockNumber = 4;
	static constexpr int BorderWidth = 8;
	static constexpr int CentralCircleRadius = 7;
	static constexpr double PI = 3.141592654;
	static constexpr COLORREF BKColor = RGB(233, 233, 233);
// 实现
protected:
	EasyXSharp::LoopAnimation Plane;
	CDC* PlaneCtrlpDC;
	CRect PlaneCtrlRect;

	EasyXSharp::LoopAnimation Meat;
	CDC* MeatCtrlpDC;
	CRect MeatCtrlRect;

	EasyXSharp::LoopAnimation Author;
	CDC* AuthorCtrlpDC;
	CRect AuthorCtrlRect;

	CToolTipCtrl Tip;	// 浮动提示框
	CFont TipFont;

	CDC* ClockCtrlpDC[ClockNumber];
	CDC ClockBuffDC[ClockNumber];
	CBitmap ClockBuffImage[ClockNumber];

	HICON DlgIcon;

	std::vector<CityTimeInfo> CityVector;		// 城市时间信息
	CRect ClockClientRect[ClockNumber];			// 时钟区域
	CRect DialCircleOutsideRect[ClockNumber];	// 时钟表盘外围
	CRect DialCircleInsideRect[ClockNumber];	// 时钟表盘内侧
	CRect CentralCircleRect[ClockNumber];		// 表盘中心圈

	CPoint ClockCenterPoint[ClockNumber];		// 时钟中心

	CString DialString[ClockNumber];			// 表盘文字
	CRect DialStrRect[ClockNumber];				// 表盘文字矩形

	CPoint ClockScaleBeg[12];					// 时钟刻度
	CPoint ClockScaleEnd[12];					// 时钟刻度

	CFont DialStringFont;					// 文字字体
	CFont CityStringFont;					// 文字字体
	CFont ButtonStringFont;					// 文字字体

	// 表盘颜色
	CBrush DialCircleOutsideBrush;			// 表盘外侧填充
	CBrush DialCircleInsideBrush;			// 表盘内侧填充
	CBrush CentralCircleBrush;				// 表盘中心圈

	// 边界颜色
	CPen HandHourPen;
	CPen HandMinutePen;
	CPen HandSecondPen;
	CPen DialCircleOutsidePen;
	CPen DialCircleInsidePen;
	CPen CentralCirclePen;
	CPen ClockScalePen[12];

	int DialCircleOutsideWidth;
	int DialCircleInsideWidth;
	int CentralCircleWidth;		// 中心圈边界宽度
	int ClockScaleWidth[12];	// 刻度宽度
	int ClockScaleLength[12];	// 刻度长度
	int HandHourWidth;			// 时针宽度
	int HandHourLength;			// 时针长度
	int HandMinuteWidth;		// 分针宽度
	int HandMinuteLength;		// 分针长度
	int HandSecondWidth;		// 秒针宽度
	int HandSecondLength;		// 秒针长度

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedShowWorldTime();
	afx_msg void OnBnClickedReturn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedPlaneImg();
	afx_msg void OnStnClickedMeatImg();
	afx_msg void OnStnClickedAuthorImg();
protected:
	void DrawClock();
public:
	afx_msg void OnDestroy();
};

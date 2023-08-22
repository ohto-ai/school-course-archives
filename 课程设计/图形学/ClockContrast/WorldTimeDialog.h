#pragma once

#ifndef WORLD_TIME_DIALOG_H
#define WORLD_TIME_DIALOG_H

#include "CityTimeInfo.h"
// WorldTimeDialog 对话框

class WorldTimeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(WorldTimeDialog)

public:
	WorldTimeDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WorldTimeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORLD_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	static BOOL LoadImageFromResource(ATL::CImage* pImage, UINT nResID, LPCTSTR lpTyp);
protected:
	CImage WorldTimeImage;
	CDC* WorldTimeImageCtrlDC;
	CRect WorldTimeImageCtrlRect;
	std::vector<WorldCityTimeInfo> CityVector;
	CToolTipCtrl Tip;
	CFont TipFont;
	CFont Font;
	CPen Pen;
	CBrush Brush;
	
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};

#endif // ! WORLD_TIME_DIALOG_H
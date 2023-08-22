
// ThatboyEncryptFileEncoderDlg.h: 头文件
//

#pragma once

#include "SkinH.h"

// CThatboyEncryptFileEncoderDlg 对话框
class CThatboyEncryptFileEncoderDlg : public CDialogEx
{
// 构造
public:
	CThatboyEncryptFileEncoderDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDDTEF_THATBOYENCRYPTFILEENCODER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrower();
	afx_msg void OnBnClickedNeedPassword();
	afx_msg void OnBnClickedNeedDeviceBind();
	afx_msg void OnBnClickedEncrypt();
	afx_msg void OnBnClickedDecrypt();
	void pushInfo(CString);
	afx_msg void OnDropFiles(HDROP hDropInfo);
protected:
	CToolTipCtrl toolTip;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	void updateFilePath(CString filePath);
};

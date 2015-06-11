
#include "AdkPrecomp.h"
#include "databasemanager.h"
#include "AdkBase64.h"
#include "AdkMemory.h"
//#include "AdkString.h"
#include "maindlg.h"
#include "Utility.h"
#include "LocalDataDir.h"

#include <shellapi.h>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

DatabaseManager* DM = NULL; 

// ////////////////////////////////////////////////////////////////////////////////
// 构造函数
//
DatabaseManager::DatabaseManager(std::wstring connStr, std::wstring User, std::wstring Password)
{
	db = QSqlDatabase::addDatabase("QODBC");

	db.setDatabaseName(QString::fromStdWString(connStr));
	db.setUserName(QString::fromStdWString(User));
	db.setPassword(QString::fromStdWString(Password));

	if ( !db.open() ) 
	{
		qDebug() << "[DatabaseManager] Open Database Failed.\r\n";

		MessageBoxW(NULL, db.lastError().text().toStdWString().c_str(), L"提示", MB_OK | MB_ICONERROR);
		qDebug() << db.lastError().text();
	}

	InitializeCriticalSection(&csPlgData);
	InitializeCriticalSection(&csGui);
	InitializeCriticalSection(&csControlConn);
	InitializeCriticalSection(&csTarConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// 析构函数
//
DatabaseManager::~DatabaseManager()
{
	DeleteCriticalSection(&csPlgData);
	DeleteCriticalSection(&csGui);    
	DeleteCriticalSection(&csControlConn);
	DeleteCriticalSection(&csTarConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询目标列表
//
void DatabaseManager::QueryTargetList()
{
	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( query.exec("SELECT * FROM TARGET_INFO") )
	{

		while ( query.next() )
		{
			Target *tar = new Target();

			tar->dwTargetID	= query.value(0).toUInt();
			tar->aniTargetName	= query.value(1).toString().toLocal8Bit();
			tar->dwGroupID	= query.value(2).toUInt();

			tar->dwOsBuildNumber		= query.value(3).toUInt();
			tar->aniRemLocalIpAddr	= query.value(4).toString().toStdString();
			tar->aniRemPublicIpAddr	= query.value(5).toString().toStdString();
			tar->aniRemMacAddr		= query.value(6).toString().toStdString();
			tar->dwProtocolVersion	= query.value(7).toUInt();
			tar->widLocalDataDir = query.value(8).toString().toStdWString();
			tar->aniLocalDataDir		= query.value(8).toString().toStdString();

			tar->dwLangId           = query.value(9).toUInt();
			tar->aniComputerNameBase64 = query.value(10).toString().toStdString();
			tar->m_netEnv = query.value(11).toUInt();
			tar->m_favorite = (query.value(13).toUInt() == 1);
			tar->m_autoGetDirInfoDepth = query.value(14).toInt();

			/*tar->aniLocalDataDir	= WideToAnsi(tar->widLocalDataDir);
			tar->widDiskDataDir		= tar->widLocalDataDir + L"\\Disk";
			tar->widUsbDataDir		= tar->widLocalDataDir + L"\\Usb";
			tar->widDelDataDir		= tar->widLocalDataDir + L"\\Delete";
			tar->wideScreenPath		= tar->widLocalDataDir + L"\\Screen";
			tar->widHttpsDataDir	= tar->widLocalDataDir + L"\\Https";
			tar->widDirPath			= tar->widLocalDataDir + L"\\Dir";*/

			SendMessage(FrmMain->Handle, WM_TARGET_FOUND, (unsigned int)tar, NULL);

		}
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 添加目标
//
void DatabaseManager::AddTarget(Target *tar)
{

	char sqlValue[1024];

	sprintf(sqlValue," VALUES (%u, '%s', %u, %u, '%s', '%s', '%s', %u, '%s', %u, %u, 0, -1)",
		tar->dwTargetID,
		tar->aniTargetName.c_str(),
		tar->dwGroupID,
		tar->dwOsBuildNumber,
		tar->aniRemLocalIpAddr.c_str(),
		tar->aniRemPublicIpAddr.c_str(),
		tar->aniRemMacAddr.c_str(),
		tar->dwProtocolVersion,
		tar->aniLocalDataDir.c_str(),
		tar->m_netEnv,
		0xFFFFFF);

	QSqlQuery query;
	QString cmd("Insert into target_info");
	cmd += " (targetId,targetName,GroupId,osBuildNumber,localIpAddr,publicIpAddr,macAddr, protocolversion, LocalDataPath, netEnv, pluginEnable, favorite, autoGetDirInfo) ";
	cmd += QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csGui);

	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] AddTarget Failed.\r\n";
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 添加目标信息
//
void DatabaseManager::UpdateTargetInfo(Target *tar)
{
	char sqlValue[1024];

	sprintf(sqlValue," targetId = %d, targetName = '%s', GroupId = %d, osBuildNumber = %d, localIpAddr = '%s', publicIpAddr = '%s', macAddr = '%s', protocolversion = %d, LocalDataPath = '%s', netEnv = %u",
					 tar->dwTargetID,
					 tar->aniTargetName.c_str(),
					 tar->dwGroupID,
					 tar->dwOsBuildNumber,
					 tar->aniRemLocalIpAddr.c_str(),
					 tar->aniRemPublicIpAddr.c_str(),
					 tar->aniRemMacAddr.c_str(),
					 tar->dwProtocolVersion,
					 tar->aniLocalDataDir.c_str(),
					 tar->m_netEnv);

	QSqlQuery query;
	QString cmd("UPDATE target_info SET ");

	cmd += QString::fromLocal8Bit(sqlValue);
	cmd += QString(" WHERE targetId = %1").arg(tar->dwTargetID);

	//qDebug() << cmd;

	EnterCriticalSection(&csGui);

	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] UpdateTargetInfo Failed.\r\n";
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 添加目标信息
//
void DatabaseManager::UpdateTargetExInfo(Target *tar)
{
	QSqlQuery query;
	QString cmd(" UPDATE target_info SET");
	
	cmd += QString(" OsLangId = %1, ComputerName = '%2'").arg(tar->dwLangId)
		.arg(QString::fromLocal8Bit(tar->aniComputerNameBase64.c_str()));
	cmd += QString(" WHERE targetId = %1").arg(tar->dwTargetID);

	EnterCriticalSection(&csGui);

	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] UpdateTargetExInfo Failed.\r\n";
	}

	LeaveCriticalSection(&csGui);
}

DWORD DatabaseManager::QueryTargetPluginStatus(DWORD targetId)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"SELECT pluginEnable FROM target_info WHERE targetId = %u", targetId);

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[UpdatetargetPluginStatus] QueryTargetPluginStatus Failed.\r\n";
	}

	query.next();

	DWORD value = query.value(0).toUInt();

	LeaveCriticalSection(&csGui);

	return value;
}

void DatabaseManager::UpdatetargetPluginStatus(DWORD targetId, DWORD status)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"UPDATE target_info SET pluginEnable = %u WHERE targetId = %u", status, targetId);

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[UpdatetargetPluginStatus] UpdateTargetExInfo Failed.\r\n";
	}

	LeaveCriticalSection(&csGui);
}

void DatabaseManager::UpdateTargetFavoriteStatus(DWORD targetId, bool status)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"UPDATE target_info SET favorite = %u WHERE targetId = %u", (unsigned int)status, targetId);

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[UpdatetargetPluginStatus] UpdateTargetExInfo Failed.\r\n";
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询自动获取设置
//
int DatabaseManager::QueryTargetAutoGetStatus(DWORD targetId)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"SELECT autoGetDirInfo FROM target_info WHERE targetId = %u", targetId);

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] QueryTargetAutoGetStatus Failed.\r\n";
	}

	query.next();

	int value = query.value(0).toInt();

	LeaveCriticalSection(&csGui);

	return value;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 更新自动获取设置
//
void DatabaseManager::UpdateTargetAutoGetStatus(DWORD targetId, int depth)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"UPDATE target_info SET autoGetDirInfo = %d WHERE targetId = %u", depth, targetId);

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] UpdateTargetAutoGetStatus Failed.\r\n";
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 移除目标
//
void DatabaseManager::ClearAndRemoveTarget(ULONG targetId)
{
	QSqlQuery query;

	EnterCriticalSection(&csGui);

	query.exec(QString("delete from monitor_clipboard where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from monitor_file_operation where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from monitor_https where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from monitor_keyboard_input where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from monitor_pass_window where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from monitor_process_execute where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from monitor_usb_operation where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from usb_offline_dir where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from offline_dir where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from async_search where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from task_file where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from task_dirinfo where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from task_dirdown where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from task_search where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from target_loginfo where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from target_logicdriver where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from target_plugin where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from target_info where targetId = %1 ").arg(targetId));

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 清除目标任务历史
//
void DatabaseManager::ClearTargetHistoryTask(ULONG targetId)
{
	QSqlQuery query;

	EnterCriticalSection(&csGui);

	query.exec(QString("delete from task_file where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from task_dirinfo where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from task_dirdown where targetId = %1 ").arg(targetId));
	query.exec(QString("delete from task_search where targetId = %1 ").arg(targetId));

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 增加目标磁盘列表
//
void DatabaseManager::AddTargetLogicDriver(ULONG targetId, DriverSet &logDriver)
{
	QSqlQuery query;
	QString cmd("Insert into target_logicdriver");
	char encode[MAX_PATH];

	AdkBase64Encode(logDriver.DriveType, 32, encode, MAX_PATH);
	cmd += " (targetId, DriverMap, DriverType, lastTime) ";
	cmd += QString(" VALUES (%1, %2, '%3', '%4')")
		.arg(targetId)
		.arg(logDriver.DriveMap)
		.arg(encode)
		.arg(TGetCurrentTime().c_str());
	
	EnterCriticalSection(&csControlConn);
	
	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] AddTargetLogicDriver Failed.\r\n";
	}

	LeaveCriticalSection(&csControlConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询目标磁盘列表
//
int DatabaseManager::QueryTargetLogicDriver(ULONG targetId, DriverSet &logDriver)
{
	QSqlQuery query;

	QString cmd = QString("select Top 1 DriverMap, DriverType from target_logicdriver where targetid = %1 ORDER BY lasttime DESC")
		.arg(targetId);

	EnterCriticalSection(&csGui);

	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] QueryTargetLogicDriver Failed.\r\n";
	}

	LeaveCriticalSection(&csGui);

	if ( query.next() )
	{
		logDriver.DriveMap = query.value(0).toInt();
		std::string base64 = query.value(1).toString().toStdString();

		// 进行反Base64编码
		//
		BYTE driverType[32];
		AdkBase64Decode(base64.c_str(), base64.length(), driverType, 32);
		CopyMemory(logDriver.DriveType, driverType, 32);

	}
	
	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询目标插件列表
//
void DatabaseManager::QueryTargetPluginList(ULONG targetId, PPLUGIN_CONTEXT PlgContext[MAX_PLG_COUNT])
{
	PPLUGIN_CONTEXT lpPluginCxt;
	DWORD			dwPluginId;

	QSqlQuery query;
	QString cmd("select * from target_plugin");
	cmd += QString(" where targetId = %1").arg(targetId);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	while ( query.next() )
	{
		dwPluginId = query.value(1).toInt();

		if (PlgContext[dwPluginId] == NULL)
		{
			lpPluginCxt = (PPLUGIN_CXT)malloc(sizeof(PLUGIN_CXT));
			ZeroMemory(lpPluginCxt, sizeof(PLUGIN_CXT));                
			lpPluginCxt->dwPluginId = dwPluginId;

			lpPluginCxt->lpszPluginName = strdup(query.value(2).toString().toAscii());
			lpPluginCxt->dwPluginVer = query.value(3).toInt();
			lpPluginCxt->dwUpdateVer = query.value(4).toInt();
			lpPluginCxt->dwUpdateType = query.value(5).toInt();
			lpPluginCxt->dwLoadType = query.value(6).toInt();
			lpPluginCxt->lpszProcList = strdup(query.value(7).toString().toAscii());

			PlgContext[dwPluginId] = lpPluginCxt;
		}
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询目标是否存在指定插件
//
bool DatabaseManager::TargetPluginIsExisted(ULONG  targetId, ULONG  pluginId)
{
	QSqlQuery query;

	EnterCriticalSection(&csControlConn);
	query.exec(QString("select * from target_plugin where targetId = %1 and plgId = %2").arg(targetId).arg(pluginId));
	LeaveCriticalSection(&csControlConn);
	
	return (query.next() != 0);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 更新目标插件信息
//
void DatabaseManager::UpdateTargetPluginInfo(ULONG           targetId,
											PPLUGIN_CONTEXT lpPlgContext)
{
	CHAR sqlValue[1024] = {0};
	sprintf(sqlValue, "UPDATE target_plugin SET \
						plgName = '%s', plgVersion = %u, plgUptVersion = %u, plgUptType = %u, \
						plgLoadType = %u, plgProcList = '%s' Where targetId = %d and plgId = %d",
						lpPlgContext->lpszPluginName,
						lpPlgContext->dwPluginVer,
						lpPlgContext->dwUpdateVer,
						lpPlgContext->dwUpdateType,
						lpPlgContext->dwLoadType,
						lpPlgContext->lpszProcList,
						targetId,
						lpPlgContext->dwPluginId);
	QSqlQuery query;
	QString cmd = QString::fromStdWString(AnsiToWide(sqlValue));

	EnterCriticalSection(&csControlConn);
	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] UpdateTargetPluginInfo Failed.\r\n";
	}
	LeaveCriticalSection(&csControlConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入目标插件信息
//
void DatabaseManager::InsertTargetPluginInfo(ULONG           targetId,
											 PPLUGIN_CONTEXT lpPlgContext)
{

	CHAR sqlValue[1024] = {0};
	sprintf(sqlValue, "INSERT INTO target_plugin (targetId, plgid, plgName, plgVersion, plgUptVersion, plgUptType, plgLoadType, plgProcList) \
						 VALUES (%u, %u, '%s', %d, %d, %d, %d, '%s')",
						 targetId,
						 lpPlgContext->dwPluginId,
						 lpPlgContext->lpszPluginName,
						 lpPlgContext->dwPluginVer,
						 lpPlgContext->dwUpdateVer,
						 lpPlgContext->dwUpdateType,
						 lpPlgContext->dwLoadType,
						 lpPlgContext->lpszProcList);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(AnsiToWide(sqlValue));

	EnterCriticalSection(&csControlConn);
	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] InsertTargetPluginInfo Failed.\r\n";
	}
	LeaveCriticalSection(&csControlConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询日志信息
//
void DatabaseManager::QueryLogInfo(ULONG targetId, PageTableWidget* table)
{

	char sqlValue[1024] = {0};

	sprintf(sqlValue, "select * from target_loginfo where targetId = %u", targetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	// false = offline true = online
	bool lastStatus = false;

	while ( query.next() )
	{
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* status = new QTableWidgetItem;
		QTableWidgetItem* publicIp = new QTableWidgetItem;
		QTableWidgetItem* localIp = new QTableWidgetItem;
		QTableWidgetItem* macAddress = new QTableWidgetItem;
		QTableWidgetItem* proc = new QTableWidgetItem;
		QTableWidgetItem* user = new QTableWidgetItem;

		time->setTextAlignment(Qt::AlignCenter);
		status->setTextAlignment(Qt::AlignCenter);
		publicIp->setTextAlignment(Qt::AlignCenter);
		localIp->setTextAlignment(Qt::AlignCenter);
		macAddress->setTextAlignment(Qt::AlignCenter);
		proc->setTextAlignment(Qt::AlignCenter);
		user->setTextAlignment(Qt::AlignCenter);

		time->setText(query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		status->setText(query.value(1).toString());
		publicIp->setText(query.value(4).toString());
		localIp->setText(query.value(3).toString());
		macAddress->setText(query.value(5).toString());
		std::string procstr = query.value(6).toString().toStdString();
		proc->setText(QString::fromStdWString(GetWideFromBase64(procstr.c_str())));
		std::string userstr = query.value(7).toString().toStdString();
		user->setText(QString::fromStdWString(GetWideFromBase64(userstr.c_str())));

		if ( query.value(1).toString() == QString::fromLocal8Bit("上线") )
		{
			time->setIcon(QIcon(QPixmap("image/normalmsg.png")));
			if ( lastStatus )
			{
				AddFakeRow(false, time, status, publicIp, localIp, macAddress, proc, user, table);
			}
			lastStatus = true;
		}
		else
		{
			time->setIcon(QIcon(QPixmap("image/errormsg.png")));

			if ( !lastStatus )
			{
				AddFakeRow(true, time, status, publicIp, localIp, macAddress, proc, user, table);
			}

			lastStatus = false;
		}

		table->AppendRow();
		table->SetAppendRowItem(0, time);
		table->SetAppendRowItem(1, status);
		table->SetAppendRowItem(2, publicIp);
		table->SetAppendRowItem(3, localIp);
		table->SetAppendRowItem(4, macAddress);
		table->SetAppendRowItem(5, proc);
		table->SetAppendRowItem(6, user);
	}

	LeaveCriticalSection(&csGui);

	table->RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 添加假记录，确保上下线成对出现
//
void DatabaseManager::AddFakeRow(
	bool online,
	QTableWidgetItem* time, 
	QTableWidgetItem* status,
	QTableWidgetItem* publicIp,
	QTableWidgetItem* localIp,
	QTableWidgetItem* macAddress,
	QTableWidgetItem* proc,
	QTableWidgetItem* user,
	PageTableWidget* table)
{
	QTableWidgetItem* timeNew = new QTableWidgetItem(*time);
	QTableWidgetItem* statusNew = new QTableWidgetItem(*status);
	QTableWidgetItem* publicIpNew = new QTableWidgetItem(*publicIp);
	QTableWidgetItem* localIpNew = new QTableWidgetItem(*localIp);
	QTableWidgetItem* macAddressNew = new QTableWidgetItem(*macAddress);
	QTableWidgetItem* procNew = new QTableWidgetItem(*proc);
	QTableWidgetItem* userNew = new QTableWidgetItem(*user);

	QDateTime lastTime = QDateTime::fromString(timeNew->text(), "yyyy-MM-dd hh:mm:ss");
	lastTime = lastTime.addSecs(-600);

	timeNew->setText(lastTime.toString("yyyy-MM-dd hh:mm:ss"));

	if ( online )
	{
		timeNew->setIcon(QIcon(QPixmap("image/normalmsg.png")));
		statusNew->setText(QString::fromLocal8Bit("上线"));
	}
	else
	{
		timeNew->setIcon(QIcon(QPixmap("image/errormsg.png")));
		statusNew->setText(QString::fromLocal8Bit("下线"));
	}

	table->AppendRow();
	table->SetAppendRowItem(0, timeNew);
	table->SetAppendRowItem(1, statusNew);
	table->SetAppendRowItem(2, publicIpNew);
	table->SetAppendRowItem(3, localIpNew);
	table->SetAppendRowItem(4, macAddressNew);
	table->SetAppendRowItem(5, procNew);
	table->SetAppendRowItem(6, userNew);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询日志详细信息
//

void DatabaseManager::QueryLogDetailInfo(unsigned int targetId, PageTableWidget* table)
{
	char sqlValue[1024] = {0};

	sprintf(sqlValue, "select top 10000 * from target_logDetailInfo where targetId = %u", targetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* content = new QTableWidgetItem;

		time->setText(query.value(2).toString());
		QString contentStr = query.value(3).toString();
		content->setText(contentStr);
		content->setToolTip(contentStr);

		table->AppendRow();
		table->SetAppendRowItem(0, time);
		table->SetAppendRowItem(1, content);
	}

	LeaveCriticalSection(&csGui);
	table->RefreshPage();


	emitLogDetailInfoFinished(targetId);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询下载日志详细信息
//

void DatabaseManager::QueryLogDownloadInfo(unsigned int targetId, PageTableWidget* table)
{
	char sqlValue[1024] = {0};

	sprintf(sqlValue, "select top 10000 * from task_file \
					  where targetId = %u \
					  and (taskType = 0 or taskTYpe = 4) \
					  and taskDirect = 1", targetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	while ( query.next() )
	{
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* id = new QTableWidgetItem;
		QTableWidgetItem* plugin = new QTableWidgetItem;
		QTableWidgetItem* status = new QTableWidgetItem;
		QTableWidgetItem* src = new QTableWidgetItem;
		QTableWidgetItem* dst = new QTableWidgetItem;
		QTableWidgetItem* size = new QTableWidgetItem;

		time->setTextAlignment(Qt::AlignCenter);
		id->setTextAlignment(Qt::AlignCenter);
		plugin->setTextAlignment(Qt::AlignCenter);
		status->setTextAlignment(Qt::AlignCenter);
		src->setTextAlignment(Qt::AlignCenter);
		dst->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		size->setTextAlignment(Qt::AlignCenter);

		time->setText(query.value(8).toString());
		id->setText(query.value(2).toString());

		plugin->setText(QString::fromLocal8Bit(ConvertPluginIdToLang(query.value(14).toUInt()).c_str()));

		unsigned int statusInt = query.value(4).toUInt();
		std::wstring statusStr = ConvertTaskStatusToLangW((TaskStatus)statusInt);
		status->setText(QString::fromStdWString(statusStr));

		std::string srcEncode = query.value(9).toString().toStdString();
		std::wstring srcDecode = GetWideFromBase64(srcEncode);

		if ( srcDecode == L".." )
			src->setText(QString::fromLocal8Bit("本地数据仿真目录"));
		else
			src->setText(QString::fromStdWString(srcDecode));

		std::string dstEncode = query.value(10).toString().toStdString();
		std::wstring dstDecode = GetWideFromBase64(dstEncode);
		dst->setText(QString::fromStdWString(dstDecode));
		dst->setToolTip(QString::fromStdWString(dstDecode));

		size->setText(query.value(13).toString());

		table->AppendRow();
		table->SetAppendRowItem(0, time);
		table->SetAppendRowItem(1, id);
		table->SetAppendRowItem(2, plugin);
		table->SetAppendRowItem(3, status);
		table->SetAppendRowItem(4, src);
		table->SetAppendRowItem(5, dst);
		table->SetAppendRowItem(6, size);

	}
	LeaveCriticalSection(&csGui);

	table->RefreshPage();

	emitLogDownloadInfoFinished(targetId);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询上传日志
//
void DatabaseManager::QueryLogUploadInfo(unsigned int targetId, PageTableWidget* table)
{
	char sqlValue[1024] = {0};

	sprintf(sqlValue, "select top 10000 * from task_file \
					  where targetId = %u \
					  and (taskType = 0 or taskTYpe = 4) \
					  and taskDirect = 0", targetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* id = new QTableWidgetItem;
		QTableWidgetItem* plugin = new QTableWidgetItem;
		QTableWidgetItem* status = new QTableWidgetItem;
		QTableWidgetItem* src = new QTableWidgetItem;
		QTableWidgetItem* dst = new QTableWidgetItem;
		QTableWidgetItem* size = new QTableWidgetItem;

		time->setTextAlignment(Qt::AlignCenter);
		id->setTextAlignment(Qt::AlignCenter);
		plugin->setTextAlignment(Qt::AlignCenter);
		status->setTextAlignment(Qt::AlignCenter);
		src->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		dst->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		size->setTextAlignment(Qt::AlignCenter);

		time->setText(query.value(8).toString());
		id->setText(query.value(2).toString());

		plugin->setText(QString::fromLocal8Bit(ConvertPluginIdToLang(query.value(14).toUInt()).c_str()));

		unsigned int statusInt = query.value(4).toUInt();
		std::wstring statusStr = ConvertTaskStatusToLangW((TaskStatus)statusInt);
		status->setText(QString::fromStdWString(statusStr));

		std::string srcEncode = query.value(9).toString().toStdString();
		std::wstring srcDecode = GetWideFromBase64(srcEncode);

		if ( srcDecode == L".." )
			src->setText(QString::fromLocal8Bit("本地数据仿真目录"));
		else
			src->setText(QString::fromStdWString(srcDecode));

		std::string dstEncode = query.value(10).toString().toStdString();
		std::wstring dstDecode = GetWideFromBase64(dstEncode);
		dst->setText(QString::fromStdWString(dstDecode));
		dst->setToolTip(QString::fromStdWString(dstDecode));

		size->setText(query.value(13).toString());

		table->AppendRow();
		table->SetAppendRowItem(0, time);
		table->SetAppendRowItem(1, id);
		table->SetAppendRowItem(2, plugin);
		table->SetAppendRowItem(3, status);
		table->SetAppendRowItem(4, src);
		table->SetAppendRowItem(5, dst);
		table->SetAppendRowItem(6, size);

	}

	LeaveCriticalSection(&csGui);
	table->RefreshPage();

	emitLogUploadInfoFinished(targetId);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询插件回传日志
//
void DatabaseManager::QueryLogPluginInfo(unsigned int targetId, PageTableWidget* table)
{
	char sqlValue[1024] = {0};

	sprintf(sqlValue, "select top 10000 * from task_file \
					  where targetId = %u \
					  and taskType = 1", targetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* id = new QTableWidgetItem;
		QTableWidgetItem* plugin = new QTableWidgetItem;
		QTableWidgetItem* status = new QTableWidgetItem;
		QTableWidgetItem* src = new QTableWidgetItem;
		QTableWidgetItem* dst = new QTableWidgetItem;
		QTableWidgetItem* size = new QTableWidgetItem;

		time->setTextAlignment(Qt::AlignCenter);
		id->setTextAlignment(Qt::AlignCenter);
		plugin->setTextAlignment(Qt::AlignCenter);
		status->setTextAlignment(Qt::AlignCenter);
		src->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		dst->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
		size->setTextAlignment(Qt::AlignCenter);

		time->setText(query.value(8).toString());
		id->setText(query.value(2).toString());

		plugin->setText(QString::fromLocal8Bit(ConvertPluginIdToLang(query.value(14).toUInt()).c_str()));

		unsigned int statusInt = query.value(4).toUInt();
		std::wstring statusStr = ConvertTaskStatusToLangW((TaskStatus)statusInt);
		status->setText(QString::fromStdWString(statusStr));

		std::string srcEncode = query.value(9).toString().toStdString();
		std::wstring srcDecode = GetWideFromBase64(srcEncode);

		if ( srcDecode == L".." )
			src->setText(QString::fromLocal8Bit("本地数据仿真目录"));
		else
			src->setText(QString::fromStdWString(srcDecode));

		std::string dstEncode = query.value(10).toString().toStdString();
		std::wstring dstDecode = GetWideFromBase64(dstEncode);
		dst->setText(QString::fromStdWString(dstDecode));
		dst->setToolTip(QString::fromStdWString(dstDecode));

		size->setText(query.value(13).toString());

		table->AppendRow();
		table->SetAppendRowItem(0, time);
		table->SetAppendRowItem(1, id);
		table->SetAppendRowItem(2, plugin);
		table->SetAppendRowItem(3, status);
		table->SetAppendRowItem(4, src);
		table->SetAppendRowItem(5, dst);
		table->SetAppendRowItem(6, size);

	}

	LeaveCriticalSection(&csGui);

	table->RefreshPage();

	emitLogPluginInfoFinished(targetId);
}


// ////////////////////////////////////////////////////////////////////////////////
// @public 插入目标日志信息
//
void DatabaseManager::InsertTargetLogInfo(ULONG      targetId,
										  const char  *status,
										  const char  *lastTime,
										  const char  *aniRemLocalIpAddr,
										  const char  *aniRemPublicIpAddr,
										  const char  *aniRemMacAddr,
										  const char  *lpOnlineProcBase64,
										  const char  *lpLoginUserBase64)
{

	QString cmd("INSERT INTO target_loginfo (targetId, status, lastTime, localIpAddr, publicIpAddr, macAddr, OnlineProcess, LoginUser)");

	if ( lpOnlineProcBase64 && lpLoginUserBase64 )
	{
		cmd += QString(" VALUES (%1, '%2', '%3', '%4', '%5', '%6', '%7', '%8')")
			.arg(targetId)
			.arg(QString::fromLocal8Bit(status))
			.arg(lastTime)
			.arg(aniRemLocalIpAddr)
			.arg(aniRemPublicIpAddr)
			.arg(aniRemMacAddr)
			.arg(lpOnlineProcBase64)
			.arg(lpLoginUserBase64);
	}
	else
	{
		cmd += QString(" VALUES (%1, '%2', '%3', '%4', '%5', '%6', NULL, NULL)")
			.arg(targetId)
			.arg(QString::fromLocal8Bit(status))
			.arg(lastTime)
			.arg(aniRemLocalIpAddr)
			.arg(aniRemPublicIpAddr)
			.arg(aniRemMacAddr);
	}

	QSqlQuery query;

	EnterCriticalSection(&csControlConn);

	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] InsertTargetLogInfo Failed.\r\n";
	}

	LeaveCriticalSection(&csControlConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入细节日志信息
//
void DatabaseManager::InsertLogDetailInfo(ULONG targetId, std::wstring time, std::wstring content)
{
	WCHAR sqlVaue[1024] = {0};
	wsprintf(sqlVaue, 
		L"INSERT INTO target_logDetailInfo (targetId, logTime, logDetail) VALUES (%d, '%s', '%s')",
		targetId,
		time.c_str(),
		content.c_str());

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlVaue))) )
	{
		qDebug() << "[DatabaseManager] InsertLogDetailInfo Failed.\r\n";
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 将目标目录信息入库
//
void DatabaseManager::AddOfflineDirInfo(Target     *tarBlock,
										std::string  timeStr,
									    const char *lpszdirPath,
									    const char *lpszdirData)
{
	// 首先看数据库中最新的一个相同路径的数据
	//
	std::string lastDirTime;
	std::string lastDirData;
	int     lastId = 0;
	DWORD   targetId = tarBlock->dwTargetID;
	char sqlValue[512];

	assert((lpszdirPath));

	EnterCriticalSection(&csGui);       // 下面的行为是一体的，所以套在一个关键区域内

	int nCount = QueryLastOfflineDirInfo(targetId, lpszdirPath, lastDirTime, lastDirData, &lastId);

	QSqlQuery query;

	if (nCount > 0)
	{
		// 删除原有数据
		//
		QString cmd = QString("delete from offline_dir where id = %1").arg(lastId);
		query.exec(cmd);
	}

	// 插入数据
	QString cmd = QString("INSERT INTO offline_dir (TargetId, DirTime, DirPath, DirData) VALUES (%1, '%2', '%3', '%4')")
		.arg(targetId)
		.arg(timeStr.c_str())
		.arg(QString::fromLocal8Bit(lpszdirPath))
		.arg(QString::fromLocal8Bit(lpszdirData));
	
	query.exec(cmd);

	if (nCount > 0)
	{
		// 比较数据是否一致
		//
		bool bSame = true;

		if (lpszdirData)
		{
			if (lastDirData.length() == 0)
			{
				bSame = false;
			}
			else if ( 0 != AdkCompareMemory((const PVOID)lpszdirData, (const PVOID)lastDirData.c_str(), AdkStrLen(lpszdirData)))
			{
				bSame = false;
			}
		}
		else
		{
			if (lastDirData.length() > 0)
			{                            \
			bSame = false;
			}
		}

		if (! bSame)
		{
			// 不相同的话, 则写入到本地数据目录中的对应文件中
			//      如果文件不存在,两条都写入,否则只写最新的一条记录
			//

			bool bExisted = false;
			std::wstring widFilePath = GetDirDataFileName(tarBlock->widDirPath, lpszdirPath, bExisted);
			std::wstring widDirPath = GetWideFromBase64(lpszdirPath);
			if ( ! bExisted)
			{
				ExportDirDataToLocal(targetId, widFilePath.c_str(), lastDirTime.c_str(), widDirPath.c_str(), lastDirData.c_str());
			}

			if (lpszdirData)
			{
				ExportDirDataToLocal(targetId, widFilePath.c_str(), timeStr.c_str(), widDirPath.c_str(), lpszdirData);
			}
		}
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询上次目标目录信息
//
int DatabaseManager::QueryLastOfflineDirInfo(ULONG        targetId,
											 const char   *lpszbase64Path,
											 std::string      &dirTime,
											 std::string      &dirData,
											 int          *lpnId)
{

	QSqlQuery query;
	QString cmd = QString("select id, dirTime, dirData from offline_dir where targetid = %1 and dirPath = '%2' ORDER By dirTime DESC")
		.arg(targetId)
		.arg(lpszbase64Path);

	EnterCriticalSection(&csGui);

	query.exec(cmd);

	LeaveCriticalSection(&csGui);

	if ( query.next() )
	{
		dirTime = query.value(1).toString().replace('T', ' ').toStdString();

		dirData = query.value(2).toString().toStdString();

		if ( lpnId )
		{
			*lpnId = query.value(0).toInt();
		}
		
		return 1;

	}

	return 0;
}

void DatabaseManager::AddAsyncSearchInfo(ULONG      targetId,
										 std::string	searchDirPathBase64,
										 DWORD      dwLevel,
										 DWORD      dwMinSize,
										 DWORD      dwMaxSize,
										 FILETIME   ftBegTime,
										 FILETIME   ftEndTime,
										 std::string	aniNameFilterBase64,
										 std::string	aniTypeFilterBase64,
										 PCHAR      lpData)
{
	SYSTEMTIME sBegTime, sEndTime;
	FileTimeToSystemTime(&ftBegTime, &sBegTime);
	FileTimeToSystemTime(&ftEndTime, &sEndTime);

	QString begTime = QString("%1-%2-%3 %4:%5")
		.arg(sBegTime.wYear)
		.arg(sBegTime.wMonth)
		.arg(sBegTime.wDay)
		.arg(sBegTime.wHour)
		.arg(sBegTime.wMinute);
	
	QString endTime = QString("%1-%2-%3 %4:%5")
		.arg(sEndTime.wYear)
		.arg(sEndTime.wMonth)
		.arg(sEndTime.wDay)
		.arg(sEndTime.wHour)
		.arg(sEndTime.wMinute);

	QSqlQuery query;
	QString cmd("Insert into async_search");
	cmd += " (targetId, searchTime, searchDirPath, [level], minSize, maxSize, begTime, endTime, nameFilter, typeFilter, Data) ";
	cmd += QString(" VALUES (%1, '%2', '%3', %4, %5, %6, '%7', '%8', '%9', ")
		.arg(targetId)
		.arg(TGetCurrentTime().c_str())
		.arg(searchDirPathBase64.c_str())
		.arg(dwLevel)
		.arg(dwMinSize)
		.arg(dwMaxSize)
		.arg(begTime)
		.arg(endTime)
		.arg(aniNameFilterBase64.c_str());
	cmd += QString("'%1', '%2')")
		.arg(aniTypeFilterBase64.c_str())
		.arg(lpData);

	EnterCriticalSection(&csPlgData);
	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] AddAsyncSearchInfo Failed.\r\n";
	}
	LeaveCriticalSection(&csPlgData);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询目录下载的历史记录
//
void DatabaseManager::QueryDirDownDetail(ULONG targetId, ULONG parentId, QTableWidget* table)
{
	char sqlValue[1024] = {0};
	sprintf(sqlValue, "select * from task_file where targetId=%u and parentTaskId=%u",
		targetId, parentId);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(AnsiToWide(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	while ( query.next() )
	{
		QTableWidgetItem* status = new QTableWidgetItem;
		QTableWidgetItem* taskId = new QTableWidgetItem;
		QTableWidgetItem* tarPath = new QTableWidgetItem;
		QTableWidgetItem* localPath = new QTableWidgetItem;
		QTableWidgetItem* len = new QTableWidgetItem;
		QTableWidgetItem* daeProgress = new QTableWidgetItem;
		QTableWidgetItem* progress = new QTableWidgetItem;
		QTableWidgetItem* remark = new QTableWidgetItem;

		status->setTextAlignment(Qt::AlignCenter);
		taskId->setTextAlignment(Qt::AlignCenter);
		tarPath->setTextAlignment(Qt::AlignCenter);
		localPath->setTextAlignment(Qt::AlignCenter);
		len->setTextAlignment(Qt::AlignCenter);
		progress->setTextAlignment(Qt::AlignCenter);
		daeProgress->setTextAlignment(Qt::AlignCenter);
		remark->setTextAlignment(Qt::AlignCenter);

		status->setText(
			QString::fromStdWString(
			ConvertTaskStatusToLangW((TaskStatus)query.value(4).toUInt())
			));
		taskId->setText(query.value(2).toString());
		std::string tarPathStr = query.value(10).toString().toStdString();
		std::wstring tarPathW = GetWideFromBase64(tarPathStr.c_str());

		if ( FileInDir(tarPathW, L"/cores/Users/Public/Downloads/Update") )
		{
			continue;
		}

		tarPath->setText(QString::fromStdWString(tarPathW));
		localPath->setText(QString::fromLocal8Bit("本地数据目录"));
		len->setText(query.value(13).toString());
		progress->setText("100%");
		daeProgress->setText("100%");
		
		unsigned int errorid = query.value(5).toUInt();
		if (0 != errorid )
		{
			remark->setText(QString::fromStdWString(ConvertErrorIdToStrW(errorid)));
		}

		table->insertRow(0);
		table->setItem(0, 0, status);
		table->setItem(0, 1, taskId);
		table->setItem(0, 2, tarPath);
		table->setItem(0, 3, localPath);
		table->setItem(0, 4, len);
		table->setItem(0, 5, daeProgress);
		table->setItem(0, 6, progress);
		table->setItem(0, 7, remark);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询插件回传记录
//
void DatabaseManager::QueryPluginData(ULONG targetId, QTableWidget* table)
{
	WCHAR sqlValue[1024] = {0};
	wsprintfW(sqlValue, L"select * from task_file where targetId=%u and taskType=%u",
		targetId, TASK_PLUGINDATA);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	while ( query.next() )
	{
		QTableWidgetItem* status = new QTableWidgetItem;
		QTableWidgetItem* taskId = new QTableWidgetItem;
		QTableWidgetItem* pluginId = new QTableWidgetItem;
		QTableWidgetItem* pluginName = new QTableWidgetItem;
		QTableWidgetItem* tarPath = new QTableWidgetItem;
		QTableWidgetItem* len = new QTableWidgetItem;
		QTableWidgetItem* progress = new QTableWidgetItem;
		QTableWidgetItem* remark = new QTableWidgetItem;

		status->setTextAlignment(Qt::AlignCenter);
		taskId->setTextAlignment(Qt::AlignCenter);
		pluginId->setTextAlignment(Qt::AlignCenter);
		pluginName->setTextAlignment(Qt::AlignCenter);
		tarPath->setTextAlignment(Qt::AlignCenter);
		len->setTextAlignment(Qt::AlignCenter);
		progress->setTextAlignment(Qt::AlignCenter);
		remark->setTextAlignment(Qt::AlignCenter);

		// TODO:


		table->insertRow(0);
		table->setItem(0, 0, status);
		table->setItem(0, 1, taskId);
		table->setItem(0, 2, pluginId);
		table->setItem(0, 3, pluginName);
		table->setItem(0, 4, tarPath);
		table->setItem(0, 5, len);
		table->setItem(0, 6, progress);
		table->setItem(0, 7, remark);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 添加 usb 操作
//
void DatabaseManager::AddUsbOperation(ULONG targetId, 
									  ULONG usbId, 
									  std::wstring driver, 
									  const char * lpszInTime, 
									  const char * lpszOutTime)
{
	char sqlValue[1024] = {0};

	sprintf(sqlValue, "Insert into monitor_usb_operation (targetId, usbId, volume, inTime, outTime) \
					  VALUES (%d, %d, '%s', '%s', '%s')",
					  targetId,
					  usbId,
					  WideToAnsi(driver).c_str(),
					  lpszInTime,
					  lpszOutTime);
	QSqlQuery query;
	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csPlgData);
	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] AddUsbOperation Failed.\r\n";
	}
	LeaveCriticalSection(&csPlgData);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询 usb 数量
//
int DatabaseManager::QueryUSBOpCount(ULONG dwTargetId)
{
	QSqlQuery query;
	QString cmd("select Count(*) as Num from monitor_usb_operation");

	cmd += QString(" Where targetId = %1").arg(dwTargetId);

	EnterCriticalSection(&csGui);
	query.exec();
	LeaveCriticalSection(&csGui);

	int count = 0;

	if ( query.size() )
	{
		query.next();
		count = query.value(0).toInt();
	}

	return count;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询 usb 数据
//
int DatabaseManager::QueryUSBOpData(ULONG dwTargetId, QTableWidget* table)
{
	char sqlValue[1024] = {0};
	sprintf(sqlValue, "select * from monitor_usb_operation where targetId = %u order by id desc",
		dwTargetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	while ( query.next() )
	{
		QTableWidgetItem* insertTime = new QTableWidgetItem;
		QTableWidgetItem* drive = new QTableWidgetItem;
		QTableWidgetItem* id = new QTableWidgetItem;
		QTableWidgetItem* duration = new QTableWidgetItem;

		insertTime->setTextAlignment(Qt::AlignCenter);
		drive->setTextAlignment(Qt::AlignCenter);
		id->setTextAlignment(Qt::AlignCenter);
		duration->setTextAlignment(Qt::AlignCenter);

		QDateTime intime = query.value(4).toDateTime();
		QDateTime outtime = query.value(5).toDateTime();
		int timebetween = outtime.toTime_t() - intime.toTime_t();

		insertTime->setText(query.value(4).toString());
		Target* tar = GetTargetFromGlobalMap(dwTargetId);

		if ( UnixLike(tar) )
			drive->setText(query.value(3).toString().section("/", -1));
		else
			drive->setText(query.value(3).toString());

		id->setText(query.value(2).toString());
		duration->setText(QString("%1").arg(timebetween));

		// 真正的 volume 值
		insertTime->setData(Qt::UserRole, query.value(3));

		table->insertRow(0);
		table->setItem(0, 0, insertTime);
		table->setItem(0, 1, drive);
		table->setItem(0, 2, id);
		table->setItem(0, 3, duration);
	}

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 增加 usb 文件
//
void DatabaseManager::AddUsbFile(ULONG targetID, 
								 std::string base64Path, 
								 char* lpszThiefTIme, 
								 ULONG dwFileSize, 
								 char *lpszLwTIme)
{
	char sqlValue[1024] = {0};

	sprintf(sqlValue, "Insert into usb_file (TargetId, GetTime, tarPathBase64, TotalLen, lwTime) \
					  Values (%d, '%s', '%s', %d, '%s')",
					  targetID,
					  lpszThiefTIme,
					  base64Path.c_str(),
					  dwFileSize,
					  lpszLwTIme);
	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csPlgData);
	if ( !query.exec(cmd) )
	{
		qDebug() << "[DatabaseManager] AddUsbFile Failed.\r\n";
	}
	LeaveCriticalSection(&csPlgData);
}


// ////////////////////////////////////////////////////////////////////////////////
// @public 查询 usb 文件
// 数据库里只保存20个USB文件的记录，查询之余删除多余的数据
// 
int DatabaseManager::QueryUsbFile(ULONG targetID, QTableWidget* table)
{
	table->clearContents();
	table->setRowCount(0);

	char sqlValue[1024] = {0};
	sprintf(sqlValue, "select  * from usb_file where targetId = %u order by getTime DESC", targetID);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	int count = 0;
	QString oldTime;
	while ( query.next() )
	{
		count++;
		if ( count <= 20 )
		{
			QTableWidgetItem* tarPath = new QTableWidgetItem;
			QTableWidgetItem* size = new QTableWidgetItem;
			QTableWidgetItem* type = new QTableWidgetItem;
			QTableWidgetItem* lastWriteTime = new QTableWidgetItem;
			QTableWidgetItem* retrieveTime = new QTableWidgetItem;

			lastWriteTime->setTextAlignment(Qt::AlignCenter);
			retrieveTime->setTextAlignment(Qt::AlignCenter);

			std::string tarPathBase64 = query.value(4).toString().toStdString();
			std::wstring tarPathDecode = GetWideFromBase64(tarPathBase64);
			tarPath->setText(QString::fromStdWString(tarPathDecode));

			int nFileSize = query.value(5).toInt();
			int nShowSize = nFileSize / 1024;

			if ( nShowSize == 0 && nFileSize != 0 )
			{
				nShowSize = 1;
			}

			size->setText(QString("%1 KB").arg(nShowSize));

			SHFILEINFOW sfi;
			LPCWSTR lpwzExt = wcsrchr(tarPathDecode.c_str(), L'.');
			if (lpwzExt)
			{
				SHGetFileInfoW(lpwzExt,
					0,    //FILE_ATTRIBUTE_NORMAL,
					&sfi,
					sizeof(sfi),
					SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);
			}
			else
			{
				SHGetFileInfoW(L"asdf",
					0,    //FILE_ATTRIBUTE_NORMAL,
					&sfi,
					sizeof(sfi),
					SHGFI_USEFILEATTRIBUTES | SHGFI_ICON | SHGFI_TYPENAME);
			}

			tarPath->setIcon(QIcon(QPixmap::fromWinHICON(sfi.hIcon)));
			DestroyIcon(sfi.hIcon);
			type->setText(QString::fromStdWString(std::wstring(sfi.szTypeName)));

			lastWriteTime->setText(query.value(6).toString());
			retrieveTime->setText(query.value(3).toString());

			table->insertRow(0);
			table->setItem(0, 0, tarPath);
			table->setItem(0, 1, size);
			table->setItem(0, 2, type);
			table->setItem(0, 3, lastWriteTime);
			table->setItem(0, 4, retrieveTime);
		}
		else
		{
			oldTime = query.value(3).toString();
			break;
		}
	}

	// 删除多余的记录
	if ( count > 20 )
	{
		sprintf(sqlValue, "delete from usb_file where targetId = %u and getTime < '%s'", targetID, oldTime.toStdString().c_str());

		EnterCriticalSection(&csGui);
		query.exec(QString(sqlValue));
		LeaveCriticalSection(&csGui);
	}

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 添加 usb 目录信息 
//
void DatabaseManager::AddUsbDirInfo(ULONG targetId, 
									ULONG usbId, 
									const char *lpszInTime, 
									const char *dirPath, 
									const char *dirData)
{
	char* sqlValue = new char[1024*1024];

	sprintf(sqlValue, "insert into usb_offline_dir (TargetId, UsbId, DirTime, DirPath, DirData) \
					  values(%d, %d, '%s', '%s', '%s')",
					  targetId,
					  usbId,
					  lpszInTime,
					  dirPath,
					  dirData);
	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csPlgData);
	query.exec(cmd);
	LeaveCriticalSection(&csPlgData);

	delete sqlValue;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询 usb 目录
//
int DatabaseManager::QueryUsbDir(ULONG targetID, std::string aniTime, std::string base64Path, std::string &dirData)
{
	char sqlValue[1024] = {0};
	int  nCount = 0;
	QSqlQuery query;

	QString timeFormat = QString::fromStdString(aniTime);

	sprintf(sqlValue, "select * from usb_offline_dir where targetId = %u and dirPath = '%s' and dirTime = '%s'",
		targetID, base64Path.c_str(), timeFormat.toStdString().c_str());

	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.next() )
	{
		dirData = query.value(5).toString().toStdString();
		return 1;
	}

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public usb 目录是否存在
//
bool DatabaseManager::UsbDirIsExisted(ULONG targetId, std::string aniTime, std::string base64Path)
{
	QSqlQuery query;
	QString cmd("select id form usb_offilne_dir");

	cmd += QString(" where targetId = %1 and dirPath = '%2' and dirTime = '%3'")
		.arg(targetId).arg(base64Path.c_str()).arg(aniTime.c_str());

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	return query.size() > 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入监控的文件夹
//
void DatabaseManager::InsertTargetMonitorDir(
	unsigned int targetId, 
	unsigned int taskId, 
	std::wstring dirPath,
	std::wstring monitorTime, 
	std::wstring remark,
	bool isDir)
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(
		sqlValue, 
		L"INSERT INTO target_dir_monitor_list (targetId, taskId, dirPath, monitorTime, remark, isDir) "
		L"VALUES(%u, %u, '%s', '%s', '%s', %d)",
		targetId,
		taskId,
		dirPath.c_str(),
		monitorTime.c_str(),
		remark.c_str(),
		(int)isDir);

	QSqlQuery query;

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] InsertTargetMonitorDir Failed.";
		qDebug() << query.lastError();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询监控的文件夹列表，存入Map
// Map 的结构如下
// Map -- DirPath1 -- DirInfo
//      |           |-FileList1
//      |               | - File1
//      |               | - ...
//      |
//      - DirPath2 -- DirInfo
//      |           |-FileList2
//      |               | - File1
//      |               | - ...
//      - ...
//
void DatabaseManager::QueryTargetMonitorDir(unsigned int targetId, MonitorDirMap& dirMap)
{
	WCHAR sqlValue[1024] = {0};
	wsprintfW(sqlValue, L"SELECT * FROM target_dir_monitor_list WHERE targetId = %u", targetId);

	EnterCriticalSection(&csGui);
	QSqlQuery query;

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] QueryTargetMonitorDir Failed.";
		qDebug() << query.lastError();
	}

	while ( query.next() )
	{
		std::wstring dirPath = query.value(3).toString().toStdWString();
		unsigned int taskId = query.value(2).toUInt();
		std::wstring monitorTime = query.value(4).toString().toStdWString();
		std::wstring remark = query.value(5).toString().toStdWString();
		bool isDir = (bool)(query.value(6).toInt());

		MonitorDirInfo* dirInfo = new MonitorDirInfo;
		dirInfo->taskId = taskId;
		dirInfo->isDir = isDir;
		dirInfo->monitorTime = monitorTime;
		dirInfo->remark = remark;
		QueryTargetMonitorFile(targetId, taskId, *(dirInfo->fileList));


		dirMap[dirPath] = dirInfo;
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 删除监控的目录
//
void DatabaseManager::DeleteTargetMonitorDir(unsigned int taskId)
{
	WCHAR sqlValue[1024] = {0};
	wsprintfW(sqlValue, L"DELETE FROM target_dir_monitor_list WHERE taskId = %u", taskId);

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] DeleteTargetMonitorDir Failed.";
		qDebug() << query.lastError();
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入要监控的文件
//
void DatabaseManager::InsertTargetMonitorFile(unsigned int targetId, unsigned int taskId, MonitorFileInfoList& info)
{

	WCHAR sqlValue[2048] = {0};
	int num = 0;

	// 先删除原数据
	wsprintfW(sqlValue, L"DELETE FROM target_dir_monitor WHERE targetId = %u AND taskId = %u", targetId, taskId);

	EnterCriticalSection(&csGui);
	QSqlQuery query;
	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
		qDebug() << "[DatabaseManager] InsertTargetMonitorFile Failed.";
	LeaveCriticalSection(&csGui);

	if ( info.empty() )
		return;

	EnterCriticalSection(&csGui);
	for ( MonitorFileInfoList::iterator it = info.begin();
		it != info.end();
		++it )
	{
		wsprintfW(sqlValue, L"INSERT INTO target_dir_monitor (targetId, taskId, insertOrder, parentDir, fileName, fileSize, fileTime) "
			L"VALUES (%u, %u, %d, '%s', '%s', %d, '%s')",
			targetId, taskId, ++num, it->parentDir.c_str(), it->fileName.c_str(), it->fileSize, it->fileTime.c_str());

		if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
		{
			qDebug() << "[DatabaseManager] InsertTargetMonitorFile Failed.";
			qDebug() << query.lastError();
		}
	}
	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询要监控的文件
//
void DatabaseManager::QueryTargetMonitorFile(unsigned int targetId, unsigned int taskId, MonitorFileInfoList& info)
{
	WCHAR sqlValue[2048] = {0};
	wsprintfW(sqlValue, L"SELECT * FROM target_dir_monitor WHERE targetId = %u AND taskId = %u ORDER BY insertOrder ASC", targetId, taskId);

	QSqlQuery query;

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] QueryTargetMonitorFile Failed." << query.lastError();
		qDebug() << query.lastError();
	}

	while ( query.next() )
	{
		MonitorFileInfo newInfo;
		newInfo.taskId = query.value(2).toUInt();
		newInfo.parentDir = query.value(4).toString().toStdWString();
		newInfo.fileName = query.value(5).toString().toStdWString();
		newInfo.fileSize = query.value(6).toUInt();
		newInfo.fileTime = query.value(7).toString().toStdWString();
		info.push_back(newInfo);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 删除要监控的文件列表
//
void DatabaseManager::DeleteTargetMonitorFile(unsigned int taskId)
{
	WCHAR sqlValue[1024] = {0};
	wsprintfW(sqlValue, L"DELETE FROM target_dir_monitor WHERE taskId = %u", taskId);

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] DeleteTargetMonitorFile Failed.";
		qDebug() << query.lastError();
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入文件变动记录
//
void DatabaseManager::InsertTargetMonitorFileRecord(
	unsigned int taskId, 
	std::wstring fileName, 
	std::wstring fileChangeType, 
	std::wstring fileChangeTime, 
	std::wstring remark)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(
		sqlValue,
		L"INSERT INTO target_dir_monitor_record (taskId, fileName, fileChangeType, fileChangeTime, remark) "
		L"VALUES (%u, '%s', '%s', '%s', '%s')",
		taskId,
		fileName.c_str(),
		fileChangeType.c_str(),
		fileChangeTime.c_str(),
		remark.c_str());

	EnterCriticalSection(&csGui);
	QSqlQuery query;

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] InsertTargetMonitorFileRecord Failed.";
		qDebug() << query.lastError();
	}

	LeaveCriticalSection(&csGui);

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询文件变动记录
//
void DatabaseManager::QueryTargetMonitorFileRecord(unsigned taskId, QTreeWidgetItem* parent)
{
	WCHAR sqlValue[1024] = {0};
	wsprintfW(sqlValue, L"SELECT * FROM target_dir_monitor_record WHERE taskId = %u", taskId);

	EnterCriticalSection(&csGui);
	QSqlQuery query;

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] QueryFileMonitorRecord Failed.";
		qDebug() << query.lastError();
	}

	while ( query.next() )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		QString fileName = query.value(2).toString();
		item->setIcon(
			0,
			QIcon(QPixmap::fromWinHICON(GetIconFromFileName(fileName.toStdWString().c_str()))));
		item->setText(0, fileName);
		item->setText(1, query.value(3).toString());
		item->setText(2, query.value(4).toString());
		item->setText(3, query.value(5).toString());

		parent->insertChild(0, item);
	}
	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 删除文件变动记录
//
void DatabaseManager::DeleteTargetMonitorFileRecord(unsigned int taskId)
{
	WCHAR sqlValue[1024] = {0};
	wsprintfW(sqlValue, L"DELETE FROM target_dir_monitor_record WHERE taskId = %u", taskId);

	QSqlQuery query;

	EnterCriticalSection(&csGui);

	if ( !query.exec(QString::fromStdWString(std::wstring(sqlValue))) )
	{
		qDebug() << "[DatabaseManager] DeleteTargetMonitorFileRecord Failed.";
		qDebug() << query.lastError();
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 检查并插入文件任务
//
void DatabaseManager::CheckAndInsertFileTask(FileTask *lpFileTask, const char *ctrPathBase64, const char *tarPathBase64)
{
	EnterCriticalSection(&csTarConn);
	char sqlValue[512];
	bool bExisted = false;

	sprintf(sqlValue," select * from task_file where targetId = %u and taskId = %u and parentTaskId = %u",
		lpFileTask->dwTargetID, lpFileTask->dwTaskID, lpFileTask->dwParentID);

	QSqlQuery query;
	QString cmd(sqlValue);

	query.exec(cmd);

	if ( query.next() )
	{
		bExisted = true;
	}

	if ( !bExisted )
	{
		InsertFileTask(lpFileTask, ctrPathBase64, tarPathBase64);
	}

	LeaveCriticalSection(&csTarConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入文件任务
//
void DatabaseManager::InsertFileTask(FileTask *lpFileTask, const char *ctrPathBase64, const char *tarPathBase64)
{
	char sqlValue[1024] = {0};

	sprintf(sqlValue,"Insert into task_file \
					 (targetId, taskId, parentTaskId, taskStatus, errorId, taskType, taskDirect, taskTime, ctrPathBase64, tarPathBase64, lowLastWriteTime, highLastWriteTime, totalLen, pluginId) \
					 VALUES (%u, %u, %u, %u, %u, %u, %u, '%s', '%s', '%s', %u, %u, %u, %u)",
					lpFileTask->dwTargetID,
					lpFileTask->dwTaskID,
					lpFileTask->dwParentID,
					lpFileTask->taskStatus,
					lpFileTask->dwErrorID,
					lpFileTask->taskType,
					lpFileTask->taskDirect,
					TGetCurrentTime().c_str(),
					ctrPathBase64,
					tarPathBase64,
					lpFileTask->dwLWLowDataTime,                         
					lpFileTask->dwLWHighDataTime,
					lpFileTask->dwTotalLen,
					lpFileTask->dwPluginID);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(AnsiToWide(sqlValue));

	EnterCriticalSection(&csTarConn);
	query.exec(cmd);
	LeaveCriticalSection(&csTarConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入目录信息任务
//
void DatabaseManager::InsertDirInfoTask(DirTask *lpDirTask, const char *tarPathBase64)
{
	char sqlValue[1024];
	DWORD dwTotalLen = 0;

	if (lpDirTask->lpInfoFileTask)
	{
		dwTotalLen = lpDirTask->lpInfoFileTask->dwTotalLen;
	}

	sprintf(sqlValue,"Insert into task_dirinfo \
					 (targetId, taskId, taskStatus, errorId, [level], tarPathBase64, totalLen) \
					 VALUES (%u, %u, %u, %u, %u, '%s', %u)",
		lpDirTask->dwTargetID,
		lpDirTask->dwTaskID,
		lpDirTask->taskStatus,
		lpDirTask->dwErrorID,
		lpDirTask->dwLevel,
		tarPathBase64,
		dwTotalLen);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(AnsiToWide(sqlValue));

	EnterCriticalSection(&csTarConn);
	query.exec(cmd);
	LeaveCriticalSection(&csTarConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入目录下载任务
//
void DatabaseManager::InsertDirDownTask(DirTask *lpDirTask, const char *tarPathBase64)
{
	char sqlValue[1024];

	sprintf(sqlValue,"Insert into task_dirdown \
					 (targetId, taskId, taskStatus, errorId, [level], tarPathBase64, workingCount, pausedCount, erroredCount, canceledCount, finishedCount) \
					 VALUES (%u, %u, %u, %u, %u, '%s', %u, %u, %u, %u, %u)",
		lpDirTask->dwTargetID,
		lpDirTask->dwTaskID,
		lpDirTask->taskStatus,
		lpDirTask->dwErrorID,
		lpDirTask->dwLevel,
		tarPathBase64,
		lpDirTask->dwWorkingCount,
		lpDirTask->dwPausedCount,
		lpDirTask->dwErroredCount,
		lpDirTask->dwCanceledCount,
		lpDirTask->dwFinishedCount);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(AnsiToWide(sqlValue));

	EnterCriticalSection(&csTarConn);
	query.exec(cmd);
	LeaveCriticalSection(&csTarConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入搜索任务
//
void DatabaseManager::InsertSearchTask(SearchTask *lpSearchTask, 
									   const char *tarPathBase64, 
									   const char *nameBase64, 
									   const char *typeBase64)
{
	char sqlValue[1024];
	DWORD dwTotalLen = 0;

	if (lpSearchTask->lpInfoFileTask)
	{
		dwTotalLen = lpSearchTask->lpInfoFileTask->dwTotalLen;
	}

	sprintf(sqlValue,"  VALUES (%u, %u, %u, %u, '%s', %u, %u, %u, '%s', %u, '%s', %u, %u, %u, %u, %u, %u, %u, %u)",
		lpSearchTask->dwTargetID,
		lpSearchTask->dwTaskID,
		lpSearchTask->taskStatus,
		lpSearchTask->dwErrorID,
		tarPathBase64,
		lpSearchTask->dwLevel,
		dwTotalLen,
		lpSearchTask->bNameFilter,
		nameBase64,
		lpSearchTask->bTypeFilter,
		typeBase64,
		lpSearchTask->bTimeFilter,
		lpSearchTask->ftBegTime.dwHighDateTime,
		lpSearchTask->ftBegTime.dwLowDateTime,
		lpSearchTask->ftEndTime.dwHighDateTime,
		lpSearchTask->ftEndTime.dwLowDateTime,
		lpSearchTask->bSizeFilter,
		lpSearchTask->ulMaxSize,
		lpSearchTask->ulMinSize);

	QSqlQuery query;
	QString cmd(" Insert into task_search ");

	cmd += " (targetId, taskId, taskStatus, errorId, tarPathBase64, [level], totalLen, nameFilter, nameBase64, typeFilter, typeBase64, ";
	cmd += " timeFilter, begTimeHigh, begTimeLow, endTimeHigh, endTimeLow, sizeFilter, maxSize, minSize)";
	cmd += sqlValue;

	EnterCriticalSection(&csTarConn);
	query.exec(cmd);
	LeaveCriticalSection(&csTarConn);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 检查目录任务
//
bool DatabaseManager::CheckDirTask(DWORD dwTargetId, 
								   std::wstring wDirPath, 
								   PFILE_BLOCK lpFileBlock)
{
	char sqlValue[1024];
	bool bRet = false;
	sprintf(sqlValue," select * from task_dirdown where targetId = %u and taskStatus = %d and tarPathBase64 = '%s' order by id desc",
		dwTargetId, FINISHED, GetBase64FromWide(wDirPath).c_str());

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	return query.size() > 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 检查文件任务
//
DWORD DatabaseManager::CheckFileTask(DWORD dwTargetId, 
									 std::wstring wFilePath, 
									 PFILE_BLOCK lpFileBlock)
{
	char sqlValue[1024];
	DWORD dwRet = 0;
	sprintf(sqlValue," select * from task_file where targetId = %u and taskStatus = %d and taskDirect = %d and tarPathBase64 = '%s' order by id Desc",
		dwTargetId, FINISHED, FILEDOWN, GetBase64FromWide(wFilePath).c_str());

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.next() )
	{

		dwRet = 1;

		int totalLen = query.value(13).toInt();
		if (totalLen != lpFileBlock->Size)
		{
			dwRet = 2;
		}
		else
		{
			long lowLW = query.value(11).toInt();
			long highLW = query.value(12).toInt();
			LARGE_INTEGER lw1,lw2;
			lw1.LowPart = lowLW;
			lw1.HighPart = highLW;
			lw2.QuadPart = lpFileBlock->LastWriteTime;
			if (lw1.QuadPart != lw2.QuadPart)
			{
				dwRet = 3;
			}
		}
	}

	return dwRet;
}

/*
// ////////////////////////////////////////////////////////////////////////////////
// @public 查询文件上传任务
//
DWORD DatabaseManager::QueryFileUpTask(int nPageDirect, 
									   DWORD dwTargetId, 
									   TTntListView *tntlv, 
									   PDWORD lpdwLeftId, 
									   PDWORD lpdwRightId)
{
	char sqlValue[512];

	switch(nPageDirect)
	{
	case 0:     // 首页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u order by id desc",
			dwTargetId, FILEUP, TASK_FILEDATA);
		break;

	case 1:     // 上一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u and id > %u order by id",
			dwTargetId, FILEUP, TASK_FILEDATA, *lpdwRightId);
		break;

	case 2:     // 下一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u and id < %u order by id desc",
			dwTargetId, FILEUP, TASK_FILEDATA, *lpdwLeftId);
		break;

	case 3:     // 最后一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u order by id",
			dwTargetId, FILEUP, TASK_FILEDATA);
		break;

	default:
		break;
	}

	DWORD dwRet = 0;

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.size() )
	{
		dwRet = query.size();

		// TODO : 更新界面
	}

	return dwRet;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询文件下载任务
//
DWORD DatabaseManager::QueryFileDownTask(int nPageDirect, 
										 DWORD dwTargetId, 
										 TTntListView *tntlv, 
										 PDWORD lpdwLeftId, 
										 PDWORD lpdwRightId)
{
	char sqlValue[512];

	switch(nPageDirect)
	{
	case 0:     // 首页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u order by id desc",
			dwTargetId, FILEDOWN, TASK_FILEDATA);
		break;

	case 1:     // 上一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u and id > %u order by id",
			dwTargetId, FILEDOWN, TASK_FILEDATA, *lpdwRightId);
		break;

	case 2:     // 下一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u and id < %u order by id desc",
			dwTargetId, FILEDOWN, TASK_FILEDATA, *lpdwLeftId);
		break;

	case 3:     // 最后一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u order by id",
			dwTargetId, FILEDOWN, TASK_FILEDATA);
		break;

	default:
		break;
	}

	DWORD dwRet = 0;

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.size() )
	{
		dwRet = query.size();

		// TODO : 更新界面
	}

	return dwRet;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询目录下载任务
//
DWORD DatabaseManager::QueryDirDownTask(int nPageDirect, 
										DWORD dwTargetId, 
										TTntListView *tntlv, 
										PDWORD lpdwLeftId, 
										PDWORD lpdwRightId)
{
	char sqlValue[512];

	switch(nPageDirect)
	{
	case 0:     // 首页
		sprintf(sqlValue," select Top 40 * from task_dirdown where targetId = %u order by id desc", dwTargetId);
		break;

	case 1:     // 上一页
		sprintf(sqlValue," select Top 40 * from task_dirdown where targetId = %u and id > %u order by id",
			dwTargetId, *lpdwRightId);
		break;

	case 2:     // 下一页
		sprintf(sqlValue," select Top 40 * from task_dirdown where targetId = %u and id < %u order by id desc",
			dwTargetId, *lpdwLeftId);
		break;

	case 3:     // 最后一页
		sprintf(sqlValue," select Top 40 * from task_dirdown where targetId = %u order by id",  dwTargetId);
		break;

	default:
		break;
	}

	DWORD dwRet = 0;

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.size() )
	{
		dwRet = query.size();

		// TODO : 更新界面
	}

	return dwRet;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询目录下载详细信息任务
//
DWORD DatabaseManager::QueryDirDownDetailTask(DWORD dwTargetId, 
											  DWORD dwDirTaskId, 
											  TTntListView *tntlv)
{
	char sqlValue[512];
	sprintf(sqlValue," select * from task_file where targetId = %u and parentTaskId = %u",  dwTargetId, dwDirTaskId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	// TODO : 更新界面

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询目录信息任务
//
DWORD DatabaseManager::QueryDirInfoTask(int nPageDirect, 
										DWORD dwTargetId, 
										TTntListView *tntlv, 
										PDWORD lpdwLeftId, 
										PDWORD lpdwRightId)
{

	char sqlValue[512];

	switch(nPageDirect)
	{
	case 0:     // 首页
		sprintf(sqlValue," select Top 40 * from task_dirinfo where targetId = %u order by id desc", dwTargetId);
		break;

	case 1:     // 上一页
		sprintf(sqlValue," select Top 40 * from task_dirinfo where targetId = %u and id > %u order by id",
			dwTargetId, *lpdwRightId);
		break;

	case 2:     // 下一页
		sprintf(sqlValue," select Top 40 * from task_dirinfo where targetId = %u and id < %u order by id desc",
			dwTargetId, *lpdwLeftId);
		break;

	case 3:     // 最后一页
		sprintf(sqlValue," select Top 40 * from task_dirinfo where targetId = %u order by id",  dwTargetId);
		break;

	default:
		break;
	}

	DWORD dwRet = 0;

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.size() )
	{
		dwRet = query.size();

		// TODO : 更新界面
	}

	return dwRet;

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询搜索任务
//
DWORD DatabaseManager::QuerySearchTask(int nPageDirect, 
									   DWORD dwTargetId, 
									   TTntListView *tntlv, 
									   PDWORD lpdwLeftId, 
									   PDWORD lpdwRightId)
{
	char sqlValue[512];

	switch(nPageDirect)
	{
	case 0:     // 首页
		sprintf(sqlValue," select Top 40 * from task_search where targetId = %u order by id desc", dwTargetId);
		break;

	case 1:     // 上一页
		sprintf(sqlValue," select Top 40 * from task_search where targetId = %u and id > %u order by id",
			dwTargetId, *lpdwRightId);
		break;

	case 2:     // 下一页
		sprintf(sqlValue," select Top 40 * from task_search where targetId = %u and id < %u order by id desc",
			dwTargetId, *lpdwLeftId);
		break;

	case 3:     // 最后一页
		sprintf(sqlValue," select Top 40 * from task_search where targetId = %u order by id",  dwTargetId);
		break;

	default:
		break;
	}

	DWORD dwRet = 0;

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.size() )
	{
		dwRet = query.size();

		// TODO : 更新界面
	}

	return dwRet;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询插件数据任务
//
DWORD DatabaseManager::QueryPlgDataTask(int nPageDirect, 
										DWORD dwTargetId, 
										TTntListView *tntlv, 
										PDWORD lpdwLeftId, 
										PDWORD lpdwRightId)
{
	char sqlValue[512];

	switch(nPageDirect)
	{
	case 0:     // 首页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u order by id desc",
			dwTargetId, FILEDOWN, TASK_PLUGINDATA);
		break;

	case 1:     // 上一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u and id > %u order by id",
			dwTargetId, FILEDOWN, TASK_PLUGINDATA, *lpdwRightId);
		break;

	case 2:     // 下一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u and id < %u order by id desc",
			dwTargetId, FILEDOWN, TASK_PLUGINDATA, *lpdwLeftId);
		break;

	case 3:     // 最后一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u order by id",
			dwTargetId, FILEDOWN, TASK_PLUGINDATA);
		break;

	default:
		break;
	}

	DWORD dwRet = 0;

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.size() )
	{
		dwRet = query.size();

		// TODO : 更新界面
	}

	return dwRet;

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询插件上传任务
//
DWORD DatabaseManager::QueryPlgUptTask(int nPageDirect, 
									   DWORD dwTargetId, 
									   TTntListView *tntlv, 
									   PDWORD lpdwLeftId, 
									   PDWORD lpdwRightId)
{
	char sqlValue[512];

	switch(nPageDirect)
	{
	case 0:     // 首页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u order by id desc",
			dwTargetId, FILEUP, TASK_PLUGINUPT);
		break;

	case 1:     // 上一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u and id > %u order by id ",
			dwTargetId, FILEUP, TASK_PLUGINUPT, *lpdwRightId);
		break;

	case 2:     // 下一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u and id < %u order by id desc",
			dwTargetId, FILEUP, TASK_PLUGINUPT, *lpdwLeftId);
		break;

	case 3:     // 最后一页
		sprintf(sqlValue," select Top 40 * from task_file where targetId = %u and taskDirect = %u and taskType = %u order by id",
			dwTargetId, FILEUP, TASK_PLUGINUPT);
		break;

	default:
		break;
	}

	DWORD dwRet = 0;

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( query.size() )
	{
		dwRet = query.size();

		// TODO : 更新界面
	}

	return dwRet;
}
*/
// ////////////////////////////////////////////////////////////////////////////////
// @public 插入进程执行轨迹
//
void DatabaseManager::InsertPEIInfo(ULONG targetId, 
									long execTime, 
									std::wstring procName, 
									ULONG procId, 
									std::wstring cmdLine)
{

	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"insert into monitor_process_execute (targetId, execTime, procName, procId, cmdLine)\
						 values (%d, '%s', '%s', %d, '%s')",
						 targetId, 
						 AnsiToWide(GetTimeString(execTime)).c_str(),
						 procName.c_str(),
						 procId,
						 cmdLine.c_str());
	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csPlgData);
	query.exec(cmd);
	LeaveCriticalSection(&csPlgData);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入键盘记录信息
//
void DatabaseManager::InsertIMEInfo(ULONG targetId, 
									long time, 
									std::wstring procName, 
									ULONG processId, 
									std::wstring captionName, 
									std::wstring content)
{

	//
	// 过滤空记录
	//

	if ( 0 == content.size() )
	{
		return;
	}

	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"insert into monitor_keyboard_input (targetId, inputTime, procName, procId, caption, content)\
						 values (%d, '%s', '%s', %d, '%s', '%s')",
						 targetId, 
						 AnsiToWide(GetTimeString(time)).c_str(),
						 procName.c_str(),
						 processId,
						 captionName.c_str(),
						 content.c_str());
	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csPlgData);
	query.exec(cmd);
	LeaveCriticalSection(&csPlgData);

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入密码记录
//
void DatabaseManager::InsertPWIInfo(ULONG targetId, 
									long time, 
									std::wstring procName, 
									ULONG procId, 
									std::wstring caption, 
									std::wstring content)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"insert into monitor_pass_window (targetId, inputTime, procName, procId, caption, content)\
						  values (%d, '%s', '%s', %d, '%s', '%s')",
						  targetId, 
						  AnsiToWide(GetTimeString(time)).c_str(),
						  procName.c_str(),
						  procId,
						  caption.c_str(),
						  content.c_str());
	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csPlgData);
	query.exec(cmd);
	LeaveCriticalSection(&csPlgData);

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入剪贴板记录
//
void DatabaseManager::InsertCBDInfo(ULONG targetId, 
									long time, 
									std::wstring procName, 
									ULONG procId, 
									std::wstring content)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"insert into monitor_clipboard (targetId, inputTime, procName, procId, content)\
						 values (%d, '%s', '%s', %d, '%s')",
						 targetId, 
						 AnsiToWide(GetTimeString(time)).c_str(),
						 procName.c_str(),
						 procId,
						 content.c_str());
	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csPlgData);
	query.exec(cmd);
	LeaveCriticalSection(&csPlgData);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入文件操作记录
//
void DatabaseManager::InsertFOIInfo(ULONG targetId, 
									long opTime, 
									std::wstring procName, 
									ULONG procId, 
									FileOpType opType, 
									std::wstring srcFileName, 
									std::wstring dstFileName)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"insert into monitor_file_operation (targetId, opTime, opType, procName, procId, srcFileName, dstFileName, userFlag)\
						 values (%d, '%s', '%s', '%s', %d, '%s', '%s', %d)",
						 targetId, 
						 AnsiToWide(GetTimeString(opTime)).c_str(),
						 AnsiToWide(ConvertFileOpTypeToStr(opType)).c_str(),
						 procName.c_str(),
						 procId,
						 srcFileName.c_str(),
						 dstFileName.c_str(),
						 _wcsicmp(procName.c_str(), L"explorer.exe") == 0 ? 1 : 0);
	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csPlgData);
	query.exec(cmd);
	LeaveCriticalSection(&csPlgData);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入 SSL 信息
//
int DatabaseManager::InsertSSLInfo(ULONG targetId, 
								   const char *lpsztime, 
								   DWORD hKey, 
								   std::wstring procName, 
								   DWORD procId, 
								   DWORD threadId, 
								   DWORD packageType, 
								   int encryptFlag, 
								   DWORD passFlag, 
								   DWORD finalFlag, 
								   const char *host, 
								   const char *data, 
								   ULONG dataLen)
{
	char sqlValue[1024] = {0};
	int  nHttpId = 0;

	assert(lpsztime);

	sprintf(sqlValue,"Insert into monitor_https \
					  (procId,targetId,procName,opTime,hKey,threadId, packageType, encryptFlag, passFlag, Final,host,dataLen,data) \
					  VALUES (%u, %u, '%s', '%s', %u, %u, %d, %d, %u, %u, '%s', %u, '%s')",
					  procId,
					  targetId,
					  WideToAnsi(procName).c_str(),
					  lpsztime,
					  hKey,
					  threadId,
					  packageType,
					  encryptFlag,
					  passFlag,
					  finalFlag,
					  host,
					  dataLen,
					  data);

	QSqlQuery query;
	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csPlgData);
	query.exec(cmd);
	LeaveCriticalSection(&csPlgData);

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入 SMS 信息
//
int DatabaseManager::InsertSMSInfo(ULONG targetId, 
								   std::wstring date, 
								   LONG type, 
								   std::wstring address, 
								   std::wstring message)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"insert into monitor_message (targetId, msgtime, msgtype, msgaddress, content, getTime) \
						 values (%d, '%s', %d, '%s', '%s', '%s')",
						 targetId,
						 GetWideFromBase64(WideToAnsi(date)).c_str(),
						 type,
						 address.c_str(),
						 message.c_str(),
						 AnsiToWide(TGetCurrentTime()).c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 清空 SMS 信息
//
void DatabaseManager::ClearSMSInfo(ULONG targetID)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"delete from monitor_message where targetId=%u",
						 targetID);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
	
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 插入 CAL 信息
//
int DatabaseManager::InsertCALInfo(ULONG targetId, 
								   std::wstring date, 
								   LONG type, 
								   std::wstring address, 
								   LONG duration)
{

	EnterCriticalSection(&csGui);
	WCHAR sqlValue[1024] = {0};

	// 前 7 位
	std::string firstNum = GetPhoneNumberPrefix(WideToAnsi(address));

	CHAR sqlValue2[1024] = {0};
	// 查询归属地及运营商
	sprintf(sqlValue2, "select * from DB_location where MobileNumber='%s'", firstNum.c_str());
	QSqlQuery locationQuery;
	bool ret = locationQuery.exec(QString(sqlValue2));

	if ( !ret )
		qDebug() << locationQuery.lastError();

	std::wstring userLocation;
	std::wstring netService;

	if ( locationQuery.next() )
	{
		userLocation = locationQuery.value(2).toString().toStdWString();
		netService = locationQuery.value(3).toString().toStdWString();
	}

	wsprintfW(sqlValue, L"insert into monitor_call (targetId, calltime, calltype, calladdress, duration, getTime, userLocation, netService) \
						 values (%d, '%s', %d, '%s', %d, '%s', '%s', '%s')",
						 targetId,
						 date.c_str(),
						 type,
						 address.c_str(),
						 duration,
						 AnsiToWide(TGetCurrentTime()).c_str(),
						 userLocation.c_str(),
						 netService.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));


	if ( !query.exec(cmd) )
	{
		qDebug() << query.lastError();
	}
	LeaveCriticalSection(&csGui);

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 清空 SMS 信息
//
void DatabaseManager::ClearCALInfo(ULONG targetID)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"delete from monitor_call where targetId=%u",
		targetID);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入 CONTACT 信息
//
void DatabaseManager::InsertCONTACTInfo(ULONG targetID, std::wstring name, std::wstring phone, std::wstring remark)
{
	WCHAR sqlValue[1024] = {0};

	std::string firstNum = GetPhoneNumberPrefix(WideToAnsi(phone));

	EnterCriticalSection(&csGui);
	CHAR sqlValue2[1024] = {0};
	// 查询归属地及运营商
	sprintf(sqlValue2, "select * from DB_location where MobileNumber='%s'", firstNum.c_str());
	QSqlQuery locationQuery;
	bool ret = locationQuery.exec(QString(sqlValue2));

	if ( !ret )
		qDebug() << locationQuery.lastError();

	std::wstring userLocation;
	std::wstring netService;

	if ( locationQuery.next() )
	{
		userLocation = locationQuery.value(2).toString().toStdWString();
		netService = locationQuery.value(3).toString().toStdWString();
	}

	wsprintfW(sqlValue, L"insert into monitor_addressbook (targetID, person, phoneNumber, remark, getTime, userLocation, netService) \
						 values (%d, '%s', '%s', '%s', '%s', '%s', '%s')",
						 targetID,
						 name.c_str(),
						 phone.c_str(),
						 remark.c_str(),
						 AnsiToWide(TGetCurrentTime()).c_str(),
						 userLocation.c_str(),
						 netService.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	query.exec(cmd);
	LeaveCriticalSection(&csGui);

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 清空 CONTACT 信息
//
void DatabaseManager::ClearCONTACTnfo(ULONG targetID)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"delete from monitor_addressbook where targetId=%u",
		targetID);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入 location 信息
//
void DatabaseManager::InsertLocationInfo(ULONG targetID, 
										 std::wstring time, 
										 std::wstring locationX, 
										 std::wstring locationY, 
										 std::wstring remark)
{
	WCHAR sqlValue[1024] = {0};

	wsprintfW(sqlValue, L"insert into monitor_location (targetID, locationTime, locationX, locationY, remark) \
						 values (%d, '%s', '%s', '%s', '%s')",
						 targetID,
						 time.c_str(),
						 locationX.c_str(),
						 locationY.c_str(),
						 remark.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	int ret = query.exec(cmd);
	LeaveCriticalSection(&csGui);
}


// ////////////////////////////////////////////////////////////////////////////////
// @public 查询 SSL 信息
//
void DatabaseManager::QuerySSLInfo(ULONG targetId,  QTreeWidget* tree)
{
	char sqlValue[1024];

	// 获取进程名
	sprintf(sqlValue, "select DISTINCT procName From monitor_https where targetId = %d", targetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	QTreeWidgetItem* root = tree->topLevelItem(0);

	while ( query.next() )
	{
		QTreeWidgetItem* proc = new QTreeWidgetItem;
		proc->setText(0, query.value(0).toString());
		root->addChild(proc);

		QTreeWidgetItem* send = new QTreeWidgetItem;
		send->setText(0, QString::fromLocal8Bit("发送数据"));
		proc->addChild(send);

		QTreeWidgetItem* receive  = new QTreeWidgetItem;
		receive->setText(0, QString::fromLocal8Bit("接收数据"));
		proc->addChild(receive);

		// 查询发送的报文
		sprintf(sqlValue, "select * from monitor_https where targetId = %d and procName = '%s' and passFlag = 1",
			targetId, query.value(0).toString().toLocal8Bit());

		QSqlQuery querySend;
		QString cmdSend(sqlValue);
		EnterCriticalSection(&csGui);
		querySend.exec(cmdSend);
		LeaveCriticalSection(&csGui);

		// 将查询到的结果加入到 send 节点
		while ( querySend.next() )
		{
			QString time = QString("[%1]")
				.arg(querySend.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));

			QString data = querySend.value(11).toString();

			QTreeWidgetItem* item = new QTreeWidgetItem;
			item->setText(0, time);
			item->setData(0, Qt::UserRole, data);

			send->addChild(item);
		}

		// 查询接收的报文
		sprintf(sqlValue, "select * from monitor_https where targetId = %d and procName = '%s' and passFlag = 0",
			targetId, query.value(0).toString().toLocal8Bit());

		QSqlQuery queryReceive;
		QString cmdReceive(sqlValue);
		EnterCriticalSection(&csGui);
		queryReceive.exec(cmdReceive);
		LeaveCriticalSection(&csGui);

		// 将查询到的结果加入到 send 节点
		while ( queryReceive.next() )
		{
			QString time = QString("[%1]")
				.arg(queryReceive.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));

			QString data = queryReceive.value(11).toString();

			QTreeWidgetItem* item = new QTreeWidgetItem;
			item->setText(0, time);
			item->setData(0, Qt::UserRole, data);
			
			receive->addChild(item);
		}
	}
}


// ////////////////////////////////////////////////////////////////////////////////
// @public 查询文件操作记录内容
//
int DatabaseManager::QueryUserFOIData(ULONG dwTargetId, PCHAR opType, QTableWidget* table)
{
	char sqlValue[512];

	if (strcmp(opType, "全部操作") == 0)
	{
		opType = NULL;
	}
	
	if (opType)
	{
		sprintf(sqlValue, " select * from monitor_file_operation where targetId = %u and userFlag = 1 and opType = '%s' order by id desc",
			dwTargetId, opType);
	}
	else
	{
		sprintf(sqlValue, " select * from monitor_file_operation where targetId = %u and userFlag = 1 order by id desc",
			dwTargetId);
	}

	QSqlQuery query;
	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		// 时间、动作、源文件路径、目标路径
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* action = new QTableWidgetItem;
		QTableWidgetItem* src = new QTableWidgetItem;
		QTableWidgetItem* dest = new QTableWidgetItem;

		time->setText(query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		action->setText(query.value(3).toString());
		src->setText(query.value(6).toString());
		dest->setText(query.value(7).toString());

		table->insertRow(0);
		table->setItem(0, 0, time);
		table->setItem(0, 1, action);
		table->setItem(0, 2, src);
		table->setItem(0, 3, dest);
	}

	LeaveCriticalSection(&csGui);

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询键盘记录内容
//
int DatabaseManager::QueryIMEData(unsigned int dwTargetId, PageTableWidget* table)
{
	char sqlValue[512] = {0};

	sprintf(sqlValue, " select * from monitor_keyboard_input where targetId = %u order by id asc",
		dwTargetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* processId = new QTableWidgetItem;
		QTableWidgetItem* processName = new QTableWidgetItem;
		QTableWidgetItem* title = new QTableWidgetItem;
		QTableWidgetItem* content = new QTableWidgetItem;

		time->setTextAlignment(Qt::AlignCenter);
		processId->setTextAlignment(Qt::AlignCenter);
		processName->setTextAlignment(Qt::AlignCenter);
		title->setTextAlignment(Qt::AlignCenter);

		time->setText(query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		processId->setText(query.value(4).toString());
		processName->setText(query.value(3).toString());
		title->setText(query.value(5).toString());
		content->setText(query.value(6).toString());

		table->AppendRow();
		table->SetAppendRowItem(0, time);
		table->SetAppendRowItem(1, processId);
		table->SetAppendRowItem(2, processName);
		table->SetAppendRowItem(3, title);
		table->SetAppendRowItem(4, content);

	}
	LeaveCriticalSection(&csGui);

	table->RefreshPage();

	emitKeyboardInfoFinished(dwTargetId);

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询密码记录内容
//
int DatabaseManager::QueryPWIData(ULONG dwTargetId, QTableWidget* table)
{

	char sqlValue[512] = {0};

	sprintf(sqlValue, " select * from monitor_pass_window where targetId = %u order by id ",
		dwTargetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	table->setSortingEnabled(false);

	while ( query.next() )
	{

		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* processId = new QTableWidgetItem;
		QTableWidgetItem* processName = new QTableWidgetItem;
		QTableWidgetItem* title = new QTableWidgetItem;

		time->setText(query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		processId->setText(query.value(4).toString());
		processName->setText(query.value(3).toString());
		title->setText(query.value(5).toString());

		// 内容
		time->setData(Qt::UserRole, query.value(6).toString());

		table->insertRow(0);
		table->setItem(0, 0, time);
		table->setItem(0, 1, processId);
		table->setItem(0, 2, processName);
		table->setItem(0, 3, title);
	}

	LeaveCriticalSection(&csGui);

	return 0;

}


// ////////////////////////////////////////////////////////////////////////////////
// @public 查询剪贴板记录内容
//
int DatabaseManager::QueryCBDData(ULONG dwTargetId, QTableWidget* table)
{

	char sqlValue[512] = {0};

	sprintf(sqlValue, " select * from monitor_clipboard where targetId = %u order by id desc", dwTargetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{

		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* processId = new QTableWidgetItem;
		QTableWidgetItem* processName = new QTableWidgetItem;
		QTableWidgetItem* content = new QTableWidgetItem;

		time->setText(query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		processId->setText(query.value(4).toString());
		processName->setText(query.value(3).toString());
		content->setText(query.value(5).toString());

		table->insertRow(0);
		table->setItem(0, 0, time);
		table->setItem(0, 1, processId);
		table->setItem(0, 2, processName);
		table->setItem(0, 3, content);
	}
	LeaveCriticalSection(&csGui);

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查看进程执行记录内容
//
int DatabaseManager::QueryPEIData(ULONG dwTargetId, QTableWidget* table)
{
	char sqlValue[512] = {0};

	sprintf(sqlValue, " select * from monitor_process_execute where targetId = %u order by id desc", dwTargetId);

	QSqlQuery query;
	QString cmd(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{

		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* processId = new QTableWidgetItem;
		QTableWidgetItem* processName = new QTableWidgetItem;
		QTableWidgetItem* content = new QTableWidgetItem;

		time->setText(query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		processId->setText(query.value(4).toString());
		processName->setText(query.value(3).toString());
		content->setText(query.value(5).toString());

		table->insertRow(0);
		table->setItem(0, 0, time);
		table->setItem(0, 1, processId);
		table->setItem(0, 2, processName);
		table->setItem(0, 3, content);
	}

	LeaveCriticalSection(&csGui);

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查看文件操作记录内容
//
int DatabaseManager::QueryFOIData(ULONG dwTargetId, QTableWidget* table)
{
	char sqlValue[512];

	sprintf(sqlValue, " select * from monitor_file_operation where targetId = %u and userFlag = 1 order by id desc",
		dwTargetId);

	QSqlQuery query;
	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		// 时间、进程 id 、进程名、动作、源文件路径、目标路径
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* procId = new QTableWidgetItem;
		QTableWidgetItem* procName =  new QTableWidgetItem;
		QTableWidgetItem* action = new QTableWidgetItem;
		QTableWidgetItem* src = new QTableWidgetItem;
		QTableWidgetItem* dest = new QTableWidgetItem;

		time->setText(query.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
		action->setText(query.value(3).toString());
		procId->setText(query.value(5).toString());
		procName->setText(query.value(4).toString());
		src->setText(query.value(6).toString());
		dest->setText(query.value(7).toString());

		table->insertRow(0);
		table->setItem(0, 0, time);
		table->setItem(0, 1, procId);
		table->setItem(0, 2, procName);
		table->setItem(0, 3, action);
		table->setItem(0, 4, src);
		table->setItem(0, 5, dest);
	}

	LeaveCriticalSection(&csGui);

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询短信记录
//
int DatabaseManager::QuerySMSData(ULONG dwTargetId, QTableWidget* table)
{
	char sqlValue[512] = {0};

	sprintf(sqlValue, " select * from monitor_message where targetId = %u ", dwTargetId);

	QSqlQuery query;
	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		// 时间、类型、联系人、内容
		QTableWidgetItem* time = new QTableWidgetItem;
		time->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* type = new QTableWidgetItem;
		type->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* contact = new QTableWidgetItem;
		QTableWidgetItem* message = new QTableWidgetItem;
		QTableWidgetItem* getTime = new QTableWidgetItem;
		getTime->setTextAlignment(Qt::AlignCenter);

		time->setText(query.value(2).toString());
		type->setText(query.value(3).toString() == "1" ? 
			QString::fromLocal8Bit("发送") : QString::fromLocal8Bit("接收"));
		contact->setText(query.value(4).toString());
		message->setText(query.value(5).toString());
		getTime->setText(query.value(6).toString());

		//time->setIcon(QIcon(QPixmap("image/message.png")));

		table->insertRow(0);
		table->setItem(0, 0, time);
		table->setItem(0, 1, type);
		table->setItem(0, 2, contact);
		table->setItem(0, 3, message);
		table->setItem(0, 4, getTime);

	}
	LeaveCriticalSection(&csGui);
	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询通话记录
//
int DatabaseManager::QueryCALData(unsigned int dwTargetId, QTableWidget* table)
{
	char sqlValue[512] = {0};

	sprintf(sqlValue, " select * from monitor_call where targetId = %u ", dwTargetId);

	QSqlQuery query;
	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		// 时间、类型、联系人、归属地、运营商、通话时长
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

		time->setText(query.value(2).toString());
		type->setText(query.value(3).toString() == "1" ? 
			QString::fromLocal8Bit("拨打") : QString::fromLocal8Bit("接听"));
		contact->setText(query.value(4).toString());
		duration->setText(query.value(5).toString() + QString::fromLocal8Bit(" 秒"));
		getTime->setText(query.value(6).toString());

		location->setText(query.value(7).toString());
		network->setText(query.value(8).toString());

		//time->setIcon(QIcon(QPixmap("image/call.png")));

		table->insertRow(0);
		table->setItem(0, 0, time);
		table->setItem(0, 1, type);
		table->setItem(0, 2, contact);
		table->setItem(0, 3, network);
		table->setItem(0, 4, location);
		table->setItem(0, 5, duration);
		table->setItem(0, 6, getTime);

	}
	LeaveCriticalSection(&csGui);
	return 0;
}

int DatabaseManager::QueryCONTACTData(unsigned int dwTargetId, QTableWidget* table)
{
	char sqlValue[512] = {0};

	sprintf(sqlValue, " select * from monitor_addressbook where targetID = %u ", dwTargetId);

	QSqlQuery query;
	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		// 联系人、电话、备注
		QTableWidgetItem* name = new QTableWidgetItem;
		//name->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* phone = new QTableWidgetItem;

		QTableWidgetItem* location = new QTableWidgetItem;
		QTableWidgetItem* network = new QTableWidgetItem;
		//phone->setTextAlignment(Qt::AlignCenter);
		QTableWidgetItem* remark = new QTableWidgetItem;

		QTableWidgetItem* getTime = new QTableWidgetItem;
		getTime->setTextAlignment(Qt::AlignCenter);

		name->setText(query.value(2).toString());
		phone->setText(query.value(3).toString());
		remark->setText(query.value(4).toString());
		getTime->setText(query.value(5).toString());
		location->setText(query.value(6).toString());
		network->setText(query.value(7).toString());

		name->setIcon(QIcon(QPixmap("image/group.png")));

		table->insertRow(0);
		table->setItem(0, 0, name);
		table->setItem(0, 1, phone);
		table->setItem(0, 2, location);
		table->setItem(0, 3, network);
		table->setItem(0, 4, remark);
		table->setItem(0, 5, getTime);

	}

	LeaveCriticalSection(&csGui);
	return 0;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询 location 信息
//
void DatabaseManager::QueryLocationInfo(ULONG targetID, QTableWidget* table)
{
	char sqlValue[512] = {0};

	sprintf(sqlValue, " select * from monitor_location where targetID = %u ", targetID);

	QSqlQuery query;
	QString cmd = QString::fromLocal8Bit(sqlValue);

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		// 时间、位置、x、y
		QTableWidgetItem* time = new QTableWidgetItem;
		QTableWidgetItem* remark = new QTableWidgetItem;

		time->setText(query.value(2).toString());
		remark->setText(query.value(5).toString());

		time->setData(Qt::UserRole, query.value(3).toString());
		remark->setData(Qt::UserRole, query.value(4).toString());

		table->insertRow(0);
		table->setItem(0, 0, time);
		table->setItem(0, 1, remark);
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入文件监控记录
//
void DatabaseManager::InsertFileMonitorRecord(ULONG dwTargetId, 
											  std::wstring recordName, 
											  std::wstring recordPath, 
											  std::wstring recordTime)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"insert into file_monitor_record (targetId, recordName, recordPath, recordTime) \
					  values (%d, '%s', '%s', '%s') ", 
					  dwTargetId,
					  recordName.c_str(),
					  recordPath.c_str(),
					  recordTime.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 清除文件监控记录
//
void DatabaseManager::CleanFileMonitorRecord(ULONG dwTargetId, std::wstring recordPath)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(
		sqlValue, 
		L"DELETE FROM file_monitor_record WHERE targetId = %u AND recordPath LIKE '%s%%'",
		dwTargetId,
		recordPath.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入文件监控列表
//
void DatabaseManager::InsertFileMonitorList(ULONG dwTargetId, 
											std::wstring fileName, 
											std::wstring filePath, 
											std::wstring fileTime, 
											std::wstring fileType, 
											ULONG isDir)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"insert into file_monitor_list (targetId, fileName, filePath, fileTime, fileType, isDir) \
					  values (%d, '%s', '%s', '%s', '%s', %d) ", 
					  dwTargetId,
					  fileName.c_str(),
					  filePath.c_str(),
					  fileTime.c_str(),
					  fileType.c_str(),
					  (unsigned int)isDir);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// 取消监控
//
void DatabaseManager::RemoveFileMonitorList(ULONG dwTargetId, std::wstring path)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"DELETE FROM file_monitor_list WHERE targetId = %u AND filePath = '%s'", dwTargetId, path.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

bool DatabaseManager::QueryFileItemMonitored(ULONG targetId, std::wstring filePath)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"select count(*) from file_monitor_list where targetId = %u and filePath = '%s'", targetId, filePath.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	query.next();
	int count = query.value(0).toInt();
	LeaveCriticalSection(&csGui);

	return ( count != 0 );
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询文件监控记录
//
void DatabaseManager::QueryFileMonitorRecord(ULONG dwTargetId, QTreeWidget* tree)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"select top 1000 * from file_monitor_record where targetId = %d", dwTargetId);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);

	while ( query.next() )
	{
		std::wstring filePath = query.value(3).toString().toStdWString();
		std::wstring time = query.value(4).toString().toStdWString();
		std::wstring remark = query.value(2).toString().toStdWString();

		QTreeWidgetItem* item = new QTreeWidgetItem;

		item->setText(0, QString::fromStdWString(filePath));
		item->setText(1, QString::fromStdWString(time));
		item->setText(2, QString::fromStdWString(remark));
		HICON icon = GetIconFromFileName(filePath.c_str());

		if ( NULL != icon )
			item->setIcon(0, QIcon(QPixmap::fromWinHICON(icon)));

		QTreeWidgetItem* parent = GetParentDirItem(tree, filePath);

		if ( parent)
			parent->addChild(item);
		
	}

	LeaveCriticalSection(&csGui);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询文件监控列表
//
void DatabaseManager::QueryFileMonitorList(ULONG dwTargetId, QTreeWidget* tree)
{
	WCHAR sqlValue[1024] = {0};

	wsprintf(sqlValue, L"select * from file_monitor_list where targetId = %d", dwTargetId);

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	while ( query.next() )
	{
		QTreeWidgetItem* item = new QTreeWidgetItem;
		item->setText(0, query.value(3).toString());

		QFileIconProvider provider;
		item->setIcon(0, provider.icon(QFileIconProvider::Folder));
		item->setData(0, Qt::UserRole, (unsigned int)FILE_ATTRIBUTE_DIRECTORY);

		tree->addTopLevelItem(item);
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 查询文件监控记录数量
//
int DatabaseManager::GetFileRecordCount(ULONG dwTargetId, std::wstring path)
{
	WCHAR sqlValue[512] = {0};

	wsprintf(sqlValue, L"select * from file_monitor_list where targetId = %d and filePath = '%s'",
		dwTargetId, path.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	if ( !query.next() )
	{
		// 查不到说明没有记录
		return 0;
	}

	wsprintf(sqlValue, L"select count(*) from file_monitor_record where targetId = %d and recordPath = '%s'",
		dwTargetId, path.c_str());

	cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);

	int count = 1;

	if ( query.next() )
	{
		count += query.value(0).toUInt();
	}

	return count;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 清空数据库
//
void DatabaseManager::CleanDatabase()
{
	QString table;
	QStringList tableList = db.tables();

	QSqlQuery query;
	QString cmd;

	foreach(table, tableList)
	{
		if ( table != "DB_location" )
		{
			cmd = QString("delete from %1").arg(table);
			query.exec(cmd);
		}
	}
}

void DatabaseManager::CleanTargetData(ULONG targetId)
{
	QSqlQuery query;
	query.exec(QString("delete from target_info where targetId = %1").arg(targetId));
}

void DatabaseManager::GetLocationFromPhoneNumber(
	const std::wstring& phoneNumber, 
	std::wstring& location, 
	std::wstring& netService )
{
	std::string firstNum = GetPhoneNumberPrefix(WideToAnsi(phoneNumber));
	CHAR sqlValue[1024] = {0};
	sprintf(sqlValue, "select * from DB_location where MobileNumber='%s'", firstNum.c_str());
	QSqlQuery locationQuery;

	EnterCriticalSection(&csGui);
	bool ret = locationQuery.exec(QString(sqlValue));

	if ( !ret )
		qDebug() << locationQuery.lastError();

	if ( locationQuery.next() )
	{
		location = locationQuery.value(2).toString().toStdWString();
		netService = locationQuery.value(3).toString().toStdWString();
	}

	LeaveCriticalSection(&csGui);
}

bool DatabaseManager::QQAccountExist(ULONG dwTargetId, std::wstring qqNumber)
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select count(*) from monitor_qq_account where targetId = %d and qqNumber = '%s'",
		dwTargetId, qqNumber.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	query.next();
	int value = query.value(0).toInt();
	LeaveCriticalSection(&csGui);

	return (value != 0);
}

void DatabaseManager::InsertQQAccount( ULONG dwTargetId, std::wstring qqNumber )
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"insert into monitor_qq_account (targetId, qqNumber) values(%d, '%s')",
		dwTargetId, qqNumber.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

bool DatabaseManager::QQFriendExist(ULONG dwTargetId, std::wstring owner, std::wstring number)
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select count(*) from monitor_qq_friend where targetId = %d and owner = '%s' and [number] = '%s'",
		dwTargetId, owner.c_str(), number.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	query.next();
	int value = query.value(0).toInt();
	LeaveCriticalSection(&csGui);

	return (value != 0);
}

void DatabaseManager::InsertQQFriend( 
	ULONG dwTargetId, 
	std::wstring owner, 
	std::wstring number, 
	std::wstring nickName, 
	std::wstring remark, 
	std::wstring signature, 
	std::wstring group )
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"insert into monitor_qq_friend (targetId, owner, [number], nickName, remark, signature, groupName)"
		L" values(%d, '%s', '%s', '%s', '%s', '%s', '%s')",
		dwTargetId, owner.c_str(), number.c_str(), nickName.c_str(), remark.c_str(), signature.c_str(), group.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	if ( !query.exec(cmd) )
		qDebug() << query.lastError();
	LeaveCriticalSection(&csGui);
}

bool DatabaseManager::QQTroopExist(ULONG targetId, std::wstring owner, std::wstring number)
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select count(*) from monitor_qq_troop where targetId = %d and owner = '%s' and troopNumber = '%s'",
		targetId, owner.c_str(), number.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	query.next();
	int value = query.value(0).toInt();
	LeaveCriticalSection(&csGui);

	return (value != 0);
}

void DatabaseManager::InsertQQTroop( 
	ULONG targetId, 
	std::wstring owner, 
	std::wstring number, 
	std::wstring troopName, 
	std::wstring troopMemo )
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"insert into monitor_qq_troop (targetId, owner, troopNumber, troopName, troopMemo)"
		L" values(%d, '%s', '%s', '%s', '%s')",
		targetId, owner.c_str(), number.c_str(), troopName.c_str(), troopMemo.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	if ( !query.exec(cmd) )
		qDebug() << query.lastError();
	LeaveCriticalSection(&csGui);
}

void DatabaseManager::InsertQQMessage( 
	ULONG dwTargetId, 
	std::wstring owner, 
	int type, 
	std::wstring containerNumber, 
	std::wstring senderNumber, 
	std::wstring senderNickName, 
	std::wstring time, 
	int msgType, 
	std::wstring content )
{
	WCHAR sqlValue[4096] = {0};
	wsprintf(sqlValue, 
		L"insert into monitor_qq_content (targetId, owner, sendType, containerNumber, senderNumber, senderNickName, sendTime, msgType, content)"
		L" values(%d, '%s', '%d', '%s', '%s', '%s', '%s', %d, '%s')",
		dwTargetId, 
		owner.c_str(), 
		type, 
		containerNumber.c_str(), 
		senderNumber.c_str(), 
		senderNickName.c_str(), 
		time.c_str(), 
		msgType, 
		content.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

bool DatabaseManager::WeixinAccountExist(ULONG dwTargetId, std::wstring weixinId)
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select count(*) from monitor_weixin_account where targetId = %d and weixinId = '%s'",
		dwTargetId, weixinId.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	query.next();
	int value = query.value(0).toInt();
	LeaveCriticalSection(&csGui);

	return (value != 0);
}

void DatabaseManager::InsertWeixinAccount( 
	ULONG dwTargetId, 
	std::wstring weixinId, 
	std::wstring nickName )
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"insert into monitor_weixin_account (targetId, weixinId, weixinNickName)"
		L" values(%d, '%s', '%s')",
		dwTargetId, weixinId.c_str(), nickName.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

bool DatabaseManager::WeixinFriendExist(ULONG dwTargetId, std::wstring weixinId, std::wstring friendId)
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"select count(*) from monitor_weixin_friend where targetId = %d and weixinId = '%s' and friendId = '%s'",
		dwTargetId, weixinId.c_str(), friendId.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	query.next();
	int value = query.value(0).toInt();
	LeaveCriticalSection(&csGui);

	return (value != 0);
}

void DatabaseManager::InsertWeixinFrineds( 
	ULONG dwTargetId, 
	std::wstring weixinId, 
	std::wstring friendId, 
	std::wstring nickName )
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"insert into monitor_weixin_friend (targetId, weixinId, friendId, friendNickName)"
		L" values(%d, '%s', '%s', '%s')",
		dwTargetId, weixinId.c_str(), friendId.c_str(), nickName.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

void DatabaseManager::InsertWeixinMessage( 
	ULONG dwTargetId, 
	std::wstring weixinId, 
	std::wstring friendId, 
	std::wstring senderId,
	std::wstring time, 
	int type, 
	std::wstring content )
{
	WCHAR sqlValue[1024] = {0};
	wsprintf(sqlValue, 
		L"insert into monitor_weixin_content (targetId, weixinId, friendId, senderId, sendTime, sendType, content)"
		L" values(%d, '%s', '%s', '%s', '%s', %d, '%s')",
		dwTargetId, weixinId.c_str(), friendId.c_str(), senderId.c_str(), time.c_str(), type, content.c_str());

	QSqlQuery query;
	QString cmd = QString::fromStdWString(std::wstring(sqlValue));

	EnterCriticalSection(&csGui);
	query.exec(cmd);
	LeaveCriticalSection(&csGui);
}

void DatabaseManager::CleanAppData(ULONG targetId)
{
	QSqlQuery query;
	//if ( !query.exec(QString("delete from monitor_qq_account where targetId = %1").arg(targetId)) )
	//	qDebug() << query.lastError();
	//query.exec(QString("delete from monitor_qq_friend where targetId = %1").arg(targetId));
	//query.exec(QString("delete from monitor_qq_troop where targetId = %1").arg(targetId));
	query.exec(QString("delete from monitor_qq_content where targetId = %1").arg(targetId));
	//query.exec(QString("delete from monitor_weixin_account where targetId = %1").arg(targetId));
	//query.exec(QString("delete from monitor_weixin_friend where targetId = %1").arg(targetId));
	query.exec(QString("delete from monitor_weixin_content where targetId = %1").arg(targetId));
}

void DatabaseManager::StartExportAppRecord(QString qpath, int targetId)
{
	m_hExport = CreateEventW(NULL, TRUE, FALSE, L"ExportEvent");
	ResetEvent(m_hExport);

	EnterCriticalSection(&csGui);

	WCHAR sqlValue[1024] = {0};
	QSqlQuery query;

	std::wstring path = qpath.toStdWString();
	path += L"\\聊天记录";
	CreateDirectoryW(path.c_str(), NULL);

	std::wstring qqPath = path + L"\\QQ";
	std::wstring weixinPath = path + L"\\微信";
	CreateDirectoryW(qqPath.c_str(), NULL);
	CreateDirectoryW(weixinPath.c_str(), NULL);

	// Step 1 : Get total record count.
	wsprintfW(sqlValue, L"select count(*) from monitor_qq_content where targetId = %d", targetId);
	query.exec(QString::fromStdWString(std::wstring(sqlValue)));
	query.next();
	int qqCount = query.value(0).toInt();

	wsprintfW(sqlValue, L"select count(*) from monitor_weixin_content where targetId = %d", targetId);
	query.exec(QString::fromStdWString(std::wstring(sqlValue)));
	query.next();
	int mmCount = query.value(0).toInt();

	int totalCount = qqCount + mmCount;
	emit emitAppRecordCount(totalCount);

	// Step2 : Export every record.

	// Step 2.1 : qq
	std::list<std::wstring> accountList;
	wsprintfW(sqlValue, L"select distinct owner from monitor_qq_content where targetId = %d", targetId);
	query.exec(QString::fromStdWString(std::wstring(sqlValue)));
	while ( query.next() )
	{
		if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hExport, 0) )
			goto CANCLE_EXPORT;

		std::wstring account = query.value(0).toString().toStdWString();
		accountList.push_back(account);
	}

	for (std::list<std::wstring>::iterator it = accountList.begin(); it != accountList.end(); ++it)
	{
		std::wstring accountPath = qqPath + L"\\" + it->c_str();
		CreateDirectoryW(accountPath.c_str(), NULL);

		wsprintfW(sqlValue, L"select distinct containerNumber from monitor_qq_content where targetId = %d and owner = '%s'", targetId, it->c_str());
		query.exec(QString::fromStdWString(std::wstring(sqlValue)));

		std::list<std::wstring> friendList;

		while ( query.next() )
		{
			if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hExport, 0) )
				goto CANCLE_EXPORT;

			std::wstring friendAccount = query.value(0).toString().toStdWString();
			friendList.push_back(friendAccount);
		}

		for ( std::list<std::wstring>::iterator itf = friendList.begin(); itf != friendList.end(); ++itf )
		{
			wsprintf(sqlValue, L"select * from monitor_qq_content where targetId = %d and owner = '%s' and containerNumber = '%s' order by sendTime",
				targetId, it->c_str(), itf->c_str());
			
			std::wstring recordFile = accountPath + L"\\" + itf->c_str() + L".txt";
			HANDLE hf = CreateFile(recordFile.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			unsigned char hdr[2] = {0xFF, 0xFE};
			DWORD dump = 0;
			WriteFile(hf, hdr, 2, &dump, NULL);
			query.exec(QString::fromStdWString(std::wstring(sqlValue)));

			while ( query.next() )
			{
				if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hExport, 0) )
				{
					CloseHandle(hf);
					goto CANCLE_EXPORT;
				}

				std::wstring senderNumber = query.value(5).toString().toStdWString();
				std::wstring time = query.value(7).toString().toStdWString();
				int msgType = query.value(8).toInt();
				std::wstring content = query.value(9).toString().toStdWString();

				WCHAR record[1024] = {0};
				wsprintfW(record, L"%s %s\r\n%s\r\n\r\n", senderNumber.c_str(), time.c_str(), content.c_str());

				WriteFile(hf, record, wcslen(record)*2, &dump, NULL);
				emit emitAppCurrentRecordAdd();
			}

			CloseHandle(hf);
		}
	}

	// Step 2.1 : weixin
	accountList.clear();
	wsprintfW(sqlValue, L"select distinct weixinId from monitor_weixin_content where targetId = %d", targetId);
	query.exec(QString::fromStdWString(std::wstring(sqlValue)));

	while ( query.next() )
	{
		if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hExport, 0) )
			goto CANCLE_EXPORT;

		std::wstring account = query.value(0).toString().toStdWString();
		accountList.push_back(account);
	}

	for (std::list<std::wstring>::iterator it = accountList.begin(); it != accountList.end(); ++it)
	{
		std::wstring accountPath = weixinPath + L"\\" + it->c_str();
		CreateDirectoryW(accountPath.c_str(), NULL);

		wsprintfW(sqlValue, L"select distinct friendId from monitor_weixin_content where targetId = %d and weixinId = '%s'", targetId, it->c_str());
		query.exec(QString::fromStdWString(std::wstring(sqlValue)));

		std::list<std::wstring> friendList;

		while ( query.next() )
		{
			if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hExport, 0) )
				goto CANCLE_EXPORT;

			std::wstring friendAccount = query.value(0).toString().toStdWString();
			friendList.push_back(friendAccount);
		}

		for ( std::list<std::wstring>::iterator itf = friendList.begin(); itf != friendList.end(); ++itf )
		{
			wsprintf(sqlValue, L"select * from monitor_weixin_content where targetId = %d and weixinId = '%s' and friendId = '%s' order by sendTime",
				targetId, it->c_str(), itf->c_str());

			std::wstring recordFile = accountPath + L"\\" + itf->c_str() + L".txt";
			HANDLE hf = CreateFile(recordFile.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			unsigned char hdr[2] = {0xFF, 0xFE};
			DWORD dump = 0;
			WriteFile(hf, hdr, 2, &dump, NULL);
			query.exec(QString::fromStdWString(std::wstring(sqlValue)));

			while ( query.next() )
			{
				if ( WAIT_OBJECT_0 == WaitForSingleObject(m_hExport, 0) )
				{
					CloseHandle(hf);
					goto CANCLE_EXPORT;
				}

				std::wstring senderId = query.value(4).toString().toStdWString();
				std::wstring time = query.value(5).toString().toStdWString();
				int msgType = query.value(6).toInt();
				std::wstring content = query.value(7).toString().toStdWString();

				WCHAR record[1024] = {0};
				wsprintfW(record, L"%s %s\r\n%s\r\n\r\n", senderId.c_str(), time.c_str(), content.c_str());

				WriteFile(hf, record, wcslen(record)*2, &dump, NULL);
				emit emitAppCurrentRecordAdd();
			}

			CloseHandle(hf);
		}
	}


CANCLE_EXPORT:

	LeaveCriticalSection(&csGui);

	if ( WAIT_OBJECT_0 != WaitForSingleObject(m_hExport, 0) )
		emitAppExportFinished();
	else
		emitAppExportCanceled();
}

void DatabaseManager::CancelExportAppRecord()
{
	SetEvent(m_hExport);
}


void DatabaseManager::UnitTest()
{
	//if ( !this->QQAccountExist(1419882686, L"532344736") )
	//	this->InsertQQAccount(1419882686, L"532344736");

	//this->InsertQQFriend(1419882686, L"532344736", L"1059299018", L"Mars.Lu++", L"我自己", L"我有一个梦想", L"家人");
	/*this->InsertQQTroop(1420373341, L"532344736", L"8231314", L"qt交流", L"不准发黄图");
	this->InsertQQMessage(1420373341, L"532344736", 0, L"1059299018", L"1059299018", L"Mars.Lu++", L"2014-10-24 14:37", 0, L"吃饭了吗");
	this->InsertQQMessage(1420373341, L"532344736", 0, L"1059299018", L"1059299018", L"Mars.Lu++", L"2014-10-24 14:37", 2, 
		L"D:\\1.amr");*/

/*	if ( !WeixinAccountExist(1419882686, L"1111" ) )
		this->InsertWeixinAccount(1419882686, L"1111", L" ");

	bool exist = WeixinFriendExist(1419882686, L"1111", L"2222");
	if ( !exist )
		this->InsertWeixinFrineds(1419882686, L"1111", L"2222", L"暴走漫画");

	this->InsertWeixinMessage(1419882686, L"1111", L"2222", L"2222", L"2014-10-24 15:37", 0, L"你拉屎的时候一定要看暴走漫画");
	this->InsertWeixinMessage(1419882686, L"1111", L"2222", L"2222", L"2014-10-24 15:37", 1, L"c:\\测试\\1.png");
	this->InsertWeixinMessage(1419882686, L"1111", L"2222", L"2222", L"2014-10-24 15:37", 2, L"D:\\1.amr");*/
}
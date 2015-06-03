#include "logdetaildlg.h"
#include "target.h"
//#include "DatabaseManager.h"
#include "pagetablewidget.h"
#include "nofocusstyle.h"
#include "Utility.h"
#include "DatabaseManager.h"

#include <QtGui>

LogDetailDlg::LogDetailDlg(QWidget *parent, Target* tar)
	: QWidget(parent)
	, m_tar(tar)
	, m_waitLogDetailDlg(NULL)
	, m_queryLogDetailFinished(false)
	, m_waitLogDownloadDlg(NULL)
	, m_queryLogDownloadFinished(false)
	, m_waitLogUploadDlg(NULL)
	, m_queryLogUploadFinished(false)
	, m_waitLogPluginDlg(NULL)
	, m_queryLogPluginFinished(false)
{
	ui.setupUi(this);

	InitLogInfo();
	InitConnection();

	RefreshOnlineLogInfo();

	// �����
	if ( SYSTEM_WINDOWS != GetSystemType(this->m_tar->dwOsBuildNumber) )
	{
		ui.chkLogDownload->hide();
		ui.chkLogUpload->hide();
	}
}

LogDetailDlg::~LogDetailDlg()
{

}

void LogDetailDlg::RefreshOnlineLogInfo()
{
	ui.tbLog->Clear();
	DM->QueryLogInfo(this->m_tar->dwTargetID, ui.tbLog);
}

void LogDetailDlg::InitLogInfo()
{
	NoFocusStyle* nofocusStyle = new NoFocusStyle(this);
	ui.tbLog->SetTableStyle(nofocusStyle);
	ui.tbDetailLog->SetTableStyle(nofocusStyle);
	ui.tbLogDownload->SetTableStyle(nofocusStyle);
	ui.tbLogUpload->SetTableStyle(nofocusStyle);
	ui.tbLogPlugin->SetTableStyle(nofocusStyle);

	ui.tbLog->SetRowCountPerPage(40);
	ui.tbLog->SetColumnCount(7);
	QStringList headers;
	headers << QString::fromLocal8Bit("ʱ��")
		<< QString::fromLocal8Bit("״̬")
		<< QString::fromLocal8Bit("�ⲿ IP ��ַ")
		<< QString::fromLocal8Bit("�ڲ� IP ��ַ")
		<< QString::fromLocal8Bit("������ַ")
		<< QString::fromLocal8Bit("���߽���")
		<< QString::fromLocal8Bit("��¼�û�");
	ui.tbLog->SetColumnLabels(headers);

	ui.tbLog->horizontalHeader()->resizeSection(1, 50);

	ui.tbDetailLog->SetRowCountPerPage(40);
	ui.tbDetailLog->SetColumnCount(2);
	QStringList detailHeaders;
	detailHeaders << QString::fromLocal8Bit("ʱ��")
		<< QString::fromLocal8Bit("����");
	ui.tbDetailLog->SetColumnLabels(detailHeaders);

	PageTableWidget* taskTables[] = {ui.tbLogDownload, ui.tbLogUpload, ui.tbLogPlugin};

	for ( int i = 0; i < sizeof(taskTables) / sizeof (PageTableWidget*); ++i )
	{
		PageTableWidget* table = taskTables[i];
		table->SetRowCountPerPage(40);
		table->SetColumnCount(7);
		QStringList headers;
		headers << QString::fromLocal8Bit("ʱ��")
			<< QString::fromLocal8Bit("ID")
			<< QString::fromLocal8Bit("���")
			<< QString::fromLocal8Bit("״̬")
			<< QString::fromLocal8Bit("����·��")
			<< QString::fromLocal8Bit("Ŀ��·��")
			<< QString::fromLocal8Bit("��С");
		table->SetColumnLabels(headers);

		table->horizontalHeader()->resizeSection(0, 150);
		table->horizontalHeader()->resizeSection(1, 80);
		table->horizontalHeader()->resizeSection(2, 150);
		table->horizontalHeader()->resizeSection(3, 50);
		table->horizontalHeader()->resizeSection(4, 200);
		table->horizontalHeader()->resizeSection(5, 200);
		table->horizontalHeader()->resizeSection(6, 50);

	}
}

void LogDetailDlg::InitConnection()
{
	// �����������־
	connect(ui.chkOnlineLog, SIGNAL(clicked()), this, SLOT(onChkOnlineLogClicked()));

	// ���ϸ����־
	connect(ui.chkDetailLog, SIGNAL(clicked()), this, SLOT(onChkLogDetailClicked()));

	// ���������־
	connect(ui.chkLogDownload, SIGNAL(clicked()), this, SLOT(onChkLogDownloadClicked()));

	// ����ϴ���־
	connect(ui.chkLogUpload, SIGNAL(clicked()), this, SLOT(onChkLogUploadClicked()));

	// ���������ݻش���־
	connect(ui.chkLogPlugin, SIGNAL(clicked()), this, SLOT(onChkLogPluginClicked()));

	// ��ѯϸ����־
	connect(this, SIGNAL(emitLogDetailInfo(unsigned int, PageTableWidget*)), DM, SLOT(QueryLogDetailInfo(unsigned int, PageTableWidget*)));

	// ��ѯ���
	connect(DM, SIGNAL(emitLogDetailInfoFinished(unsigned int)), this, SLOT(onQueryLogDetailFinished(unsigned int)));

	// ��ѯ������־
	connect(this, SIGNAL(emitLogDownloadInfo(unsigned int, PageTableWidget*)), DM, SLOT(QueryLogDownloadInfo(unsigned int, PageTableWidget*)));

	// ��ѯ���
	connect(DM, SIGNAL(emitLogDownloadInfoFinished(unsigned int)), this, SLOT(onQueryLogDownloadFinished(unsigned int)));

	// ��ѯ�ϴ���־
	connect(this, SIGNAL(emitLogUploadInfo(unsigned int, PageTableWidget*)), DM, SLOT(QueryLogUploadInfo(unsigned int, PageTableWidget*)));

	// ��ѯ���
	connect(DM, SIGNAL(emitLogUploadInfoFinished(unsigned int)), this, SLOT(onQueryLogUploadFinished(unsigned int)));

	// ��ѯ����ش���־
	connect(this, SIGNAL(emitLogPluginInfo(unsigned int, PageTableWidget*)), DM, SLOT(QueryLogPluginInfo(unsigned int, PageTableWidget*)));

	// ��ѯ���
	connect(DM, SIGNAL(emitLogPluginInfoFinished(unsigned int)), this, SLOT(onQueryLogPluginFinished(unsigned int)));
}

void LogDetailDlg::onChkOnlineLogClicked()
{
	ui.stkLog->setCurrentIndex(0);
}


void LogDetailDlg::onChkLogDetailClicked()
{
	ui.stkLog->setCurrentIndex(1);

	if ( !m_queryLogDetailFinished && NULL == m_waitLogDetailDlg )
	{
		emit emitLogDetailInfo(this->m_tar->dwTargetID, ui.tbDetailLog);
		m_waitLogDetailDlg = new WaitDlg(ui.tbDetailLog);
		//qDebug() << ui.tbDetailLog->size();
		m_waitLogDetailDlg->show();
	}
}

void LogDetailDlg::onChkLogDownloadClicked()
{
	ui.stkLog->setCurrentIndex(2);

	if ( !m_queryLogDownloadFinished && NULL == m_waitLogDownloadDlg )
	{
		emit emitLogDownloadInfo(this->m_tar->dwTargetID, ui.tbLogDownload);
		m_waitLogDownloadDlg = new WaitDlg(ui.tbLogDownload);
		//qDebug() << ui.tbDetailLog->size();
		m_waitLogDownloadDlg->show();
	}
}

void LogDetailDlg::onChkLogUploadClicked()
{
	ui.stkLog->setCurrentIndex(3);

	if ( !m_queryLogUploadFinished && NULL == m_waitLogUploadDlg )
	{
		emit emitLogUploadInfo(this->m_tar->dwTargetID, ui.tbLogUpload);
		m_waitLogUploadDlg = new WaitDlg(ui.tbLogUpload);
		//qDebug() << ui.tbDetailLog->size();
		m_waitLogUploadDlg->show();
	}
}

void LogDetailDlg::onChkLogPluginClicked()
{
	ui.stkLog->setCurrentIndex(4);

	if ( !m_queryLogPluginFinished && NULL == m_waitLogPluginDlg )
	{
		emit emitLogPluginInfo(this->m_tar->dwTargetID, ui.tbLogPlugin);
		m_waitLogPluginDlg = new WaitDlg(ui.tbLogPlugin);
		//qDebug() << ui.tbDetailLog->size();
		m_waitLogPluginDlg->show();
	}
}

void LogDetailDlg::onQueryLogDetailFinished(unsigned int tarId)
{
	if ( tarId != this->m_tar->dwTargetID )
		return;

	if ( m_waitLogDetailDlg )
	{
		m_waitLogDetailDlg->close();
		delete m_waitLogDetailDlg;
		m_waitLogDetailDlg = NULL;
	}
	m_queryLogDetailFinished = true;
}

void LogDetailDlg::onQueryLogDownloadFinished(unsigned int tarId)
{
	if ( tarId != this->m_tar->dwTargetID )
		return;

	if ( m_waitLogDownloadDlg )
	{
		m_waitLogDownloadDlg->close();
		delete m_waitLogDownloadDlg;
		m_waitLogDownloadDlg = NULL;
	}
	m_queryLogDownloadFinished = true;
}

void LogDetailDlg::onQueryLogUploadFinished(unsigned int tarId)
{
	if ( tarId != this->m_tar->dwTargetID )
		return;

	if ( m_waitLogUploadDlg )
	{
		m_waitLogUploadDlg->close();
		delete m_waitLogUploadDlg;
		m_waitLogUploadDlg = NULL;
	}
	m_queryLogUploadFinished = true;
}

void LogDetailDlg::onQueryLogPluginFinished(unsigned int tarId)
{
	if ( tarId != this->m_tar->dwTargetID )
		return;

	if ( m_waitLogPluginDlg )
	{
		m_waitLogPluginDlg->close();
		delete m_waitLogPluginDlg;
		m_waitLogPluginDlg = NULL;
	}
	m_queryLogPluginFinished = true;
}

void LogDetailDlg::AddDetail(const wchar_t* info)
{
	std::wstring time = AnsiToWide(TGetCurrentTime());

	QTableWidgetItem* timeItem = new QTableWidgetItem;
	QTableWidgetItem* content = new QTableWidgetItem;

	timeItem->setText(QString::fromStdWString(time));
	content->setText(QString::fromStdWString(std::wstring(info)));

	ui.tbDetailLog->AppendRow();
	ui.tbDetailLog->SetAppendRowItem(0, timeItem);
	ui.tbDetailLog->SetAppendRowItem(1, content);
	ui.tbDetailLog->RefreshPage();
}

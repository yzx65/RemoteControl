#include "exportappinfodlg.h"

#include <Windows.h>
#include <string>

#include "DatabaseManager.h"

ExportAppInfoDlg::ExportAppInfoDlg(QString path, int targetId)
	: QDialog(0)
	, m_path(path)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowTitleHint);

	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancelClicked()));

	connect(this, SIGNAL(emitStart(QString, int)), DM, SLOT(StartExportAppRecord(QString, int)));

	connect(DM, SIGNAL(emitAppRecordCount(int)), this, SLOT(GetRecordCount(int)));
	connect(DM, SIGNAL(emitAppCurrentRecordAdd()), this, SLOT(CurrentRecordAdd()));
	connect(DM, SIGNAL(emitAppExportFinished()), this, SLOT(ExportFinished()));
	connect(DM, SIGNAL(emitAppExportCanceled()), this, SLOT(ExportCanceled()));

	emitStart(path, targetId);

	InitCustomText(this);
}

ExportAppInfoDlg::~ExportAppInfoDlg()
{

}

void ExportAppInfoDlg::GetRecordCount( int count )
{
	ui.progress->setMaximum(count);
	m_count = count;
}

void ExportAppInfoDlg::CurrentRecordAdd()
{
	int value = ui.progress->value() + 1;
	ui.progress->setValue(value);

	WCHAR text[1024] = {0};
	wsprintfW(text, L"正在导出第 %d 条聊天记录 ...", value);
	
	ui.lbText->setText(QString::fromStdWString(std::wstring(text)));
}

void ExportAppInfoDlg::ExportFinished()
{
	accept();
}

void ExportAppInfoDlg::ExportCanceled()
{
	reject();
}

void ExportAppInfoDlg::OnBtnCancelClicked()
{
	DM->CancelExportAppRecord();
}

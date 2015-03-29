#include "uploadfiledlg.h"
#include <QFileDialog>
#include <Windows.h>

// ////////////////////////////////////////////////////////////////////////////////
// 构造函数
//
UploadFileDlg::UploadFileDlg(QWidget *parent, QString remotePath)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.edtRemotePath->setText(remotePath);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));
	connect(ui.btnBrowse, SIGNAL(clicked()), this, SLOT(OnBtnBrowseClicked()));
}

// ////////////////////////////////////////////////////////////////////////////////
// 析构函数
//
UploadFileDlg::~UploadFileDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 获取本地文件路径
//
QString UploadFileDlg::GetLocalPath()
{
	return ui.edtLocalFile->text();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 获取文件大小
//
unsigned int UploadFileDlg::GetFileSize()
{
	HANDLE hFile = CreateFileW(
		ui.edtLocalFile->text().toStdWString().c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD dwDump = 0;
	unsigned int size = ::GetFileSize(hFile, &dwDump);
	CloseHandle(hFile);

	return size;
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 确定
//
void UploadFileDlg::OnOk()
{
	if ( ui.edtLocalFile->text().isEmpty() )
	{
		MessageBoxA((HWND)this->winId(), "请选择一个文件", "提示", MB_OK);
		return;
	}
	accept();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 浏览
//
void UploadFileDlg::OnBtnBrowseClicked()
{
	QString fileName = QFileDialog::getOpenFileName();

	if ( !fileName.isEmpty() )
	{
		ui.edtLocalFile->setText(fileName.replace('/', '\\'));
	}
}

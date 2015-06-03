#include "uploadfiledlg.h"
#include <QFileDialog>
#include <Windows.h>
#include "Utility.h"

// ////////////////////////////////////////////////////////////////////////////////
// ���캯��
//
UploadFileDlg::UploadFileDlg(QWidget *parent, QString remotePath)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.edtRemotePath->setText(remotePath);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));
	connect(ui.btnBrowse, SIGNAL(clicked()), this, SLOT(OnBtnBrowseClicked()));

	InitCustomText(this);
}

// ////////////////////////////////////////////////////////////////////////////////
// ��������
//
UploadFileDlg::~UploadFileDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public ��ȡ�����ļ�·��
//
QString UploadFileDlg::GetLocalPath()
{
	return ui.edtLocalFile->text();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ��ȡ�ļ���С
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
// @private slot ȷ��
//
void UploadFileDlg::OnOk()
{
	if ( ui.edtLocalFile->text().isEmpty() )
	{
		MessageBoxA((HWND)this->winId(), "��ѡ��һ���ļ�", "��ʾ", MB_OK);
		return;
	}
	accept();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ���
//
void UploadFileDlg::OnBtnBrowseClicked()
{
	QString fileName = QFileDialog::getOpenFileName();

	if ( !fileName.isEmpty() )
	{
		ui.edtLocalFile->setText(fileName.replace('/', '\\'));
	}
}

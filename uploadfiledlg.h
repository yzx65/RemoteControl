/*!
	Description : �ϴ��ļ�
	Author		: Ruining Song
	Date		: 2013.11.22
	Remark		:
*/

#ifndef UPLOADFILEDLG_H
#define UPLOADFILEDLG_H

#include <QDialog>
#include "ui_uploadfiledlg.h"

class UploadFileDlg : public QDialog
{
	Q_OBJECT

public:

	// ���캯��
	UploadFileDlg(QWidget *parent, QString remotePath);

	// ��������
	~UploadFileDlg();

	// ��ȡ�����ļ�·��
	QString GetLocalPath();

	// ��ȡ�ļ���С
	unsigned int GetFileSize();

private slots:

	// ȷ��
	void OnOk();

	// ���
	void OnBtnBrowseClicked();

private:
	Ui::UploadFileDlg ui;
};

#endif // UPLOADFILEDLG_H

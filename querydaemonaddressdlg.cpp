#include "querydaemonaddressdlg.h"
#include "maindlg.h"

#include "include/T5.h"
#include "Utility.h"

QueryDaemonAddressDlg::QueryDaemonAddressDlg(QWidget *parent, Target* tar)
	: QDialog(parent)
	, m_tar(tar)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.btnQuery, SIGNAL(clicked()), this, SLOT(OnBtnQueryClicked()));

	ui.edtTargetId->setText(QString("%1").arg(tar->dwTargetID));

	InitCustomText(this);
}

QueryDaemonAddressDlg::~QueryDaemonAddressDlg()
{

}

void QueryDaemonAddressDlg::OnQueryDaemonAddressFinished( MSG* msg )
{
	Target* tar = (Target*)(msg->wParam);
	PDAEMONADDR lpDaemonAddr = (PDAEMONADDR)(msg->lParam);

	if ( m_tar->dwTargetID != tar->dwTargetID )
		return;

	ui.cmbIP->setCurrentIndex(lpDaemonAddr->dwAddrType);

	if (lpDaemonAddr->dwAddrType == 0)
	{
		struct in_addr in;
		in.S_un.S_addr =lpDaemonAddr->dwIp;
		ui.edtIP->setText(inet_ntoa(in));
	}
	else
	{
		ui.edtIP->setText(lpDaemonAddr->szDomainName);
	}

	ui.edtPort->setText(QString("%1").arg(lpDaemonAddr->dwPort));
}

void QueryDaemonAddressDlg::OnQueryDaemonAddressFinished2( MSG* msg )
{
	Target* tar = (Target*)(msg->wParam);
	PDAEMONADDR lpDaemonAddr = (PDAEMONADDR)(msg->lParam);

	if ( m_tar->dwTargetID != tar->dwTargetID )
		return;

	ui.cmbIP2->setCurrentIndex(lpDaemonAddr->dwAddrType);

	if (lpDaemonAddr->dwAddrType == 0)
	{
		struct in_addr in;
		in.S_un.S_addr =lpDaemonAddr->dwIp;
		ui.edtIP2->setText(inet_ntoa(in));
	}
	else
	{
		ui.edtIP2->setText(lpDaemonAddr->szDomainName);
	}

	ui.edtPort2->setText(QString("%1").arg(lpDaemonAddr->dwPort));
}

void QueryDaemonAddressDlg::OnBtnQueryClicked()
{
	FrmMain->ctrConn->Send_QDA(m_tar->dwTargetID);
}
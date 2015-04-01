#include "recorddlg.h"

RecordDlg::RecordDlg(QWidget *parent, Target* tar)
	: QFrame(parent), m_tar(tar)
{
	ui.setupUi(this);
}

RecordDlg::~RecordDlg()
{

}

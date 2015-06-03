#ifndef MAPINFODLG_H
#define MAPINFODLG_H

#include <QWidget>
#include "ui_mapinfodlg.h"

class Target;
class QAxWidget;
class MapInfoDlg : public QWidget
{
	Q_OBJECT

public:
	MapInfoDlg(QWidget *parent, Target* tar);
	~MapInfoDlg();

public:
	void GetNewLocation(MSG* msg);

private:
	void InitConnection();
	void InitWidgetAppearance();
	void InitMapInfo();

	void SetLocation(std::wstring x, std::wstring y);

private slots:

	void onTbLocationHistoryItemClicked(QTableWidgetItem* item);
	void onBtnGetLocationClicked();

private:
	Ui::MapInfoDlg ui;
	Target* m_tar;

	QAxWidget* m_webBrowser;
};

#endif // MAPINFODLG_H

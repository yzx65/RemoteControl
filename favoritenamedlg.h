#ifndef FAVORITENAMEDLG_H
#define FAVORITENAMEDLG_H

#include <QDialog>
#include "ui_favoritenamedlg.h"

#include <string>

class FavoriteNameDlg : public QDialog
{
	Q_OBJECT

public:
	FavoriteNameDlg(const std::wstring& path);
	~FavoriteNameDlg();

	std::wstring GetFavoriteName();

private slots:
	void OnOK();

private:
	Ui::FavoriteNameDlg ui;
};

#endif // FAVORITENAMEDLG_H

#ifndef SKIN_H
#define SKIN_H

#include <QtGui>
#include "Utility.h"

inline QString GetStylesheetFromFile(std::wstring controlName)
{
	std::wstring setting = GetExePath() + L"\\setting.ini";
	std::wstring skinName = ReadStringPolicyFromLocal(L"Skin", L"Name", setting.c_str());
	QString filePath = QString::fromStdWString(GetExePath() + L"\\Config\\" + skinName + L"\\" + controlName + L".txt");
	QFile file(filePath);

	file.open(QIODevice::ReadOnly | QIODevice::Text);

	QString style = file.readAll();
	file.close();

	return style;
}

inline void WriteStylesheetToFile(std::wstring style, std::wstring control, QString content)
{
	QFile file(QString::fromStdWString(GetExePath() + L"\\Config\\" + style + L"\\" + control + L".txt"));
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream stream(&file);
	stream << content;
	file.close();
}


#endif // SKIN_H
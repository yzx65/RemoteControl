#ifndef PICCONTAINER_H
#define PICCONTAINER_H

#include <QWidget>

class PicContainer : public QWidget
{
	Q_OBJECT
public:
	PicContainer(QWidget* parent = 0);
	~PicContainer();

	void SetPath(QString path);

protected:
	void paintEvent(QPaintEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);

private:
	QPixmap* m_pic;
	QString m_picPath;
};

#endif // PICCONTAINER_H
#include "PicContainer.h"

#include <QPainter>
#include <QRect>

#include <Windows.h>
#include <shellapi.h>

PicContainer::PicContainer(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_pic = new QPixmap;
}

PicContainer::~PicContainer()
{
	delete m_pic;
}

void PicContainer::SetPath(QString path) 
{ 
	m_picPath = path; 
	bool ret = m_pic->load(m_picPath);

	if ( !ret )
		ret = m_pic->load(m_picPath, "jpg");

	if ( !ret )
		ret = m_pic->load(m_picPath, "png");

	update();
}

void PicContainer::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	QBrush bg(QColor(170, 170, 170));

	painter.fillRect(this->rect(), bg);

	if ( m_picPath != "" )
	{
		int border = 20;
		QRect targetRect(border, border, this->width()-2*border, this->height()-2*border);

		double rateW = double(m_pic->width()) / double(targetRect.width());
		double rateH = double(m_pic->height()) / double(targetRect.height());

		QRect realRect;

		if ( rateW > rateH )
		{
			// rateW is right.
			int realH = int(double(m_pic->height()) / rateW);
			realRect.setX(targetRect.x());
			realRect.setY((targetRect.height() - realH)/2 + targetRect.y());
			realRect.setWidth(targetRect.width());
			realRect.setHeight(realH);
		}
		else
		{
			int realW = int(double(m_pic->width()) / rateH);
			realRect.setX((targetRect.width() - realW)/2 + targetRect.x());
			realRect.setY(targetRect.y());
			realRect.setWidth(realW);
			realRect.setHeight(targetRect.height());
		}

		painter.drawPixmap(realRect, *m_pic, m_pic->rect());
	}
}

void PicContainer::mouseDoubleClickEvent(QMouseEvent *e)
{
	ShellExecute(NULL, L"open", m_picPath.toStdWString().c_str(), NULL, NULL, SW_SHOW);
}
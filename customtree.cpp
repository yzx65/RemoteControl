#include "customtree.h"
#include <QMouseEvent>

CustomTree::CustomTree(QWidget *parent)
	: QTreeWidget(parent)
{

}

CustomTree::~CustomTree()
{

}

void CustomTree::mouseReleaseEvent( QMouseEvent *event )
{
	if ( event->button() == Qt::LeftButton )
		QTreeWidget::mouseReleaseEvent(event);
}

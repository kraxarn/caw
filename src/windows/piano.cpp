#include "windows/piano.hpp"

#include <QGraphicsScene>

Piano::Piano(QWidget *parent)
	: QGraphicsView(parent)
{
	setScene(new QGraphicsScene(this));
}

void Piano::showEvent(QShowEvent *event)
{
	QGraphicsView::showEvent(event);
}

void Piano::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
}

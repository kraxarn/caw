#include "window/oscilloscope.hpp"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QShowEvent>
#include <QWidget>

Oscilloscope::Oscilloscope(QWidget *parent)
	: QGraphicsView(parent),
	color(QApplication::palette().text().color())
{
	setScene(new QGraphicsScene(this));
}

void Oscilloscope::showEvent(QShowEvent *event)
{
	QGraphicsView::showEvent(event);

	const auto x = qFloor(width() / 2.0) - 1;
	scene()->addLine(-x, 0, x, 0, color);
}

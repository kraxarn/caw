#include "oscilloscope.hpp"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QShowEvent>
#include <QWidget>
#include <QWindow>

Oscilloscope::Oscilloscope(QWidget *parent)
	: QGraphicsView(parent),
	color(QApplication::palette().text().color()),
	text(nullptr)
{
	setScene(new QGraphicsScene(this));

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Oscilloscope::showEvent(QShowEvent *event)
{
	QGraphicsView::showEvent(event);

	const auto x = qFloor(width() / 2.0);
	scene()->addLine(-x, 0, x, 0, color);
}

void Oscilloscope::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	scene()->setSceneRect({{0, 0}, event->size()});
}

void Oscilloscope::setText(const QString &text)
{
	if (this->text == nullptr)
	{
		this->text = scene()->addText(text);
		return;
	}

	this->text->setPlainText(text);
}

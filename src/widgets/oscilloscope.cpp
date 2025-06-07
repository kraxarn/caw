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
	text(nullptr),
	line(nullptr)
{
	setScene(new QGraphicsScene(this));

	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Oscilloscope::showEvent(QShowEvent *event)
{
	QGraphicsView::showEvent(event);

	const auto y = qFloor(height() / 2.0);
	line = scene()->addLine(0, y, width(), y, color);
}

void Oscilloscope::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	scene()->setSceneRect({{0, 0}, event->size()});

	if (line != nullptr)
	{
		const auto y = qFloor(height() / 2.0);
		line->setLine(0, y, width(), y);
	}
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

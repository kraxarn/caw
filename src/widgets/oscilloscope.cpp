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
	line = scene()->addLine(defaultLine(), color);
}

void Oscilloscope::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	scene()->setSceneRect({{0, 0}, event->size()});

	if (line != nullptr)
	{
		line->setLine(defaultLine());
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

auto Oscilloscope::defaultLine() const -> QLineF
{
	const auto y = height() / 2.0;
	return {0, y, static_cast<qreal>(width()), y};
}

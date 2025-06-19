#include "windows/piano.hpp"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QResizeEvent>

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
	scene()->setSceneRect({{0, 0}, event->size()});
}

auto Piano::sizeHint() const -> QSize
{
	constexpr int height = 110;
	return {0, height};
}

void Piano::addOctave()
{
	scene()->addRect(
		{
			0,
			0,
			whiteKeyWidth,
			scene()->height() - 1,
		},
		QPen(Qt::white)
	);

	scene()->addRect(
		{
			0,
			0,
			blackKeyWidth,
			(scene()->height() * blackKeySize) - 1,
		},
		QPen(Qt::black)
	);
}

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

	for (auto i = 0; i < octaveCount; i++)
	{
		addOctave(i);
	}
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

void Piano::addOctave(const int octave) const
{
	const int offset = octave * (whiteKeyWidth * octaveWhiteKeyCount);

	for (auto i = 0; i < octaveWhiteKeyCount; i++)
	{
		const QRectF rect(
			offset + (i * whiteKeyWidth),
			0,
			whiteKeyWidth,
			scene()->height() - 1
		);
		scene()->addRect(rect, QPen(Qt::black), QBrush(Qt::white));
	}

	for (auto i = 0; i < octaveBlackKeyCount; i++)
	{
		const QRectF rect(
			offset + ((whiteKeyWidth * (i + 1 + (i > 1 ? 1 : 0))) - (blackKeyWidth / 2)),
			0,
			blackKeyWidth,
			(scene()->height() * blackKeySize) - 1
		);
		scene()->addRect(rect, QPen(Qt::black), QBrush(Qt::black));
	}
}

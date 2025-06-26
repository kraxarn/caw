#include "windows/piano.hpp"
#include "pianokey.hpp"

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

	for (quint8 i = 0; i < octaveCount; i++)
	{
		addOctave(i);
	}
}

void Piano::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	scene()->setSceneRect({{0, 0}, event->size()});
}

void Piano::mousePressEvent(QMouseEvent *event)
{
	QGraphicsView::mousePressEvent(event);

	const auto item = itemAt(event->pos());
	qDebug() << PianoKey::toString(item->data(0).value<quint8>());
}

void Piano::mouseReleaseEvent(QMouseEvent *event)
{
	QGraphicsView::mouseReleaseEvent(event);
}

auto Piano::sizeHint() const -> QSize
{
	constexpr int height = 110;
	return {0, height};
}

void Piano::addOctave(const quint8 octave) const
{
	const int offset = octave * (whiteKeyWidth * octaveWhiteKeyCount);

	for (quint8 i = 0; i < octaveWhiteKeyCount; i++)
	{
		const QRectF rect(
			offset + (i * whiteKeyWidth),
			0,
			whiteKeyWidth,
			scene()->height() - 1
		);

		auto *item = scene()->addRect(rect, QPen(Qt::black), QBrush(Qt::white));
		item->setData(0, QVariant::fromValue<quint8>((octave * 12) + i));
	}

	for (quint8 i = 0; i < octaveBlackKeyCount; i++)
	{
		const QRectF rect(
			offset + ((whiteKeyWidth * (i + 1 + (i > 1 ? 1 : 0))) - (blackKeyWidth / 2)),
			0,
			blackKeyWidth,
			(scene()->height() * blackKeySize) - 1
		);

		auto *item = scene()->addRect(rect, QPen(Qt::black), QBrush(Qt::black));
		item->setData(0, QVariant::fromValue<quint8>((octave * 12) + i));
	}
}

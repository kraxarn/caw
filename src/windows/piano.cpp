#include "windows/piano.hpp"
#include "pianokey.hpp"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QApplication>

Piano::Piano(QWidget *parent)
	: QGraphicsView(parent)
{
	setScene(new QGraphicsScene(this));
}

void Piano::showEvent(QShowEvent *event)
{
	QGraphicsView::showEvent(event);

	const auto baseColor = palette().button().color();
	keyBorderColor = baseColor.darker();
	whiteKeyColor = baseColor.lighter(whiteKeyColorFactor);
	blackKeyColor = baseColor.darker(blackKeyColorFactor);

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

	const auto *item = itemAt(event->pos());
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
	constexpr std::array whiteKeys{
		Note::C, Note::D, Note::E, Note::F, Note::G, Note::A, Note::B,
	};

	constexpr std::array blackKeys{
		Note::CSharp, Note::DSharp, Note::FSharp, Note::GSharp, Note::ASharp,
	};

	const float offset = static_cast<float>(octave) * (whiteKeyWidth * whiteKeys.size());
	constexpr int octaveKeyCount = whiteKeys.size() + blackKeys.size();

	for (size_t i = 0; i < whiteKeys.size(); i++)
	{
		const QRectF rect(
			offset + (static_cast<float>(i) * whiteKeyWidth),
			0,
			whiteKeyWidth,
			scene()->height() - 1
		);

		auto *item = scene()->addRect(rect, keyBorderColor, whiteKeyColor);
		const auto key = static_cast<quint8>(whiteKeys.at(i));
		item->setData(0, QVariant::fromValue<quint8>((octave * octaveKeyCount) + key));
	}

	for (size_t i = 0; i < blackKeys.size(); i++)
	{
		const QRectF rect(
			offset + ((whiteKeyWidth * (static_cast<float>(i) + 1.F + (i > 1 ? 1.F : 0.F)))
				- (blackKeyWidth / 2.F)),
			0,
			blackKeyWidth,
			(scene()->height() * blackKeySize) - 1
		);

		auto *item = scene()->addRect(rect, keyBorderColor, blackKeyColor);
		const auto key = static_cast<quint8>(blackKeys.at(i));
		item->setData(0, QVariant::fromValue<quint8>((octave * octaveKeyCount) + key));
	}
}

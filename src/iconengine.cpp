#include "iconengine.hpp"

#include <QPainter>
#include <QSvgRenderer>
#include <QWidget>

IconEngine::IconEngine(const QString &filename, const QColor &color)
	: filename(filename),
	color(color)
{
}

void IconEngine::paint(QPainter *painter, const QRect &rect,
	[[maybe_unused]] QIcon::Mode mode, [[maybe_unused]] QIcon::State state)
{
	QSvgRenderer svg(filename);
	if (!svg.isValid())
	{
		return;
	}

	// How to draw lines/outlines
	painter->setPen(color);
	// How to draw fills
	painter->setBrush(color);

	svg.render(painter, {rect});
}

auto IconEngine::clone() const -> QIconEngine *
{
	return new IconEngine(filename, color);
}

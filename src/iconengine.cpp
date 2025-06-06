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

auto IconEngine::pixmap(const QSize &size, const QIcon::Mode mode,
	const QIcon::State state) -> QPixmap
{
	QImage image(size, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	auto pixmap = QPixmap::fromImage(image, Qt::NoFormatConversion);
	QPainter painter(&pixmap);
	const QRect rect({0, 0}, size);

	paint(&painter, rect, mode, state);
	return pixmap;
}

auto IconEngine::clone() const -> QIconEngine *
{
	return new IconEngine(filename, color);
}

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

	svg.render(painter, {rect});
}

auto IconEngine::pixmap(const QSize &size, const QIcon::Mode mode,
	const QIcon::State state) -> QPixmap
{
	QImage image(size, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	auto pixmap = QPixmap::fromImage(image, Qt::NoFormatConversion);
	const QRect rect({0, 0}, size);

	QPainter painter(&pixmap);
	paint(&painter, rect, mode, state);

	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	painter.fillRect(rect, color);

	return pixmap;
}

auto IconEngine::clone() const -> QIconEngine *
{
	return new IconEngine(filename, color);
}

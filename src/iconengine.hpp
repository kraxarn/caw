#pragma once

#include <QIconEngine>

class IconEngine final: public QIconEngine
{
public:
	IconEngine(const QString &filename, const QColor &color);

	void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) override;

	[[nodiscard]]
	auto pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) -> QPixmap override;

	[[nodiscard]]
	auto clone() const -> QIconEngine * override;

private:
	const QString filename;
	const QColor color;
};

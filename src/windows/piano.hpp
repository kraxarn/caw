#pragma once

#include <QGraphicsView>

class Piano final: public QGraphicsView
{
	Q_OBJECT

public:
	explicit Piano(QWidget *parent);

	[[nodiscard]]
	auto sizeHint() const -> QSize override;

protected:
	void showEvent(QShowEvent *event) override;

	void resizeEvent(QResizeEvent *event) override;

private:
	static constexpr qreal blackKeySize = 2.0 / 3.0;

	static constexpr int whiteKeyWidth = 24;
	static constexpr int blackKeyWidth = 16;

	void addOctave();
};

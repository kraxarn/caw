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

	void mousePressEvent(QMouseEvent *event) override;

	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	static constexpr qreal blackKeySize = 2.0 / 3.0;

	static constexpr auto whiteKeyWidth = 24.F;
	static constexpr auto blackKeyWidth = 16.F;

	static constexpr quint8 octaveCount = 7;

	static constexpr auto whiteKeyColorFactor = 150 * 3;
	static constexpr auto blackKeyColorFactor = 200 * 3;

	void addOctave(quint8 octave) const;

	QPen keyBorder;
	QBrush whiteKeyColor;
	QBrush blackKeyColor;
};

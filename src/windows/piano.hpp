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

	static constexpr auto whiteKeyWidth = 24;
	static constexpr auto blackKeyWidth = 16;

	static constexpr auto octaveWhiteKeyCount = 7;
	static constexpr auto octaveBlackKeyCount = 5;
	static constexpr auto octaveCount = 7;

	void addOctave(int octave) const;
};

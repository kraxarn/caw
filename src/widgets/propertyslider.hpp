#pragma once

#include <QLabel>
#include <QSlider>
#include <QWidget>

class PropertySlider final: public QWidget
{
	Q_OBJECT

public:
	explicit PropertySlider(QWidget *parent);

	[[nodiscard]]
	auto slider() const -> QSlider *;

	[[nodiscard]]
	auto value() const -> QWidget *;

private:
	QSlider *mSlider;
	QLabel *mLabel;

	void onValueChanged(int value) const;
};

#pragma once

#include <QLineEdit>
#include <QSlider>
#include <QWidget>

class ValueSlider final: public QWidget
{
	Q_OBJECT

public:
	explicit ValueSlider(QWidget *parent);

	[[nodiscard]]
	auto slider() const -> QSlider *;

	[[nodiscard]]
	auto value() const -> QWidget *;

private:
	QSlider *mSlider;
	QLineEdit *mLineEdit;
};

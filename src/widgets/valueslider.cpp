#include "widgets/valueslider.hpp"

ValueSlider::ValueSlider(QWidget *parent)
	: QWidget(parent),
	mSlider(new QSlider(Qt::Horizontal, this)),
	mLineEdit(new QLineEdit(this))
{
	mLineEdit->setFixedWidth(50);
}

auto ValueSlider::slider() const -> QSlider *
{
	return mSlider;
}

auto ValueSlider::value() const -> QWidget *
{
	return mLineEdit;
}

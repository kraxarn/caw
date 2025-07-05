#include "widgets/valueslider.hpp"

ValueSlider::ValueSlider(QWidget *parent)
	: QWidget(parent),
	mSlider(new QSlider(Qt::Horizontal, this)),
	mLabel(new QLabel(QStringLiteral("0"), this))
{
}

auto ValueSlider::slider() const -> QSlider *
{
	return mSlider;
}

auto ValueSlider::value() const -> QWidget *
{
	return mLabel;
}

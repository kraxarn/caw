#include "widgets/valueslider.hpp"

#include <QLabel>
#include <QSlider>
#include <QString>
#include <QWidget>

ValueSlider::ValueSlider(QWidget *parent)
	: QWidget(parent),
	mSlider(new QSlider(Qt::Horizontal, this)),
	mLabel(new QLabel(QStringLiteral("0"), this))
{
	connect(mSlider, &QSlider::valueChanged,
		this, &ValueSlider::onValueChanged);
}

auto ValueSlider::slider() const -> QSlider *
{
	return mSlider;
}

auto ValueSlider::value() const -> QWidget *
{
	return mLabel;
}

void ValueSlider::onValueChanged(const int value) const
{
	mLabel->setText(QString::number(value));
}

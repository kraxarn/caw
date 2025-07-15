#include "widgets/propertyslider.hpp"
#include "font.hpp"

#include <QLabel>
#include <QSlider>
#include <QString>
#include <QWidget>

PropertySlider::PropertySlider(QWidget *parent)
	: QWidget(parent),
	mSlider(new QSlider(Qt::Horizontal, this)),
	mLabel(new QLabel(QStringLiteral("0"), this))
{
	mLabel->setMinimumWidth(Font::numberWidth() * 7);

	connect(mSlider, &QSlider::valueChanged,
		this, &PropertySlider::onValueChanged);
}

auto PropertySlider::slider() const -> QSlider *
{
	return mSlider;
}

auto PropertySlider::value() const -> QWidget *
{
	return mLabel;
}

void PropertySlider::setRange(const int min, const int max) const
{
	mSlider->setRange(min, max);
}

void PropertySlider::onValueChanged(const int value) const
{
	mLabel->setText(QString::number(value));
}

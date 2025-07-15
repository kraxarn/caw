#include "widgets/propertyslider.hpp"
#include "font.hpp"

#include <QLabel>
#include <QSlider>
#include <QString>
#include <QWidget>

PropertySlider::PropertySlider(QWidget *parent)
	: QWidget(parent),
	mSlider(new QSlider(Qt::Horizontal, this)),
	mLabel(new QLabel(QStringLiteral("0"), this)),
	mMin(0),
	mMax(255),
	mStep(1)
{
	mLabel->setMinimumWidth(Font::numberWidth() * 7);
	mSlider->setRange(mMin, mMax);

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

void PropertySlider::setRange(const int min, const int max)
{
	// This could be quite confusing, maybe reconsider
	if (mStep == 1)
	{
		if (min % 5 == 0 && max % 5 == 0)
		{
			mStep = 5;
		}
		else if (max >= 32 && min % 2 == 0 && max % 2 == 0)
		{
			mStep = 2;
		}
	}

	mMin = min / mStep;
	mMax = max / mStep;

	mSlider->setRange(mMin, mMax);
}

void PropertySlider::setStep(const int step)
{
	mStep = step;
	setRange(mMin, mMax);
}

void PropertySlider::onValueChanged(const int value) const
{
	mLabel->setText(QString::number(value * mStep));
}

#include "windows/playback.hpp"
#include "widgets/oscilloscope.hpp"
#include "widgets/playcontrols.hpp"

#include <QVBoxLayout>

Playback::Playback(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QVBoxLayout(this);
	layout->setSpacing(0);

	auto *oscilloscope = new Oscilloscope(this);
	layout->addWidget(oscilloscope);

	auto *playControls = new PlayControls(this);
	layout->addWidget(playControls);
}

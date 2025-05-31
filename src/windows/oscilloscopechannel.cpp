#include "windows/oscilloscopechannel.hpp"
#include "widgets/oscilloscope.hpp"

#include <QGridLayout>

OscilloscopeChannel::OscilloscopeChannel(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QGridLayout(this);

	for (qsizetype i = 0; i < channelCount; i++)
	{
		auto *widget = new Oscilloscope(this);
		layout->addWidget(widget, i / 2, i % 2);
	}
}

#include "windows/oscilloscopechannel.hpp"
#include "widgets/oscilloscope.hpp"

#include <QGridLayout>

OscilloscopeChannel::OscilloscopeChannel(const quint8 channelCount, QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QGridLayout(this);

	for (quint8 i = 0; i < channelCount; i++)
	{
		auto *widget = new Oscilloscope(this);
		layout->addWidget(widget, i / 2, i % 2);
	}
}

auto OscilloscopeChannel::sizeHint() const -> QSize
{
	constexpr auto width = 440;
	constexpr auto height = 0;

	return {width, height};
}

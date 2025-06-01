#pragma once

#include <QWidget>

class OscilloscopeChannel final: public QWidget
{
	Q_OBJECT

public:
	OscilloscopeChannel(quint8 channelCount, QWidget *parent);

	[[nodiscard]]
	auto sizeHint() const -> QSize override;
};

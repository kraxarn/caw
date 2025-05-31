#pragma once

#include <QWidget>

class OscilloscopeChannel final: public QWidget
{
	Q_OBJECT

public:
	explicit OscilloscopeChannel(QWidget *parent);

private:
	static constexpr qsizetype channelCount = 6; // TBD
};

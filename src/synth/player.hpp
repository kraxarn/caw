#pragma once

#include <QAudio>
#include <QAudioSink>
#include <QBuffer>
#include <QObject>
#include <QtTypes>

class Player final: QObject
{
	Q_OBJECT

public:
	Player();

	~Player() override;

	void play();

private:
	QBuffer buffer;
	QAudioSink *sink;

	void onSinkStateChanged(QAudio::State state);
};

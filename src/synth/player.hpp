#pragma once

#include <QAudio>
#include <QAudioSink>
#include <QBuffer>
#include <QObject>
#include <QtTypes>

#include "pl/pl_synth.h"

class Player final: public QObject
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

	auto render(pl_synth_song_t *song, QBuffer &samples, qint16 *tempSamples) -> int;
};

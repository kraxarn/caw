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
	QBuffer mBuffer;
	QAudioSink *mSink;

	void onSinkStateChanged(QAudio::State state);

	auto render(pl_synth_song_t *song, qint16 *samples, qint16 *tempSamples) -> int;
};

#include "synth/player.hpp"

#include <QAudioDevice>
#include <QAudioFormat>
#include <QAudioSink>
#include <QDebug>
#include <QElapsedTimer>
#include <QMediaDevices>
#include <QtTypes>
#include <QVarLengthArray>

#include <array>

#define PL_SYNTH_IMPLEMENTATION
#include "pl/pl_synth.h"

// TODO: Copied from example.c (load from file instead)
pl_synth_song_t song = {
	.row_len = 8481,
	.num_tracks = 4,
	.tracks = (pl_synth_track_t[]){
			{
				.synth = {7,0,0,0,121,1,7,0,0,0,91,3,0,100,1212,5513,100,0,6,19,3,121,6,21,0,1,1,29},
				.sequence_len = 12,
				.sequence = (uint8_t[]){1,2,1,2,1,2,0,0,1,2,1,2},
				.patterns = (pl_synth_pattern_t[]){
					{.notes = {138,145,138,150,138,145,138,150,138,145,138,150,138,145,138,150,136,145,138,148,136,145,138,148,136,145,138,148,136,145,138,148}},
					{.notes = {135,145,138,147,135,145,138,147,135,145,138,147,135,145,138,147,135,143,138,146,135,143,138,146,135,143,138,146,135,143,138,146}}
				}
			},
			{
				.synth = {7,0,0,0,192,1,6,0,9,0,192,1,25,137,1111,16157,124,1,982,89,6,25,6,77,0,1,3,69},
				.sequence_len = 12,
				.sequence = (uint8_t[]){0,0,1,2,1,2,3,3,3,3,3,3},
				.patterns = (pl_synth_pattern_t[]){
					{.notes = {138,138,0,138,140,0,141,0,0,0,0,0,0,0,0,0,136,136,0,136,140,0,141}},
					{.notes = {135,135,0,135,140,0,141,0,0,0,0,0,0,0,0,0,135,135,0,135,140,0,141,0,140,140}},
					{.notes = {145,0,0,0,145,143,145,150,0,148,0,146,0,143,0,0,0,145,0,0,0,145,143,145,139,0,139,0,0,142,142}}
				}
			},
			{
				.synth = {7,0,0,1,255,0,7,0,0,1,255,0,0,100,0,3636,174,2,500,254,0,27},
				.sequence_len = 12,
				.sequence = (uint8_t[]){1,1,1,1,0,0,1,1,1,1,1,1},
				.patterns = (pl_synth_pattern_t[]){
					{.notes = {135,135,0,135,139,0,135,135,135,0,135,139,0,135,135,135,0,135,139,0,135,135,135,0,135,139,0,135,135,135,0,135}}
				}
			},
			{
				.synth = {8,0,0,1,200,0,7,0,0,0,211,3,210,50,200,6800,153,4,11025,254,6,32,5,61,0,1,4,60},
				.sequence_len = 12,
				.sequence = (uint8_t[]){1,1,1,1,0,0,1,1,1,1,1,1},
				.patterns = (pl_synth_pattern_t[]){
					{.notes = {0,0,0,0,140,0,0,0,0,0,0,0,140,0,0,0,0,0,0,0,140,0,0,0,0,0,0,0,140}}
				}
			}
	}
};

Player::Player()
	: mSink(nullptr)
{
}

Player::~Player()
{
	if (mSink != nullptr)
	{
		mSink->deleteLater();
	}
}

void Player::play()
{
	QElapsedTimer timer;
	timer.start();

	std::array<float, PL_SYNTH_TAB_SIZE> synthTab;
	pl_synth_init(synthTab.data());

	const auto numSamples = static_cast<qsizetype>(pl_synth_song_len(&song));
	auto *tempSamples = new qint16[numSamples * 2];

	// [220 ms] pl_synth_song
	// [620 ms] int16_y* (samples) -> QBuffer
	// [225 ms] QBuffer -> QVarLengthArray

	QVarLengthArray<qint16> buffer(numSamples*2);
	render(&song, buffer.data(), tempSamples);
	mBuffer.setData(reinterpret_cast<const char *>(buffer.data()), buffer.size() * sizeof(qint16));
	delete[] tempSamples;

	qInfo() << "Song rendered in " << timer.elapsed() << "ms";

	QAudioFormat format;
	format.setSampleRate(PL_SYNTH_SAMPLERATE);
	format.setChannelCount(2);
	format.setSampleFormat(QAudioFormat::Int16);

	QAudioDevice device(QMediaDevices::defaultAudioOutput());
	qInfo() << "Using device:" << device.description();

	if (!device.isFormatSupported(format))
	{
		qWarning() << "Format not supported by device";
		return;
	}

	mBuffer.open(QIODevice::ReadOnly);
	mBuffer.seek(0);

	if (mSink != nullptr)
	{
		mSink->deleteLater();
	}

	mSink = new QAudioSink(format, this);
	connect(mSink, &QAudioSink::stateChanged,
		this, &Player::onSinkStateChanged);

	mSink->start(&mBuffer);
}

auto Player::render(pl_synth_song_t *song, qint16 *samples, qint16 *tempSamples) -> int
{
	// TODO: Too similar to pl_synth_song

	const int len = pl_synth_song_len(song);
	const int len2 = len * 2;

	for (auto t = 0; t < song->num_tracks; t++) {
		pl_synth_track_t *track = &song->tracks[t];
		memset(tempSamples, 0, sizeof(int16_t) * len2);

		for (auto si = 0; si < track->sequence_len; si++) {
			int writePos = song->row_len * si * 32;
			if (const int pi = track->sequence[si]; pi > 0) {
				const unsigned char *pattern = track->patterns[pi-1].notes;
				for (auto row = 0; row < 32; row++) {
					if (const int note = pattern[row]; note > 0) {
						pl_synth_gen(tempSamples, writePos, song->row_len, note, &track->synth);
					}
					writePos += song->row_len;
				}
			}
		}

		if (track->synth.fx_delay_amt) {
			const int delayShift = (track->synth.fx_delay_time * song->row_len) / 2;
			const float delayAmount = track->synth.fx_delay_amt / 255.0;
			pl_synth_apply_delay(tempSamples, len, delayShift, delayAmount);
		}

		for (auto i = 0; i < len2; i++) {
			samples[i] = clamp<qint16>(samples[i] + static_cast<int>(tempSamples[i]));
		}
	}

	return len;
}

void Player::onSinkStateChanged(const QAudio::State state)
{
	switch (state)
	{
		case QAudio::ActiveState:
			qInfo() << "Sink active";
			break;

		case QAudio::SuspendedState:
			qInfo() << "Sink suspended";
			break;

		case QAudio::StoppedState:
			qInfo() << "Sink stopped";
			break;

		case QAudio::IdleState:
			qInfo() << "Sink idle";
			break;
	}
}

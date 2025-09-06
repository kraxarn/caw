#pragma once

#include <QtTypes>

enum class Waveform: quint8
{
	SineWave     = 1,
	SquareWave   = 2,
	Sawtooth     = 3,
	TriangleWave = 4,
};

enum class Filter: quint8
{
	None  = 0,
	Low   = 1,
	High  = 2,
	Band  = 3,
	Notch = 4,
};

struct Oscillator
{
	quint8 octave;     // oct
	quint8 semitone;   // det
	quint8 detune;     // detune
	bool xenv;         // xenv
	quint8 volume;     // vol
	Waveform waveform; // waveform
};

struct Envelope
{
	quint32 attackTime;  // attack
	quint32 sustainTime; // sustain
	quint32 releaseTime; // release
	quint32 volume;      // master
};

struct Fx
{
	Filter filter;       // filter
	quint32 frequency;   // freq
	quint8 resonance;    // resonance
	quint8 delayTime;    // delay_time
	quint8 delayAmount;  // delay_amt
	quint8 panFrequency; // pan_freq
	quint8 panAmount;    // pan_amt
};

struct Lfo
{
	bool osc1;         // osc_freq
	bool fx;           // fx_freq
	quint8 frequency;  // freq
	quint8 amount;     // amt;
	Waveform waveform; // waveform
};

struct Instrument
{
	Oscillator osc1;
	Oscillator osc2;
	quint8 noiseFader;
	Envelope env;
	Fx fx;
	Lfo lfo;
};

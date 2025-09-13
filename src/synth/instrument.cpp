#include "synth/instrument.hpp"

#include <QString>
#include <QJsonArray>

auto Instrument::fromJson(const QJsonObject &json) -> Instrument
{
	const auto osc = json[QStringLiteral("osc")].toArray();
	const auto env = json[QStringLiteral("env")].toObject();
	const auto fx = json[QStringLiteral("fx")].toObject();
	const auto lfo = json[QStringLiteral("lfo")].toObject();

	return {
		.name = json[QStringLiteral("name")].toString(),
		.osc1 = {
			.octave = static_cast<quint8>(osc[0][QStringLiteral("oct")].toInt()),
			.semitone = static_cast<quint8>(osc[0][QStringLiteral("det")].toInt()),
			.detune = static_cast<quint8>(osc[0][QStringLiteral("detune")].toInt()),
			.xenv = osc[0][QStringLiteral("xenv")].toBool(),
			.volume = static_cast<quint8>(osc[0][QStringLiteral("vol")].toInt()),
			.waveform = static_cast<Waveform>(osc[0][QStringLiteral("waveform")].toInt()),
		},
		.osc2 = {
			.octave = static_cast<quint8>(osc[1][QStringLiteral("oct")].toInt()),
			.semitone = static_cast<quint8>(osc[1][QStringLiteral("det")].toInt()),
			.detune = static_cast<quint8>(osc[1][QStringLiteral("detune")].toInt()),
			.xenv = osc[1][QStringLiteral("xenv")].toBool(),
			.volume = static_cast<quint8>(osc[1][QStringLiteral("vol")].toInt()),
			.waveform = static_cast<Waveform>(osc[1][QStringLiteral("waveform")].toInt()),
		},
		.noiseFader = static_cast<quint8>(json[QStringLiteral("noise_fader")].toInt()),
		.env = {
			.attackTime = static_cast<quint32>(env[QStringLiteral("attack")].toInt()),
			.sustainTime = static_cast<quint32>(env[QStringLiteral("sustain")].toInt()),
			.releaseTime = static_cast<quint32>(env[QStringLiteral("release")].toInt()),
			.volume = static_cast<quint32>(env[QStringLiteral("master")].toInt()),
		},
		.fx = {
			.filter = static_cast<Filter>(fx[QStringLiteral("filter")].toInt()),
			.frequency = static_cast<quint32>(fx[QStringLiteral("freq")].toInt()),
			.resonance = static_cast<quint8>(fx[QStringLiteral("resonance")].toInt()),
			.delayTime = static_cast<quint8>(fx[QStringLiteral("delay_time")].toInt()),
			.delayAmount = static_cast<quint8>(fx[QStringLiteral("delay_amt")].toInt()),
			.panFrequency = static_cast<quint8>(fx[QStringLiteral("pan_freq")].toInt()),
			.panAmount = static_cast<quint8>(fx[QStringLiteral("pan_amt")].toInt()),
		},
		.lfo = {
			.osc1 = lfo[QStringLiteral("osc_freq")].toBool(),
			.fx = lfo[QStringLiteral("fx_freq")].toBool(),
			.frequency = static_cast<quint8>(lfo[QStringLiteral("freq")].toInt()),
			.amount = static_cast<quint8>(lfo[QStringLiteral("amt")].toInt()),
			.waveform = static_cast<Waveform>(lfo[QStringLiteral("waveform")].toInt()),
		},
	};
}

#include "synth/instrument.hpp"

#include <QString>

auto instrumentFromJson(const QJsonObject &json) -> Instrument
{
	return {
		.name = json[QStringLiteral("name")].toString(),
		.osc1 = {
			.octave = static_cast<quint8>(json[QStringLiteral("osc1_oct")].toInt()),
			.semitone = static_cast<quint8>(json[QStringLiteral("osc1_det")].toInt()),
			.detune = static_cast<quint8>(json[QStringLiteral("osc1_detune")].toInt()),
			.xenv = json[QStringLiteral("osc1_xenv")].toBool(),
			.volume = static_cast<quint8>(json[QStringLiteral("osc1_vol")].toInt()),
			.waveform = static_cast<Waveform>(json[QStringLiteral("osc1_waveform")].toInt()),
		},
		.osc2 = {
			.octave = static_cast<quint8>(json[QStringLiteral("osc2_oct")].toInt()),
			.semitone = static_cast<quint8>(json[QStringLiteral("osc2_det")].toInt()),
			.detune = static_cast<quint8>(json[QStringLiteral("osc2_detune")].toInt()),
			.xenv = json[QStringLiteral("osc2_xenv")].toBool(),
			.volume = static_cast<quint8>(json[QStringLiteral("osc2_vol")].toInt()),
			.waveform = static_cast<Waveform>(json[QStringLiteral("osc2_waveform")].toInt()),
		},
		.noiseFader = 0,
		.env = {},
		.fx = {},
		.lfo = {},
	};
}

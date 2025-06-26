#include "pianokey.hpp"

auto PianoKey::toString(const quint8 key) -> QString
{
	return QStringLiteral("%1%2")
		.arg(noteName(key % 12))
		.arg((key / 12) + 1);
}

auto PianoKey::noteName(const quint8 note) -> QString
{
	switch (note)
	{
		case 0:
			return QStringLiteral("C-");
		case 1:
			return QStringLiteral("C#");
		case 2:
			return QStringLiteral("D-");
		case 3:
			return QStringLiteral("D#");
		case 4:
			return QStringLiteral("E-");
		case 5:
			return QStringLiteral("F-");
		case 6:
			return QStringLiteral("F#");
		case 7:
			return QStringLiteral("G-");
		case 8:
			return QStringLiteral("G#");
		case 9:
			return QStringLiteral("A-");
		case 10:
			return QStringLiteral("A#");
		case 11:
			return QStringLiteral("B-");
		default:
			return QStringLiteral("--");
	}
}

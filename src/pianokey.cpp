#include "pianokey.hpp"

auto PianoKey::toString(const quint8 key) -> QString
{
	return QStringLiteral("%1%2")
		.arg(noteName(static_cast<Note>(key % keyCount)))
		.arg((key / keyCount) + 1);
}

auto PianoKey::noteName(const Note note) -> QString
{
	switch (note)
	{
		case Note::C:
			return QStringLiteral("C-");
		case Note::CSharp:
			return QStringLiteral("C#");
		case Note::D:
			return QStringLiteral("D-");
		case Note::DSharp:
			return QStringLiteral("D#");
		case Note::E:
			return QStringLiteral("E-");
		case Note::F:
			return QStringLiteral("F-");
		case Note::FSharp:
			return QStringLiteral("F#");
		case Note::G:
			return QStringLiteral("G-");
		case Note::GSharp:
			return QStringLiteral("G#");
		case Note::A:
			return QStringLiteral("A-");
		case Note::ASharp:
			return QStringLiteral("A#");
		case Note::B:
			return QStringLiteral("B-");
		default:
			return QStringLiteral("--");
	}
}

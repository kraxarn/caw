#include "pianokey.hpp"

auto PianoKey::toString() const -> QString
{
	return QStringLiteral("%1%2%3")
		.arg(QChar::fromLatin1(key + (key < 5 ? 'C' : 'A' - 5)))
		.arg(sharp ? QLatin1Char('#') : QLatin1Char('-'))
		.arg(octave + 1);
}

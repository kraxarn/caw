#pragma once

#include <QTypeInfo>

struct PianoKey
{
	quint8 octave;
	quint8 key;
	bool sharp;
};

Q_DECLARE_TYPEINFO(PianoKey, Q_PRIMITIVE_TYPE);

Q_DECLARE_METATYPE(PianoKey);

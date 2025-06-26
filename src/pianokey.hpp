#pragma once

#include <QMetaType>
#include <QTypeInfo>

struct PianoKey
{
	quint8 octave;
	quint8 key;
	bool sharp;

	auto toString() const -> QString;
};

Q_DECLARE_TYPEINFO(PianoKey, Q_PRIMITIVE_TYPE);

Q_DECLARE_METATYPE(PianoKey);

#pragma once

#include <QString>

class PianoKey
{
public:
	static auto toString(quint8 key) -> QString;

private:
	PianoKey() = default;

	static auto noteName(quint8 note) -> QString;
};

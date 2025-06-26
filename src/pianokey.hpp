#pragma once

#include <QString>

enum class Note: quint8
{
	C      = 0,
	CSharp = 1,
	D      = 2,
	DSharp = 3,
	E      = 4,
	F      = 5,
	FSharp = 6,
	G      = 7,
	GSharp = 8,
	A      = 9,
	ASharp = 10,
	B      = 11,
};

class PianoKey
{
public:
	static auto toString(quint8 key) -> QString;

	static constexpr quint8 keyCount = 12;

private:
	PianoKey() = default;

	static auto noteName(Note note) -> QString;
};

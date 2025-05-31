#pragma once

#include <QtTypes>

using Note = struct note_t
{
	quint8 key;
	quint8 velocity;
	quint8 effect;
	quint8 parameter;
};

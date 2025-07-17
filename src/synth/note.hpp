#pragma once

#include <QtTypes>

using Note = struct
{
	quint8 key; // note
	quint8 velocity;
	quint8 effect;
	quint8 parameter;
};

#pragma once

#include <QFont>

class Font
{
public:
	[[nodiscard]]
	static auto monospace() -> QFont;

	[[nodiscard]]
	static auto numberWidth() -> int;

private:
	Font() = default;
};

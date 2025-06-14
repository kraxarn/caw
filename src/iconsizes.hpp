#pragma once

#include <QSize>

class IconSizes
{
public:
	[[nodiscard]]
	static auto largeToolBar() -> QSize;

	[[nodiscard]]
	static auto smallToolBar() -> QSize;

private:
	static constexpr auto largeToolBarSize = 24;
	static constexpr auto smallToolBarSize = 16;

	IconSizes() = default;
};

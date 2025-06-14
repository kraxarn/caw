#include "iconsizes.hpp"

auto IconSizes::largeToolBar() -> QSize
{
	return {largeToolBarSize, largeToolBarSize};
}

auto IconSizes::smallToolBar() -> QSize
{
	return {smallToolBarSize, smallToolBarSize};
}

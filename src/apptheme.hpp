#pragma once

#include <QPalette>

/*
 * Oil 6 Palette
 * By GrafxKid
 * https://lospec.com/palette-list/oil-6
 */

class AppTheme final: public QPalette
{
	Q_GADGET

public:
	AppTheme();

private:
	static constexpr QRgb color1 = 0xfffbf5ef;
	static constexpr QRgb color2 = 0xfff2d3ab;
	static constexpr QRgb color3 = 0xffc69fa5;
	static constexpr QRgb color4 = 0xff8b6d9c;
	static constexpr QRgb color5 = 0xff494d7e;
	static constexpr QRgb color6 = 0xff272744;
};

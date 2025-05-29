#include "font.hpp"

#include <QFont>
#include <QFontDatabase>

auto Font::monospace() -> QFont
{
	return QFontDatabase::systemFont(QFontDatabase::FixedFont);
}

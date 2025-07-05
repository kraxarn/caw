#include "font.hpp"

#include <QChar>
#include <QFont>
#include <QFontDatabase>
#include <QFontMetrics>
#include <QtMinMax>

auto Font::monospace() -> QFont
{
	return QFontDatabase::systemFont(QFontDatabase::FixedFont);
}

auto Font::numberWidth() -> int
{
	const QFont font;
	const QFontMetrics metrics(font);
	auto max = 0;

	for (auto i = '0'; i <= '9'; i++)
	{
		const auto chr = QChar::fromLatin1(i);
		max = qMax(max, metrics.boundingRect(chr).width());
	}

	return max;
}

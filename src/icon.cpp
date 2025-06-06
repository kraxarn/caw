#include "icon.hpp"
#include "iconengine.hpp"

#include <QMetaEnum>
#include <QWidget>

auto Icon::get(const QWidget *parent, const ::IconName icon) -> QIcon
{
	const auto filename = QStringLiteral(":/icons/solid/%1.svg")
		.arg(getIconName(icon));

	const auto color = parent->palette().color(parent->foregroundRole());

	return QIcon(new IconEngine(filename, color));
}

auto Icon::getIconName(::IconName icon) -> QString
{
	const auto meta = QMetaEnum::fromType<::IconName>();
	const auto value = static_cast<quint64>(icon);
	const auto key = meta.valueToKey(value);

	auto str = QString::fromUtf8(key);

	for (auto i = str.length() - 1; i >= 0; i--)
	{
		if (!str.at(i).isUpper())
		{
			continue;
		}

		str.replace(i, 1, str.at(i).toLower());

		if (i > 0)
		{
			str.insert(i, QChar::fromLatin1('-'));
			i--;
		}
	}

	return str;
}

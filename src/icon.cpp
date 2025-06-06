#include "icon.hpp"

#include <QFont>
#include <QMetaEnum>
#include <QString>

auto Icon::get(const ::IconName icon) -> QIcon
{
	const auto name = QStringLiteral(":/icons/solid/%1")
		.arg(getIconName(icon));

	return QIcon(name);
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

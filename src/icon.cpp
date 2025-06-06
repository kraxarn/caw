#include "icon.hpp"

#include <QFont>
#include <QString>

auto Icon::font() -> QFont
{
	return {QStringLiteral("Font Awesome 6 Free")};
}

auto Icon::get(const IconName icon) -> QString
{
	const QChar icChar(static_cast<quint16>(icon));
	return {icChar};
}

void Icon::set(QAction *action, const IconName icon)
{
	action->setToolTip(action->text());
	action->setText(get(icon));
	action->setFont(font());
}

auto Icon::get(const Value icon) -> QIcon
{
	const auto name = QStringLiteral(":/icons/solid/%1")
		.arg(getIconName(icon));

	return QIcon(name);
}

auto Icon::getIconName(const Value icon) -> QString
{
	const auto meta = QMetaEnum::fromType<Value>();
	const auto key = meta.valueToKey(icon);

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

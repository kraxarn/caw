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

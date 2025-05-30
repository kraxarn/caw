#include "icon.hpp"

#include <QFont>

QString Icon::fontName = QStringLiteral("Font Awesome 6 Free");

auto Icon::get(const IconName icon) -> QString
{
	const QChar ch(static_cast<quint16>(icon));
	return {ch};
}

void Icon::set(QAction *action, const IconName icon)
{
	action->setToolTip(action->text());
	action->setText(get(icon));
	action->setFont(QFont(fontName));
}

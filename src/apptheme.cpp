#include "apptheme.hpp"

#include <QQuickStyle>
#include <QColor>

AppTheme::AppTheme(QObject *parent)
	: QObject(parent)
{
}

void AppTheme::setStyle()
{
	QQuickStyle::setStyle(QStringLiteral("Imagine"));
}

auto AppTheme::qmlAttachedProperties(QObject *object) -> AppTheme *
{
	return new AppTheme(object);
}

auto AppTheme::toString(const QColor &color) -> QString
{
	return QStringLiteral("#%1%2%3%4")
		.arg(color.alpha(), 2, 16, QChar::fromLatin1('0'))
		.arg(color.red(), 2, 16, QChar::fromLatin1('0'))
		.arg(color.green(), 2, 16, QChar::fromLatin1('0'))
		.arg(color.blue(), 2, 16, QChar::fromLatin1('0'));
}

auto AppTheme::windowText() const -> QString
{
	return toString({color1});
}

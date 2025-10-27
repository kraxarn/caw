#include "apptheme.hpp"

#include <QQuickStyle>

AppTheme::AppTheme()
{
	QQuickStyle::setStyle(QStringLiteral("Imagine"));

	setColor(WindowText, color1);
}

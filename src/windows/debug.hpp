#pragma once

#include <QWidget>

class Debug final: public QWidget
{
	Q_OBJECT

public:
	explicit Debug(QWidget *parent);

private:
	[[nodiscard]]
	auto iconsTab() -> QWidget *;

	[[nodiscard]]
	static auto iconName(QIcon::ThemeIcon themeIcon) -> QString;
};

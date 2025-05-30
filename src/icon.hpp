#pragma once

#include "iconname.hpp"

#include <QAction>

class Icon final
{
public:
	[[nodiscard]]
	static auto get(IconName icon) -> QString;

	static void set(QAction *action, IconName icon);

private:
	static QString fontName;

	Icon() = delete;
};

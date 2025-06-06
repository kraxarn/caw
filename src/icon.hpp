#pragma once

#include "iconname.hpp"

#include <QAction>

class Icon final
{
	Q_GADGET

public:
	[[nodiscard]]
	[[deprecated]]
	static auto get(IconName icon) -> QString;

	[[deprecated]]
	static void set(QAction *action, IconName icon);

private:
	Icon() = default;

	[[nodiscard]]
	static auto font() -> QFont;

public:
	enum Value : quint8
	{
		Play,
		ForwardStep,
		RotateRight,
		AnglesDown,
		Circle,
		Repeat,
		Plus,
		Minus,
		Clone,
		ChevronUp,
		ChevronDown,
		Link,
		LinkSlash,
		FolderOpen,
		FloppyDisk,
		Xmark,
	};

	Q_ENUM(Value)

	static auto get(Value icon) -> QIcon;

private:
	[[nodiscard]]
	static auto getIconName(Value icon) -> QString;
};

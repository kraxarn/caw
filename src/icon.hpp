#pragma once

#include <QAction>

class Icon final
{
	Q_GADGET

public:
	enum class IconName : quint8
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

	Q_ENUM(IconName)

	static auto get(const QWidget *parent, IconName icon) -> QIcon;

private:
	Icon() = default;

	[[nodiscard]]
	static auto getIconName(IconName icon) -> QString;
};

using IconName = Icon::IconName;

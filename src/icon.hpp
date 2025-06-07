#pragma once

#include <QAction>

class Icon final
{
	Q_GADGET

public:
	enum class IconName : quint8
	{
		AnglesDown,
		Bug,
		ChevronDown,
		ChevronUp,
		Circle,
		Clone,
		CompactDisc,
		FileCirclePlus,
		FloppyDisk,
		FolderOpen,
		ForwardStep,
		Gear,
		Link,
		LinkSlash,
		Minus,
		Play,
		Plus,
		Repeat,
		RotateRight,
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

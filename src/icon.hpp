#pragma once

#include <QAction>

class Icon final
{
	Q_GADGET

public:
	[[deprecated]]
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

	enum class Mdi : quint8
	{
		SineWave,
		SquareWave,
		SawtoothWave,
		TriangleWave,
	};

	Q_ENUM(IconName)
	Q_ENUM(Mdi)

	[[nodiscard]]
	[[deprecated]]
	static auto get(const QWidget *parent, IconName icon) -> QIcon;

	[[nodiscard]]
	static auto get(Mdi mdi, const QWidget *parent) -> QIcon;

private:
	Icon() = default;

	[[nodiscard]]
	[[deprecated]]
	static auto getIconName(IconName icon) -> QString;

	[[nodiscard]]
	static auto getIconName(Mdi mdi) -> QString;
};

using IconName = Icon::IconName;
using Mdi = Icon::Mdi;

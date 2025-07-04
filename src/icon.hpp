#pragma once

#include <QAction>

class Icon final
{
	Q_GADGET

public:
	enum class Mdi : quint8
	{
		Bug,
		ChevronDoubleDown,
		ChevronDown,
		ChevronUp,
		Cog,
		ContentDuplicate,
		ContentSave,
		Delete,
		Export,
		FilePlus,
		FolderOpen,
		Link,
		LinkOff,
		Minus,
		Play,
		Plus,
		Record,
		Repeat,
		SawtoothWave,
		SineWave,
		SquareWave,
		StepForward,
		TriangleWave,
	};

	Q_ENUM(Mdi)

	[[nodiscard]]
	static auto get(Mdi mdi, const QWidget *parent) -> QIcon;

private:
	Icon() = default;

	[[nodiscard]]
	static auto getIconName(Mdi mdi) -> QString;
};

using Mdi = Icon::Mdi;

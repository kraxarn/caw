#include "maintoolbar.hpp"
#include "icon.hpp"

MainToolBar::MainToolBar(QWidget *parent)
	: QToolBar(parent)
{
	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

	addAction(Icon::get(this, IconName::FileCirclePlus), QStringLiteral("New"));
	addAction(Icon::get(this, IconName::FolderOpen), QStringLiteral("Open"));
	addAction(Icon::get(this, IconName::FloppyDisk), QStringLiteral("Save"));
	addAction(Icon::get(this, IconName::CompactDisc), QStringLiteral("Export"));

	addSeparator();

	addAction(Icon::get(this, IconName::Gear), QStringLiteral("Settings"));
}

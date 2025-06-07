#include "maintoolbar.hpp"
#include "icon.hpp"

#include <QFileDialog>

MainToolBar::MainToolBar(QWidget *parent)
	: QToolBar(parent)
{
	setIconSize(iconSize() * 0.75);
	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

	addAction(Icon::get(this, IconName::FileCirclePlus), QStringLiteral("New"));

	const auto *open = addAction(Icon::get(this, IconName::FolderOpen), QStringLiteral("Open"));
	connect(open, &QAction::triggered, this, &MainToolBar::onOpenTriggered);

	addAction(Icon::get(this, IconName::FloppyDisk), QStringLiteral("Save"));
	addAction(Icon::get(this, IconName::CompactDisc), QStringLiteral("Export"));

	addSeparator();

	addAction(Icon::get(this, IconName::Bug), QStringLiteral("Debug"));
	addAction(Icon::get(this, IconName::Gear), QStringLiteral("Settings"));
}

void MainToolBar::onOpenTriggered([[maybe_unused]] bool checked)
{
	const auto objectName = QStringLiteral("OpenFileDialog");
	if (auto *child = findChild<QFileDialog *>(objectName); child != nullptr)
	{
		child->open();
		return;
	}

	auto *dialog = new QFileDialog(this);
	dialog->setObjectName(objectName);

	dialog->setWindowTitle(QStringLiteral("Open project"));
	dialog->setNameFilter(QStringLiteral("JSON project file (*.caw.json)"));

	dialog->open();
}

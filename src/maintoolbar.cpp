#include "maintoolbar.hpp"
#include "icon.hpp"
#include "iconsizes.hpp"

#include <QFileDialog>

MainToolBar::MainToolBar(QWidget *parent)
	: QToolBar(parent)
{
	setIconSize(IconSizes::largeToolBar());
	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

	addAction(Icon::get(Mdi::FilePlus, this), QStringLiteral("New"));

	const auto *open = addAction(Icon::get(Mdi::FolderOpen, this), QStringLiteral("Open"));
	connect(open, &QAction::triggered, this, &MainToolBar::onOpenTriggered);

	addAction(Icon::get(Mdi::ContentSave, this), QStringLiteral("Save"));
	addAction(Icon::get(Mdi::Export, this), QStringLiteral("Export"));

	addSeparator();

	addAction(Icon::get(Mdi::Bug, this), QStringLiteral("Debug"));
	addAction(Icon::get(Mdi::Cog, this), QStringLiteral("Settings"));
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

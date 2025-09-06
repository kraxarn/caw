#include "windows/instruments.hpp"
#include "icon.hpp"
#include "iconsizes.hpp"
#include "lists/instrumentlist.hpp"

#include <QToolBar>
#include <QVBoxLayout>

Instruments::Instruments(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QVBoxLayout(this);
	layout->setSpacing(0);

	layout->addWidget(toolBar());

	auto *list = new InstrumentList(this);
	layout->addWidget(list, 1);
}

QSize Instruments::sizeHint() const
{
	return {160, 180};
}

auto Instruments::toolBar() -> QToolBar *
{
	auto *toolbar = new QToolBar(this);
	toolbar->setIconSize(IconSizes::smallToolBar());

	toolbar->addAction(Icon::get(Mdi::Plus, this), QStringLiteral("Add"));
	toolbar->addAction(Icon::get(Mdi::ContentDuplicate, this), QStringLiteral("Duplicate"));
	toolbar->addAction(Icon::get(Mdi::FolderOpen, this), QStringLiteral("Open..."));
	toolbar->addAction(Icon::get(Mdi::ContentSave, this), QStringLiteral("Save"));
	toolbar->addAction(Icon::get(Mdi::ChevronUp, this),QStringLiteral("Move up"));
	toolbar->addAction(Icon::get(Mdi::ChevronDown, this), QStringLiteral("Move down"));
	toolbar->addAction(Icon::get(Mdi::Delete, this), QStringLiteral("Delete"));

	return toolbar;
}

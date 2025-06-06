#include "windows/instrument.hpp"
#include "icon.hpp"
#include "lists/instrumentlist.hpp"

#include <QToolBar>
#include <QVBoxLayout>

Instrument::Instrument(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QVBoxLayout(this);
	layout->setSpacing(0);

	layout->addWidget(toolBar());

	auto *list = new InstrumentList(this);
	layout->addWidget(list, 1);
}

QSize Instrument::sizeHint() const
{
	return {160, 180};
}

auto Instrument::toolBar() -> QToolBar *
{
	auto *toolbar = new QToolBar(this);
	toolbar->setIconSize(toolbar->iconSize() * 0.5);

	toolbar->addAction(Icon::get(this, IconName::Plus), QStringLiteral("Add"));
	toolbar->addAction(Icon::get(this, IconName::Clone), QStringLiteral("Duplicate"));
	toolbar->addAction(Icon::get(this, IconName::FolderOpen), QStringLiteral("Open..."));
	toolbar->addAction(Icon::get(this, IconName::FloppyDisk), QStringLiteral("Save"));
	toolbar->addAction(Icon::get(this, IconName::ChevronUp),QStringLiteral("Move up"));
	toolbar->addAction(Icon::get(this, IconName::ChevronDown), QStringLiteral("Move down"));
	toolbar->addAction(Icon::get(this, IconName::Xmark), QStringLiteral("Delete"));

	return toolbar;
}

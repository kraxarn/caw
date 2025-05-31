#include "windows/instrument.hpp"
#include "icon.hpp"
#include "iconname.hpp"
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

	auto *add = toolbar->addAction(QStringLiteral("Add"));
	Icon::set(add, IconName::Plus);

	auto *duplicate = toolbar->addAction(QStringLiteral("Duplicate"));
	Icon::set(duplicate, IconName::Clone);

	auto *open = toolbar->addAction(QStringLiteral("Open..."));
	Icon::set(open, IconName::FolderOpen);

	auto *save = toolbar->addAction(QStringLiteral("Save"));
	Icon::set(save, IconName::FloppyDisk);

	auto *moveUp = toolbar->addAction(QStringLiteral("Move up"));
	Icon::set(moveUp, IconName::ChevronUp);

	auto *moveDown = toolbar->addAction(QStringLiteral("Move down"));
	Icon::set(moveDown, IconName::ChevronDown);

	auto *remove = toolbar->addAction(QStringLiteral("Delete"));
	Icon::set(remove, IconName::XMark);

	return toolbar;
}

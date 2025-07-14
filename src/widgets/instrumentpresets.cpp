#include "widgets/instrumentpresets.hpp"
#include "icon.hpp"
#include "iconsizes.hpp"

#include <QComboBox>
#include <QHBoxLayout>
#include <QToolBar>

InstrumentPresets::InstrumentPresets(QWidget *parent)
	: QGroupBox(QStringLiteral("Preset"), parent),
	mPreset(new QComboBox(this))
{
	auto *layout = new QHBoxLayout(this);
	layout->addWidget(mPreset, 1);

	addDefaultPresets();

	auto *toolBar = new QToolBar(this);
	toolBar->setIconSize(IconSizes::smallToolBar());
	layout->addWidget(toolBar);

	toolBar->addAction(Icon::get(Mdi::FolderOpen, this), QStringLiteral("Load preset"));
	toolBar->addAction(Icon::get(Mdi::ContentSave, this), QStringLiteral("Save preset"));
}

void InstrumentPresets::addDefaultPresets() const
{
	mPreset->addItems({
		QStringLiteral("Default"),
		QStringLiteral("Softy"),
		QStringLiteral("Classic 8-bit"),
		QStringLiteral("Square"),
		QStringLiteral("Bell"),
		QStringLiteral("Base string"),
		QStringLiteral("Bass drum 1"),
		QStringLiteral("Bass drum 2"),
		QStringLiteral("Bass drum 3"),
		QStringLiteral("Snare 1"),
		QStringLiteral("Snare 2"),
		QStringLiteral("Hi-hat 1"),
		QStringLiteral("Hi-hat 2"),
		QStringLiteral("Smash"),
		QStringLiteral("Pipe hit"),
		QStringLiteral("Wind"),
	});
}

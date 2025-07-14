#include "widgets/instrumentpresets.hpp"
#include "icon.hpp"
#include "iconsizes.hpp"
#include "menus/loadpresetmenu.hpp"

#include <QComboBox>
#include <QHBoxLayout>
#include <QToolBar>
#include <QToolButton>

InstrumentPresets::InstrumentPresets(QWidget *parent)
	: QGroupBox(QStringLiteral("Preset"), parent),
	mPreset(new QComboBox(this)),
	mLoadPreset(new QAction(this)),
	mSavePreset(new QAction(this))
{
	auto *layout = new QHBoxLayout(this);
	layout->addWidget(mPreset, 1);

	addDefaultPresets();

	auto *toolBar = new QToolBar(this);
	toolBar->setIconSize(IconSizes::smallToolBar());
	layout->addWidget(toolBar);

	mLoadPreset->setText(QStringLiteral("Load preset"));
	mLoadPreset->setIcon(Icon::get(Mdi::FolderOpen, this));
	mLoadPreset->setMenu(new LoadPresetMenu(this));
	toolBar->addAction(mLoadPreset);

	auto *loadButton = qobject_cast<QToolButton *>(toolBar->widgetForAction(mLoadPreset));
	loadButton->setPopupMode(QToolButton::InstantPopup);

	mSavePreset->setText(QStringLiteral("Save preset"));
	mSavePreset->setIcon(Icon::get(Mdi::ContentSave, this));
	toolBar->addAction(mSavePreset);
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

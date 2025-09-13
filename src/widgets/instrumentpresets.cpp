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
	  mPreset(new QLineEdit(this)),
	  mLoadPreset(new QAction(this)),
	  mSavePreset(new QAction(this))
{
	auto *layout = new QHBoxLayout(this);

	mPreset->setText(QStringLiteral("Built-in/Default"));
	layout->addWidget(mPreset, 1);

	auto *toolBar = new QToolBar(this);
	toolBar->setIconSize(IconSizes::smallToolBar());
	layout->addWidget(toolBar);

	auto *presetMenu = new LoadPresetMenu(this);
	connect(presetMenu, &LoadPresetMenu::presetLoaded,
		this, &InstrumentPresets::onPresetLoaded);

	mLoadPreset->setText(QStringLiteral("Load preset"));
	mLoadPreset->setIcon(Icon::get(Mdi::FolderOpen, this));
	mLoadPreset->setMenu(presetMenu);
	toolBar->addAction(mLoadPreset);

	auto *loadButton = qobject_cast<QToolButton *>(toolBar->widgetForAction(mLoadPreset));
	loadButton->setPopupMode(QToolButton::InstantPopup);

	mSavePreset->setText(QStringLiteral("Save preset"));
	mSavePreset->setIcon(Icon::get(Mdi::ContentSave, this));
	toolBar->addAction(mSavePreset);
}

void InstrumentPresets::onPresetLoaded(const Instrument &instrument)
{
	mPreset->setText(QStringLiteral("Built-in/%1").arg(instrument.name));

	emit presetLoaded(instrument);
}

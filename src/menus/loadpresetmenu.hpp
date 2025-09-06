#pragma once

#include "synth/instrument.hpp"

#include <QMenu>

class LoadPresetMenu final: public QMenu
{
	Q_OBJECT

public:
	explicit LoadPresetMenu(QWidget *parent);

signals:
	void presetLoaded(const Instrument &instrument);

private:
	QMenu *mBuiltIn;

	void onBuiltInAboutToShow() const;

	void onActionTriggered(const QAction *action);
};

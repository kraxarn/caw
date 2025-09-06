#pragma once

#include "synth/instrument.hpp"

#include <QAction>
#include <QLineEdit>
#include <QGroupBox>

class InstrumentPresets final: public QGroupBox
{
	Q_OBJECT

public:
	explicit InstrumentPresets(QWidget *parent);

signals:
	void presetLoaded(const Instrument &instrument);

private:
	QLineEdit *mPreset;
	QAction *mLoadPreset;
	QAction *mSavePreset;

	void onPresetLoaded(const Instrument &instrument);
};

#pragma once

#include <QAction>
#include <QComboBox>
#include <QGroupBox>

class InstrumentPresets final: public QGroupBox
{
	Q_OBJECT

public:
	explicit InstrumentPresets(QWidget *parent);

private:
	QComboBox *mPreset;
	QAction *mLoadPreset;
	QAction *mSavePreset;

	void addDefaultPresets() const;
};

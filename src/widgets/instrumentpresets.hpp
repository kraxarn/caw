#pragma once

#include <QAction>
#include <QLineEdit>
#include <QGroupBox>

class InstrumentPresets final: public QGroupBox
{
	Q_OBJECT

public:
	explicit InstrumentPresets(QWidget *parent);

private:
	QLineEdit *mPreset;
	QAction *mLoadPreset;
	QAction *mSavePreset;
};

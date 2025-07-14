#pragma once

#include <QComboBox>
#include <QGroupBox>

class InstrumentPresets final: public QGroupBox
{
	Q_OBJECT

public:
	explicit InstrumentPresets(QWidget *parent);

private:
	QComboBox *mPreset;

	void addDefaultPresets() const;
};

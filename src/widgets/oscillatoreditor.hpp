#pragma once

#include "widgets/editorpanel.hpp"
#include "widgets/propertyslider.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QtTypes>
#include <QWidget>

class OscillatorEditor final: public EditorPanel
{
	Q_OBJECT

public:
	OscillatorEditor(quint8 index, QWidget *parent);

private:
	QComboBox *mEnvelope;
	QCheckBox *mXenv;
	PropertySlider *mVol;
	PropertySlider *mOct;
	PropertySlider *mSemi;
	PropertySlider *mDet;
};

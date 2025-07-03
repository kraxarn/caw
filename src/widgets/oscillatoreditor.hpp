#pragma once

#include "widgets/editorpanel.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
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
	QSlider *mVol;
	QSlider *mOct;
	QSlider *mSemi;
	QSlider *mDet;
};

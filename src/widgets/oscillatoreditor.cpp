#include "widgets/oscillatoreditor.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QtTypes>
#include <QVariant>
#include <QWidget>

OscillatorEditor::OscillatorEditor(const quint8 index, QWidget *parent)
	: EditorPanel(QStringLiteral("Oscillator %1").arg(index), parent)
{
	mEnvelope = addEnvelope();

	mXenv = addCheckBox(QStringLiteral("Modulates frequency"));

	mVol = addSlider(QStringLiteral("Volume"));
	mVol->setRange(0, 255);

	mOct = addSlider(QStringLiteral("Octave"));
	mOct->setRange(0, 16);

	mSemi = addSlider(QStringLiteral("Semitune"));
	mSemi->setRange(0, 11);

	mDet = addSlider(QStringLiteral("Detune"));
	mDet->setRange(0, 255);
}

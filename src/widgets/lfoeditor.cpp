#include "widgets/lfoeditor.hpp"

LfoEditor::LfoEditor(QWidget *parent)
	: EditorPanel(QStringLiteral("LFO"), parent)
{
	addEnvelope();

	addCheckBox(QStringLiteral("FX"));
	addCheckBox(QStringLiteral("Oscillator 1"));

	auto *amt = addSlider(QStringLiteral("AMT"));
	amt->setRange(0, 255);

	auto *freq = addSlider(QStringLiteral("FREQ"));
	freq->setRange(0, 16);
}

#include "widgets/lfoeditor.hpp"

LfoEditor::LfoEditor(QWidget *parent)
	: EditorPanel(QStringLiteral("LFO"), parent)
{
	addEnvelope();

	auto *amt = addSlider(QStringLiteral("AMT"));
	amt->setRange(0, 255);

	auto *freq = addSlider(QStringLiteral("FREQ"));
	freq->setRange(0, 16);
}

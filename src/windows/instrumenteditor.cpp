#include "windows/instrumenteditor.hpp"

#include <QFileDialog>

#include "widgets/oscilloscope.hpp"

#include <QGridLayout>
#include <QGroupBox>

InstrumentEditor::InstrumentEditor(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QGridLayout(this);

	auto *oscilloscope = new Oscilloscope(this);
	layout->addWidget(oscilloscope, 0, 0, 1, 2);

	auto preset = new QGroupBox(QStringLiteral("Preset"), this);
	layout->addWidget(preset, 1, 0, 1, 2);

	auto *osc1 = new QGroupBox(QStringLiteral("OSC 1"), this);
	layout->addWidget(osc1, 2, 0);

	auto *osc2 = new QGroupBox(QStringLiteral("OSC 2"), this);
	layout->addWidget(osc2, 2, 1);

	auto *envelope = new QGroupBox(QStringLiteral("ENVELOPE"), this);
	layout->addWidget(envelope, 3, 0);

	auto *lfo = new QGroupBox(QStringLiteral("LFO"), this);
	layout->addWidget(lfo, 3, 1);

	auto *fx = new QGroupBox(QStringLiteral("FX"), this);
	layout->addWidget(fx, 4, 0, 1, 2);
}

#include "windows/instrumenteditor.hpp"

#include <QFileDialog>

#include "widgets/oscilloscope.hpp"

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>

InstrumentEditor::InstrumentEditor(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QGridLayout(this);

	auto *oscilloscope = new Oscilloscope(this);
	layout->addWidget(oscilloscope, 0, 0, 1, 2);

	layout->addWidget(preset(), 1, 0, 1, 2);

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

auto InstrumentEditor::preset() -> QWidget *
{
	auto *group = new QGroupBox(QStringLiteral("Preset"), this);
	auto *layout = new QVBoxLayout(group);

	auto *presets = new QComboBox(this);
	layout->addWidget(presets);

	presets->addItems({
		QStringLiteral("Default"),
		QStringLiteral("Softy"),
		QStringLiteral("Classic 8-bit"),
		QStringLiteral("Square"),
		QStringLiteral("Bell"),
		QStringLiteral("Base string"),
		QStringLiteral("Bass drum 1"),
		QStringLiteral("Bass drum 2"),
		QStringLiteral("Bass drum 3"),
		QStringLiteral("Snare 1"),
		QStringLiteral("Snare 2"),
		QStringLiteral("Hi-hat 1"),
		QStringLiteral("Hi-hat 2"),
		QStringLiteral("Smash"),
		QStringLiteral("Pipe hit"),
		QStringLiteral("Wind"),
	});

	return group;
}

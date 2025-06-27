#include "windows/instrumenteditor.hpp"

#include <QFileDialog>

#include "widgets/oscilloscope.hpp"

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSlider>

InstrumentEditor::InstrumentEditor(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QGridLayout(this);

	auto *oscilloscope = new Oscilloscope(this);
	oscilloscope->setMaximumHeight(150);
	layout->addWidget(oscilloscope, 0, 0, 1, 2);

	layout->addWidget(preset(), 1, 0, 1, 2);

	layout->addWidget(osc1(), 2, 0);

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

auto InstrumentEditor::osc1() -> QWidget *
{
	auto *group = new QGroupBox(QStringLiteral("Oscillator 1"), this);
	auto *layout = new QGridLayout(group);

	auto *envLabel = new QLabel(QStringLiteral("Envelope"), this);
	layout->addWidget(envLabel, 0, 0);

	auto *envComboBox = new QComboBox(this);
	envComboBox->addItems({
		QStringLiteral("Square wave"),
		QStringLiteral("Sine wave"),
		QStringLiteral("Sawtooth"),
		QStringLiteral("Triangle wave"),
	});
	layout->addWidget(envComboBox, 0, 1);

	auto *volLabel = new QLabel(QStringLiteral("Volume"), this);
	layout->addWidget(volLabel, 1, 0);

	auto *volSlider = new QSlider(Qt::Horizontal, this);
	volSlider->setRange(0, 255);
	volSlider->setValue(0xcc);
	layout->addWidget(volSlider, 1, 1);

	auto *octLabel = new QLabel(QStringLiteral("Octave"), this);
	layout->addWidget(octLabel, 2, 0);

	auto *octSlider = new QSlider(Qt::Horizontal, this);
	octSlider->setRange(0, 16);
	layout->addWidget(octSlider, 2, 1);

	auto *semiLabel = new QLabel(QStringLiteral("Semitune"), this);
	layout->addWidget(semiLabel, 3, 0);

	auto *semiSlider = new QSlider(Qt::Horizontal, this);
	semiSlider->setRange(0, 11);
	layout->addWidget(semiSlider, 3, 1);

	auto *detLabel = new QLabel(QStringLiteral("Detune"), this);
	layout->addWidget(detLabel, 4, 0);

	auto *detSlider = new QSlider(Qt::Horizontal, this);
	detSlider->setRange(0, 255);
	layout->addWidget(detSlider, 4, 1);

	return group;
}

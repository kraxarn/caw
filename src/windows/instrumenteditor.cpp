#include "windows/instrumenteditor.hpp"
#include "icon.hpp"
#include "iconsizes.hpp"
#include "widgets/oscilloscope.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSlider>
#include <QToolBar>

InstrumentEditor::InstrumentEditor(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QGridLayout(this);

	auto *oscilloscope = new Oscilloscope(this);
	oscilloscope->setMaximumHeight(150);
	layout->addWidget(oscilloscope, 0, 0, 1, 2);

	layout->addWidget(preset(), 1, 0, 1, 2);

	layout->addWidget(osc(1), 2, 0);
	layout->addWidget(osc(2), 2, 1);

	layout->addWidget(envelope(), 3, 0);

	auto *lfo = new QGroupBox(QStringLiteral("LFO"), this);
	layout->addWidget(lfo, 3, 1);

	auto *fx = new QGroupBox(QStringLiteral("FX"), this);
	layout->addWidget(fx, 4, 0, 1, 2);
}

auto InstrumentEditor::preset() -> QWidget *
{
	auto *group = new QGroupBox(QStringLiteral("Preset"), this);
	auto *layout = new QHBoxLayout(group);

	auto *presets = new QComboBox(this);
	layout->addWidget(presets, 1);

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

	auto *toolBar = new QToolBar(this);
	toolBar->setIconSize(IconSizes::smallToolBar());
	layout->addWidget(toolBar);

	toolBar->addAction(Icon::get(this, IconName::FolderOpen), QStringLiteral("Load preset"));
	toolBar->addAction(Icon::get(this, IconName::FloppyDisk), QStringLiteral("Save preset"));

	return group;
}

auto InstrumentEditor::osc(const quint8 idx) -> QWidget *
{
	auto *group = new QGroupBox(QStringLiteral("Oscillator %1").arg(idx), this);
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

	auto *xenvComboBox = new QCheckBox(QStringLiteral("Modulates frequency"));
	layout->addWidget(xenvComboBox, 1, 0, 1, 2);

	auto *volLabel = new QLabel(QStringLiteral("Volume"), this);
	layout->addWidget(volLabel, 2, 0);

	auto *volSlider = new QSlider(Qt::Horizontal, this);
	volSlider->setRange(0, 255);
	volSlider->setValue(0xcc);
	layout->addWidget(volSlider, 2, 1);

	auto *octLabel = new QLabel(QStringLiteral("Octave"), this);
	layout->addWidget(octLabel, 3, 0);

	auto *octSlider = new QSlider(Qt::Horizontal, this);
	octSlider->setRange(0, 16);
	layout->addWidget(octSlider, 3, 1);

	auto *semiLabel = new QLabel(QStringLiteral("Semitune"), this);
	layout->addWidget(semiLabel, 4, 0);

	auto *semiSlider = new QSlider(Qt::Horizontal, this);
	semiSlider->setRange(0, 11);
	layout->addWidget(semiSlider, 4, 1);

	auto *detLabel = new QLabel(QStringLiteral("Detune"), this);
	layout->addWidget(detLabel, 5, 0);

	auto *detSlider = new QSlider(Qt::Horizontal, this);
	detSlider->setRange(0, 255);
	layout->addWidget(detSlider, 5, 1);

	return group;
}

auto InstrumentEditor::envelope() -> QWidget *
{
	auto *group = new QGroupBox(QStringLiteral("Envelope"), this);
	auto *layout = new QGridLayout(group);

	auto *mastLabel = new QLabel(QStringLiteral("Master volume"), this);
	layout->addWidget(mastLabel, 0, 0);

	auto *mastSlider = new QSlider(Qt::Horizontal, this);
	mastSlider->setRange(0, 255);
	mastSlider->setValue(0xcc);
	layout->addWidget(mastSlider, 0, 1);

	auto *attLabel = new QLabel(QStringLiteral("Attack time"), this);
	layout->addWidget(attLabel, 1, 0);

	auto *attSlider = new QSlider(Qt::Horizontal, this);
	attSlider->setRange(0, 200'000);
	layout->addWidget(attSlider, 1, 1);

	auto *sustLabel = new QLabel(QStringLiteral("Sustain time"), this);
	layout->addWidget(sustLabel, 2, 0);

	auto *sustSlider = new QSlider(Qt::Horizontal, this);
	sustSlider->setRange(0, 200'000);
	layout->addWidget(sustSlider, 2, 1);

	auto *relLabel = new QLabel(QStringLiteral("Release time"), this);
	layout->addWidget(relLabel, 3, 0);

	auto *relSlider = new QSlider(Qt::Horizontal, this);
	relSlider->setRange(0, 200'000);
	layout->addWidget(relSlider, 3, 1);

	return group;
}

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
	layout->addWidget(lfo(), 3, 1);

	layout->addWidget(fx(), 4, 0, 1, 2);
}

auto InstrumentEditor::slider(const QString &text, const int row, const int column,
	const int columnSpan, const QWidget *parent) -> QSlider *
{
	auto *layout = qobject_cast<QGridLayout *>(parent->layout());
	if (layout == nullptr)
	{
		qFatal() << "no layout:" << parent->objectName();
		return new QSlider();
	}

	auto *label = new QLabel(text, this);
	layout->addWidget(label, row, column);

	auto *slider = new QSlider(Qt::Horizontal, this);
	layout->addWidget(slider, row, column + 1, 1, columnSpan);

	return slider;
}

auto InstrumentEditor::slider(const QString &text, const int row, const int column, const QWidget *parent) -> QSlider *
{
	return slider(text, row, column, 1, parent);
}

auto InstrumentEditor::slider(const QString &text, const int rowSpan, const QWidget *parent) -> QSlider *
{
	const auto *layout = qobject_cast<QGridLayout *>(parent->layout());
	const int row = layout != nullptr ? layout->rowCount() : 0;

	return slider(text, row, 0, rowSpan, parent);
}

auto InstrumentEditor::slider(const QString &text, const QWidget *parent) -> QSlider *
{
	return slider(text, 1, parent);
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

auto InstrumentEditor::lfo() -> QWidget *
{
	auto *group = new QGroupBox(QStringLiteral("LFO"), this);
	auto *layout = new QGridLayout(group);
	layout->setAlignment(Qt::AlignTop);

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

	auto *amtSlider = slider(QStringLiteral("AMT"), group);
	amtSlider->setRange(0, 255);

	auto *freqSlider = slider(QStringLiteral("FREQ"), group);
	freqSlider->setRange(0, 16);

	return group;
}

auto InstrumentEditor::fx() -> QWidget *
{
	auto *group = new QGroupBox(QStringLiteral("FX"), this);
	auto *layout = new QGridLayout(group);
	layout->setAlignment(Qt::AlignTop);

	auto *filterLabel = new QLabel(QStringLiteral("Filter"), this);
	layout->addWidget(filterLabel, 0, 0);

	auto *filterComboBox = new QComboBox(this);
	filterComboBox->addItems({
		QStringLiteral("None"),
		QStringLiteral("Low pass"),
		QStringLiteral("High pass"),
		QStringLiteral("Band pass"),
		QStringLiteral("Notch"),
	});
	layout->addWidget(filterComboBox, 0, 1, 1, 3);

	auto *freqSlider = slider(QStringLiteral("Filter frequency"), 3, group);
	freqSlider->setRange(0, 11025);

	auto *resSlider = slider(QStringLiteral("Filter resonance"), 3, group);
	resSlider->setRange(0, 255);

	auto *delaySlider = slider(QStringLiteral("Delay"), group);
	delaySlider->setRange(0, 248);

	auto *delayTimeSlider = slider(QStringLiteral("Time"), 3, 2, group);
	delayTimeSlider->setRange(0, 16);

	auto *panSlider = slider(QStringLiteral("Pan"), group);
	panSlider->setRange(0, 255);

	auto *panFreqSlider = slider(QStringLiteral("Frequency"), 4, 2, group);
	panFreqSlider->setRange(0, 16);

	auto *noiseSlider = slider(QStringLiteral("Noise volume"), 3, group);
	noiseSlider->setRange(0, 255);

	return group;
}

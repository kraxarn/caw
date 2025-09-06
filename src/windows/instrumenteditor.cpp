#include "windows/instrumenteditor.hpp"
#include "icon.hpp"
#include "iconsizes.hpp"
#include "widgets/envelopeeditor.hpp"
#include "widgets/fxeditor.hpp"
#include "widgets/instrumentpresets.hpp"
#include "widgets/lfoeditor.hpp"
#include "widgets/oscillatoreditor.hpp"
#include "widgets/oscilloscope.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QToolBar>

InstrumentEditor::InstrumentEditor(QWidget *parent)
	: QWidget(parent),
	mOsc1(new OscillatorEditor(1, this)),
	mOsc2(new OscillatorEditor(2, this)),
	mPresets(new InstrumentPresets(this)),
	mEnv(new EnvelopeEditor(this)),
	mLfo(new LfoEditor(this)),
	mFx(new FxEditor(this))
{
	auto *layout = new QGridLayout(this);

	auto *oscilloscope = new Oscilloscope(this);
	oscilloscope->setMaximumHeight(150);
	layout->addWidget(oscilloscope, 0, 0, 1, 2);

	layout->addWidget(mPresets, 1, 0, 1, 2);

	layout->addWidget(mOsc1, 2, 0);
	layout->addWidget(mOsc2, 2, 1);

	layout->addWidget(mEnv, 3, 0);
	layout->addWidget(mLfo, 3, 1);

	layout->addWidget(mFx, 4, 0, 1, 2);

	connect(mPresets, &InstrumentPresets::presetLoaded,
		this, &InstrumentEditor::onPresetLoaded);
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

void InstrumentEditor::onPresetLoaded(const Instrument &instrument)
{
	qInfo() << "Loaded:" << instrument.name;
}

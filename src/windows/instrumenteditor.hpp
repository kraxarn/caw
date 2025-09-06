#pragma once

#include "widgets/envelopeeditor.hpp"
#include "widgets/fxeditor.hpp"
#include "widgets/instrumentpresets.hpp"
#include "widgets/lfoeditor.hpp"
#include "widgets/oscillatoreditor.hpp"

#include <QSlider>
#include <QWidget>

class InstrumentEditor final: public QWidget
{
	Q_OBJECT

public:
	explicit InstrumentEditor(QWidget *parent);

private:
	OscillatorEditor *mOsc1;
	OscillatorEditor *mOsc2;
	InstrumentPresets *mPresets;
	EnvelopeEditor *mEnv;
	LfoEditor *mLfo;
	FxEditor *mFx;

	[[nodiscard]]
	auto fx() -> QWidget *;

	[[nodiscard]]
	auto slider(const QString &text, const QWidget *parent) -> QSlider *;
	[[nodiscard]]
	auto slider(const QString &text, int rowSpan, const QWidget *parent) -> QSlider *;
	[[nodiscard]]
	auto slider(const QString &text, int row, int column, const QWidget *parent) -> QSlider *;
	[[nodiscard]]
	auto slider(const QString &text, int row, int column, int columnSpan, const QWidget *parent) -> QSlider *;

	void onPresetLoaded(const Instrument &instrument);
};

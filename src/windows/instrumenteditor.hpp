#pragma once

#include "widgets/oscillatoreditor.hpp"

#include <QSlider>
#include <QWidget>

class InstrumentEditor final: public QWidget
{
	Q_OBJECT

public:
	explicit InstrumentEditor(QWidget *parent);

private:
	[[nodiscard]]
	auto preset() -> QWidget *;

	[[nodiscard]]
	auto envelope() -> QWidget *;
	[[nodiscard]]
	auto lfo() -> QWidget *;
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

	OscillatorEditor *osc1;
	OscillatorEditor *osc2;
};

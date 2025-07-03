#pragma once

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
	auto osc(quint8 idx) -> QWidget *;
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
};

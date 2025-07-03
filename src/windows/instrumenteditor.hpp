#pragma once

#include <QSlider>
#include <QWidget>

class InstrumentEditor final: public QWidget
{
	Q_OBJECT

public:
	explicit InstrumentEditor(QWidget *parent);

private:
	auto preset() -> QWidget *;
	auto osc(quint8 idx) -> QWidget *;
	auto envelope() -> QWidget *;
	auto lfo() -> QWidget *;

	auto slider(const QString &text, const QWidget *parent) -> QSlider *;
};

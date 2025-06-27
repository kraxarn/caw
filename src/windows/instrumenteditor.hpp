#pragma once

#include <QWidget>

class InstrumentEditor final: public QWidget
{
	Q_OBJECT

public:
	explicit InstrumentEditor(QWidget *parent);

private:
	auto preset() -> QWidget *;
};

#pragma once

#include <QToolBar>
#include <QWidget>

class Instrument final: public QWidget
{
	Q_OBJECT

public:
	explicit Instrument(QWidget *parent);

private:
	auto toolBar() -> QToolBar *;
};

#pragma once

#include <QToolBar>
#include <QWidget>

class Instrument final: public QWidget
{
	Q_OBJECT

public:
	explicit Instrument(QWidget *parent);

	QSize sizeHint() const override;

private:
	auto toolBar() -> QToolBar *;
};

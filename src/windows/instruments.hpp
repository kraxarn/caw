#pragma once

#include <QToolBar>
#include <QWidget>

class Instruments final: public QWidget
{
	Q_OBJECT

public:
	explicit Instruments(QWidget *parent);

	QSize sizeHint() const override;

private:
	auto toolBar() -> QToolBar *;
};

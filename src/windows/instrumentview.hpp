#pragma once

#include <QToolBar>
#include <QWidget>

class InstrumentView final: public QWidget
{
	Q_OBJECT

public:
	explicit InstrumentView(QWidget *parent);

	QSize sizeHint() const override;

private:
	auto toolBar() -> QToolBar *;
};

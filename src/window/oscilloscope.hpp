#pragma once

#include <QGraphicsView>

class Oscilloscope final: public QGraphicsView
{
	Q_OBJECT

public:
	explicit Oscilloscope(QWidget *parent);

protected:
	void showEvent(QShowEvent *event) override;

private:
	QPen color;
};

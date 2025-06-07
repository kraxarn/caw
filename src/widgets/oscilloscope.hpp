#pragma once

#include <QGraphicsTextItem>
#include <QGraphicsView>

class Oscilloscope final: public QGraphicsView
{
	Q_OBJECT

public:
	explicit Oscilloscope(QWidget *parent);

	void setText(const QString &text);

protected:
	void showEvent(QShowEvent *event) override;

	void resizeEvent(QResizeEvent *event) override;

private:
	QPen color;
	QGraphicsTextItem *text;
};

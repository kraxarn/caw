#pragma once

#include <QGraphicsView>

class Piano final: public QGraphicsView
{
	Q_OBJECT

public:
	explicit Piano(QWidget *parent);

protected:
	void showEvent(QShowEvent *event) override;

	void resizeEvent(QResizeEvent *event) override;
};

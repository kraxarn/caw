#pragma once

#include <QDockWidget>

class Order final: public QDockWidget
{
	Q_OBJECT

public:
	explicit Order(QWidget *parent);
};

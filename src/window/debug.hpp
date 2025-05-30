#pragma once

#include <QWidget>

class Debug final: public QWidget
{
	Q_OBJECT

public:
	explicit Debug(QWidget *parent);
};

#pragma once

#include <QTreeView>

class Order final: public QWidget
{
	Q_OBJECT

public:
	explicit Order(QWidget *parent);

private:
	QTreeView *list;
};

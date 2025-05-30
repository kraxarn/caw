#pragma once

#include <QTreeView>
#include <QToolBar>

class Order final: public QWidget
{
	Q_OBJECT

public:
	explicit Order(QWidget *parent);

private:
	QToolBar *toolBar;
	QTreeView *list;

	void addToolBar();
};

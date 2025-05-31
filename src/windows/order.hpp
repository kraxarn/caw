#pragma once

#include <QToolBar>
#include <QTreeView>

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

#include "orderlist.hpp"
#include "font.hpp"
#include "models/ordermodel.hpp"

#include <QHeaderView>
#include <QShowEvent>
#include <QStandardItemModel>
#include <QTreeView>
#include <QWidget>

OrderList::OrderList(QWidget *parent)
	: QTreeView(parent)
{
	auto *model = new OrderModel(this);
	QTreeView::setModel(model);

	setFont(Font::monospace());
	setRootIsDecorated(false);

	header()->setSectionResizeMode(QHeaderView::Stretch);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void OrderList::showEvent(QShowEvent *event)
{
	QTreeView::showEvent(event);
}

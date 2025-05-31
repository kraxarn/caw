#include "orderlist.hpp"
#include "font.hpp"
#include "model/ordermodel.hpp"

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
}

void OrderList::showEvent(QShowEvent *event)
{
	QTreeView::showEvent(event);

	for (auto i = 0; i < model()->columnCount(); i++)
	{
		resizeColumnToContents(i);
		setColumnWidth(i, static_cast<int>(static_cast<double>(columnWidth(i)) * 1.5));
	}
}

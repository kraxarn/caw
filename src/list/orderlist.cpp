#include "orderlist.hpp"
#include "model/ordermodel.hpp"
#include "font.hpp"

#include <QStandardItemModel>

OrderList::OrderList(QWidget *parent)
	: QTreeView(parent)
{
	auto *model = new OrderModel(this);
	QTreeView::setModel(model);

	setFont(Font::monospace());
	setRootIsDecorated(false);
}

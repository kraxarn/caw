#include "window/order.hpp"
#include "list/orderlist.hpp"

Order::Order(QWidget *parent)
	: QDockWidget(parent)
{
	setWindowTitle(QStringLiteral("Order"));
	setWidget(new OrderList(this));
	setDockLocation(Qt::TopDockWidgetArea);
}

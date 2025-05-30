#include "window/order.hpp"
#include "list/orderlist.hpp"

#include <QVBoxLayout>

Order::Order(QWidget *parent)
	: QWidget(parent)
{
	setWindowTitle(QStringLiteral("aaa"));

	auto *layout = new QVBoxLayout(this);

	list = new OrderList(this);
	layout->addWidget(list, 1);
}

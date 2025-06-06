#include "windows/order.hpp"
#include "icon.hpp"
#include "lists/orderlist.hpp"

#include <QString>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

Order::Order(QWidget *parent)
	: QWidget(parent),
	toolBar(nullptr)
{
	auto *layout = new QVBoxLayout(this);
	layout->setSpacing(0);

	addToolBar();
	layout->addWidget(toolBar);

	list = new OrderList(this);
	layout->addWidget(list, 1);
}

QSize Order::sizeHint() const
{
	return {200, 180};
}

void Order::addToolBar()
{
	toolBar = new QToolBar(this);
	toolBar->setIconSize(toolBar->iconSize() * 0.5);

	toolBar->addAction(Icon::get(IconName::Plus), QStringLiteral("Add order"));
	toolBar->addAction(Icon::get(IconName::Minus), QStringLiteral("Remove order"));
	toolBar->addAction(Icon::get(IconName::Clone), QStringLiteral("Duplicate order..."));
	toolBar->addAction(Icon::get(IconName::ChevronUp),QStringLiteral("Move order up"));
	toolBar->addAction(Icon::get(IconName::ChevronDown), QStringLiteral("Move order down"));
	toolBar->addAction(Icon::get(IconName::LinkSlash), QStringLiteral("Order change mode..."));
}

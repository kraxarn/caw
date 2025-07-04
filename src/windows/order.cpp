#include "windows/order.hpp"
#include "icon.hpp"
#include "iconsizes.hpp"
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
	toolBar->setIconSize(IconSizes::smallToolBar());

	toolBar->addAction(Icon::get(Mdi::Plus, this), QStringLiteral("Add order"));
	toolBar->addAction(Icon::get(Mdi::Minus, this), QStringLiteral("Remove order"));
	toolBar->addAction(Icon::get(Mdi::ContentDuplicate, this), QStringLiteral("Duplicate order..."));
	toolBar->addAction(Icon::get(Mdi::ChevronUp, this),QStringLiteral("Move order up"));
	toolBar->addAction(Icon::get(Mdi::ChevronDown, this), QStringLiteral("Move order down"));
	toolBar->addAction(Icon::get(Mdi::LinkOff, this), QStringLiteral("Order change mode..."));
}

#include "windows/order.hpp"
#include "icon.hpp"
#include "iconname.hpp"
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

	auto *add = toolBar->addAction(QStringLiteral("Add order"));
	Icon::set(add, IconName::Plus);

	auto *remove = toolBar->addAction(QStringLiteral("Remove order"));
	Icon::set(remove, IconName::Minus);

	auto *duplicate = toolBar->addAction(QStringLiteral("Duplicate order..."));
	Icon::set(duplicate, IconName::Clone);

	auto *moveUp = toolBar->addAction(QStringLiteral("Move order up"));
	Icon::set(moveUp, IconName::ChevronUp);

	auto *moveDown = toolBar->addAction(QStringLiteral("Move order down"));
	Icon::set(moveDown, IconName::ChevronDown);

	auto *changeMode = toolBar->addAction(QStringLiteral("Order change mode..."));
	Icon::set(changeMode, IconName::LinkSlash);
}

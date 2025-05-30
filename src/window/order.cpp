#include "window/order.hpp"
#include "list/orderlist.hpp"

#include <QToolBar>
#include <QVBoxLayout>

Order::Order(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QVBoxLayout(this);
	layout->setSpacing(0);

	addToolBar();
	layout->addWidget(toolBar);

	list = new OrderList(this);
	layout->addWidget(list, 1);
}

void Order::addToolBar()
{
	toolBar = new QToolBar(this);
	toolBar->setIconSize(toolBar->iconSize() * 0.5);

	toolBar->addAction(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd),
		QStringLiteral("Add order"));

	toolBar->addAction(QIcon::fromTheme(QIcon::ThemeIcon::ListRemove),
		QStringLiteral("Remove order"));

	toolBar->addAction(QIcon::fromTheme(QIcon::ThemeIcon::EditCopy),
		QStringLiteral("Duplicate order..."));

	toolBar->addAction(QIcon::fromTheme(QIcon::ThemeIcon::GoUp),
		QStringLiteral("Move order up"));

	toolBar->addAction(QIcon::fromTheme(QIcon::ThemeIcon::GoDown),
		QStringLiteral("Move order down"));

	toolBar->addAction(QIcon::fromTheme(QIcon::ThemeIcon::InsertLink),
		QStringLiteral("Order change mode..."));
}

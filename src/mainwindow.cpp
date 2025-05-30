#include "mainwindow.hpp"
#include "mainmenubar.hpp"
#include "list/orderlist.hpp"
#include "window/pattern.hpp"

#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(QStringLiteral("caw"));
	resize(1280, 720); // TODO

	menuBar = new MainMenuBar(this);
	setMenuBar(menuBar);

	setCentralWidget(new Pattern(this));

	order = new QDockWidget(QStringLiteral("Order"), this);
	order->setWidget(new Order(order));
	addDockWidget(Qt::TopDockWidgetArea, order);
}

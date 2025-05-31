#include "mainwindow.hpp"
#include "mainmenubar.hpp"
#include "window/order.hpp"
#include "window/oscilloscope.hpp"
#include "window/pattern.hpp"
#include "window/playcontrols.hpp"

#include <QDockWidget>
#include <QString>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(QStringLiteral("caw"));
	resize(1280, 720); // TODO

	menuBar = new MainMenuBar(this);
	setMenuBar(menuBar);

	setCentralWidget(new Pattern(this));

	auto *order = new QDockWidget(QStringLiteral("Orders"), this);
	order->setWidget(new Order(order));
	addDockWidget(Qt::TopDockWidgetArea, order);

	auto *oscilloscope = new QDockWidget(QStringLiteral("Oscilloscope"), this);
	oscilloscope->setWidget(new Oscilloscope(oscilloscope));
	addDockWidget(Qt::TopDockWidgetArea, oscilloscope);

	auto *playControls = new QDockWidget(QStringLiteral("Play controls"), this);
	playControls->setWidget(new PlayControls(playControls));
	addDockWidget(Qt::TopDockWidgetArea, playControls);
}

#include "mainwindow.hpp"
#include "mainmenubar.hpp"
#include "windows/order.hpp"
#include "windows/pattern.hpp"
#include "windows/playback.hpp"

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

	auto *playback = new QDockWidget(QStringLiteral("Playback"), this);
	playback->setWidget(new Playback(playback));
	addDockWidget(Qt::TopDockWidgetArea, playback);
}

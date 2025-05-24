#include "mainwindow.hpp"
#include "mainmenubar.hpp"
#include "window/pattern.hpp"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(QStringLiteral("caw"));

	menuBar = new MainMenuBar(this);
	setMenuBar(menuBar);

	setCentralWidget(new Pattern(this));
}

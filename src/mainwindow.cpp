#include "mainwindow.hpp"

#include <variant>
#include "mainmenubar.hpp"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(QStringLiteral("caw"));

	menuBar = new MainMenuBar(this);
	setMenuBar(menuBar);
}

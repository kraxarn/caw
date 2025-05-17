#include "mainwindow.hpp"

#include <variant>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(QStringLiteral("caw"));
}

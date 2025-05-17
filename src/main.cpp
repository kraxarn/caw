#include "mainwindow.hpp"

#include <QApplication>

auto main(int argc, char *argv[]) -> int
{
	QApplication app(argc, argv);

	MainWindow window(nullptr);
	window.show();

	return QCoreApplication::exec();
}

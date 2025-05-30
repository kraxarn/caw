#include "mainwindow.hpp"

#include <QApplication>
#include <QFontDatabase>

auto main(int argc, char *argv[]) -> int
{
	QApplication app(argc, argv);

	QFontDatabase::addApplicationFont(QStringLiteral(":/fontawesome.otf"));

	MainWindow window(nullptr);
	window.show();

	return QCoreApplication::exec();
}

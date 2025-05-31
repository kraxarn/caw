#include "mainwindow.hpp"

#include <QApplication>
#include <QCoreApplication>
#include <QFontDatabase>
#include <QString>

auto main(int argc, char *argv[]) -> int
{
	const QApplication app(argc, argv);

	QFontDatabase::addApplicationFont(QStringLiteral(":/fontawesome.otf"));

	MainWindow window(nullptr);
	window.show();

	return QCoreApplication::exec();
}

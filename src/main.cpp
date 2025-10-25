#include <QCoreApplication>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>

#include "models/instrumentmodel.hpp"
#include "models/ordermodel.hpp"
#include "models/patternmodel.hpp"

namespace
{
	void defineTypes(const QQmlApplicationEngine &engine)
	{
		engine.rootContext()->setContextProperty(QStringLiteral("AppName"),
			QCoreApplication::applicationName());

		engine.rootContext()->setContextProperty(QStringLiteral("AppVersion"),
			QCoreApplication::applicationVersion());

		engine.rootContext()->setContextProperty(QStringLiteral("QtVersion"),
			QStringLiteral(QT_VERSION_STR));

		engine.rootContext()->setContextProperty(QStringLiteral("BuildDate"),
			QStringLiteral(__DATE__));

		qmlRegisterType<InstrumentModel>("InstrumentModel", 1, 0, "InstrumentModel");
		qmlRegisterType<OrderModel>("OrderModel", 1, 0, "OrderModel");
		qmlRegisterType<PatternModel>("PatternModel", 1, 0, "PatternModel");
	}
}

auto main(int argc, char *argv[]) -> int
{
	QCoreApplication::setApplicationName(QStringLiteral(APP_NAME));
	QCoreApplication::setApplicationVersion(QStringLiteral(APP_VERSION));

	// For now at least
	QGuiApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

	const QGuiApplication app(argc, argv);

	QFontDatabase::addApplicationFont(QStringLiteral(":/fontawesome.otf"));

	QQmlApplicationEngine engine;
	defineTypes(engine);

	engine.loadFromModule(APP_NAME, "Main");

	return QGuiApplication::exec();
}

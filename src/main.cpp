#include <QFontDatabase>
#include <QGuiApplication>
#include <QString>

#include "models/instrumentmodel.hpp"
#include "models/ordermodel.hpp"
#include "models/patternmodel.hpp"
#include "apptheme.hpp"

namespace
{
	void defineTypes(QQmlApplicationEngine &engine)
	{
		engine.rootContext()->setContextProperty(QStringLiteral("AppName"),
			QCoreApplication::applicationName());

		engine.rootContext()->setContextProperty(QStringLiteral("AppVersion"),
			QCoreApplication::applicationVersion());

		engine.rootContext()->setContextProperty(QStringLiteral("QtVersion"),
			QStringLiteral(QT_VERSION_STR));

		engine.rootContext()->setContextProperty(QStringLiteral("BuildDate"),
			QStringLiteral(__DATE__));

		engine.addImportPath(QStringLiteral(":/"));

		qmlRegisterType<InstrumentModel>("InstrumentModel", 1, 0, "InstrumentModel");
		qmlRegisterType<OrderModel>("OrderModel", 1, 0, "OrderModel");
		qmlRegisterType<PatternModel>("PatternModel", 1, 0, "PatternModel");

		qmlRegisterUncreatableType<AppTheme>("AppTheme", 1, 0, "AppTheme",
			QStringLiteral("Attached property"));
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

	AppTheme::setStyle();

	engine.loadFromModule(APP_NAME, "Main");

	return QGuiApplication::exec();
}

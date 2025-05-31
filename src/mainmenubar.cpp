#include "mainmenubar.hpp"
#include "window/debug.hpp"

#include <QAction>
#include <QDockWidget>
#include <QMainWindow>
#include <QString>
#include <QWidget>

MainMenuBar::MainMenuBar(QWidget *parent)
	: QMenuBar(parent)
{
	addMenu(fileMenu());
	addMenu(editMenu());
	addMenu(settingsMenu());
	addMenu(windowMenu());
	addMenu(helpMenu());
}

auto MainMenuBar::fileMenu() -> QMenu *
{
	auto *menu = addMenu(QStringLiteral("&File"));

	auto *newMenu = menu->addMenu(QStringLiteral("&New"));
	newMenu->addAction(QStringLiteral("&Project..."));
	newMenu->addAction(QStringLiteral("From &clipboard..."));

	menu->addAction(QStringLiteral("&Open..."));
	menu->addAction(QStringLiteral("Open &recent"));
	menu->addSeparator();
	menu->addAction(QStringLiteral("&Save"));
	menu->addAction(QStringLiteral("Save &as..."));
	menu->addSeparator();
	menu->addAction(QStringLiteral("&Export..."));
	menu->addSeparator();
	menu->addAction(QStringLiteral("&Quit..."));

	return menu;
}

auto MainMenuBar::editMenu() -> QMenu *
{
	auto *menu = addMenu(QStringLiteral("&Edit"));
	return menu;
}

auto MainMenuBar::settingsMenu() -> QMenu *
{
	auto *menu = addMenu(QStringLiteral("&Settings"));
	return menu;
}

auto MainMenuBar::windowMenu() -> QMenu *
{
	auto *menu = addMenu(QStringLiteral("&Window"));
	return menu;
}

auto MainMenuBar::helpMenu() -> QMenu *
{
	auto *menu = addMenu(QStringLiteral("&Help"));

	const auto *debug = menu->addAction(QStringLiteral("&Debug"));
	connect(debug, &QAction::triggered,
		this, &MainMenuBar::onHelpDebugTriggered);

	return menu;
}

void MainMenuBar::onHelpDebugTriggered([[maybe_unused]] bool checked) const
{
	auto *mainWindow = qobject_cast<QMainWindow *>(window());
	if (mainWindow == nullptr)
	{
		qWarning() << "Main window not found";
		return;
	}

	auto *dockWidget = new QDockWidget(QStringLiteral("Debug"), mainWindow);
	dockWidget->setWidget(new Debug(dockWidget));
	dockWidget->setFloating(true);

	mainWindow->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}

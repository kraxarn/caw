#include "mainmenubar.hpp"

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
	return menu;
}

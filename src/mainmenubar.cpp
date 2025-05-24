#include "mainmenubar.hpp"

MainMenuBar::MainMenuBar(QWidget *parent)
	: QMenuBar(parent)
{
	addMenu(fileMenu());
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

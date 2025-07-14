#include "menus/loadpresetmenu.hpp"

LoadPresetMenu::LoadPresetMenu(QWidget *parent)
	: QMenu(parent)
{
	auto *builtIn = addMenu(QStringLiteral("Built-in"));
	builtIn->addAction(QStringLiteral("Default"));
	builtIn->addAction(QStringLiteral("Softy"));
	builtIn->addAction(QStringLiteral("Classic 8-bit"));
	builtIn->addAction(QStringLiteral("Square"));
	builtIn->addAction(QStringLiteral("Bell"));
	builtIn->addAction(QStringLiteral("Base string"));
	builtIn->addAction(QStringLiteral("Bass drum 1"));
	builtIn->addAction(QStringLiteral("Bass drum 2"));
	builtIn->addAction(QStringLiteral("Bass drum 3"));
	builtIn->addAction(QStringLiteral("Snare 1"));
	builtIn->addAction(QStringLiteral("Snare 2"));
	builtIn->addAction(QStringLiteral("Hi-hat 1"));
	builtIn->addAction(QStringLiteral("Hi-hat 2"));
	builtIn->addAction(QStringLiteral("Smash"));
	builtIn->addAction(QStringLiteral("Pipe hit"));
	builtIn->addAction(QStringLiteral("Wind"));

	auto *custom = addMenu(QStringLiteral("Custom"));
	custom->addAction(QStringLiteral("Nothing here"))->setEnabled(false);

	addSeparator();
	addAction(QStringLiteral("Load from file..."));
}

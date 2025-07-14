#include "menus/loadpresetmenu.hpp"

LoadPresetMenu::LoadPresetMenu(QWidget *parent)
	: QMenu(parent)
{
	auto *builtIn = addMenu(QStringLiteral("Built-in"));
	addAction(builtIn, QStringLiteral("Default"))->setChecked(true);
	addAction(builtIn, QStringLiteral("Softy"));
	addAction(builtIn, QStringLiteral("Classic 8-bit"));
	addAction(builtIn, QStringLiteral("Square"));
	addAction(builtIn, QStringLiteral("Bell"));
	addAction(builtIn, QStringLiteral("Base string"));
	addAction(builtIn, QStringLiteral("Bass drum 1"));
	addAction(builtIn, QStringLiteral("Bass drum 2"));
	addAction(builtIn, QStringLiteral("Bass drum 3"));
	addAction(builtIn, QStringLiteral("Snare 1"));
	addAction(builtIn, QStringLiteral("Snare 2"));
	addAction(builtIn, QStringLiteral("Hi-hat 1"));
	addAction(builtIn, QStringLiteral("Hi-hat 2"));
	addAction(builtIn, QStringLiteral("Smash"));
	addAction(builtIn, QStringLiteral("Pipe hit"));
	addAction(builtIn, QStringLiteral("Wind"));

	auto *custom = addMenu(QStringLiteral("Custom"));
	custom->addAction(QStringLiteral("Nothing here"))->setEnabled(false);

	addSeparator();
	QMenu::addAction(QStringLiteral("Load from file..."));
}

auto LoadPresetMenu::addAction(QMenu *menu, const QString &text) -> QAction *
{
	auto *action = menu->addAction(text);
	action->setCheckable(true);

	return action;
}

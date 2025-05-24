#pragma once

#include <QMenuBar>

class MainMenuBar final: public QMenuBar
{
	Q_OBJECT

public:
	explicit MainMenuBar(QWidget *parent);

private:
	[[nodiscard]]
	auto fileMenu() -> QMenu *;

	[[nodiscard]]
	auto editMenu() -> QMenu *;

	[[nodiscard]]
	auto settingsMenu() -> QMenu *;

	[[nodiscard]]
	auto windowMenu() -> QMenu *;

	[[nodiscard]]
	auto helpMenu() -> QMenu *;
};

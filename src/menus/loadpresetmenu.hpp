#pragma once

#include <QMenu>

class LoadPresetMenu final: public QMenu
{
	Q_OBJECT

public:
	explicit LoadPresetMenu(QWidget *parent);

private:
	static auto addAction(QMenu *menu, const QString &text) -> QAction *;
};

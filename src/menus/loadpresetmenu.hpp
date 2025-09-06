#pragma once

#include <QMenu>

class LoadPresetMenu final: public QMenu
{
	Q_OBJECT

public:
	explicit LoadPresetMenu(QWidget *parent);

private:
	QMenu *mBuiltIn;

	void onBuiltInAboutToShow() const;

	void onActionTriggered(const QAction *action) const;
};

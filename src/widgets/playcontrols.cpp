#include "widgets/playcontrols.hpp"
#include "icon.hpp"
#include "iconname.hpp"

#include <QString>
#include <QToolBar>
#include <QWidget>

PlayControls::PlayControls(QWidget *parent)
	: QToolBar(parent)
{
	auto *play = addAction(QStringLiteral("Play"));
	Icon::set(play, IconName::Play);

	auto *playBeginning = addAction(QStringLiteral("Play from the beginning of this pattern"));
	Icon::set(playBeginning, IconName::ForwardStep);

	auto *step = addAction(QStringLiteral("Step one row"));
	Icon::set(step, IconName::AnglesDown);

	auto *edit = addAction(QStringLiteral("Edit"));
	Icon::set(edit, IconName::Circle);

	auto *repeat = addAction(QStringLiteral("Repeat pattern"));
	Icon::set(repeat, IconName::Repeat);
}

#include "widgets/playcontrols.hpp"
#include "icon.hpp"
#include "iconsizes.hpp"

#include <QString>
#include <QToolBar>
#include <QWidget>

PlayControls::PlayControls(QWidget *parent)
	: QToolBar(parent)
{
	setIconSize(IconSizes::smallToolBar());

	addAction(Icon::get(this, IconName::Play), QStringLiteral("Play"));
	addAction(Icon::get(this, IconName::ForwardStep), QStringLiteral("Play from the beginning of this pattern"));
	addAction(Icon::get(this, IconName::AnglesDown), QStringLiteral("Step one row"));
	addAction(Icon::get(this, IconName::Circle), QStringLiteral("Edit"));
	addAction(Icon::get(this, IconName::Repeat), QStringLiteral("Repeat pattern"));
}

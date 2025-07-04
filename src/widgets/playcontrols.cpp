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

	addAction(Icon::get(Mdi::Play, this), QStringLiteral("Play"));
	addAction(Icon::get(Mdi::StepForward, this), QStringLiteral("Play from the beginning of this pattern"));
	addAction(Icon::get(Mdi::ChevronDoubleDown, this), QStringLiteral("Step one row"));
	addAction(Icon::get(Mdi::Record, this), QStringLiteral("Edit"));
	addAction(Icon::get(Mdi::Repeat, this), QStringLiteral("Repeat pattern"));
}

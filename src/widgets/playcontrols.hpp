#pragma once

#include <QToolBar>

class PlayControls final: public QToolBar
{
	Q_OBJECT

public:
	explicit PlayControls(QWidget *parent);
};

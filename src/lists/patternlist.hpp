#pragma once

#include <QTreeView>

class PatternList final: public QTreeView
{
	Q_OBJECT

public:
	PatternList(quint8 channelCount, QWidget *parent);
};

#pragma once

#include <QTreeWidget>

class Pattern final: public QTreeWidget
{
	Q_OBJECT

public:
	explicit Pattern(QWidget *parent);

private:
	void setChannelCount(int count);
};

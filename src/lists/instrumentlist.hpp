#pragma once

#include <QTreeView>

class InstrumentList final: public QTreeView
{
	Q_OBJECT

public:
	explicit InstrumentList(QWidget *parent);

protected:
	void showEvent(QShowEvent *event) override;
};

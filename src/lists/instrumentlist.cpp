#include "lists/instrumentlist.hpp"
#include "models/instrumentmodel.hpp"

#include <QTreeWidget>

InstrumentList::InstrumentList(QWidget *parent)
	: QTreeView(parent)
{
	auto *model = new InstrumentModel(this);
	QTreeView::setModel(model);

	setRootIsDecorated(false);
}

void InstrumentList::showEvent(QShowEvent *event)
{
	QTreeView::showEvent(event);
}

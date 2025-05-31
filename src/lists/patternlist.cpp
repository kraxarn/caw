#include "lists/patternlist.hpp"
#include "models/patternmodel.hpp"

#include <QTreeView>

PatternList::PatternList(const quint8 channelCount, QWidget *parent)
	: QTreeView(parent)
{
	auto *model = new PatternModel(channelCount, this);
	QTreeView::setModel(model);
}

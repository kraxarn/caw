#include "lists/patternlist.hpp"
#include "font.hpp"
#include "models/patternmodel.hpp"

#include <QTreeView>

PatternList::PatternList(const quint8 channelCount, QWidget *parent)
	: QTreeView(parent)
{
	auto *model = new PatternModel(channelCount, this);
	QTreeView::setModel(model);

	setFont(Font::monospace());
	setRootIsDecorated(false);

	setColumnWidth(0, baseWidth * 2);
	for (auto i = 1; i <= model->columnCount({}); i++)
	{
		setColumnWidth(i, baseWidth * 3);
	}
}

auto PatternList::sizeHint() const -> QSize
{
	constexpr auto width = 800;
	constexpr auto height = 500;

	return {width, height};
}

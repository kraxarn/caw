#include "window/pattern.hpp"

#include <QString>
#include <QStringList>
#include <QTreeWidget>
#include <QWidget>

Pattern::Pattern(QWidget *parent)
	: QTreeWidget(parent)
{
	setChannelCount(8);
}

void Pattern::setChannelCount(const int count)
{
	QStringList labels;
	labels.reserve(count);

	for (auto i = 0; i < count; i++)
	{
		labels.append(QStringLiteral("Ch. %1").arg(i + 1));
	}

	setHeaderLabels(labels);
}

#include "window/debug.hpp"

#include <QTabWidget>
#include <QLabel>

Debug::Debug(QWidget *parent)
	: QWidget(parent)
{
	auto *tabs = new QTabWidget(this);

	tabs->addTab(new QLabel(QStringLiteral("hi mom"), tabs), QStringLiteral("Icons"));
}

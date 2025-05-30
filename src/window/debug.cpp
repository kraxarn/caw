#include "window/debug.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QTabWidget>
#include <QScrollArea>

Debug::Debug(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QVBoxLayout(this);

	auto *tabs = new QTabWidget(this);
	layout->addWidget(tabs);

	tabs->addTab(iconsTab(), QStringLiteral("Icons"));
}

auto Debug::iconsTab() -> QWidget *
{
	auto *widget = new QWidget(this);
	auto *layout = new QGridLayout(widget);

	for (auto i = 0; i < static_cast<int>(QIcon::ThemeIcon::NThemeIcons); i++)
	{
		constexpr auto iconSize = 32;

		const auto themeIcon = static_cast<QIcon::ThemeIcon>(i);
		if (!QIcon::hasThemeIcon(themeIcon))
		{
			continue;
		}

		const auto iconPixmap = QIcon::fromTheme(themeIcon).pixmap(iconSize, iconSize);
		auto *icon = new QLabel(widget);
		icon->setPixmap(iconPixmap);
		layout->addWidget(icon, i, 0);

		auto *label = new QLabel(QString::number(i), widget);
		layout->addWidget(label, i, 1);
	}

	auto *scrollArea = new QScrollArea(this);
	scrollArea->setWidget(widget);

	return scrollArea;
}

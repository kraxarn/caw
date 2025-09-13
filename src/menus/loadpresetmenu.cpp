#include "menus/loadpresetmenu.hpp"
#include "synth/instrument.hpp"

#include <QDirIterator>
#include <QJsonDocument>
#include <QJsonObject>

LoadPresetMenu::LoadPresetMenu(QWidget *parent)
	: QMenu(parent)
{
	mBuiltIn = addMenu(QStringLiteral("Built-in"));

	connect(mBuiltIn,
		&QMenu::aboutToShow,
		this,
		&LoadPresetMenu::onBuiltInAboutToShow
	);

	connect(mBuiltIn,
		&QMenu::triggered,
		this,
		&LoadPresetMenu::onActionTriggered
	);

	auto *custom = addMenu(QStringLiteral("Custom"));
	custom->addAction(QStringLiteral("Nothing here"))->setEnabled(false);

	addSeparator();
	addAction(QStringLiteral("Load from file..."));
}

void LoadPresetMenu::onBuiltInAboutToShow() const
{
	if (!mBuiltIn->isEmpty())
	{
		return;
	}

	QList<Instrument> presets;
	QDirIterator iter(QStringLiteral(":/presets"));
	while (iter.hasNext())
	{
		QFile file(iter.next());
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qWarning() << "Failed to open" << file.fileName()
				<< ":" << file.errorString();
			continue;
		}

		QJsonParseError parseError;
		const auto json = QJsonDocument::fromJson(file.readAll(), &parseError);
		file.close();

		if (parseError.error != QJsonParseError::NoError)
		{
			qWarning() << "Failed to open" << file.fileName()
				<< ":" << parseError.errorString();
			continue;
		}

		presets.append(Instrument::fromJson(json.object()));
	}

	std::ranges::sort(presets, [](const Instrument &a, const Instrument &b) -> bool
	{
		return a.name.localeAwareCompare(b.name) < 0;
	});

	for (const auto &preset: presets)
	{
		auto *action = mBuiltIn->addAction(preset.name);
		action->setCheckable(true);
		action->setChecked(preset.name == QStringLiteral("Default"));
		action->setData(QVariant::fromValue(preset));
	}
}

void LoadPresetMenu::onActionTriggered(const QAction *action)
{
	if (action == nullptr)
	{
		return;
	}

	// Preset
	if (action->data().canConvert<Instrument>())
	{
		const auto instrument = action->data().value<Instrument>();
		emit presetLoaded(instrument);

		for (auto *buildInAction: mBuiltIn->actions())
		{
			if (buildInAction != action)
			{
				buildInAction->setChecked(false);
			}
		}
	}
}

#include "widgets/editorpanel.hpp"
#include "icon.hpp"
#include "enums/envelope.hpp"
#include "widgets/propertyslider.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QWidget>

EditorPanel::EditorPanel(const QString &title, QWidget *parent)
	: QGroupBox(title, parent),
	mGrid(new QGridLayout(this))
{
	mGrid->setAlignment(Qt::AlignTop);
	mGrid->setColumnStretch(1, 1);
}

auto EditorPanel::row() const -> int
{
	return mGrid->rowCount();
}

auto EditorPanel::addSlider(const QString &text, const int row, const int column, const int columnSpan) -> QSlider *
{
	auto *label = new QLabel(text, this);
	mGrid->addWidget(label, row, column);

	const auto *prop = new PropertySlider(this);
	mGrid->addWidget(prop->slider(), row, column + 1, 1, columnSpan);
	mGrid->addWidget(prop->value(), row, column + columnSpan + 1);

	return prop->slider();
}

auto EditorPanel::addSlider(const QString &text, const int column, const int columnSpan) -> QSlider *
{
	return addSlider(text, row(), column, columnSpan);
}

auto EditorPanel::addSlider(const QString &text, const int column) -> QSlider *
{
	return addSlider(text, column, 1);
}

auto EditorPanel::addSlider(const QString &text) -> QSlider *
{
	return addSlider(text, 0);
}

auto EditorPanel::addCheckBox(const QString &text) -> QCheckBox *
{
	auto *checkBox = new QCheckBox(text, this);
	mGrid->addWidget(checkBox, row(), 0, 1, 3);
	return checkBox;
}

auto EditorPanel::addComboBox(const QString &text) -> QComboBox *
{
	return addComboBox(text, 0);
}

auto EditorPanel::addComboBox(const QString &text, const int column) -> QComboBox *
{
	return addComboBox(text, column, 2);
}

auto EditorPanel::addComboBox(const QString &text, const int column, const int columnSpan) -> QComboBox *
{
	auto *label = new QLabel(text, this);
	mGrid->addWidget(label, row(), column);

	auto *comboBox = new QComboBox(this);
	mGrid->addWidget(comboBox, row() - 1, column + 1, 1, columnSpan);

	return comboBox;
}

auto EditorPanel::addEnvelope() -> QComboBox *
{
	auto *comboBox = addComboBox(QStringLiteral("Envelope"));

	comboBox->addItem(
		Icon::get(Mdi::SquareWave, this),
		QStringLiteral("Square wave"),
		QVariant::fromValue(Envelope::Square)
	);

	comboBox->addItem(
		Icon::get(Mdi::SineWave, this),
		QStringLiteral("Sine wave"),
		QVariant::fromValue(Envelope::Sine)
	);

	comboBox->addItem(
		Icon::get(Mdi::SawtoothWave, this),
		QStringLiteral("Sawtooth"),
		QVariant::fromValue(Envelope::Sawtooth)
	);

	comboBox->addItem(
		Icon::get(Mdi::TriangleWave, this),
		QStringLiteral("Triangle wave"),
		QVariant::fromValue(Envelope::Triangle)
	);

	return comboBox;
}

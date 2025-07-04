#include "widgets/editorpanel.hpp"
#include "icon.hpp"
#include "enums/envelope.hpp"

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

auto EditorPanel::addSlider(const QString &text, const int column, const int columnSpan) -> QSlider *
{
	auto *label = new QLabel(text, this);
	mGrid->addWidget(label, row(), column);

	auto *slider = new QSlider(Qt::Horizontal, this);
	mGrid->addWidget(slider, row() - 1, column + 1, 1, columnSpan);

	auto *lineEdit = new QLineEdit(this);
	lineEdit->setFixedWidth(50);
	mGrid->addWidget(lineEdit, row() - 1, column + 2);

	return slider;
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

auto EditorPanel::addEnvelope() -> QComboBox *
{
	auto *label = new QLabel(QStringLiteral("Envelope"), this);
	mGrid->addWidget(label, row(), 0);

	auto *comboBox = new QComboBox(this);

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

	mGrid->addWidget(comboBox, row() - 1, 1, 1, 2);

	return comboBox;
}

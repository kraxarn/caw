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
	: QGroupBox(title, parent)
{
	auto *layout = new QGridLayout(this);
	layout->setAlignment(Qt::AlignTop);
	layout->setColumnStretch(1, 1);
}

auto EditorPanel::grid() const -> QGridLayout *
{
	return qobject_cast<QGridLayout *>(layout());
}

auto EditorPanel::row() const -> int
{
	return grid()->rowCount();
}

auto EditorPanel::addSlider(const QString &text, const int row, const int column, const int columnSpan) -> QSlider *
{
	auto *label = new QLabel(text, this);
	grid()->addWidget(label, row, column);

	auto *slider = new QSlider(Qt::Horizontal, this);
	grid()->addWidget(slider, row, column + 1, 1, columnSpan);

	auto *lineEdit = new QLineEdit(this);
	lineEdit->setFixedWidth(50);
	grid()->addWidget(lineEdit, row, column + 2);

	return slider;
}

auto EditorPanel::addSlider(const QString &text, const int row, const int column) -> QSlider *
{
	return addSlider(text, row, column, 1);
}

auto EditorPanel::addSlider(const QString &text, const int rowSpan) -> QSlider *
{
	return addSlider(text, row(), 0, rowSpan);
}

auto EditorPanel::addSlider(const QString &text) -> QSlider *
{
	return addSlider(text, 1);
}

auto EditorPanel::addCheckBox(const QString &text) -> QCheckBox *
{
	auto *checkBox = new QCheckBox(text, this);
	grid()->addWidget(checkBox, row(), 0, 1, 3);
}

auto EditorPanel::addEnvelope() -> QComboBox *
{
	auto *label = new QLabel(QStringLiteral("Envelope"), this);
	grid()->addWidget(label, row(), 0);

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

	grid()->addWidget(comboBox, row() - 1, 1, 1, 2);

	return comboBox;
}

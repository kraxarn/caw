#pragma once

#include "widgets/propertyslider.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QString>
#include <QWidget>

class EditorPanel: public QGroupBox
{
	Q_OBJECT

protected:
	EditorPanel(const QString &title, QWidget *parent);

	auto addSlider(const QString &text) -> PropertySlider *;
	auto addSlider(const QString &text, int column) -> PropertySlider *;
	auto addSlider(const QString &text, int column, int columnSpan) -> PropertySlider *;
	auto addSlider(const QString &text, int row, int column, int columnSpan) -> PropertySlider *;

	auto addCheckBox(const QString &text) -> QCheckBox *;

	auto addComboBox(const QString &text) -> QComboBox *;
	auto addComboBox(const QString &text, int column) -> QComboBox *;
	auto addComboBox(const QString &text, int column, int columnSpan) -> QComboBox *;

	auto addEnvelope() -> QComboBox *;

	[[nodiscard]]
	auto row() const -> int;

private:
	QGridLayout *mGrid;
};

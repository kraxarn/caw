#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QSlider>
#include <QString>
#include <QWidget>

class EditorPanel: public QGroupBox
{
	Q_OBJECT

protected:
	EditorPanel(const QString &title, QWidget *parent);

	[[nodiscard]]
	auto addSlider(const QString &text) -> QSlider *;

	[[nodiscard]]
	auto addSlider(const QString &text, int column) -> QSlider *;

	[[nodiscard]]
	auto addSlider(const QString &text, int column, int columnSpan) -> QSlider *;

	[[nodiscard]]
	auto addCheckBox(const QString &text) -> QCheckBox *;

	[[nodiscard]]
	auto addEnvelope() -> QComboBox *;

	[[nodiscard]]
	auto row() const -> int;

private:
	QGridLayout *mGrid;
};

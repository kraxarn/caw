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

	auto addSlider(const QString &text) -> QSlider *;
	auto addSlider(const QString &text, int column) -> QSlider *;
	auto addSlider(const QString &text, int column, int columnSpan) -> QSlider *;

	auto addCheckBox(const QString &text) -> QCheckBox *;

	auto addEnvelope() -> QComboBox *;

	[[nodiscard]]
	auto row() const -> int;

private:
	QGridLayout *mGrid;
};

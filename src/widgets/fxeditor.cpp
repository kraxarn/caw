#include "widgets/fxeditor.hpp"

FxEditor::FxEditor(QWidget *parent)
	: EditorPanel(QStringLiteral("FX"), parent)
{
	auto *filter = addComboBox(QStringLiteral("Filter"), 0, 5);
	filter->addItems({
		QStringLiteral("None"),
		QStringLiteral("Low pass"),
		QStringLiteral("High pass"),
		QStringLiteral("Band pass"),
		QStringLiteral("Notch"),
	});

	auto *freq = addSlider(QStringLiteral("Filter frequency"), 0, 4);
	freq->setRange(0, 11'025);

	auto *res = addSlider(QStringLiteral("Filter resonance"), 0, 4);
	res->setRange(0, 255);

	auto *delay = addSlider(QStringLiteral("Delay"));
	delay->setRange(0, 248);

	auto *delayTime = addSlider(QStringLiteral("Time"), 4, 3, 1);
	delayTime->setRange(0, 16);

	auto *pan = addSlider(QStringLiteral("Pan"));
	pan->setRange(0, 255);

	auto *panFreq = addSlider(QStringLiteral("Frequency"), 5, 3, 1);
	panFreq->setRange(0, 16);

	auto *noise = addSlider(QStringLiteral("Noise volume"), 0, 4);
	noise->setRange(0, 255);
}

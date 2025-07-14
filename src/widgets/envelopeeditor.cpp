#include "widgets/envelopeeditor.hpp"

EnvelopeEditor::EnvelopeEditor(QWidget *parent)
	: EditorPanel(QStringLiteral("Envelope"), parent)
{
	auto *mast = addSlider(QStringLiteral("Master volume"));
	mast->setRange(0, 255);

	auto *att = addSlider(QStringLiteral("Attack time"));
	att->setRange(0, 200'000);

	auto *sust = addSlider(QStringLiteral("Sustain time"));
	sust->setRange(0, 200'000);

	auto *rel = addSlider(QStringLiteral("Release time"));
	rel->setRange(0, 200'000);
}

#pragma once

#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>

class SongInfo final: public QWidget
{
	Q_OBJECT

public:
	explicit SongInfo(QWidget *parent);

	[[nodiscard]]
	auto sizeHint() const -> QSize override;

private:
	QLineEdit *name;
	QLineEdit *author;
	QLineEdit *album;
	QTextEdit *comment;
};

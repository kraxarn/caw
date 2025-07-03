#pragma once

#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>

class SongInfo final: public QWidget
{
	Q_OBJECT

public:
	explicit SongInfo(QWidget *parent);

private:
	QLineEdit *name;
	QLineEdit *author;
	QLineEdit *album;
	QTextEdit *comment;
};

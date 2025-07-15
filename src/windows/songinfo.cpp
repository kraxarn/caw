#include "windows/songinfo.hpp"

#include <QGridLayout>
#include <QLabel>

#include "lists/instrumentlist.hpp"

SongInfo::SongInfo(QWidget *parent)
	: QWidget(parent)
{
	auto *layout = new QGridLayout(this);
	layout->setAlignment(Qt::AlignTop);

	auto *nameLabel = new QLabel(QStringLiteral("Name"), this);
	layout->addWidget(nameLabel, 0, 0);

	name = new QLineEdit(this);
	layout->addWidget(name, 0, 1);

	auto *authorLabel = new QLabel(QStringLiteral("Author"), this);
	layout->addWidget(authorLabel, 1, 0);

	author = new QLineEdit(this);
	layout->addWidget(author, 1, 1);

	auto *albumLabel = new QLabel(QStringLiteral("Album"), this);
	layout->addWidget(albumLabel, 2, 0);

	album = new QLineEdit(this);
	layout->addWidget(album, 2, 1);

	auto *commentLabel = new QLabel(QStringLiteral("Comment"), this);
	layout->addWidget(commentLabel, 3, 0);

	comment = new QTextEdit(this);
	layout->addWidget(comment, 3, 1);
}

auto SongInfo::sizeHint() const -> QSize
{
	constexpr auto width = 120;
	constexpr auto height = 180;

	return {width, height};
}

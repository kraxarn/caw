#include "mainwindow.hpp"
#include "maintoolbar.hpp"
#include "lists/patternlist.hpp"
#include "windows/instrument.hpp"
#include "windows/order.hpp"
#include "windows/oscilloscopechannel.hpp"
#include "windows/piano.hpp"
#include "windows/playback.hpp"
#include "windows/songinfo.hpp"

#include <QDockWidget>
#include <QString>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle(QStringLiteral("caw"));
	setWindowIcon(QIcon(QStringLiteral(":/logos/caw")));

	auto *toolBar = new MainToolBar(this);
	addToolBar(toolBar);

	setCentralWidget(new PatternList(channelCount, this));

	auto *order = new QDockWidget(QStringLiteral("Orders"), this);
	order->setWidget(new Order(order));
	addDockWidget(Qt::TopDockWidgetArea, order);

	auto *playback = new QDockWidget(QStringLiteral("Playback"), this);
	playback->setWidget(new Playback(playback));
	addDockWidget(Qt::TopDockWidgetArea, playback);

	auto *instruments = new QDockWidget(QStringLiteral("Instruments"), this);
	instruments->setWidget(new Instrument(instruments));
	addDockWidget(Qt::TopDockWidgetArea, instruments);

	auto *songInfo = new QDockWidget(QStringLiteral("Song Info"), this);
	songInfo->setWidget(new SongInfo(songInfo));
	addDockWidget(Qt::TopDockWidgetArea, songInfo);

	auto *oscilloscopeChannel = new QDockWidget(QStringLiteral("Oscilloscope per-channel"), this);
	oscilloscopeChannel->setWidget(new OscilloscopeChannel(channelCount, oscilloscopeChannel));
	addDockWidget(Qt::RightDockWidgetArea, oscilloscopeChannel);

	auto *piano = new QDockWidget(QStringLiteral("Piano"), this);
	piano->setWidget(new Piano(piano));
	addDockWidget(Qt::BottomDockWidgetArea, piano);
}

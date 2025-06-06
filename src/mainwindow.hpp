#pragma once

#include <QMainWindow>

class MainWindow final: public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent);

private:
	static constexpr quint8 channelCount = 8; // TBD
};

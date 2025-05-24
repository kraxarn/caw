#pragma once

#include <QMainWindow>
#include <QMenuBar>

class MainWindow final: public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent);

private:
	QMenuBar *menuBar;
};

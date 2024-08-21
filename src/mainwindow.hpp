#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <qmainwindow.h>
#include <qtmetamacros.h>
#include <qwidget.h>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void on_actionExit_triggered();

private:
	Ui::MainWindow* ui;
};

#endif // MAINWINDOW_HPP

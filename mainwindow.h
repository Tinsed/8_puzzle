#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <problem.h>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	Problem* pProblem;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

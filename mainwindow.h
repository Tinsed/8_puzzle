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
public:
	Problem *problem;
	QList<Node*> *solution;
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionNew_triggered();

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_horizontalSlider_sliderMoved(int position);

	void on_pushButton_4_clicked();

	void on_pushButton_5_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

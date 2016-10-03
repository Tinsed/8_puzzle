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
	QVector<State* (*)(Node*, int&)>* op;
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionNew_triggered();

	void on_pushButton_clicked();

	void on_pushButton_step_clicked();

	void on_horizontalSlider_sliderMoved(int position);

	void on_pushButton_4_clicked();

	void on_pushButton_5_clicked();

	void on_actionDFS_triggered(bool checked);

	void on_action_triggered(bool checked);

	void on_action_3_triggered(bool checked);

	void on_action_4_triggered(bool checked);

	void on_checkBox_stateChanged(int arg1);

	void on_pushButton_3_clicked();

	void on_checkBox_2_stateChanged(int arg1);

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

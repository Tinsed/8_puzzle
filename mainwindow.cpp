#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "actionsPr.h"
#include "problem.h"

extern void refreshEvents(){
	QApplication::processEvents();
}

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
	{
		problem = nullptr;
		ui->setupUi(this);
	}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionNew_triggered()
{
	QVector<State* (*)(Node*, int&)> op;
	op.append(up);
	op.append(right);
	op.append(down);
	op.append(left);
	problem = new Problem(op,goalTest,nullptr,0);
}

void MainWindow::on_pushButton_clicked()
{
	if(problem){
		QQueue<Node*> fringe;
		Node* result = Tree_Search(*problem, fringe, ui->textEdit);
		ui->textEdit->append((result)?("\nSuccess! "+result->getState()->toString()):"NUF!");
	}
}

void MainWindow::on_pushButton_2_clicked()
{
	State* result = new State();
	result->fromString("1234x5678");
	ui->textEdit->append(result->toString());
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
	ui->label_10->setText("Depth: " + QString::number(position));
	if(problem)
		problem->setMaxDepth(position);
}

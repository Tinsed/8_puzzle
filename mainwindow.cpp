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
	Node* result = new Node();
	ui->textEdit->append(result->getState()->toString());
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
	ui->label_10->setText("Depth: " + QString::number(position));
	if(problem)
		problem->setMaxDepth(position);
}

void MainWindow::on_pushButton_4_clicked()
{
	if(problem && ui->lineEdit->text().length()==9){
		problem->getInitSate()->fromString(ui->lineEdit->text());
	}
}

void MainWindow::on_pushButton_5_clicked()
{
	if(problem && ui->lineEdit->text().length()==9){
		problem->getTargetSate()->fromString(ui->lineEdit_2->text());
	}
}

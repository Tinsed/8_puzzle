#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "actionsPr.h"
#include "problem.h"
#include <QTime>

extern bool writeLog = false;

extern void refreshEvents(){
	QApplication::processEvents();
}

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
	{
		problem = nullptr;
		solution = nullptr;
		ui->setupUi(this);
	}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionNew_triggered()
{

	if(problem){
		delete problem;
	}
	QVector<State* (*)(Node*, int&)>* op = new QVector<State* (*)(Node*, int&)>();
	problem = new Problem(op,goalTest,nullptr,0);

	if(ui->lineEdit->text().length()==9){
		problem->getInitSate()->fromString(ui->lineEdit->text());
	}
	if(ui->lineEdit->text().length()==9){
		problem->getTargetSate()->fromString(ui->lineEdit_2->text());
	}

	op->append(up);
	op->append(right);
	op->append(down);
	op->append(left);
}

void MainWindow::on_pushButton_clicked()
{
	if(problem == nullptr){
		ui->textEdit->append("Open problem!\n");
		return;
	}

	QQueue<Node*>* fringe = new QQueue<Node*>();
	QHash<QString,Node*>* visitedNodes = new QHash<QString,Node*>();

	problem->setMaxDepth(ui->horizontalSlider->value());

	ui->textEdit->append("Initial: "+problem->getInitSate()->toString());
	ui->textEdit->append("Target: "+problem->getTargetSate()->toString());
	ui->textEdit->append("Depth: "+QString::number(problem->getMaxDepth())+"\n");

	QTime start = QTime::currentTime();
	Node* result = Tree_Search(problem, visitedNodes,fringe, ui->textEdit);
	ui->textEdit->append("Time elapsed: "+QString::number(start.elapsed())+"ms");
	if(result == 0){
		ui->textEdit->append("NUF!\n");
	}else{
		ui->textEdit->append("\nSuccess! "+result->getState()->toString());
		if(solution)
			delete solution;
		solution = new QList<Node*>();
		for(Node* i = result;i;i=i->getParentNode())
			solution->insert(solution->begin(),i);
		ui->textEdit->append("Path:");
		for(auto i:*solution)
			ui->textEdit->append(QString::number(i->getDepth())+"	"+getActStr(i->getAction())+"	"+i->getState()->toString());
		ui->textEdit->append("");
	}
	for(auto s:*visitedNodes){
		if(s!= nullptr)
			delete s;
	}
	delete visitedNodes;
	/*for(auto s:*fringe){
		if(s!= nullptr)
			try{delete s;}
			catch(...){}
	}*/
	delete fringe;
}

void MainWindow::on_pushButton_2_clicked()
{
	State* result = new State();
	result->fromString("123x45678");
	ui->textEdit->append(result->toString());
	delete result;
	result = new State(0x12345678,3);
	ui->textEdit->append(result->toString());
	delete result;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
	ui->label_10->setText("Depth: " + QString::number(position));
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

void MainWindow::on_actionDFS_triggered(bool checked)
{
	if(checked){
		ui->action->setChecked(false);
		ui->action_3->setChecked(false);
		ui->action_4->setChecked(false);
	}
}

void MainWindow::on_action_triggered(bool checked)
{
	if(checked){
		ui->actionDFS->setChecked(false);
		ui->action_3->setChecked(false);
		ui->action_4->setChecked(false);
	}
}

void MainWindow::on_action_3_triggered(bool checked)
{
	if(checked){
		ui->actionDFS->setChecked(false);
		ui->action->setChecked(false);
		ui->action_4->setChecked(false);
	}
}

void MainWindow::on_action_4_triggered(bool checked)
{
	if(checked){
		ui->actionDFS->setChecked(false);
		ui->action->setChecked(false);
		ui->action_3->setChecked(false);
	}
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
	writeLog = arg1==2;
}

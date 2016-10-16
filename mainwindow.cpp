#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "actionsPr.h"
#include "problem.h"



extern bool writeLog = false;
extern bool stepMode = false;
extern bool doStep = false;
extern bool doStop = false;
extern int countStep = 0;
extern int countObj = 0;

extern void refreshEvents(){
	QApplication::processEvents();
}

int iTypeAlg = 0;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
	{
		problem = nullptr;
		op = nullptr;
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
	if(op)
		delete op;
	op = new QVector<State* (*)(Node*, int&)>();
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
	doStep = false;
	doStop = false;
	countStep = 0;
	countObj = 0;
	ui->textEdit->clear();
	if(problem == nullptr){
		ui->textEdit->append("Open problem!\n");
		return;
	}

	problem->setMaxDepth(ui->horizontalSlider->value());

	QList<Node*>* solution = SolveProblem(problem,ui->textEdit,iTypeAlg);
	ui->textEdit->append("Steps: "+QString::number(countStep));
	ui->textEdit->append("Objects: "+QString::number(countObj));
	if(solution == nullptr){
		ui->textEdit->append("NUF!\n");
	}else{
		ui->textEdit->append("\nSuccess! "+solution->last()->getState()->toString());
		ui->textEdit->append("Path:");
		for(auto i:*solution)
			ui->textEdit->append(QString::number(i->getDepth())+"	"+getActStr(i->getAction())+"	"+i->getState()->toString());
		ui->textEdit->append("");
		for(auto i:*solution)
			delete i;
	}
	delete solution; //TODO: global
}

void MainWindow::on_pushButton_step_clicked()
{
	doStep = true;
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
		iTypeAlg = BFS;
		ui->action->setChecked(false);
		ui->action_3->setChecked(false);
		ui->action_4->setChecked(false);
	}else{
		if(!ui->action->isChecked()||!ui->action_3->isChecked()||!ui->action_4->isChecked()){
			ui->actionDFS->setChecked(true);
		}
	}
}

void MainWindow::on_action_triggered(bool checked)
{
	if(checked){
		iTypeAlg = DLS;
		ui->actionDFS->setChecked(false);
		ui->action_3->setChecked(false);
		ui->action_4->setChecked(false);
	}else{
		if(!ui->actionDFS->isChecked()||!ui->action_3->isChecked()||!ui->action_4->isChecked()){
			ui->action->setChecked(true);
		}
	}
}

void MainWindow::on_action_3_triggered(bool checked)
{
	if(checked){
		iTypeAlg = ERRCOUNT;
		ui->actionDFS->setChecked(false);
		ui->action->setChecked(false);
		ui->action_4->setChecked(false);
	}else{
		if(!ui->action->isChecked()||!ui->actionDFS->isChecked()||!ui->action_4->isChecked()){
			ui->action_3->setChecked(true);
		}
	}
}

void MainWindow::on_action_4_triggered(bool checked)
{
	if(checked){
		iTypeAlg = MTT;
		ui->actionDFS->setChecked(false);
		ui->action->setChecked(false);
		ui->action_3->setChecked(false);
	}else{
		if(!ui->action->isChecked()||!ui->actionDFS->isChecked()||!ui->action_3->isChecked()){
			ui->action_4->setChecked(true);
		}
	}
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
	writeLog = arg1==2;
}

void MainWindow::on_pushButton_3_clicked()
{
	/*State* result = new State();
	result->fromString("123x45678");
	ui->textEdit->append(result->toString());
	ui->textEdit->append(QString::number(result->getHashI(),16));
	delete result;
	result = new State(0x12345678,3);
	ui->textEdit->append(result->toString());
	ui->textEdit->append(QString::number(result->getHashI(),16));
	delete result;*/
	if(stepMode)
		doStep=true;
	doStop = true;
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
	stepMode = arg1==2;
}

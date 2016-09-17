#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <problem.h>

MainWindow::MainWindow(QWidget *parent) :

	pProblem = new Problem();

	QMainWindow(parent),
	ui(new Ui::MainWindow)
	{
		ui->setupUi(this);
	}

MainWindow::~MainWindow()
{
	delete ui;
}

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "NeuronNetwork/Test.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
	ui->setupUi(this);

	welcome = new Welcome();
	edit = new Edit();
	help = new Help();

	edit->hide();
	help->hide();

	ui->centralWidget->layout()->addWidget(welcome);
	ui->centralWidget->layout()->addWidget(edit);
	ui->centralWidget->layout()->addWidget(help);

	ui->buttonGroup->button(-2)->setChecked(true);

	connectSignalSlots();
}

void MainWindow::connectSignalSlots(void){
	connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(editMenuItemPressed(int)));
	connect(ui->actionRun_tests, SIGNAL(triggered()), this, SLOT(runTests()));

	connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotDataOnStdout()));
	connect(&process, SIGNAL(readyReadStandardError()), this, SLOT(slotProcessError()));
	connect(&process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotProcessError()));
	connect(&process, SIGNAL(started()), this, SLOT(slotProcessStart()));
	connect(&process, SIGNAL(finished(int)), this, SLOT(slotProcessFinish(int)));
}

void MainWindow::editMenuItemPressed(int button){
	button = abs(button);
	if(button > 2 && button < 8){
		welcome->hide();
		help->hide();
		edit->show();
		edit->setWidget(button);
	}else if(button == 2){
		edit->hide();
		help->hide();
		welcome->show();
	}else if(button == 8){
		welcome->hide();
		edit->hide();
		help->show();
	}
}

void MainWindow::runTests(){
	QString program = "/home/petr/Dokumenty/NeuronNetwork/NeuronNetwork-build-desktop-Qt_v_CEST__Debug/main";
	QStringList arguments;
	arguments << "-t";

	//QProcess p(this);
	txtBox.show();

	process.start(program, arguments);
/*
	QMessageBox msgBox;
	msgBox.show();

	while(p.Running){
		p.waitForReadyRead(100);
		QString out = QString(p.readAll());
		msgBox.setText(out);
	}*/
}

void MainWindow::slotDataOnStdout(){
	qDebug() << "slotDataOnStdout";
	txtBox.appendText(QString(process.readAllStandardOutput() + '\n'));
}

void MainWindow::slotStderr(){
	qDebug() << "std error";
}

void MainWindow::slotProcessError(){
	qDebug() << "error";
}

void MainWindow::slotProcessStart(){
	qDebug() << "start";
}

void MainWindow::slotProcessFinish(int exitCode){
	qDebug() << "finish: " << exitCode;
	QString str = process.readAllStandardOutput();
	qDebug() << str;
}

MainWindow::~MainWindow(){
	delete welcome;
	delete edit;
	delete help;
	delete ui;
}

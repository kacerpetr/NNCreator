#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Dialog/AboutDialog.h"

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
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));

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

void MainWindow::showAboutDialog(){
	AboutDialog ad;
	ad.exec();
}

void MainWindow::runTests(){
	QString program = "/media/Arch-data/NeuralNetCreator/Build-debug/main";

	QStringList arguments;
	arguments << "-t";

	txtBox.show();
	process.start(program, arguments);
}

void MainWindow::slotDataOnStdout(){
	txtBox.appendText(QString(process.readAllStandardOutput()));
}

void MainWindow::slotStderr(){
	txtBox.appendText(QString(process.readAllStandardError()));
}

void MainWindow::slotProcessError(){
	txtBox.appendText("Process error ...");
	txtBox.appendText(QString(process.readAllStandardError()));
}

void MainWindow::slotProcessStart(){
	txtBox.appendText("Process started / state changed to running ...\n");
}

void MainWindow::slotProcessFinish(int exitCode){
	txtBox.appendText(QString("Process finished: ") + QString().setNum(exitCode));
	txtBox.appendText(QString(process.readAll()));
}

MainWindow::~MainWindow(){
	delete welcome;
	delete edit;
	delete help;
	delete ui;
}

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Dialog/AboutDialog.h"
#include <QLabel>
#include <QMessageBox>
#include "Dialog/NewProjectDialog.h"

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

	connectSignalSlot();

	statusBarLabel = new QLabel;
	statusBarLabel->setText("Neural network Creator");
	ui->statusBar->addWidget(statusBarLabel);	
}

MainWindow::~MainWindow(){
	delete welcome;
	delete edit;
	delete help;
	delete ui;
}

void MainWindow::connectSignalSlot(){
	connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(editMenuItemPressed(int)));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
	connect(ui->actionAboutQt4, SIGNAL(triggered()), this, SLOT(aboutQt()));

	connect(ui->actionNewProject, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(welcome->getNewProjectButton(), SIGNAL(pressed()), this, SLOT(newProject()));

	connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
}

void MainWindow::enableEdit(){
	if(edit->getWorkspace()->getProjectCount() > 0){
		ui->trainingPatternButton->setEnabled(true);
		ui->topologyButton->setEnabled(true);
		ui->learningButton->setEnabled(true);
		ui->testingButton->setEnabled(true);
	}
}

///////////////////////////////////////////////////////////////////
///////// Slots ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

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

void MainWindow::aboutQt(){
	QMessageBox::aboutQt(this);
}

void MainWindow::newProject(){
	edit->newProject();
	enableEdit();
	ui->trainingPatternButton->click();
}

void MainWindow::openProject(){

}


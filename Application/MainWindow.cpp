#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Dialog/AboutDialog.h"
#include <QLabel>
#include <QMessageBox>

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

	statusBarLabel = new QLabel;
	statusBarLabel->setText("Neural network Creator");
	ui->statusBar->addWidget(statusBarLabel);	
}

void MainWindow::connectSignalSlots(void){
	connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(editMenuItemPressed(int)));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
	connect(ui->actionAboutQt4, SIGNAL(triggered()), this, SLOT(aboutQt()));
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

void MainWindow::aboutQt(){
	QMessageBox::aboutQt(this);
}

MainWindow::~MainWindow(){
	delete workspace;
	delete welcome;
	delete edit;
	delete help;
	delete ui;
}

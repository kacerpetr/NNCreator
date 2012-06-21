#include "MainWindow.h"
#include "ui_MainWindow.h"

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

MainWindow::~MainWindow(){
	delete welcome;
	delete edit;
	delete help;
	delete ui;
}

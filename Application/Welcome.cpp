#include "Welcome.h"
#include "ui_Welcome.h"

Welcome::Welcome(QWidget *parent) : QWidget(parent), ui(new Ui::Welcome){
	ui->setupUi(this);
}

Welcome::~Welcome(){
	delete ui;
}

QToolButton* Welcome::getNewProjectButton(){
	return ui->newProjectButton;
}

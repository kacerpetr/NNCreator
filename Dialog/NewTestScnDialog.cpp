#include "NewTestScnDialog.h"
#include "ui_NewTestScnDialog.h"
#include <QDebug>

NewTestScnDialog::NewTestScnDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewTestScnDialog), confirmed(false){
	ui->setupUi(this);
	connect(ui->okButton, SIGNAL(pressed()), this, SLOT(ok()));
}

NewTestScnDialog::~NewTestScnDialog(){
	delete ui;
}

QString NewTestScnDialog::getName(){
	return ui->scenarioNameEdit->text();
}

bool NewTestScnDialog::isConfirmed(){
	return confirmed;
}

void NewTestScnDialog::ok(){
	confirmed = true;
	close();
}

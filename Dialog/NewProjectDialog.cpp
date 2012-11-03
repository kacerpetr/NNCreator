#include "NewProjectDialog.h"
#include "ui_NewProjectDialog.h"
#include <QFileDialog>

NewProjectDialog::NewProjectDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewProjectDialog), confirmed(false){
	ui->setupUi(this);
	connect(ui->okButton, SIGNAL(pressed()), this, SLOT(ok()));
	connect(ui->browseButton, SIGNAL(pressed()), this, SLOT(browse()));
}

NewProjectDialog::~NewProjectDialog(){
	delete ui;
}

bool NewProjectDialog::isConfirmed(){
	return confirmed;
}

QString NewProjectDialog::getPath(){
	return ui->pathEdit->text();
}

QString NewProjectDialog::getName(){
	return ui->nameEdit->text();
}

void NewProjectDialog::browse(){
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::DirectoryOnly);
	dialog.exec();

	if(dialog.result() == QFileDialog::Accepted){
		ui->pathEdit->setText(dialog.selectedFiles()[0]);
	}
}

void NewProjectDialog::ok(){
	confirmed = true;
	close();
}

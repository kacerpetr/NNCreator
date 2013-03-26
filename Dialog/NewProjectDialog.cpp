#include "NewProjectDialog.h"
#include "ui_NewProjectDialog.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace Dialog{

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

QString NewProjectDialog::checkPath(){
    QString chars = "\/:*?\"<>|";

    //check invalid characters in project name
    QString name = getName();
    for(int i = 0; i < chars.length(); i++){
        if(name.contains(chars[i]))
            return tr("Project name contains some invalid characters \ / : * ? \" < > |.");
    }

    QString path = getPath();
    QFileInfo info;

    //check if given path exists
    info.setFile(path);
    if(!info.exists())
        return tr("Project path does not exist.");

    //checks if project folder does not exist
    info.setFile(path+"/"+name);
    if(info.exists())
        return tr("Project folder already exists.");

    //all is ok, project can (probably) be created
    return QString();
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
    QString err = checkPath();
    if(!err.isNull()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Create project"));
        msgBox.setText(tr("Project can't be created, check project name and path."));
        msgBox.setInformativeText(err);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
	confirmed = true;
	close();
}

}

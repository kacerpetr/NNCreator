#include "NewProjectDialog.h"
#include "ui_NewProjectDialog.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace Dialog{

/**
 * Class constructor.
 */
NewProjectDialog::NewProjectDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::NewProjectDialog),
    confirmed(false)
{
	ui->setupUi(this);
	connect(ui->okButton, SIGNAL(pressed()), this, SLOT(ok()));
	connect(ui->browseButton, SIGNAL(pressed()), this, SLOT(browse()));
}

/**
 * Class destructor.
 */
NewProjectDialog::~NewProjectDialog(){
	delete ui;
}

/**
 * Returns true if dialog is closed by pressing ok button.
 */
bool NewProjectDialog::isConfirmed(){
	return confirmed;
}

/**
 * Returns project path.
 */
QString NewProjectDialog::getPath(){
	return ui->pathEdit->text();
}

/**
 * Returns project name.
 */
QString NewProjectDialog::getName(){
	return ui->nameEdit->text();
}

/**
 * Checks if project path and name is valid.
 */
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

/**
 * Browsse button slot, shows QFileDialog to select directory.
 */
void NewProjectDialog::browse(){
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::DirectoryOnly);
	dialog.exec();

	if(dialog.result() == QFileDialog::Accepted){
		ui->pathEdit->setText(dialog.selectedFiles()[0]);
	}
}

/**
 * Ok button slot.
 */
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

#include "FileNameDialog.h"
#include "ui_FileNameDialog.h"
#include <QMessageBox>

namespace Dialog{

FileNameDialog::FileNameDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::FileNameDialog),
    success(false)
{
    ui->setupUi(this);
    connect(ui->cancelButton, SIGNAL(pressed()), this, SLOT(cancelPressed()));
    connect(ui->okButton, SIGNAL(pressed()), this, SLOT(okPressed()));
}

FileNameDialog::~FileNameDialog(){
    delete ui;
}

void FileNameDialog::setTitle(QString text){
    setWindowTitle(text);
}

QString FileNameDialog::title() const{
    return windowTitle();
}

void FileNameDialog::setHeader(QString text){
    ui->label->setText(text);
}

QString FileNameDialog::header() const{
    return ui->label->text();
}

void FileNameDialog::setText(QString text){
    ui->lineEdit->setText(text);
}

QString FileNameDialog::text() const{
    return ui->lineEdit->text();
}

bool FileNameDialog::ok() const{
    return success;
}

QString FileNameDialog::checkName(){
    QString chars = "\\/:*?\"<>|";

    //check invalid characters in name
    QString name = text();
    for(int i = 0; i < chars.length(); i++){
        if(name.contains(chars[i]))
            return tr("File name contains some invalid characters \\ / : * ? \" < > |.");
    }

    return QString();
}

void FileNameDialog::cancelPressed(){
    close();
}

void FileNameDialog::okPressed(){
    QString err = checkName();
    if(!err.isNull()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Filename"));
        msgBox.setText(tr("Invalid filename entered."));
        msgBox.setInformativeText(err);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    success = true;
    close();
}

}

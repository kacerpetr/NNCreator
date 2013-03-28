#include "FileNameDialog.h"
#include "ui_FileNameDialog.h"
#include <QMessageBox>

namespace Dialog{

/**
 * Class constructor.
 */
FileNameDialog::FileNameDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::FileNameDialog),
    success(false)
{
    ui->setupUi(this);
    connect(ui->cancelButton, SIGNAL(pressed()), this, SLOT(cancelPressed()));
    connect(ui->okButton, SIGNAL(pressed()), this, SLOT(okPressed()));
}

/**
 * Class destructor.
 */
FileNameDialog::~FileNameDialog(){
    delete ui;
}

/**
 * Sets window title.
 */
void FileNameDialog::setTitle(QString text){
    setWindowTitle(text);
}

/**
 * Returns window title.
 */
QString FileNameDialog::title() const{
    return windowTitle();
}

/**
 * Sets text input header.
 */
void FileNameDialog::setHeader(QString text){
    ui->label->setText(text);
}

/**
 * Returns text input header.
 */
QString FileNameDialog::header() const{
    return ui->label->text();
}

/**
 * Sets text input value.
 */
void FileNameDialog::setText(QString text){
    ui->lineEdit->setText(text);
}

/**
 * Returns text input value.
 */
QString FileNameDialog::text() const{
    return ui->lineEdit->text();
}

/**
 * Retruns true if dialog is closed by pressing ok button.
 */
bool FileNameDialog::ok() const{
    return success;
}

/**
 * Checks name for invalid characters.
 * @return Null string if name is valid or error string.
 */
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

/**
 * Cancel button slot.
 */
void FileNameDialog::cancelPressed(){
    close();
}

/**
 * Ok button slot.
 */
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

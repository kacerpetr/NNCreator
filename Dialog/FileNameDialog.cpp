/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

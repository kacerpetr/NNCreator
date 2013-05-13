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

#ifndef FILENAMEDIALOG_H
#define FILENAMEDIALOG_H

#include <QDialog>

namespace Ui {
    class FileNameDialog;
}

/**
 * Contains dialog classes.
 */
namespace Dialog{

/**
 * Filename dialog class.
 */
class FileNameDialog : public QDialog{
    Q_OBJECT
    
    public:
        FileNameDialog(QWidget *parent = 0);
        ~FileNameDialog();
        void setTitle(QString text);
        QString title() const;
        void setHeader(QString text);
        QString header() const;
        void setText(QString text);
        QString text() const;
        bool ok() const;

    private:
        QString checkName();

    private slots:
        void cancelPressed();
        void okPressed();

    private:
        /** File name dialog ui pointer. */
        Ui::FileNameDialog *ui;
        /** True if ok button pressed. */
        bool success;
};

}

#endif // FILENAMEDIALOG_H

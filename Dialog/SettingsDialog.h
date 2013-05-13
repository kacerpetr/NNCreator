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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
    class SettingsDialog;
}

/**
 * Contains dialog classes.
 */
namespace Dialog{

/**
 * Raw settings dialog class.
 */
class SettingsDialog : public QDialog{
    Q_OBJECT
    
    public:
        SettingsDialog(QWidget *parent = 0);
        ~SettingsDialog();
        bool ok();

    private slots:
        void applyPressed();
        void cancelPressed();

    private:
        /** Settings dialog ui class. */
        Ui::SettingsDialog *ui;
        /** True if dialog is closed by ok button. */
        bool confirmed;
        /** List of item labels. */
        QList<QLabel*> label;
        /** List of item values. */
        QList<QLineEdit*> edit;
};

}

#endif // SETTINGSDIALOG_H

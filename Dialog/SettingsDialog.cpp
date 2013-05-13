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

#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "Util/Settings.h"

namespace Dialog{

/**
 * Class constructor.
 */
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    confirmed(false)
{
    ui->setupUi(this);

    Settings& set = Settings::get();
    QMap<QString,QString> map = set.allData();
    QList<QString> list = map.keys();

    for(int i = 0; i < list.length(); i++){
        QLabel* lbl = new QLabel(this);
        lbl->setText(list[i]);
        label.append(lbl);
        QLineEdit* led = new QLineEdit(this);
        led->setText(map[list[i]]);
        edit.append(led);
        ui->formLayout->addRow(lbl, led);
    }

    connect(ui->applyButton, SIGNAL(pressed()), this, SLOT(applyPressed()));
    connect(ui->cancelButton, SIGNAL(pressed()), this, SLOT(cancelPressed()));
}

/**
 * Class destructor.
 */
SettingsDialog::~SettingsDialog(){
    delete ui;
}

/**
 * Apply button slot, saves settings changes.
 */
void SettingsDialog::applyPressed(){
    QMap<QString,QString> map;
    for(int i = 0; i < label.length(); i++){
        map.insert(label[i]->text(), edit[i]->text());
    }

    Settings& set = Settings::get();
    set.saveData(map);

    confirmed = true;
    close();
}

/**
 * Cancel button slot.
 */
void SettingsDialog::cancelPressed(){
    confirmed = false;
    close();
}

/**
 * Returns true if dialog is closed by pressing ok button.
 */
bool SettingsDialog::ok(){
    return confirmed;
}

}

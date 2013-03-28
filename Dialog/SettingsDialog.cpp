#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "Util/Settings.h"
using namespace Util;

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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
    class SettingsDialog;
}

namespace Dialog{

class SettingsDialog : public QDialog{
    Q_OBJECT
    
    public:
        explicit SettingsDialog(QWidget *parent = 0);
        ~SettingsDialog();
        bool isConfirmed();

    private slots:
        void applyPressed();
        void cancelPressed();

    private:
        QList<QLabel*> label;
        QList<QLineEdit*> edit;
        Ui::SettingsDialog *ui;
        bool confirmed;
};

}

#endif // SETTINGSDIALOG_H

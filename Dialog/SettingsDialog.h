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

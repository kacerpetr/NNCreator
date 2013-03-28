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

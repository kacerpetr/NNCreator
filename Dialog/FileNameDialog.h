#ifndef FILENAMEDIALOG_H
#define FILENAMEDIALOG_H

#include <QDialog>

namespace Ui {
    class FileNameDialog;
}

namespace Dialog{

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
        Ui::FileNameDialog *ui;
        bool success;
};

}

#endif // FILENAMEDIALOG_H

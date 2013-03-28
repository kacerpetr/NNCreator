#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
	class NewProjectDialog;
}

/**
 * Contains dialog classes.
 */
namespace Dialog{

/**
 * New project dialog class.
 */
class NewProjectDialog : public QDialog{
	Q_OBJECT
		
	public:
        NewProjectDialog(QWidget *parent = 0);
		~NewProjectDialog();
		bool isConfirmed();
		QString getPath();
		QString getName();

    private:
        QString checkPath();

	public slots:
		void browse();
		void ok();

	private:
        /** New project dialog ui pointer. */
		Ui::NewProjectDialog *ui;
        /** True if dialog is closed by ok button. */
		bool confirmed;
};

}

#endif // NEWPROJECTDIALOG_H

#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
	class NewProjectDialog;
}

class NewProjectDialog : public QDialog{
	Q_OBJECT
		
	public:
		explicit NewProjectDialog(QWidget *parent = 0);
		~NewProjectDialog();
		bool isConfirmed();
		QString getPath();
		QString getName();

	public slots:
		void browse();
		void ok();

	private:
		Ui::NewProjectDialog *ui;
		bool confirmed;
};

#endif // NEWPROJECTDIALOG_H

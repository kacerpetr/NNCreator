#ifndef NEWTESTSCNDIALOG_H
#define NEWTESTSCNDIALOG_H

#include <QDialog>
#include "../Project/Project.h"

namespace Ui {
	class NewTestScnDialog;
}

class NewTestScnDialog : public QDialog{
	Q_OBJECT
		
	public:
		explicit NewTestScnDialog(QWidget *parent = 0);
		~NewTestScnDialog();
		QString getName();
		bool isConfirmed();

	public slots:
		void ok();

	private:
		Ui::NewTestScnDialog *ui;
		bool confirmed;
};

#endif // NEWTESTSCNDIALOG_H

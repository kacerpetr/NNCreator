#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui{
	class AboutDialog;
}

/**
 * Contains dialog classes.
 */
namespace Dialog{

/**
 * Shows basic info about application and its author.
 */
class AboutDialog : public QDialog{
	Q_OBJECT
		
	public:
        AboutDialog(QWidget *parent = 0);
		~AboutDialog();
		
	private:
        /** About dialog ui pointer. */
		Ui::AboutDialog *ui;
};

}
#endif // ABOUTDIALOG_H

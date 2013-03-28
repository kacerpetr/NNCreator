#ifndef TEXTVIEWBOXDIALOG_H
#define TEXTVIEWBOXDIALOG_H

#include <QDialog>

namespace Ui{
	class TextViewBoxDialog;
}

/**
 * Contains dialog classes.
 */
namespace Dialog{

/**
 * Shows text in read only text edit.
 */
class TextViewBoxDialog : public QDialog{
	Q_OBJECT
		
	public:
        TextViewBoxDialog(QWidget *parent = 0);
        ~TextViewBoxDialog();
		void appendText(QString text);
		
	private:
        /** Text view box dialog in pointer. */
		Ui::TextViewBoxDialog *ui;
};

}

#endif // TEXTVIEWBOXDIALOG_H

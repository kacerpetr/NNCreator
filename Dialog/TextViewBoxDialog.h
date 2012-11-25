#ifndef TEXTVIEWBOXDIALOG_H
#define TEXTVIEWBOXDIALOG_H

#include <QDialog>

namespace Ui{
	class TextViewBoxDialog;
}

class TextViewBoxDialog : public QDialog{
	Q_OBJECT
		
	public:
		explicit TextViewBoxDialog(QWidget *parent = 0);
		void appendText(QString text);
		~TextViewBoxDialog();
		
	private:
		Ui::TextViewBoxDialog *ui;
};

#endif // TEXTVIEWBOXDIALOG_H

#ifndef TEXTVIEWBOX_H
#define TEXTVIEWBOX_H

#include <QDialog>

namespace Ui{
	class TextViewBox;
}

class TextViewBox : public QDialog{
	Q_OBJECT
		
	public:
		explicit TextViewBox(QWidget *parent = 0);
		void appendText(QString text);
		~TextViewBox();
		
	private:
		Ui::TextViewBox *ui;
};

#endif // TEXTVIEWBOX_H

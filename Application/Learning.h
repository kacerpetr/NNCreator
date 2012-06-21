#ifndef LEARNING_H
#define LEARNING_H

#include <QWidget>

namespace Ui {
class Learning;
}

class Learning : public QWidget
{
		Q_OBJECT
		
	public:
		explicit Learning(QWidget *parent = 0);
		~Learning();
		
	private:
		Ui::Learning *ui;
};

#endif // LEARNING_H

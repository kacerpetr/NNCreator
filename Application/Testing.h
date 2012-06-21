#ifndef TESTING_H
#define TESTING_H

#include <QWidget>

namespace Ui {
class Testing;
}

class Testing : public QWidget
{
		Q_OBJECT
		
	public:
		explicit Testing(QWidget *parent = 0);
		~Testing();
		
	private:
		Ui::Testing *ui;
};

#endif // TESTING_H

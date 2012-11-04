#ifndef TESTING_H
#define TESTING_H

#include <QWidget>

namespace Ui {
class TestingWidget;
}

class TestingWidget : public QWidget
{
		Q_OBJECT
		
	public:
		explicit TestingWidget(QWidget *parent = 0);
		~TestingWidget();
		
	private:
		Ui::TestingWidget *ui;
};

#endif // TESTING_H

#ifndef LEARNINGWIDGET_H
#define LEARNINGWIDGET_H

#include <QWidget>

namespace Ui {
class LearningWidget;
}

class LearningWidget : public QWidget
{
		Q_OBJECT
		
	public:
		explicit LearningWidget(QWidget *parent = 0);
		~LearningWidget();
		
	private:
		Ui::LearningWidget *ui;
};

#endif // LEARNINGWIDGET_H

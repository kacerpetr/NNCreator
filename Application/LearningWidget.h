#ifndef LEARNINGWIDGET_H
#define LEARNINGWIDGET_H

#include <QWidget>
#include "Project/LearningConfigModel.h"

namespace Ui {
	class LearningWidget;
}

class LearningWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit LearningWidget(QWidget *parent = 0);
		~LearningWidget();
		void setModel(LearningConfigModel* model);
		bool hasModel();
		
	private:
		Ui::LearningWidget *ui;
		LearningConfigModel* model;
};

#endif // LEARNINGWIDGET_H

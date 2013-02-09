#ifndef LEARNINGWIDGET_H
#define LEARNINGWIDGET_H

#include <QWidget>
#include "Project/LearningConfigModel.h"

using namespace Project;
namespace Ui{class LearningWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The LearningWidget class.
 */
class LearningWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit LearningWidget(QWidget *parent = 0);
		~LearningWidget();
		void setModel(LearningConfigModel* model);
		bool hasModel();

	private slots:
		void closeBtnPressed();

	signals:
		void closePressed(BaseModel*);

	private:
		Ui::LearningWidget *ui;
		LearningConfigModel* model;
};

}

#endif // LEARNINGWIDGET_H

#ifndef LEARNINGWIDGET_H
#define LEARNINGWIDGET_H

#include <QWidget>
#include "Project/LearningConfigModel.h"
#include "GuiPart/NetParamWidget.h"
#include "GuiPart/Plot1D.h"

using namespace ProjectData;
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
		void startLearning();
		void stopLearning();
		void learningStoped(int iteration, long time, double error);
		void updateLearning(int iteration, long time, double error);
		void datasetSelected(QString name);
		void networkSelected(QString name);
		void lrnCoefChanged(double value);
		void maxIterChanged(int value);
		void maxErrChanged(double value);
		void maxTimeChanged(int value);

	signals:
		void closePressed(BaseModel*);

	private:
		Plot1D* graph;
		Ui::LearningWidget *ui;
		LearningConfigModel* model;
		NetParamWidget* npw;
};

}

#endif // LEARNINGWIDGET_H

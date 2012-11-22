#ifndef TRAININGPATTERNWIDGET_H
#define TRAININGPATTERNWIDGET_H

#include <QWidget>
#include "Project/TrainingPatternModel.h"

using namespace Project;

namespace Ui{
	class TrainingPatternWidget;
}

class TrainingPatternWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit TrainingPatternWidget(QWidget *parent = 0);
		~TrainingPatternWidget();
		void setModel(TrainingPatternModel* model);
		bool hasModel();

	public slots:
		void showContextMenu();

	private:
		Ui::TrainingPatternWidget *ui;
		Project::TrainingPatternModel* model;
};

#endif // TRAININGPATTERNWIDGET_H

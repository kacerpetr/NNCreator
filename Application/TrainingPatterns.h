#ifndef TRAININGPATTERNS_H
#define TRAININGPATTERNS_H

#include <QWidget>
#include "Project/TrainingPatternModel.h"

namespace Ui {
class TrainingPatterns;
}

class TrainingPatterns : public QWidget
{
		Q_OBJECT
		
	public:
		explicit TrainingPatterns(QWidget *parent = 0);
		~TrainingPatterns();
		
	private:
		Ui::TrainingPatterns *ui;
		Project::TrainingPatternModel* tpm;
};

#endif // TRAININGPATTERNS_H

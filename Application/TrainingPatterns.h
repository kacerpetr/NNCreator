#ifndef TRAININGPATTERNS_H
#define TRAININGPATTERNS_H

#include <QWidget>

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
};

#endif // TRAININGPATTERNS_H

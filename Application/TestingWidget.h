#ifndef TESTING_H
#define TESTING_H

#include <QWidget>
#include "Project/TestingScenarioModel.h"
#include "Project/Project.h"

using namespace Project;

namespace Ui {
	class TestingWidget;
}

class TestingWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit TestingWidget(QWidget *parent = 0);
		~TestingWidget();
		void setModel(TestingScenarioModel* model);
		bool hasModel();

	private:
		Ui::TestingWidget *ui;
		TestingScenarioModel* model;
};


#endif // TESTING_H

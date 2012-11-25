#ifndef TESTINGSCENARIOMODEL_H
#define TESTINGSCENARIOMODEL_H

#include <QString>
#include "TrainingPatternModel.h"

namespace Project{

enum TestingScenarioType{
	TEST_BY_DATASET,
	OUTPUT_SPACE_GRAPH,
	TESTING_SCRIPT
};

class TestingScenarioModel{
	public:
		TestingScenarioModel(TestingScenarioType type);
		~TestingScenarioModel();
		void setName(QString name);
		QString getName() const;
		TrainingPatternModel* getDatasetModel();
		TestingScenarioType getType();

	private:
		QString name;
		TestingScenarioType type;
		TrainingPatternModel* datasetModel;
};

}

#endif // TESTINGSCENARIOMODEL_H

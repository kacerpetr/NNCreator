#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QFileInfo>
#include <QString>
#include "TrainingPatternModel.h"
#include "NeuralNetworkModel.h"
#include "LearningConfigModel.h"
#include "TestingScenarioModel.h"

namespace Project{

class Project{
	public:
		Project();
		Project(QString path, QString name);
		~Project();

		QString getName() const;
		QString getPath() const;
		void setName(QString name);
		void setPath(QString path);

		TrainingPatternModel* getTrainingPattern(int index);
		NeuralNetworkModel* getNeuralNetwork(int index);
		LearningConfigModel* getLearningConfig(int index);
		TestingScenarioModel* getTestingScenario(int index);

		int getTrainingPatternCount() const;
		int getNeuralNetworkCount() const;
		int getLearningConfigCount() const;
		int getTestingScenarioCount() const;

		void createTrainingPattern(QString name);
		void createNeuralNetwork(QString name);
		void createLearningConfig(QString name);
		void createTestingScenario(QString name, TestingScenarioType type);

		void removeTrainingPattern(int index);
		void removeNeuralNetwork(int index);
		void removeLearningConfig(int index);
		void removeTestingScenario(int index);

		QString getTrainingPatternName(int index) const;
		QString getNeuralNetworkName(int index) const;
		QString getLearningConfigName(int index) const;
		QString getTestingScenarioName(int index) const;

	private:
		QString name;
		QString path;
		QList<TrainingPatternModel*> trainingPattern;
		QList<NeuralNetworkModel*> neuralNetwork;
		QList<LearningConfigModel*> learningConfig;
		QList<TestingScenarioModel*> testingScenario;
};

}

#endif // PROJECT_H

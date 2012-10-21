#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QFileInfo>
#include "NeuralNetwork/AbstractTrainingPattern.h"
#include "NeuralNetwork/AbstractNeuralNetwork.h"
#include "NeuralNetwork/AbstractLearningMachine.h"

using namespace NeuralNetwork;

namespace Project{

class Project{
	public:
		Project();
		Project(QString path, QString name);
		~Project();

		AbstractNeuralNetwork* getNeuralNetwork(int index);
		AbstractTrainingPattern* getTrainingPattern(int index);
		AbstractLearningMachine* getLearningMachine(int index);

		QFileInfo& getNeuralNetworkFile(int index);
		QFileInfo& getTrainingPatternFile(int index);
		QFileInfo& getLearningMachineFile(int index);

		int getNeuralNetworkCount() const;
		int getTrainingPatternCount() const;
		int getLearningMachineCount() const;
		int getGraphCount() const;

		void createNeuralNetwork();
		void createTrainingPattern();
		void createLearningMachine();

		void removeNeuralNetwork(int index);
		void removeTrainingPattern(int index);
		void removeLearningMachine(int index);

		QString getName() const;
		void setName(QString name);

		QString getPath() const;
		void setPath(QString path);

	private:
		QList<AbstractNeuralNetwork*> neuralNetwork;
		QList<AbstractTrainingPattern*> trainingPattern;
		QList<AbstractLearningMachine*> learningMachine;
		QList<QFileInfo> neuralNetworkFile;
		QList<QFileInfo> trainingPatternFile;
		QList<QFileInfo> learningMachineFile;
		QString name;
		QString path;
};

}

#endif // PROJECT_H

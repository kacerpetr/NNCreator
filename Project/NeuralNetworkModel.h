#ifndef NEURALNETWORKMODEL_H
#define NEURALNETWORKMODEL_H

#include <QString>

class NeuralNetworkModel{
	public:
		NeuralNetworkModel();
		void setName(QString name);
		QString getName() const;

	private:
		QString name;
};

#endif // NEURALNETWORKMODEL_H

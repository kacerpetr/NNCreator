#ifndef TOPOLOGYEDITMODEL_H
#define TOPOLOGYEDITMODEL_H

#include <QString>
#include "NeuralNetwork/MlnNetSt.h"
#include "BaseModel.h"
using namespace NeuralNetwork;

/**
 * Contains data models and classes related with project.
 */
namespace Project{

/**
 * Data model of neural network topology editor.
 */
class TopologyEditModel : public QObject, public BaseModel{
	Q_OBJECT

	public:
		TopologyEditModel();
		void duplicateLayer(int layer);
		void removeLayer(int layer);
		void appendLayer();
		void setNeuronCount(int layer, int count);
		int neuronCount(int layer);
		QList<double> weights(int layer, int neuron);
		int weightCount(int layer);
		int inputCount();
		int layerCount();
		void save();
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);
		void randomizeWeights();
		void randomizeBias();
		void setWeightSeed(int value);
		void setWeightMin(double value);
		void setWeightMax(double value);
		void setBiasSeed(int value);
		void setBiasMin(double value);
		void setBiasMax(double value);
		int weightSeed() const;
		double weightMin() const;
		double weightMax() const;
		int biasSeed() const;
		double biasMin() const;
		double biasMax() const;
		int weightCount() const;
		int neuronCount() const;
		int outputCount() const;

	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);

	private:
		double wgSeed;
		double wgMin;
		double wgMax;
		double bsSeed;
		double bsMin;
		double bsMax;
		MlnNetSt net;
};

}
#endif // TOPOLOGYEDITMODEL_H

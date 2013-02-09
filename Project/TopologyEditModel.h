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
		void save();
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);

	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);

	private:
		MlnNetSt net;
};

}
#endif // TOPOLOGYEDITMODEL_H

#ifndef TOPOLOGYEDITMODEL_H
#define TOPOLOGYEDITMODEL_H

#include <QString>
#include "NeuralNetwork/MlnNetSt.h"
#include "BaseModel.h"
using namespace NeuralNetwork;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Data model of neural network topology editor.
 */
class TopologyEditModel : public BaseModel, public MlnNetSt{
	Q_OBJECT

	public:
		/** Class constructor. */
		TopologyEditModel();

		/** Class destructor. */
		virtual ~TopologyEditModel();

		/** Saves model to file. */
		void save();

		/** Randomizes weights of all neurons in neural network. */
		void randomizeWeights();

		/** Randomizes biases of all neurons in neural network. */
		void randomizeBiases();

		/** Sets seed for random weight generation. */
		void setWeightSeed(int value);

		/** Returns seed for random weight generation. */
		int weightSeed() const;

		/** Sets minimal random weight value. */
		void setWeightMin(double value);

		/** Returns minimal random weight value. */
		double weightMin() const;

		/** Sets maximal random weight value. */
		void setWeightMax(double value);

		/** Returns maximal random weight value. */
		double weightMax() const;

		/** Sets seed for random bias generation. */
		void setBiasSeed(int value);

		/** Returns seed for random bias generation. */
		int biasSeed() const;

		/** Sets minimal random bias value. */
		void setBiasMin(double value);

		/** Returns minimal random bias value. */
		double biasMin() const;

		/** Sets maximal random bias value. */
		void setBiasMax(double value);

		/** Returns maximal random bias value. */
		double biasMax() const;

	private:
		/** Seed for random weight generation. */
		double wgSeed;
		/** Minimal random weight value. */
		double wgMin;
		/** Maximal random weigth value. */
		double wgMax;
		/** Seed for random bias generation. */
		double bsSeed;
		/** Minimal random bias value. */
		double bsMin;
		/** Maximal random bias value. */
		double bsMax;
};

}
#endif // TOPOLOGYEDITMODEL_H

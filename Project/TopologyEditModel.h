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
		virtual void save();

		/** Randomizes weights of all neurons in neural network. */
		void randomizeWeights();

		/** Randomizes biases of all neurons in neural network. */
		void randomizeBiases();

        /** Randomizes biases of all neurons in neural network. */
        void randomizeSlopes();

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

        /** Sets seed for random slope generation. */
        void setSlopeSeed(int value);

        /** Returns seed for random slope generation. */
        int slopeSeed() const;

        /** Sets minimal random slope value. */
        void setSlopeMin(double value);

        /** Returns minimal random slope value. */
        double slopeMin() const;

        /** Sets maximal random slope value. */
        void setSlopeMax(double value);

        /** Returns maximal random slope value. */
        double slopeMax() const;

		/** Sets selected layer id. */
		void setSelectedLayer(int layer);

		/** Returns selected layer's id */
		int selectedLayer() const;

		/** Returns common transfer function of neurons. */
		TransferFcn transferFunction();

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
        /** Seed for random slope generation. */
        double slpSeed;
        /** Minimal random slope value. */
        double slpMin;
        /** Maximal random slope value. */
        double slpMax;
		/** Selected layer */
		int layer;
};

}
#endif // TOPOLOGYEDITMODEL_H

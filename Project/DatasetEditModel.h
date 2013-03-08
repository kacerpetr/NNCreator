#ifndef DATASETEDITMODEL_H
#define DATASETEDITMODEL_H

#include "BaseModel.h"
#include "DatasetViewModel.h"
using namespace NeuralNetwork;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Data model for editor of training and testing datasets.
 */
class DatasetEditModel : public BaseModel, public Dataset{
	Q_OBJECT

	public:
		/** DatasetEditModel class constructor. */
		DatasetEditModel();

		/** Class destructor. */
		~DatasetEditModel();

		/** Saves model to file. */
		virtual void save();

		/** Sets pattern count of dataset. */
		void setPatternCount(int count);

		/** Sets output count of dataset. */
		void setInputCount(int count);

		/** Sets input count of dataset. */
		void setOutputCount(int count);

		/** Returns dataset table view model. */
		DatasetViewModel* viewModel();

	private:
		/** Dataset table view pointer. */
		DatasetViewModel* viewMdl;
};

}

#endif // TRAININGPATTERNMODEL_H

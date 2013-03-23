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
		DatasetEditModel();
		~DatasetEditModel();
		virtual void save();
		void setPatternCount(int count);
		void setInputCount(int count);
		void setOutputCount(int count);
		DatasetViewModel* viewModel();

	private slots:
		void dataChanged();

	private:
		/** Dataset table view pointer. */
		DatasetViewModel* viewMdl;
};

}

#endif // TRAININGPATTERNMODEL_H

#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>

/**
 * Contains data models and classes related with project.
 */
namespace Project{

/** Project data model types. */
enum ModelType{
	DatasetEdit = 0, /**< Dataset editor model. */
	TopologyEdit = 1, /**< Topology editor model. */
	LearningConfig = 2, /**< Learning configuration model. */
	DatasetTest = 3, /**< Dataset test model. */
	GraphTest = 4 /**< Output graph model. */
};

/**
 * Base class of project data models.
 */
class BaseModel{
	public:
		BaseModel(ModelType modelType);
		ModelType getModelType() const;
		QString getName() const;
		void setName(QString name);
		bool isSaved() const;

	protected:
		inline void setSaved(bool saved);

	private:
		ModelType mdlType;
		QString mdlName;
		bool mdlSaved;
};

}
#endif // BASEMODEL_H

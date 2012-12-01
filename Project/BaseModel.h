#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>

namespace Project{

enum ModelType{
	DatasetEdit = 0,
	TopologyEdit = 1,
	LearningConfig = 2,
	DatasetTest = 3,
	GraphTest = 4
};

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

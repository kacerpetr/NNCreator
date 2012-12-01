#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QFileInfo>
#include <QString>
#include "DatasetEditModel.h"
#include "TopologyEditModel.h"
#include "LearningConfigModel.h"
#include "DatasetTestModel.h"
#include "GraphTestModel.h"

namespace Project{

class Project{
	public:
		Project();
		Project(QString path, QString name);
		~Project();
		QString getName() const;
		QString getPath() const;
		void setName(QString name);
		void setPath(QString path);
		BaseModel* getModel(int index);
		BaseModel* getModel(int index, const ModelType type);
		void createModel(QString name, ModelType type);
		void removeModel(int index);
		int count(const ModelType type) const;
		QString getModelName(int index, const ModelType type) const;

	private:
		QString name;
		QString path;
		QList<BaseModel*> model;
};

}

#endif // PROJECT_H

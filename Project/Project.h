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

/**
 * Contains data models and classes related with project.
 */
namespace Project{

/**
 * Project class, contains project data models.
 */
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
		BaseModel* lastModel();
		void createModel(QString name, QString path, ModelType type);
		void removeModel(int index);
		int count(const ModelType type) const;
		QString getModelName(int index, const ModelType type) const;
		QList<BaseModel*> getOpenedItems();

	private:
		void openFile(BaseModel* model);

	private:
		QString name;
		QString path;
		QList<BaseModel*> model;
};

}

#endif // PROJECT_H

#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QFileInfo>
#include <QString>
#include "Util/globaldef.h"
#include "BaseModel.h"
#include <QObject>

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

class BaseModel;

/**
 * Project class, contains project data models.
 */
class Project : public QObject{
	Q_OBJECT

	public:
		Project();
		Project(QString path, QString name);
		~Project();
		QString getName() const;
		QString path() const;
		void setName(QString name);
		void setPath(QString path);
		BaseModel* getModel(int index);
		BaseModel* getModel(int index, const ModelType type);
		BaseModel* getModel(QString name, const ModelType type);
		QList<BaseModel*> getRelatedDataset(QString networkName);
		BaseModel* lastModel();
		void createModel(QString name, ModelType type);
		int count(const ModelType type) const;
		int count() const;
		QString getModelName(int index, const ModelType type) const;
		QList<BaseModel*> getOpenedItems();
		QList<BaseModel*> unsavedItems();
		void openModel(QString path, ModelType type);
		bool save();
		void emitModelRenamed(QString newName, QString oldName, ModelType type);
		void removeModel(BaseModel* mdl);

	private:
		void openFile(BaseModel* model);

	signals:
		void modelRenamed(QString, QString, ModelType);
		void modelDeleted(QString, ModelType);

	private:
		QString name;
		QString pathVal;
		QList<BaseModel*> model;
};

}

#endif // PROJECT_H

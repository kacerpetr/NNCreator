#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>
#include <QObject>

/**
 * Contains data models and classes related with project.
 */
namespace Project{

/** Project data model types. */
enum ModelType{
	DatasetEdit,    /**< Dataset editor model. */
	TopologyEdit,   /**< Topology editor model. */
	LearningConfig, /**< Learning configuration model. */
	DatasetTest,    /**< Dataset test model. */
	GraphTest       /**< Output graph model. */
};

/**
 * Base class of project data models.
 */
class BaseModel{
	public:
		BaseModel(ModelType modelType);
		void setName(QString name);
		void setPath(QString path);
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);
		void setProjectPath(QString path);
		QString projectPath();
		ModelType type() const;
		QString name() const;
		QString path() const;
		bool isSaved() const;
		bool isOpened() const;
		virtual void save() = 0;
		QString folder() const;

	protected:
		bool mdlSaved;
		bool mdlOpened;
		QString prjPath;

	private:
		ModelType mdlType;
		QString mdlName;
		QString mdlPath;
};

}
#endif // BASEMODEL_H

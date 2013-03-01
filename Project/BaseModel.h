#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QObject>
#include "Util/globaldef.h"
#include "NeuralNetwork/BpAlgSt.h"
#include "NeuralNetwork/MlnNetSt.h"
#include "NeuralNetwork/Dataset.h"
#include "Project.h"

using namespace NeuralNetwork;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

//forward declaration of Project class
class Project;

/**
 * Base class of project data models.
 */
class BaseModel : public QObject{
	Q_OBJECT

	public:
		/** Class constructor. */
		BaseModel(ModelType modelType);

		/** Returns information about type of descendant. */
		ModelType type() const;

		/** Sets name of model. */
		void setName(QString name);

		/** Returns name of model. */
		QString name() const;

		/** Sets pointer to model's project. */
		void setProject(Project* prj);

		/** Returns pointer to model's project. */
		Project* project();

		/** Sets project to opened or closed state. */
		void setOpened(bool state);

		/** Checks if project is in opened or closed state. */
		bool isOpened() const;

		/** Sets project to saved or unsaved state. */
		void setSaved(bool state);

		/** Checks if project is in saved or unsaved state. */
		bool isSaved() const;

		/** Returns absolute path to model file. */
		QString pathName() const;

		/** Retruns file name of model. */
		QString fileName() const;

		/** Returns relative path to model file from model folder. */
		QString relPathName() const;

		/** Returns absolute path of folder where model is / will be saved. */
		QString path() const;

		/** Returns absolute path of model's project. */
		QString projectPath() const;

		/** Returns name of folder of models with current model's type. */
		QString folder() const;

		/** Emits changed signal. */
		virtual void modelChanged(ChangeType type);

	protected:
		/** Model's project pointer. */
		Project* prj;

	public slots:
		/** All model must implement save method. */
		virtual void save() = 0;

	signals:
		/** Emited when model is opened or closed. */
		void opened(BaseModel*);
		/** Emited when model is saved or modified first time. */
		void saved(BaseModel*);
		/** Emited when model's content is changed. */
		void changed(ChangeType);

	private:
		/** True if model is saved */
		bool mdlSaved;
		/** True if model is opened */
		bool mdlOpened;
		/** Type of descendant model class */
		ModelType mdlType;
		/** Name of model. */
		QString mdlName;
};

}
#endif // BASEMODEL_H

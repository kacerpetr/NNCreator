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

		/** Returns absolute path of folder where model will be saved. */
		QString path() const;

		/** Returns absolute path of model's project folder */
		QString projectPath() const;

		/** Returns name of folder of models with current model's type. */
		QString folder() const;

		/** Sets new model name, renames model file end emits rename signal. */
		void rename(QString name);

		/** Emits changed signal. */
		void modelChanged(ChangeType type);

		///// selection of network or dataset, that are needed by some models to work /////

		/** Returns name of selected neural network. */
		QString selectedNetworkName();

		/** Returns name of selected dataset. */
		QString selectedDatasetName();

		/** Returns pointer of selected neural network. */
		BaseModel* selectedNetwork();

		/** Returns pointer of selected dataset. */
		BaseModel* selectedDataset();

		/** Selects network with given name. */
		void selectNetwork(QString name);

		/** Selects dataset with given name. */
		void selectDataset(QString name);

		/** Returns list of names of selectable neural networks. */
		QStringList networkList();

		/** Returns list of names of selectable datasets determined by selected network. */
		QStringList datasetList(QString name);

	public slots:
		/** All model must implement save method. */
		virtual void save() = 0;

	private slots:
		void selectedModelRenamed(QString newName, QString oldName, ModelType type);
		void selectedModelDeleted(QString name, ModelType type);

	signals:
		/** Emited when model is opened or closed. */
		void opened(BaseModel*);

		/** Emited when model is saved or modified first time. */
		void saved(BaseModel*);

		/** Emited when model's content is changed. */
		void changed(ChangeType);

	private:
		/** Model's project pointer. */
		Project* prj;

		/** True if model is saved */
		bool mdlSaved;

		/** True if model is opened */
		bool mdlOpened;

		/** Type of descendant model class */
		ModelType mdlType;

		/** Name of model. */
		QString mdlName;

		///// selection of network or dataset, that are needed by some models to work /////

		/** Name of selected dataset */
		QString selSet;

		/** Name of selected neural network */
		QString selNet;
};

}
#endif // BASEMODEL_H

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
		BaseModel(ModelType modelType);
		ModelType type() const;
		void setName(QString name);
		QString name() const;
		void setProject(Project* prj);
		Project* project();
		void setOpened(bool state);
		bool isOpened() const;
		void setSaved(bool state);
		bool isSaved() const;
		QString pathName() const;
		QString fileName() const;
		QString relPathName() const;
		QString path() const;
		QString projectPath() const;
		QString folder() const;
		void rename(QString name);
		bool remove();
        QStringList otherPlot();
		void modelChanged(ChangeType type);
		void reload();

		///// selection of network or dataset, that are needed by some models to work /////
        QString selectedNetworkName();
		QString selectedDatasetName();
        BaseModel* selectedNetwork();
		BaseModel* selectedDataset();
		void selectNetwork(QString name);
		void selectDataset(QString name);
		QStringList networkList();
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

    protected:
        /** Model's project pointer. */
        Project* prj;

	private:
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

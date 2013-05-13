/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QObject>
#include "Util/Globaldef.h"
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

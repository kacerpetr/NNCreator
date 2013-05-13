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

#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QFileInfo>
#include <QString>
#include "Util/Globaldef.h"
#include "BaseModel.h"
#include <QObject>

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

//forward deflaration of BaseModel class
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
        void duplicateModel(int index, QString copyName, ModelType type);
		int count(const ModelType type) const;
		int count() const;
		QString getModelName(int index, const ModelType type) const;
		QList<BaseModel*> getOpenedItems();
		QList<BaseModel*> unsavedItems();
		void openModel(QString path, ModelType type);
		bool save();
		void emitModelRenamed(QString newName, QString oldName, ModelType type);
		void removeModel(BaseModel* mdl);
		void reloadModel(BaseModel* mdl);
		void unloadModel(BaseModel* mdl);

	private:
		void openFile(BaseModel* model);

	signals:
        /** Emitted when model is renamed. */
        void modelRenamed(QString, QString, ModelType);
        /** Emitted when model is deleted. */
        void modelDeleted(QString, ModelType);

	private:
        /** Name of project. */
		QString name;
        /** Absolute path of project. */
		QString pathVal;
        /** List of models in project. */
		QList<BaseModel*> model;
};

}

#endif // PROJECT_H

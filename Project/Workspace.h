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

#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QList>
#include <QAbstractItemModel>
#include "Project.h"

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Workspace class, contains all opened projects, serves as datamodel of project tree.
 */
class Workspace : public QAbstractItemModel{
	Q_OBJECT

	public:
		Workspace(QObject* parent = 0);
		~Workspace();

		////////////////////////////////////////////////////////////////
		//////// AbstractItemModel methods /////////////////////////////
		////////////////////////////////////////////////////////////////

		QVariant data(const QModelIndex &index, int role) const;
		QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

		////////////////////////////////////////////////////////////////
		//////// Workspace management methods //////////////////////////
		////////////////////////////////////////////////////////////////

		void createProject(QString path, QString name);
		void createDataset(const QModelIndex& prj, QString name);
        void duplicateDataset(const QModelIndex& index, QString name);
		void createNeuralNetwork(const QModelIndex& prj, QString name);
		void createLearningConfig(const QModelIndex& prj, QString name);
		void createDatasetTest(const QModelIndex& prj, QString name);
		void createGraphTest(const QModelIndex& prj, QString name);
		BaseModel* getModel(const QModelIndex& index);
		QList<BaseModel*> getOpenedItems();
		QList<BaseModel*> unsavedItems();
		BaseModel* firstOpened();
		bool openProject(QString file);
		Project* project(QModelIndex& index);
		void closeProject(QModelIndex& index);
		void removeModel(QModelIndex& index);
		void reloadModel(BaseModel* mdl);

		////////////////////////////////////////////////////////////////
		//////// Static Metods /////////////////////////////////////////
		////////////////////////////////////////////////////////////////

		static bool isProjectIndex(const QModelIndex& index);
		static bool isCategoryIndex(const QModelIndex& index);
		static bool isItemIndex(const QModelIndex& index);
		static int getProjectId(const QModelIndex& index);
		static int getCategoryId(const QModelIndex& index);
		static int getItemId(const QModelIndex& index);

	private:
        /** List of opened project. */
		QList<Project*> prj;
};

}

#endif // WORKSPACE_H

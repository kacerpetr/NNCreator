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
		QList<Project*> prj;
};

}

#endif // WORKSPACE_H

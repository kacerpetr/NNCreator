#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QList>
#include <QAbstractItemModel>
#include "Project.h"

namespace Project{

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
		void createDataset(const QModelIndex& project, QString name);
		void createNeuralNetwork(const QModelIndex& project, QString name);
		void createLearningConfig(const QModelIndex& project, QString name);
		void createDatasetTest(const QModelIndex& project, QString name);
		void createGraphTest(const QModelIndex& project, QString name);
		BaseModel* getModel(const QModelIndex& index);

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
		QList<Project> project;
};

}

#endif // WORKSPACE_H

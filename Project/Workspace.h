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
		void createTrainingPattern(const QModelIndex& index, QString name);
		void createNeuralNetwork(const QModelIndex& index, QString name);
		void createLearningConfig(const QModelIndex& index, QString name);
		void createTestingScenario(const QModelIndex& index, QString name, TestingScenarioType type);

		Project& getProject(int index);
		int getProjectCount();

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

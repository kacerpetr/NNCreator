#ifndef EDIT_H
#define EDIT_H

#include <QWidget>
#include <QMenu>
#include <QModelIndex>
#include "TrainingPatterns.h"
#include "Topology.h"
#include "Learning.h"
#include "Testing.h"
#include "Project/Workspace.h"

using namespace Project;

namespace Ui{
	class Edit;
}

class Edit : public QWidget{
	Q_OBJECT

	public:
		explicit Edit(QWidget *parent = 0);
		~Edit();
		void connectSignalSlot();
		void setWidget(int id);
		void hideAll(void);
		Workspace* getWorkspace();

	public slots:
		void showContextMenu();
		void newProject();
		void newTrainingPattern();
		void newNeuralNetwork();
		void newLearningConfig();
		void newTestingScenario();

	private:
		Ui::Edit *ui;
		TrainingPatterns* trainingPatterns;
		Topology* topology;
		Learning* learning;
		Testing* testing;
		Workspace* workspace;
		QMenu* contextMenu;
};

#endif // EDIT_H

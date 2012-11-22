#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "WelcomeWidget.h"
#include "TrainingPatternWidget.h"
#include "TopologyWidget.h"
#include "LearningWidget.h"
#include "TestingWidget.h"
#include "HelpWidget.h"
#include "NoModelWidget.h"
#include "Project/Workspace.h"

using namespace Project;

namespace Ui{
	class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT
		
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		void initLayout();
		void initWorkspace();
		void connectSignalSlot();
		void checkMainButtons(int button);

	public slots:
		void showAboutDialog();
		void showAboutQt();
		void editMenuItemPressed(int button);
		void showContextMenu();
		void projectViewTreeClick(QModelIndex index);

		void newProject();
		void newTrainingPattern();
		void newNeuralNetwork();
		void newLearningConfig();
		void newTestingScenario();

	private:
		// Main application widgets
		WelcomeWidget* welcome;
		TrainingPatternWidget* trainingPattern;
		TopologyWidget* topology;
		LearningWidget* learning;
		TestingWidget* testing;
		HelpWidget* help;
		NoModelWidget* noModel;
		//Other variables
		Ui::MainWindow *ui;
		Workspace* workspace;
};

#endif // MAINWINDOW_H

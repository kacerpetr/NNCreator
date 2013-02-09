#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include "WelcomeWidget.h"
#include "DatasetEditWidget.h"
#include "TopologyWidget.h"
#include "LearningWidget.h"
#include "DatasetTestWidget.h"
#include "HelpWidget.h"
#include "NoModelWidget.h"
#include "OutputGraphWidget.h"
#include "Project/Workspace.h"

using namespace Project;
namespace Ui{class MainWindow;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The MainWindow class.
 */
class MainWindow : public QMainWindow{
	Q_OBJECT
		
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		void setWidget(QWidget* widget);
		void setModel(BaseModel* model);
		void checkMainButtons(int button);
		void updateOpenedList();

	public slots:
		void showAboutDialog();
		void showAboutQt();
		void editMenuItemPressed(int button);
		void showContextMenu();
		void projectViewTreeClick(QModelIndex index);
		void showHelp();

		void newProject();
		void newTrainingPattern();
		void newNeuralNetwork();
		void newLearningConfig();
		void newDatasetTest();
		void newGraphTest();

		void closeEdit(BaseModel* mdl);

	private:
		// Main application widgets
		NoModelWidget* noModel;
		WelcomeWidget* welcome;
		DatasetEditWidget* dataset;
		TopologyWidget* topology;
		LearningWidget* learning;
		DatasetTestWidget* datasetTest;
		OutputGraphWidget* graphTest;
		HelpWidget* help;

		//Other variables
		Ui::MainWindow *ui;
		Workspace* workspace;
		QWidget* currentWidget;
};

}

#endif // MAINWINDOW_H

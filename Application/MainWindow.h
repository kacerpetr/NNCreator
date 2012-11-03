#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "Welcome.h"
#include "Edit.h"
#include "Help.h"
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
		void connectSignalSlot();
		void enableEdit();

	public slots:
		void newProject();
		void openProject();
		void showAboutDialog();
		void editMenuItemPressed(int button);
		void aboutQt();
		
	private:
		Ui::MainWindow *ui;
		Welcome* welcome;
		Edit* edit;
		Help* help;
		QWidget* editWidget;
		QLabel* statusBarLabel;
};

#endif // MAINWINDOW_H

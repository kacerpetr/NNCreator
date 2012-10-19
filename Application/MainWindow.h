#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "Welcome.h"
#include "Edit.h"
#include "Help.h"

namespace Ui{
	class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT
		
	public:
		explicit MainWindow(QWidget *parent = 0);
		void connectSignalSlots();
		~MainWindow();

	public slots:
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtTest/QtTest>
#include "Welcome.h"
#include "Edit.h"
#include "Help.h"
#include "QMessageBox"
#include "Dialog/TextViewBox.h"

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
		void runTests();
		void slotDataOnStdout();
		void slotStderr();
		void slotProcessError();
		void slotProcessStart();
		void slotProcessFinish(int);
		
	private:
		Ui::MainWindow *ui;
		Welcome* welcome;
		Edit* edit;
		Help* help;
		QWidget* editWidget;
		QProcess process;
		TextViewBox txtBox;
};

#endif // MAINWINDOW_H

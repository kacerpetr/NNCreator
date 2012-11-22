#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include "Dialog/AboutDialog.h"
#include "Dialog/NewProjectDialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
	ui->setupUi(this);
	initLayout();
	initWorkspace();
	connectSignalSlot();
}

MainWindow::~MainWindow(){
	delete welcome;
	delete trainingPattern;
	delete topology;
	delete learning;
	delete testing;
	delete help;
	delete ui;
	delete workspace;
}

///////////////////////////////////////////////////////////////////
///////// Public methods //////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void MainWindow::initLayout(){
	welcome = new WelcomeWidget(this);
	trainingPattern = new TrainingPatternWidget(this);
	topology = new TopologyWidget(this);
	learning = new LearningWidget(this);
	testing = new TestingWidget(this);
	help = new HelpWidget(this);
	noModel = new NoModelWidget(this);

	ui->projectViewFrame->hide();
	trainingPattern->hide();
	topology->hide();
	learning->hide();
	testing->hide();
	help->hide();
	noModel->hide();
	ui->welcomeButton->setChecked(true);

	ui->projectView->addWidget(welcome);
	ui->projectView->addWidget(trainingPattern);
	ui->projectView->addWidget(topology);
	ui->projectView->addWidget(learning);
	ui->projectView->addWidget(testing);
	ui->projectView->addWidget(help);
	ui->projectView->addWidget(noModel);
}

void MainWindow::initWorkspace(){
	workspace = new Workspace(this);
	ui->projectViewTree->setModel(workspace);
}

void MainWindow::connectSignalSlot(){
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
	connect(ui->actionAboutQt4, SIGNAL(triggered()), this, SLOT(showAboutQt()));
	connect(ui->buttonGroup, SIGNAL(buttonPressed(int)), this, SLOT(editMenuItemPressed(int)));
	connect(ui->projectViewTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
	connect(ui->projectViewTree, SIGNAL(pressed(QModelIndex)), this, SLOT(projectViewTreeClick(QModelIndex)));
	connect(ui->actionNewProject, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui->actionNewTrainingPattern, SIGNAL(triggered()), this, SLOT(newTrainingPattern()));
	connect(ui->actionNewNeuralNetwork, SIGNAL(triggered()), this, SLOT(newNeuralNetwork()));
	connect(ui->actionNewLearningConfig, SIGNAL(triggered()), this, SLOT(newLearningConfig()));
	connect(ui->actionNewTestingScenario, SIGNAL(triggered()), this, SLOT(newTestingScenario()));
}

///////////////////////////////////////////////////////////////////
///////// Slots ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void MainWindow::showAboutDialog(){
	AboutDialog ad;
	ad.exec();
}

void MainWindow::showAboutQt(){
	QMessageBox::aboutQt(this);
}

void MainWindow::editMenuItemPressed(int button){
	welcome->hide();
	trainingPattern->hide();
	topology->hide();
	learning->hide();
	testing->hide();
	help->hide();
	noModel->hide();
	ui->projectViewFrame->hide();

	switch(abs(button)){
		case 2:
			welcome->show();
			break;
		case 3:
			ui->projectViewFrame->show();
			if(trainingPattern->hasModel()){
				trainingPattern->show();
			}else{
				noModel->show();
			}
			break;
		case 4:
			ui->projectViewFrame->show();
			if(topology->hasModel()){
				topology->show();
			}else{
				noModel->show();
			}
			break;
		case 5:
			ui->projectViewFrame->show();
			if(learning->hasModel()){
				learning->show();
			}else{
				noModel->show();
			}
			break;
		case 6:
			ui->projectViewFrame->show();
			if(testing->hasModel()){
				testing->show();
			}else{
				noModel->show();
			}
			break;
		case 7:
			help->show();
			break;
	}
}

void MainWindow::checkMainButtons(int button){
	ui->welcomeButton->setChecked(false);
	ui->trainingPatternButton->setChecked(false);
	ui->topologyButton->setChecked(false);
	ui->learningButton->setChecked(false);
	ui->testingButton->setChecked(false);
	ui->helpButton->setChecked(false);

	switch(abs(button)){
		case 2:
			ui->welcomeButton->setChecked(true);
			break;
		case 3:
			ui->trainingPatternButton->setChecked(true);
			break;
		case 4:
			ui->topologyButton->setChecked(true);
			break;
		case 5:
			ui->learningButton->setChecked(true);
			break;
		case 6:
			ui->testingButton->setChecked(true);
			break;
		case 7:
			ui->helpButton->setChecked(true);
			break;
	}
}

void MainWindow::showContextMenu(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	QMenu menu;

	if(item.isEmpty() || !item[0].isValid()){
		menu.addAction("New project" , this , SLOT(newProject()));
	}
	else if(Workspace::isProjectIndex(item[0])){
		menu.addAction("New project" , this , SLOT(newProject()));
		menu.addAction("Close project" , this , SLOT(newTrainingPattern()));
		menu.addAction("Delete project" , this , SLOT());
		menu.addSeparator();
		menu.addAction("New training pattern" , this , SLOT(newTrainingPattern()));
		menu.addAction("New neural network" , this , SLOT(newNeuralNetwork()));
		menu.addAction("New learning configuration" , this , SLOT(newLearningConfig()));
		menu.addAction("New testing scenario" , this , SLOT(newTestingScenario()));
	}
	else if(Workspace::isCategoryIndex(item[0])){
		switch(Workspace::getCategoryId(item[0])){
			case 0:
				menu.addAction("New training pattern" , this , SLOT(newTrainingPattern()));
				menu.addAction("Clear training patterns" , this , SLOT());
				break;
			case 1:
				menu.addAction("New neural network" , this , SLOT(newNeuralNetwork()));
				menu.addAction("Clear neural networks" , this , SLOT());
				break;
			case 2:
				menu.addAction("New learning configuration" , this , SLOT(newLearningConfig()));
				menu.addAction("Clear learning configurations" , this , SLOT());
				break;
			case 3:
				menu.addAction("New testing scenario" , this , SLOT(newTestingScenario()));
				menu.addAction("Clear testing scenarios" , this , SLOT());
		}
	}
	else if(Workspace::isItemIndex(item[0])){
		switch(Workspace::getCategoryId(item[0])){
			case 0:
				menu.addAction("Delete" , this , SLOT());
				menu.addAction("Copy" , this , SLOT());
				menu.addAction("Paste" , this , SLOT());
				break;
			case 1:
				menu.addAction("Delete" , this , SLOT());
				menu.addAction("Copy" , this , SLOT());
				menu.addAction("Paste" , this , SLOT());
				break;
			case 2:
				menu.addAction("Delete" , this , SLOT());
				menu.addAction("Copy" , this , SLOT());
				menu.addAction("Paste" , this , SLOT());
				break;
			case 3:
				menu.addAction("Delete" , this , SLOT());
				menu.addAction("Copy" , this , SLOT());
				menu.addAction("Paste" , this , SLOT());
				break;
		}
	}

	menu.popup(QCursor::pos());
	menu.exec();
}

void MainWindow::projectViewTreeClick(QModelIndex index){
	if(Workspace::isItemIndex(index)){
		int projectId = Workspace::getProjectId(index);
		int itemId = Workspace::getItemId(index);
		switch(Workspace::getCategoryId(index)){
			case 0:
				qDebug() << projectId << " " << itemId;
				trainingPattern->setModel(workspace->getProject(projectId).getTrainingPattern(itemId));
				break;
			case 1:
				topology->setModel(workspace->getProject(projectId).getNeuralNetwork(itemId));
				break;
			case 2:
				learning->setModel(workspace->getProject(projectId).getLearningConfig(itemId));
				break;
			case 3:
				testing->setModel(workspace->getProject(projectId).getTestingScenario(itemId));
				break;
		}
		editMenuItemPressed(Workspace::getCategoryId(index)+3);
		checkMainButtons(Workspace::getCategoryId(index)+3);
	}
}

void MainWindow::newProject(){
	NewProjectDialog dialog;
	dialog.exec();
	if(dialog.isConfirmed()){
		workspace->createProject(dialog.getPath(), dialog.getName());
		QModelIndex lastProjectIndex = workspace->index(workspace->getProjectCount()-1);
		ui->projectViewTree->expand(lastProjectIndex);
		ui->trainingPatternButton->click();
	}
}

void MainWindow::newTrainingPattern(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;
	QString header = tr("Create new training pattern");
	QString label = tr("Pattern name:");
	bool ok;
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);
	if(ok && !name.isEmpty()){
		workspace->createTrainingPattern(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

void MainWindow::newNeuralNetwork(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;
	QString header = tr("Create new neural network");
	QString label = tr("Neural network name:");
	bool ok;
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);
	if(ok && !name.isEmpty()){
		workspace->createNeuralNetwork(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

void MainWindow::newLearningConfig(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;
	QString header = tr("Create new learning config");
	QString label = tr("Learning config name:");
	bool ok;
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);
	if(ok && !name.isEmpty()){
		workspace->createLearningConfig(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

void MainWindow::newTestingScenario(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;
	QString header = tr("Create new testing scenario");
	QString label = tr("Testing scenario name:");
	bool ok;
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);
	if(ok && !name.isEmpty()){
		workspace->createTestingScenario(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

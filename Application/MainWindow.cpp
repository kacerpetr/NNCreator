#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include "Dialog/AboutDialog.h"
#include "Dialog/NewProjectDialog.h"
#include "Dialog/NewTestScnDialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
	//setup ui
	ui->setupUi(this);

	// connects signals and slots
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

	//creates edit widgets
	noModel = new NoModelWidget();
	welcome = new WelcomeWidget();
	dataset = new DatasetEditWidget();
	topology = new TopologyWidget();
	learning = new LearningWidget();
	datasetTest = new DatasetTestWidget();
	graphTest = new OutputGraphWidget();
	help = new HelpWidget();

	//adds widgets to stack widget
	ui->windowStack->addWidget(noModel);
	ui->windowStack->addWidget(welcome);
	ui->windowStack->addWidget(dataset);
	ui->windowStack->addWidget(topology);
	ui->windowStack->addWidget(learning);
	ui->windowStack->addWidget(datasetTest);
	ui->windowStack->addWidget(graphTest);
	ui->windowStack->addWidget(help);

	//workspace tree
	workspace = new Workspace(this);
	ui->projectViewTree->setModel(workspace);
	ui->projectViewFrame->hide();

	//control buttons
	ui->welcomeButton->setChecked(true);

	//current widget
	setWidget(welcome);
}

MainWindow::~MainWindow(){
	delete welcome;
	delete dataset;
	delete topology;
	delete learning;
	delete datasetTest;
	delete help;
	delete ui;
	delete workspace;
}

///////////////////////////////////////////////////////////////////
///////// Public methods //////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void MainWindow::setWidget(QWidget* widget){
	//hide all widgets
	noModel->hide();
	welcome->hide();
	dataset->hide();
	topology->hide();
	learning->hide();
	datasetTest->hide();
	graphTest->hide();
	help->hide();

	//sets current widget
	ui->windowStack->setCurrentWidget(widget);
	widget->show();

	//show or hide workspace view
	if(widget != welcome && widget != help){
		ui->projectViewFrame->show();
	}else{
		ui->projectViewFrame->hide();
	}
}

void MainWindow::setModel(BaseModel* model){
	switch(model->getModelType()){
		case DatasetEdit:
			dataset->setModel((DatasetEditModel*)model);
			setWidget(dataset);
			checkMainButtons(3);
			break;

		case TopologyEdit:
			topology->setModel((TopologyEditModel*)model);
			setWidget(topology);
			checkMainButtons(4);
			break;

		case LearningConfig:
			learning->setModel((LearningConfigModel*)model);
			setWidget(learning);
			checkMainButtons(5);
			break;

		case DatasetTest:
			datasetTest->setModel((DatasetTestModel*)model);
			setWidget((datasetTest));
			checkMainButtons(6);
			break;

		case GraphTest:
			graphTest->setModel((GraphTestModel*)model);
			setWidget(graphTest);
			checkMainButtons(6);
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

///////////////////////////////////////////////////////////////////
///////// Slots ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void MainWindow::editMenuItemPressed(int button){
	switch(abs(button)){
		case 2:
			setWidget(welcome);
			break;

		case 3:
			if(dataset->hasModel()){
				setWidget(dataset);
			}else{
				setWidget(noModel);
			}
			break;

		case 4:
			if(topology->hasModel()){
				setWidget(topology);
			}else{
				setWidget(noModel);
			}
			break;

		case 5:
			if(learning->hasModel()){
				setWidget(learning);
			}else{
				setWidget(noModel);
			}
			break;

		case 6:
			if(datasetTest->hasModel()){
				setWidget(datasetTest);
			}else{
				setWidget(noModel);
			}
			break;

		case 7:
			setWidget(help);
			break;
	}
}

void MainWindow::showContextMenu(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	QMenu menu;

	//no item selected
	if(item.isEmpty() || !item[0].isValid()){
		menu.addAction("New project" , this , SLOT(newProject()));
	}

	//project selected
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

	//model category selected
	else if(Workspace::isCategoryIndex(item[0])){
		switch(Workspace::getCategoryId(item[0])){
			case DatasetEdit:
				menu.addAction("New training pattern" , this , SLOT(newTrainingPattern()));
				menu.addAction("Clear training patterns" , this , SLOT());
				break;
			case TopologyEdit:
				menu.addAction("New neural network" , this , SLOT(newNeuralNetwork()));
				menu.addAction("Clear neural networks" , this , SLOT());
				break;
			case LearningConfig:
				menu.addAction("New learning configuration" , this , SLOT(newLearningConfig()));
				menu.addAction("Clear learning configurations" , this , SLOT());
				break;
			case DatasetTest:
				menu.addAction("New dataset test" , this , SLOT(newDatasetTest()));
				menu.addAction("Clear tests" , this , SLOT());
				break;
			case GraphTest:
				menu.addAction("New output graph" , this , SLOT(newGraphTest()));
				menu.addAction("Clear graphs" , this , SLOT());
				break;
		}
	}

	//item selected
	else if(Workspace::isItemIndex(item[0])){
		menu.addAction("Delete" , this , SLOT());
		menu.addAction("Copy" , this , SLOT());
		menu.addAction("Paste" , this , SLOT());
	}

	menu.popup(QCursor::pos());
	menu.exec();
}

void MainWindow::projectViewTreeClick(QModelIndex index){
	if(Workspace::isItemIndex(index)){
		setModel(workspace->getModel(index));
	}
}

void MainWindow::newProject(){
	NewProjectDialog dialog;
	dialog.exec();

	if(dialog.isConfirmed()){
		workspace->createProject(dialog.getPath(), dialog.getName());
		ui->projectViewTree->expandAll();
	}
}

void MainWindow::newTrainingPattern(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString header = tr("Create new training pattern");
	QString label = tr("Pattern name:");
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);

	if(ok && !name.isEmpty()){
		workspace->createDataset(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

void MainWindow::newNeuralNetwork(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString header = tr("Create new neural network");
	QString label = tr("Neural network name:");
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);

	if(ok && !name.isEmpty()){
		workspace->createNeuralNetwork(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

void MainWindow::newLearningConfig(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString header = tr("Create new learning config");
	QString label = tr("Learning config name:");
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);

	if(ok && !name.isEmpty()){
		workspace->createLearningConfig(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

void MainWindow::newDatasetTest(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString header = tr("Create new dataset test");
	QString label = tr("Dataset test name:");
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);

	if(ok && !name.isEmpty()){
		workspace->createDatasetTest(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

void MainWindow::newGraphTest(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString header = tr("Create new graph test");
	QString label = tr("Graph test name:");
	QString name = QInputDialog::getText(this, header, label, QLineEdit::Normal, QString(""), &ok);

	if(ok && !name.isEmpty()){
		workspace->createGraphTest(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

void MainWindow::showAboutDialog(){
	AboutDialog ad;
	ad.exec();
}

void MainWindow::showAboutQt(){
	QMessageBox::aboutQt(this);
}

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include "Dialog/AboutDialog.h"
#include "Dialog/NewProjectDialog.h"

namespace Application{

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
	//setup ui
	ui->setupUi(this);

	//top menubar
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
	connect(ui->actionAboutQt4, SIGNAL(triggered()), this, SLOT(showAboutQt()));
	connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));
	connect(ui->actionNewProject, SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
	connect(ui->actionSaveAll, SIGNAL(triggered()), this, SLOT(saveAll()));
	connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));

	//left control panel
	connect(ui->buttonGroup, SIGNAL(buttonPressed(int)), this, SLOT(editMenuItemPressed(int)));

	//project view tree
	connect(ui->projectViewTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
	connect(ui->projectViewTree, SIGNAL(pressed(QModelIndex)), this, SLOT(projectViewTreeClick(QModelIndex)));

	//creates edit widgets
	noModel = new NoModelWidget();
	welcome = new WelcomeWidget();
	dataset = new DatasetEditWidget();
	topology = new TopologyWidget();
	learning = new LearningWidget();
	datasetTest = new DatasetTestWidget();
	graphTest = new OutputGraphWidget();
	help = new HelpWidget();

	//connects edit widget signals
	connect(dataset, SIGNAL(closePressed(BaseModel*)), this, SLOT(closeEdit(BaseModel*)));
	connect(topology, SIGNAL(closePressed(BaseModel*)), this, SLOT(closeEdit(BaseModel*)));
	connect(learning, SIGNAL(closePressed(BaseModel*)), this, SLOT(closeEdit(BaseModel*)));
	connect(datasetTest, SIGNAL(closePressed(BaseModel*)), this, SLOT(closeEdit(BaseModel*)));
	connect(graphTest, SIGNAL(closePressed(BaseModel*)), this, SLOT(closeEdit(BaseModel*)));

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

	setWidget(welcome);
}

MainWindow::~MainWindow(){
	delete noModel;
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
	if(model == NULL){
		setWidget(noModel);
		return;
	}

	switch(model->type()){
		case DatasetEdit:
			dataset->setModel((DatasetEditModel*)model);
			setWidget(dataset);
			checkMainButtons(-3);
			break;

		case TopologyEdit:
			topology->setModel((TopologyEditModel*)model);
			setWidget(topology);
			checkMainButtons(-4);
			break;

		case LearningConfig:
			learning->setModel((LearningConfigModel*)model);
			setWidget(learning);
			checkMainButtons(-5);
			break;

		case DatasetTest:
			datasetTest->setModel((DatasetTestModel*)model);
			setWidget((datasetTest));
			checkMainButtons(-6);
			break;

		case GraphTest:
			graphTest->setModel((GraphTestModel*)model);
			setWidget(graphTest);
			checkMainButtons(-7);
			break;
	}
}

void MainWindow::checkMainButtons(int button){
	ui->welcomeButton->setChecked(false);
	ui->datasetButton->setChecked(false);
	ui->topologyButton->setChecked(false);
	ui->learningButton->setChecked(false);
	ui->datasetTestButton->setChecked(false);
	ui->graphTestButton->setChecked(false);
	ui->helpButton->setChecked(false);

	switch(button){
		case -2:
			ui->welcomeButton->setChecked(true);
			break;

		case -3:
			ui->datasetButton->setChecked(true);
			break;

		case -4:
			ui->topologyButton->setChecked(true);
			break;

		case -5:
			ui->learningButton->setChecked(true);
			break;

		case -6:
			ui->datasetTestButton->setChecked(true);
			break;

		case -7:
			ui->graphTestButton->setChecked(true);
			break;

		case -8:
			ui->helpButton->setChecked(true);
			break;
	}
}

///////////////////////////////////////////////////////////////////
///////// Slots ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void MainWindow::editMenuItemPressed(int button){
	switch(button){
		case -2:
			setWidget(welcome);
			break;

		case -3:
			if(dataset->hasModel()){
				setWidget(dataset);
			}else{
				setWidget(noModel);
			}
			break;

		case -4:
			if(topology->hasModel()){
				setWidget(topology);
			}else{
				setWidget(noModel);
			}
			break;

		case -5:
			if(learning->hasModel()){
				setWidget(learning);
			}else{
				setWidget(noModel);
			}
			break;

		case -6:
			if(datasetTest->hasModel()){
				setWidget(datasetTest);
			}else{
				setWidget(noModel);
			}
			break;

		case -7:
			if(graphTest->hasModel()){
				setWidget(graphTest);
			}else{
				setWidget(noModel);
			}
			break;

		case -8:
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
		menu.addAction("Open project" , this , SLOT(newProject()));
	}

	//project selected
	else if(Workspace::isProjectIndex(item[0])){
		menu.addAction("New project" , this , SLOT(newProject()));
		menu.addAction("Open project" , this , SLOT(newProject()));
		menu.addAction("Close project" , this , SLOT(newTrainingPattern()));
	}

	//model category selected
	else if(Workspace::isCategoryIndex(item[0])){
		switch(Workspace::getCategoryId(item[0])){
			case DatasetEdit:
				menu.addAction("New dataset" , this , SLOT(newTrainingPattern()));
				break;

			case TopologyEdit:
				menu.addAction("New neural network" , this , SLOT(newNeuralNetwork()));
				break;

			case LearningConfig:
				menu.addAction("New learning configuration" , this , SLOT(newLearningConfig()));
				break;

			case DatasetTest:
				menu.addAction("New dataset test" , this , SLOT(newDatasetTest()));
				break;

			case GraphTest:
				menu.addAction("New output graph" , this , SLOT(newGraphTest()));
				break;
		}
	}

	//item selected
	else if(Workspace::isItemIndex(item[0])){
		menu.addAction("Delete" , this , SLOT());
		menu.addAction("Rename" , this , SLOT());
	}

	menu.popup(QCursor::pos());
	menu.exec();
}

void MainWindow::projectViewTreeClick(QModelIndex index){
	if(Workspace::isItemIndex(index)){
		BaseModel* mdl = workspace->getModel(index);
		connectModel(mdl);
		currentModel = mdl;
		mdl->setOpened(true);
		setModel(mdl);
	}
}

void MainWindow::mdlSaved(BaseModel* mdl){
	updateOpenedList();
}

void MainWindow::mdlOpened(BaseModel* mdl){
	updateOpenedList();
}

void MainWindow::closeEdit(BaseModel* mdl){
	if(!mdl->isSaved()){
		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		if(ret == QMessageBox::Cancel) return;
		if(ret == QMessageBox::Save) mdl->save();
	}

	mdl->setOpened(false);
	currentModel = NULL;

	switch(mdl->type()){
		case DatasetEdit:
			dataset->setModel(NULL);
			setModel(workspace->firstOpened());
			break;

		case TopologyEdit:
			topology->setModel(NULL);
			setModel(workspace->firstOpened());
			break;

		case LearningConfig:
			learning->setModel(NULL);
			setModel(workspace->firstOpened());
			break;

		case DatasetTest:
			datasetTest->setModel(NULL);
			setModel(workspace->firstOpened());
			break;

		case GraphTest:
			graphTest->setModel(NULL);
			setModel(workspace->firstOpened());
			break;
	}
}

void MainWindow::openProject(){
	QString fileName = QFileDialog::getOpenFileName(
		this,
		tr("Open project"),
		"",
		tr("Project files (.prj)(*.prj)")
	);
}

void MainWindow::save(){
	if(currentModel == NULL) return;
	currentModel->save();
}

void MainWindow::saveAll(){
	QList<BaseModel*> list = workspace->unsavedItems();
	for(int i = 0; i < list.length(); i++){
		list[i]->save();
	}
}

void MainWindow::connectModel(BaseModel* mdl){
	switch(mdl->type()){
		case DatasetEdit:
			connect((DatasetEditModel*)mdl, SIGNAL(opened(BaseModel*)), this, SLOT(mdlOpened(BaseModel*)), Qt::UniqueConnection);
			connect((DatasetEditModel*)mdl, SIGNAL(saved(BaseModel*)), this, SLOT(mdlSaved(BaseModel*)), Qt::UniqueConnection);
			break;

		case TopologyEdit:
			connect((TopologyEditModel*)mdl, SIGNAL(opened(BaseModel*)), this, SLOT(mdlOpened(BaseModel*)), Qt::UniqueConnection);
			connect((TopologyEditModel*)mdl, SIGNAL(saved(BaseModel*)), this, SLOT(mdlSaved(BaseModel*)), Qt::UniqueConnection);
			break;

		case LearningConfig:
			connect((LearningConfigModel*)mdl, SIGNAL(opened(BaseModel*)), this, SLOT(mdlOpened(BaseModel*)), Qt::UniqueConnection);
			connect((LearningConfigModel*)mdl, SIGNAL(saved(BaseModel*)), this, SLOT(mdlSaved(BaseModel*)), Qt::UniqueConnection);
			break;

		case DatasetTest:
			connect((DatasetTestModel*)mdl, SIGNAL(opened(BaseModel*)), this, SLOT(mdlOpened(BaseModel*)), Qt::UniqueConnection);
			connect((DatasetTestModel*)mdl, SIGNAL(saved(BaseModel*)), this, SLOT(mdlSaved(BaseModel*)), Qt::UniqueConnection);
			break;

		case GraphTest:
			connect((GraphTestModel*)mdl, SIGNAL(opened(BaseModel*)), this, SLOT(mdlOpened(BaseModel*)), Qt::UniqueConnection);
			connect((GraphTestModel*)mdl, SIGNAL(saved(BaseModel*)), this, SLOT(mdlSaved(BaseModel*)), Qt::UniqueConnection);
			break;
	}
}

void MainWindow::updateOpenedList(){
	ui->openedFilesView->clear();
	QList<BaseModel*> list = workspace->getOpenedItems();
	for(int i = 0; i < list.length(); i++){
		QString txt = list[i]->name();
		if(!list[i]->isSaved()) txt += "*";
		ui->openedFilesView->addItem(txt);
	}
}

void MainWindow::newProject(){
	Dialog::NewProjectDialog dialog;
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
	Dialog::AboutDialog ad;
	ad.exec();
}

void MainWindow::showAboutQt(){
	QMessageBox::aboutQt(this);
}

void MainWindow::showHelp(){
	editMenuItemPressed(-8);
	checkMainButtons(-8);
}

}

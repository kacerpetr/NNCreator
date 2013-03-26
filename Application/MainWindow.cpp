#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include "Dialog/AboutDialog.h"
#include "Dialog/SettingsDialog.h"
#include "Dialog/NewProjectDialog.h"
#include "Util/Settings.h"
#include "GuiPart/OpenedListItem.h"

namespace Application{

/**
 * Class constructor.
 */
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	//setup ui
	ui->setupUi(this);

	//top menubar
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));
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

	//opened files list
	connect(ui->openedFilesView, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(showOpened(QListWidgetItem*)));

	//creates edit widgets
	noModel = new NoModelWidget(this);
	welcome = new WelcomeWidget(this);
	dataset = new DatasetEditWidget(this);
	topology = new TopologyWidget(this);
    learning = new LearningWidget(this);
	datasetTest = new DatasetTestWidget(this);
	graphTest = new OutputGraphWidget(this);
	help = new HelpWidget(this);

	//connects edit widget signals
	connect(welcome, SIGNAL(newProject()), this, SLOT(newProject()));
	connect(welcome, SIGNAL(openProject()), this, SLOT(openProject()));
	connect(welcome, SIGNAL(openRecent(QString)), this, SLOT(openRecent(QString)));
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

/**
 * Class destructor.
 */
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

/**
 * Shows given edit widget and hides others.
 */
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

/**
 * Sets edit widget by given model and checks proper left menu button.
 */
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

/**
 * Checks button of given id in left menu.
 */
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

/**
 * Handles left menu button pressed signal.
 */
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

/**
 * Creates and shows project view context menu.
 */
void MainWindow::showContextMenu(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	QMenu menu;

	//no item selected
	if(item.isEmpty() || !item[0].isValid()){
        menu.addAction(tr("New project") , this , SLOT(newProject()));
        menu.addAction(tr("Open project") , this , SLOT(openProject()));
	}

	//project selected
	else if(Workspace::isProjectIndex(item[0])){
        menu.addAction(tr("New project") , this , SLOT(newProject()));
        menu.addAction(tr("Open project") , this , SLOT(openProject()));
        menu.addAction(tr("Close project") , this , SLOT(closeProject()));
	}

	//model category selected
	else if(Workspace::isCategoryIndex(item[0])){
		switch(Workspace::getCategoryId(item[0])){
			case DatasetEdit:
                menu.addAction(tr("New dataset") , this , SLOT(newDataset()));
				break;

			case TopologyEdit:
                menu.addAction(tr("New neural network") , this , SLOT(newNeuralNetwork()));
				break;

			case LearningConfig:
                menu.addAction(tr("New learning configuration") , this , SLOT(newLearningConfig()));
				break;

			case DatasetTest:
                menu.addAction(tr("New dataset test") , this , SLOT(newDatasetTest()));
				break;

			case GraphTest:
                menu.addAction(tr("New graph test") , this , SLOT(newGraphTest()));
				break;
		}
	}

	//item selected
	else if(Workspace::isItemIndex(item[0])){
        menu.addAction(tr("Rename") , this , SLOT(renameModel()));
        menu.addAction(tr("Delete") , this , SLOT(removeModel()));
	}

	menu.popup(QCursor::pos());
	menu.exec();
}

/**
 * Handles project view tree click.
 */
void MainWindow::projectViewTreeClick(QModelIndex index){
	if(Workspace::isItemIndex(index)){
		BaseModel* mdl = workspace->getModel(index);
		connectModel(mdl);
		currentModel = mdl;
		mdl->setOpened(true);
		setModel(mdl);
	}
}

/**
 * Handles signal emmited when project is saved.
 */
void MainWindow::mdlSaved(BaseModel* mdl){
	updateOpenedList();
}

/**
 * Handles signal emmited when project is opened.
 */
void MainWindow::mdlOpened(BaseModel* mdl){
	updateOpenedList();
}

/**
 * Handles signal emmited when edit is closed.
 */
bool MainWindow::closeEdit(BaseModel* mdl, bool closeApp){
	if(!mdl->isSaved()){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Close"));
        msgBox.setText(tr("The document \"") + mdl->name() + tr("\" has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
		if(closeApp) msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
		else msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);

		int ret = msgBox.exec();

		if(ret == QMessageBox::Cancel){
			return false;
		}
		else if(ret == QMessageBox::Save){
			mdl->save();
		}
		else if(ret == QMessageBox::Discard && !closeApp){
			workspace->reloadModel(mdl);
		}
	}

	mdl->setOpened(false);
	currentModel = NULL;

	switch(mdl->type()){
		case DatasetEdit:
			dataset->setModel(NULL);
			break;

		case TopologyEdit:
			topology->setModel(NULL);
			break;

		case LearningConfig:
			learning->setModel(NULL);
			break;

		case DatasetTest:
			datasetTest->setModel(NULL);
			break;

		case GraphTest:
			graphTest->setModel(NULL);
			break;
	}

	setModel(workspace->firstOpened());
	return true;
}

/**
 * Opens project selected by user.
 */
void MainWindow::openProject(){
	QString fileName = QFileDialog::getOpenFileName(
		this,
		tr("Open project"),
		"",
		tr("Project file (.xml)(*.xml)")
	);
	if(!fileName.isEmpty()){
		if(!workspace->openProject(fileName)){
			Util::Settings& settings = Util::Settings::get();
			settings.unregisterProject(fileName);
			return;
		}
		checkMainButtons(-3);
		editMenuItemPressed(-3);
		ui->projectViewTree->expandAll();
	}
}

/**
 * Closes project.
 */
void MainWindow::closeProject(){
	QModelIndex index = ui->projectViewTree->currentIndex();
	if(workspace->isProjectIndex(index)){
		QList<BaseModel*> opened = workspace->project(index)->getOpenedItems();
		for(int i = 0; i < opened.length(); i++)
			if(!closeEdit(opened[i])) return;
		workspace->project(index)->save();
		workspace->closeProject(index);
	}
}

/**
 * Asks user for new name and renames selected model.
 */
void MainWindow::renameModel(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

    BaseModel* mdl = workspace->getModel(item[0]);
    Q_ASSERT(mdl!=NULL);

    Dialog::FileNameDialog dialog;
    dialog.setTitle(tr("Rename"));
    dialog.setHeader(tr("New name:"));
    dialog.setText(mdl->name());
    dialog.exec();

    QString name = dialog.text();
    if(dialog.ok() && !name.isEmpty()){
		if(Workspace::isItemIndex(item[0]))
			workspace->getModel(item[0])->rename(name);
	}
}

/**
 * Removes selected model.
 */
void MainWindow::removeModel(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;
	workspace->removeModel(item[0]);
	setModel(workspace->firstOpened());
	updateOpenedList();
}

/**
 * Opens project at given path.
 */
void MainWindow::openRecent(QString path){
	if(!workspace->openProject(path)){
		Util::Settings& settings = Util::Settings::get();
		settings.unregisterProject(path);
		return;
	}
	checkMainButtons(-3);
	editMenuItemPressed(-3);
	ui->projectViewTree->expandAll();
}

/**
 * Handles item pressed signal when item in opened files list is clicked.
 */
void MainWindow::showOpened(QListWidgetItem* item){
    currentModel = ((OpenedListItem*)item)->model();
    setModel(((OpenedListItem*)item)->model());
}

/**
 * Saves current model.
 */
void MainWindow::save(){
	if(currentModel == NULL) return;
	currentModel->save();
}

/**
 * Saves all unsaved items.
 */
void MainWindow::saveAll(){
	QList<BaseModel*> list = workspace->unsavedItems();
	for(int i = 0; i < list.length(); i++){
		list[i]->save();
	}
}

/**
 * Asks user to save usaved item before application is closed.
 */
void MainWindow::closeEvent(QCloseEvent *event){
	QList<BaseModel*> opened = workspace->getOpenedItems();
	for(int i = 0; i < opened.length(); i++) closeEdit(opened[i], true);
}

/**
 * Connects given model with main window slots.
 */
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

/**
 * Recreates list of opened items.
 */
void MainWindow::updateOpenedList(){
	ui->openedFilesView->clear();
	QList<BaseModel*> list = workspace->getOpenedItems();
	for(int i = 0; i < list.length(); i++){
		connectModel(list[i]);
		OpenedListItem* item = new OpenedListItem();
		item->setModel(list[i]);
		ui->openedFilesView->addItem(item);
	}
}

/**
 * Creates project with name defined by user.
 */
void MainWindow::newProject(){
	Dialog::NewProjectDialog dialog;
	dialog.exec();

	if(dialog.isConfirmed()){
		workspace->createProject(dialog.getPath(), dialog.getName());
		ui->projectViewTree->expandAll();
        checkMainButtons(-3);
        editMenuItemPressed(-3);
        ui->projectViewTree->expandAll();
	}
}

/**
 * Creates new dataset with name defined by user.
 */
void MainWindow::newDataset(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

    Dialog::FileNameDialog dialog;
    dialog.setTitle(tr("Create new dataset"));
    dialog.setHeader(tr("Dataset name:"));
    dialog.exec();

    QString name = dialog.text();
    if(dialog.ok() && !name.isEmpty()){
		workspace->createDataset(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

/**
 * Creates new neural network with name defined by user.
 */
void MainWindow::newNeuralNetwork(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

    Dialog::FileNameDialog dialog;
    dialog.setTitle(tr("Create new neural network"));
    dialog.setHeader(tr("Neural network name:"));
    dialog.exec();

    QString name = dialog.text();
    if(dialog.ok() && !name.isEmpty()){
		workspace->createNeuralNetwork(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

/**
 * Creates new learning config with name defined by user.
 */
void MainWindow::newLearningConfig(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

    Dialog::FileNameDialog dialog;
    dialog.setTitle(tr("Create new learning configuration"));
    dialog.setHeader(tr("Learning configuration name:"));
    dialog.exec();

    QString name = dialog.text();
    if(dialog.ok() && !name.isEmpty()){
		workspace->createLearningConfig(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

/**
 * Creates new dataset test with name defined by user.
 */
void MainWindow::newDatasetTest(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

    Dialog::FileNameDialog dialog;
    dialog.setTitle(tr("Create new dataset test"));
    dialog.setHeader(tr("Dataset test name:"));
    dialog.exec();

    QString name = dialog.text();
    if(dialog.ok() && !name.isEmpty()){
		workspace->createDatasetTest(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

/**
 * Creates new graph test with name defined by user.
 */
void MainWindow::newGraphTest(){
	QModelIndexList item = ui->projectViewTree->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

    Dialog::FileNameDialog dialog;
    dialog.setTitle(tr("Create new graph test"));
    dialog.setHeader(tr("Graph test name:"));
    dialog.exec();

    QString name = dialog.text();
    if(dialog.ok() && !name.isEmpty()){
		workspace->createGraphTest(item[0], name);
		ui->projectViewTree->expand(item[0]);
	}
}

/**
 * Shows dialog with info about application.
 */
void MainWindow::showAboutDialog(){
	Dialog::AboutDialog ad;
	ad.exec();
}

/**
 * Shows dialog with info about Qt.
 */
void MainWindow::showAboutQt(){
	QMessageBox::aboutQt(this);
}

/**
 * Shows settings dialog.
 */
void MainWindow::showSettingsDialog(){
    Dialog::SettingsDialog sd;
    sd.exec();
}

/**
 * Switch left menu to help item.
 */
void MainWindow::showHelp(){
	editMenuItemPressed(-8);
	checkMainButtons(-8);
}

}

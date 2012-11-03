#include "Edit.h"
#include "ui_Edit.h"
#include "Dialog/NewProjectDialog.h"
#include <QCursor>
#include <QDebug>
#include <QInputDialog>

Edit::Edit(QWidget *parent) : QWidget(parent), ui(new Ui::Edit){
	ui->setupUi(this);

	trainingPatterns = new TrainingPatterns(this);
	topology = new Topology(this);
	learning = new Learning(this);
	testing = new Testing(this);

	ui->fileList->addWidget(trainingPatterns);
	ui->fileList->addWidget(topology);
	ui->fileList->addWidget(learning);
	ui->fileList->addWidget(testing);

	workspace = new Workspace();
	ui->projectView->setModel(workspace);
	ui->projectView->expandAll();

	connectSignalSlot();
}

Edit::~Edit(){
	delete trainingPatterns;
	delete topology;
	delete learning;
	delete testing;
	delete ui;
	delete workspace;
}

void Edit::connectSignalSlot(){
	connect(ui->projectView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
}

void Edit::hideAll(void){
	trainingPatterns->hide();
	topology->hide();
	learning->hide();
	testing->hide();
}

void Edit::setWidget(int id){
	hideAll();
	switch(id){
		case 3:
			trainingPatterns->show();
			break;
		case 4:
			topology->show();
			break;
		case 5:
			learning->show();
			break;
		case 6:
			testing->show();
			break;
	}
}

void Edit::showContextMenu(){
	QModelIndexList item = ui->projectView->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;
	QMenu menu;

	if(!workspace->parent(item[0]).isValid()){
		menu.addAction("New project" , this , SLOT(newProject()));
		menu.addAction("Close project" , this , SLOT(newTrainingPattern()));
		menu.addAction("Delete project" , this , SLOT());
		menu.addSeparator();
		menu.addAction("New training pattern" , this , SLOT(newTrainingPattern()));
		menu.addAction("New neural network" , this , SLOT(newNeuralNetwork()));
		menu.addAction("New learning configuration" , this , SLOT(newLearningConfig()));
		menu.addAction("New testing scenario" , this , SLOT(newTestingScenario()));
	}else if(workspace->parent(item[0]).internalId() < 10000){
		menu.addAction("New project" , this , SLOT(newProject()));
		menu.addAction("Close project" , this , SLOT(newTrainingPattern()));
		menu.addAction("Delete project" , this , SLOT());
		menu.addSeparator();
		if(item[0].row() == 0){
			menu.addSeparator();
			menu.addAction("New training pattern" , this , SLOT(newTrainingPattern()));
			menu.addAction("Clear training patterns" , this , SLOT());
		}else if(item[0].row() == 1){
			menu.addAction("New neural network" , this , SLOT(newNeuralNetwork()));
			menu.addAction("Clear neural networks" , this , SLOT());
		}else if(item[0].row() == 2){
			menu.addAction("New learning configuration" , this , SLOT(newLearningConfig()));
			menu.addAction("Clear learning configurations" , this , SLOT());
		}else if(item[0].row() == 3){
			menu.addAction("New testing scenario" , this , SLOT(newTestingScenario()));
			menu.addAction("Clear testing scenarios" , this , SLOT());
		}
	}

	menu.popup(QCursor::pos());
	menu.exec();
}

void Edit::newProject(){
	NewProjectDialog dialog;
	dialog.exec();
	if(dialog.isConfirmed()){
		workspace->createProject(dialog.getPath(), dialog.getName());
		ui->projectView->expand(workspace->index(workspace->getProjectCount()-1));
	}
}

void Edit::newTrainingPattern(){
	QModelIndexList item = ui->projectView->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString name = QInputDialog::getText(
		this,
		tr("Create new training pattern"),
		tr("Pattern name:"),
		QLineEdit::Normal,
		QString("newPattern"),
		&ok
	);

	if(ok && !name.isEmpty()){
		workspace->createTrainingPattern(item[0], name);
		ui->projectView->expand(item[0]);
	}
}

void Edit::newNeuralNetwork(){
	QModelIndexList item = ui->projectView->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString name = QInputDialog::getText(
		this,
		tr("Create new neural network"),
		tr("Neural network name:"),
		QLineEdit::Normal,
		QString("newNeuralNetwork"),
		&ok
	);

	if(ok && !name.isEmpty()){
		ui->projectView->expand(item[0]);
		workspace->createNeuralNetwork(item[0], name);
	}
}

void Edit::newLearningConfig(){
	QModelIndexList item = ui->projectView->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString name = QInputDialog::getText(
		this,
		tr("Create new learning coniguration"),
		tr("Learning config name:"),
		QLineEdit::Normal,
		QString("newLearningConfig"),
		&ok
	);

	if(ok && !name.isEmpty()){
		ui->projectView->expand(item[0]);
		workspace->createLearningConfig(item[0], name);
	}
}

void Edit::newTestingScenario(){
	QModelIndexList item = ui->projectView->selectionModel()->selectedIndexes();
	if(item.isEmpty() || !item[0].isValid()) return;

	bool ok;
	QString name = QInputDialog::getText(
		this,
		tr("Create new testing scenario"),
		tr("Testing scenario name:"),
		QLineEdit::Normal,
		QString("newTestingScenario"),
		&ok
	);

	if(ok && !name.isEmpty()){
		ui->projectView->expand(item[0]);
		workspace->createTestingScenario(item[0], name);
	}
}

Workspace* Edit::getWorkspace(){
	return this->workspace;
}

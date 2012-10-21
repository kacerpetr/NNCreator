#include "Edit.h"
#include "ui_Edit.h"

Edit::Edit(QWidget *parent) : QWidget(parent), ui(new Ui::Edit){
	ui->setupUi(this);

	trainingPatterns = new TrainingPatterns(this);
	topology = new Topology(this);
	learning = new Learning(this);
	testing = new Testing(this);
	graphs = new Graphs(this);

	ui->fileList->addWidget(trainingPatterns);
	ui->fileList->addWidget(topology);
	ui->fileList->addWidget(learning);
	ui->fileList->addWidget(testing);
	ui->fileList->addWidget(graphs);

	workspace = new Workspace();
	workspace->createProject("path1", "Pokus");
	workspace->createProject("path2", "Experiment");
	workspace->createProject("path2", "SomeProject");

	ui->projectView->setModel(workspace);
	ui->projectView->expandAll();
}

void Edit::hideAll(void){
	trainingPatterns->hide();
	topology->hide();
	learning->hide();
	testing->hide();
	graphs->hide();
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
		case 7:
			graphs->show();
			break;
	}
}

Edit::~Edit(){
	delete trainingPatterns;
	delete topology;
	delete learning;
	delete testing;
	delete graphs;
	delete ui;
}


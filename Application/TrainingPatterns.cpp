#include "TrainingPatterns.h"
#include "ui_TrainingPatterns.h"
#include <QDebug>
#include <QMenu>

TrainingPatterns::TrainingPatterns(QWidget *parent) : QWidget(parent), ui(new Ui::TrainingPatterns){
	ui->setupUi(this);

	tpm = new Project::TrainingPatternModel();
	ui->tableView->setModel(tpm);

	connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
}

void TrainingPatterns::showContextMenu(){
	QMenu* contextMenu = new QMenu(this);
	Q_CHECK_PTR(contextMenu);

	contextMenu->addAction("New" , this , SLOT(newUnitBtnSlot()));
	contextMenu->addAction("Clone" , this , SLOT(cloneUnitBtnSlot()));

	contextMenu->popup(QCursor::pos());
	contextMenu->exec();

	delete contextMenu;
	contextMenu = 0;
}

TrainingPatterns::~TrainingPatterns(){
	delete ui;
}

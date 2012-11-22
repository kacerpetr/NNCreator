#include "TrainingPatternWidget.h"
#include "ui_TrainingPatternWidget.h"
#include <QDebug>
#include <QMenu>

TrainingPatternWidget::TrainingPatternWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TrainingPatternWidget), model(NULL){
	ui->setupUi(this);
	connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
}

TrainingPatternWidget::~TrainingPatternWidget(){
	delete ui;
}


void TrainingPatternWidget::showContextMenu(){
	QMenu* contextMenu = new QMenu(this);
	Q_CHECK_PTR(contextMenu);
	contextMenu->addAction("New" , this , SLOT(newUnitBtnSlot()));
	contextMenu->addAction("Clone" , this , SLOT(cloneUnitBtnSlot()));
	contextMenu->popup(QCursor::pos());
	contextMenu->exec();
	delete contextMenu;
	contextMenu = 0;
}


void TrainingPatternWidget::setModel(TrainingPatternModel* model){
	ui->itemName->setText(model->getName());
	ui->tableView->setModel(model);
	this->model = model;
}

bool TrainingPatternWidget::hasModel(){
	return model != NULL;
}

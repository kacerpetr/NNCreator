#include "DatasetEditWidget.h"
#include "ui_DatasetEditWidget.h"
#include <QDebug>
#include <QMenu>

DatasetEditWidget::DatasetEditWidget(QWidget *parent) : QWidget(parent), ui(new Ui::DatasetEditWidget), model(NULL){
	ui->setupUi(this);
	connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
}

DatasetEditWidget::~DatasetEditWidget(){
	delete ui;
}


void DatasetEditWidget::showContextMenu(){
	QMenu* contextMenu = new QMenu(this);
	Q_CHECK_PTR(contextMenu);
	contextMenu->addAction("New" , this , SLOT(newUnitBtnSlot()));
	contextMenu->addAction("Clone" , this , SLOT(cloneUnitBtnSlot()));
	contextMenu->popup(QCursor::pos());
	contextMenu->exec();
	delete contextMenu;
	contextMenu = 0;
}


void DatasetEditWidget::setModel(DatasetEditModel* model){
	ui->itemName->setText(model->getName());
	ui->tableView->setModel(model);
	this->model = model;
}

bool DatasetEditWidget::hasModel(){
	return model != NULL;
}

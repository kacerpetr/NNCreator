#include "LearningWidget.h"
#include "ui_LearningWidget.h"

LearningWidget::LearningWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LearningWidget)
{
	ui->setupUi(this);
}

LearningWidget::~LearningWidget()
{
	delete ui;
}

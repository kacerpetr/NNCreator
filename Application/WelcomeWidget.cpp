#include "WelcomeWidget.h"
#include "ui_WelcomeWidget.h"

namespace Application{

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::WelcomeWidget){
	ui->setupUi(this);
}

WelcomeWidget::~WelcomeWidget(){
	delete ui;
}

QToolButton* WelcomeWidget::getNewProjectButton(){
	return ui->newProjectButton;
}

}

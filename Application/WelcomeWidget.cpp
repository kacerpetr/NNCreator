#include "WelcomeWidget.h"
#include "ui_WelcomeWidget.h"

namespace Application{

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::WelcomeWidget){
	ui->setupUi(this);
}

WelcomeWidget::~WelcomeWidget(){
	delete ui;
}

void WelcomeWidget::newBtnPressed(){

}

void WelcomeWidget::openBtnPressed(){

}

void WelcomeWidget::slotOnePressed(){

}

void WelcomeWidget::slotTwoPressed(){

}

void WelcomeWidget::slotThreePressed(){

}

void WelcomeWidget::slotFourPressed(){

}

void WelcomeWidget::slotFivePressed(){

}


}

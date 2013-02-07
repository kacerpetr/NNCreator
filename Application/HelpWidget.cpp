#include "HelpWidget.h"
#include "ui_HelpWidget.h"

namespace Application{

HelpWidget::HelpWidget(QWidget *parent) : QWidget(parent), ui(new Ui::HelpWidget){
	ui->setupUi(this);
}

HelpWidget::~HelpWidget(){
	delete ui;
}

}

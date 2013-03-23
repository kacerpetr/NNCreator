#include "HelpWidget.h"
#include "ui_HelpWidget.h"
#include <QUrl>

namespace Application{

HelpWidget::HelpWidget(QWidget *parent) : QWidget(parent), ui(new Ui::HelpWidget){
	ui->setupUi(this);
    ui->webView->setUrl(QUrl("./Help/index.html"));
}

HelpWidget::~HelpWidget(){
	delete ui;
}

}

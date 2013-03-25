#include "HelpWidget.h"
#include "ui_HelpWidget.h"
#include <QUrl>

namespace Application{

/**
 * Class consturctor.
 */
HelpWidget::HelpWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::HelpWidget)
{
	ui->setupUi(this);
    ui->webView->setUrl(QUrl("./Help/index.html"));
}

/**
 * Class destructor.
 */
HelpWidget::~HelpWidget(){
	delete ui;
}

}

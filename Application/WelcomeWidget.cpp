#include "WelcomeWidget.h"
#include "ui_WelcomeWidget.h"
#include "GuiPart/LabelButton.h"
#include <QDebug>
#include "Util/Settings.h"

using namespace Util;

namespace Application{

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::WelcomeWidget){
	ui->setupUi(this);

	// new project
	newBtn = new LabelButton(this);
	newBtn->setText(
		"<img style=\"float:left;\" src=\":/newDoc22\"/>"
		"<div style=\"font-weight:bold; margin-top:5px; float:left;\">"
		+ tr("New project") + "</div>"
	);
	ui->startupFrame->layout()->addWidget(newBtn);
	connect(newBtn, SIGNAL(pressed()), this, SLOT(newButtonPressed()));

	// open project
	openBtn = new LabelButton(this);
	openBtn->setText(
		"<img style=\"float:left;\" src=\":/openDoc22\"/>"
		"<div style=\"margin-left:4px; font-weight:bold; margin-top:5px; float:left;\">"
		+ tr("Open project") + "</div>"
	);
	ui->startupFrame->layout()->addWidget(openBtn);
	connect(openBtn, SIGNAL(pressed()), this, SLOT(openButtonPressed()));

	// creates recent project buttons
	createRecentBtn();

	// recreates recent project buttons when project is opened or created
	connect(Settings::getPointer(), SIGNAL(recentChanged()), this, SLOT(recentChanged()));
}

WelcomeWidget::~WelcomeWidget(){
	delete newBtn;
	delete openBtn;
	for(int i = 0; i < 5; i++) delete btn[i];
	delete ui;
}

void WelcomeWidget::createRecentBtn(){
	Settings& settings = Settings::get();
	QList<TRecentProject> recPrj = settings.recentProject();

	//creates recent project buttons
	for(int i = 0; i < recPrj.length(); i++){
		btn.append(new LabelButton(this));
		btn[i]->setText("<b>" + recPrj[i].name + "</b> - " + recPrj[i].path);
		ui->recentProjectFrame->layout()->addWidget(btn[i]);
		connect(btn[i], SIGNAL(pressed(LabelButton*)), this, SLOT(openRecentPressed(LabelButton*)));
	}
}

void WelcomeWidget::removeRecentBtn(){
	for(int i = 0; i < btn.length(); i++){
		ui->recentProjectFrame->layout()->removeWidget(btn[i]);
		delete btn[i];
	}
	btn.clear();
}

void WelcomeWidget::newButtonPressed(){
	emit newProject();
}

void WelcomeWidget::openButtonPressed(){
	emit openProject();
}

void WelcomeWidget::openRecentPressed(LabelButton* button){
	for(int i = 0; i < btn.length(); i++){
		if(button == btn[i]){
			Settings& settings = Settings::get();
			QList<TRecentProject> recPrj = settings.recentProject();
			emit openRecent(recPrj[i].path);
			break;
		}
	}
}

void WelcomeWidget::recentChanged(){
	removeRecentBtn();
	createRecentBtn();
}

}

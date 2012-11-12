#include "TopologyWidget.h"
#include "ui_TopologyWidget.h"
#include "LayerEditWidget.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLine>

TopologyWidget::TopologyWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TopologyWidget){
	ui->setupUi(this);

	connect(ui->addLayerButton, SIGNAL(pressed()), this, SLOT(appendInnerLayer()));

	layerEditLayout = new QVBoxLayout(ui->layerScrollAreaContent);
	ui->layerScrollAreaContent->setLayout(layerEditLayout);
	layerEditLayout->setMargin(0);
	layerEditLayout->setSpacing(0);
	layerEditLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

	createBasicLayers();
}

TopologyWidget::~TopologyWidget(){
	delete ui;
}

void TopologyWidget::setModel(NeuralNetworkModel* model){
	ui->itemName->setText(model->getName());
}

void TopologyWidget::createBasicLayers(){
	if(layerEditList.count() > 0) return;

	LayerEditWidget* wgIn = new LayerEditWidget(ui->layerScrollAreaContent);
	wgIn->setLayerName("[0] Input layer: ");
	wgIn->setAsInputLayer(true);
	wgIn->setDuplicateButtonDisabled(true);
	wgIn->setRemoveButtonDisabled(true);

	LayerEditWidget* wgOut = new LayerEditWidget(ui->layerScrollAreaContent);
	wgOut->setLayerName("[1] Output layer: ");
	wgOut->setRemoveButtonDisabled(true);
	wgOut->setDuplicateButtonDisabled(true);

	QFrame* line = new QFrame(ui->layerScrollAreaContent);
	line->setObjectName(QString::fromUtf8("line"));
	line->setMaximumHeight(2);
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);

	layerEditLayout->insertWidget(0, wgIn);
	layerEditLayout->insertWidget(0, line);
	layerEditLayout->insertWidget(0, wgOut);

	layerEditList.append(wgIn);
	layerEditList.append(wgOut);

	connect(wgIn, SIGNAL(widgetPressed(LayerEditWidget*)), this, SLOT(widgetPressed(LayerEditWidget*)));
	connect(wgOut, SIGNAL(widgetPressed(LayerEditWidget*)), this, SLOT(widgetPressed(LayerEditWidget*)));
}

void TopologyWidget::appendInnerLayer(){
	QFrame* line = new QFrame(ui->layerScrollAreaContent);
	line->setObjectName(QString::fromUtf8("line"));
	line->setMaximumHeight(2);
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	layerEditLayout->insertWidget(2, line);

	LayerEditWidget* wg = new LayerEditWidget(ui->layerScrollAreaContent);
	layerEditLayout->insertWidget(2, wg);
	layerEditList.insert(layerEditList.count()-1, wg);
	connect(wg, SIGNAL(widgetPressed(LayerEditWidget*)), this, SLOT(widgetPressed(LayerEditWidget*)));

	QString innName = "[" + QString::number(layerEditList.count()-2) + "] Inner layer: ";
	QString outName = "[" + QString::number(layerEditList.count()-1) + "] Output layer: ";
	wg->setLayerName(innName);
	layerEditList.last()->setLayerName(outName);
}

void TopologyWidget::removeLayer(int index){

}

void TopologyWidget::widgetPressed(LayerEditWidget* widget){
	for(int i = 0; i < layerEditList.count(); i++){
		if(widget != layerEditList[i]){
			layerEditList[i]->setSelected(false);
		}
	}
}

#include "LearningWidget.h"
#include "ui_LearningWidget.h"
#include <QDebug>

namespace Application{

/**
 * Class constructor.
 */
LearningWidget::LearningWidget(MainWindow* parent) :
    QWidget(parent),
    ui(new Ui::LearningWidget),
    model(NULL),
    mainWin(parent)
{
    //autogenerated stuff
    ui->setupUi(this);

    //creates and adds newt param widget to layout
	npw = new NetParamWidget(this);
	ui->splitterH->addWidget(npw);

    //connects signals and slots
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));
	connect(ui->startBtn, SIGNAL(pressed()), this, SLOT(startLearning()));
	connect(ui->stopBtn, SIGNAL(pressed()), this, SLOT(stopLearning()));
	connect(ui->datasetBox, SIGNAL(activated(QString)), this, SLOT(datasetSelected(QString)));
	connect(ui->networkBox, SIGNAL(activated(QString)), this, SLOT(networkSelected(QString)));
	connect(ui->lrnCoefBox, SIGNAL(valueChanged(double)), this, SLOT(lrnCoefChanged(double)));
	connect(ui->maxErrBox, SIGNAL(valueChanged(double)), this, SLOT(maxErrChanged(double)));
	connect(ui->maxIterBox, SIGNAL(valueChanged(int)), this, SLOT(maxIterChanged(int)));
    connect(ui->maxTimeBox, SIGNAL(valueChanged(int)), this, SLOT(maxTimeChanged(int)));
}

/**
 * Class destructor.
 */
LearningWidget::~LearningWidget(){
	delete ui;
}

/**
 * Sets given model to edit widget.
 */
void LearningWidget::setModel(LearningConfigModel* model){
    this->model = model;

    //disables certain parts of GUI
	ui->startBtn->setDisabled(true);
	ui->stopBtn->setDisabled(true);
	npw->setDisabled(true);

    //clears widget when NULL pointer given
	if(model == NULL){
		ui->itemName->setText(QString());
        setPlot(NULL);
	}
    //fills view with model data
	else{
        //backups saved flag state
		bool saved = model->isSaved();

        //sets model values to GUI items
		ui->itemName->setText(model->name());
		ui->maxErrBox->setValue(model->maxErr());
		ui->maxIterBox->setValue(model->maxIter());
		ui->lrnCoefBox->setValue(model->lrnCoef());
		ui->maxTimeBox->setValue(model->maxTime());

        //generates and selects
        genNetworkList();

        //sets plot to show in layout
        setPlot(model->plot());

        //connects signals of model
		connect(model, SIGNAL(update(int,long,double)), this, SLOT(updateLearning(int,long,double)), Qt::UniqueConnection);
        connect(model, SIGNAL(stoped()), this, SLOT(learningStoped()), Qt::UniqueConnection);
		connect(model, SIGNAL(changed(ChangeType)), this, SLOT(modelChanged(ChangeType)), Qt::UniqueConnection);

        //restores saved flag state
		model->setSaved(saved);
	}
}

/**
 * Adds model's plot to layout.
 * @param plot will be removed from layout when NULL given
 */
void LearningWidget::setPlot(Plot1D* plot){
    //removes plot from layout and hides it
    if(!ui->graphFrame->layout()->isEmpty()){
        QWidget* wg = ui->graphFrame->layout()->takeAt(0)->widget();
        if(wg != NULL){
            ui->graphFrame->layout()->removeWidget(wg);
            wg->hide();
        }
    }

    //adds new plot to layout
    if(plot != NULL){
        ui->graphFrame->layout()->addWidget(plot);
        plot->show();
    }
}

/**
 * Returns true if widget has some model.
 */
bool LearningWidget::hasModel(){
	return model != NULL;
}

/**
 * Called when model is changed.
 * @param type type of model change
 */
void LearningWidget::modelChanged(ChangeType type){
	if(type == ModelRenamed)
		ui->itemName->setText(model->name());
	else if(type == SelectedNetworkRenamed)
        genNetworkList();
	else if(type == SelectedDatasetRenamed)
        genNetworkList();
	else if(type == SelectedNetworkDeleted)
        genNetworkList();
	else if(type == SelectedDatasetDeleted)
        genNetworkList();
}

/**
 * Emits closePressed signal when close button is pressed.
 */
void LearningWidget::closeBtnPressed(){
	emit closePressed(model);
}

/**
 * Starts learning process.
 */
void LearningWidget::startLearning(){
	model->startLearning();
	ui->stopBtn->setEnabled(true);
    ui->startBtn->setEnabled(false);
}

/**
 * Stops learning process.
 */
void LearningWidget::stopLearning(){
	model->stopLearning();
}

/**
 * Slot called when learning stops or finishes.
 */
void LearningWidget::learningStoped(){
	ui->stopBtn->setEnabled(false);
    ui->startBtn->setEnabled(true);
}

/**
 * Updates line edits during learning.
 */
void LearningWidget::updateLearning(int iteration, long time, double error){
	ui->actErrorEdit->setText(QString::number(error));
	ui->actIterEdit->setText(QString::number(iteration));
	ui->actTimeEdit->setText(QString::number(time));
}

/**
 * Adds and selects saved network and dataset names to list boxes.
 */
void LearningWidget::genNetworkList(){
    //clears selection box and adds existing networks names
    ui->networkBox->clear();
    ui->networkBox->addItem(QString(tr("<Choose neural network>")));
    QStringList nets = model->networkList();
    if(!nets.isEmpty()) ui->networkBox->addItems(nets);

    //looks for selected network name in selection box
    int index = ui->networkBox->findText(model->selectedNetworkName());

    //selects widget that was found
    if(index > 0){
        ui->networkBox->setCurrentIndex(index);
        networkSelected(model->selectedNetworkName());
    }
    //or just clears dataset selection box
    else{
        ui->datasetBox->clear();
        ui->datasetBox->addItem(QString(tr("<No network selected>")));
    }
}

/**
 * Called when neural network selected.
 * @param name selected network name
 */
void LearningWidget::networkSelected(QString name){
    //clears selections and disables GUI items if
    //first item (dummy item) is selected
	if(ui->networkBox->currentIndex() < 1){
		model->selectNetwork(QString());
		ui->startBtn->setEnabled(false);
		npw->setEnabled(false);
        ui->datasetBox->clear();
        ui->datasetBox->setEnabled(false);
		return;
	}

    //clears and enable dataset selection box
    ui->datasetBox->clear();
    ui->datasetBox->setEnabled(true);

    //gets list of possible datasets for selected network
	QStringList list = model->datasetList(name);

    //if there is no possible datasets
	if(list.isEmpty()){
        ui->datasetBox->addItem(QString(tr("<No dataset available for this network>")));
		ui->startBtn->setEnabled(false);
    }
    //fills dataset selection box and tries to select selected name in select box
    else{
        ui->datasetBox->addItem(QString(tr("<Select training dataset>")));
		ui->datasetBox->addItems(list);
		if(!model->selectedDatasetName().isEmpty()){
			int index = ui->datasetBox->findText(model->selectedDatasetName());
			if(index > 0) ui->datasetBox->setCurrentIndex(index);
			ui->startBtn->setEnabled(true);
        }else{
			ui->startBtn->setEnabled(false);
		}
    }

    //stores selected network name in model
	model->selectNetwork(name);

    //gets selected network
	BaseModel* mdl = model->selectedNetwork();
	Q_ASSERT(mdl != NULL);

    //sets and opens selected network
	npw->setModel((TopologyEditModel*)mdl);
    npw->setEnabled(true);
    mainWin->connectModel(mdl);
    mdl->setOpened(true);
}

/**
 * Called when dataset selected.
 */
void LearningWidget::datasetSelected(QString name){
    //clears selections and disables GUI items if
    //first item (dummy item) is selected
	if(ui->datasetBox->currentIndex() == -1){
		model->selectDataset(QString());
		ui->startBtn->setEnabled(false);
		return;
	}

    //enables start learning button
	ui->startBtn->setEnabled(true);
    //stores selected dataset name in model
	model->selectDataset(name);
}

/**
 * Sets new user defined value of learning coeficient in current model.
 */
void LearningWidget::lrnCoefChanged(double value){
	model->setLrnCoef(value);
}

/**
 * Sets new user defined value of stop iteration in current model.
 */
void LearningWidget::maxIterChanged(int value){
	model->setMaxIter(value);
}

/**
 * Sets new user defined value of stop error in current model.
 */
void LearningWidget::maxErrChanged(double value){
	model->setMaxErr(value);
}

/**
 * Sets new user defined value of stop time in current model.
 */
void LearningWidget::maxTimeChanged(int value){
	model->setMaxTime(value);
}

}

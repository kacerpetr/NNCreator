#include <cmath>
#include "BpAlgSt.h"

namespace NeuralNetwork{

///////////////////////////////////////////////
///// Public //////////////////////////////////
///////////////////////////////////////////////

BpAlgSt::BpAlgSt() : AbstractLrnAlg(),
  updateInterval(10),
  stopIter(1000),
  stopError(0.01),
  stopTime(QTime(0,0,2,0)),
  running(false),
  net(NULL),
  data(NULL)
{}

BpAlgSt::BpAlgSt(BpAlgSt& obj) : AbstractLrnAlg(),
  updateInterval(obj.updateInterval),
  stopIter(obj.stopIter),
  stopError(obj.stopError),
  stopTime(obj.stopTime),
  running(obj.running),
  net(obj.net),
  data(obj.data)
{}

void BpAlgSt::setNetwork(AbstractBpNet* net){
	this->net = net;
	if(net != NULL) genDeltaArray();
}

void BpAlgSt::setDataset(AbstractDataset* data){
	this->data = data;
}

void BpAlgSt::setUpdateInterval(int interval){
	this->updateInterval = interval;
}

void BpAlgSt::setStopIteration(int stopIter){
	this->stopIter = stopIter;
}

void BpAlgSt::setStopError(double stopErr){
	this->stopError = stopErr;
}

void BpAlgSt::setStopTime(QTime stopTime){
	this->stopTime = stopTime;
}

AbstractBpNet* BpAlgSt::getNetwork(){
	return net;
}

AbstractDataset* BpAlgSt::getDataset(){
	return data;
}

int BpAlgSt::getUpdateInterval() const{
	return updateInterval;
}

int BpAlgSt::getStopIteration() const{
	return stopIter;
}

double BpAlgSt::getStopError() const{
	return stopError;
}

QTime BpAlgSt::getStopTime() const{
	return stopTime;
}

bool BpAlgSt::isRunning() const{
	return running;
}

BpAlgSt::~BpAlgSt(){}

///////////////////////////////////////////////
///// Slots ///////////////////////////////////
///////////////////////////////////////////////

void BpAlgSt::start(){
	Q_ASSERT(net != NULL);
	Q_ASSERT(data != NULL);

	//emits start signal
	emit started();

	//value initialization
	actIter = 0;
	actTime = QTime();
	actError = 0;
	running = true;
	double sumErr = 0;

	while(!running){
		for(int i = 0; i < data->patternCount(); i++){
			if(!running) break;
			//feedforward
			output = net->getLayerOutput((*data)[i]);
			//output error calculation
			sumErr += calcError(i);
			//output layer delta calculation
			calcOutputDelta(i);
			//inner layer delta calculation
			calcInnerDelta();
			//weight adjustment
			adjustWeight();
		}
		if(actIter == 0 || actIter % updateInterval == 0){
			emit update(actIter, actTime, actError);
		}
		actIter++;
	}

	//signal that tells that learning is finished
	emit stoped(actIter, actTime, actError);
}

void BpAlgSt::stop(){
	running = false;
}

///////////////////////////////////////////////
///// Private /////////////////////////////////
///////////////////////////////////////////////

/*
 * E = 0.5 * sum[i = 0 ... out_count](y_i - t_i)^2
 */

double BpAlgSt::calcError(int pattern){
	double err = 0.0;
	for(int i = 0; i < output.last().length(); i++){
		double val = (*data)(pattern)[i] - output.last()[i];
		err += val*val;
	}
	return 0.5 * err;
}

/*
 * for all output neurons:
 * delta = (t - y) * f'(bias + sum(inner_layer_outs * weights))
 */

void BpAlgSt::calcOutputDelta(int pattern){
	int l = net->getLayerCount() - 1;
	for(int n = 0; n < net->getNeuronCount(l); n++){
		double sum = 0.0;
		for(int w = 0; w < (*net)[l][n].weightCount(); w++){
			sum += output[l][w] * (*net)[l][n][w];
		}
		sum += (*net)[l][n].getBias();
		delta[l][n] = ((*data)(pattern)[n] - output.last()[n]) * (*net)[l][n].trFcnD(sum);
	}
}

/*
 * for all neurons in inner layer L:
 * delta = sum(delta_[L+1] * weight_[L+1]) * f'(bias + sum(layer_[L-1]_outs * neuron_[L,n]_weight))
 */

void BpAlgSt::calcInnerDelta(){
	//over all inner layers
	for(int l = net->getLayerCount()-2; l >= 0; l--){
		//over all neurons in inner layer
		for(int n = 0; n < net->getNeuronCount(l); n++){
			//first sum
			double sum1 = 0.0;
			for(int m = 0; m < (*net).getNeuronCount(l+1); m++){
				sum1 += delta[l+1][m] * (*net)[l+1][m][n];
			}
			//second sum
			double sum2 = 0.0;
			for(int w = 0; w < (*net)[l][n].weightCount(); w++){
				sum2 += output[l][w] * (*net)[l][n][w];
			}
			sum2 += (*net)[l][n].getBias();
			//delta calculation
			delta[l][n] = sum1 * (*net)[l][n].trFcnD(sum2);
		}
	}
}

/*
 * for all neurons N in all layers L:
 * delta_Bias = alpha * delta[L,N]
 * delta_W    = alpha *
 */

void BpAlgSt::adjustWeight(){
	//TODO (temporary solution)
	double alpha = 1;

	//over all layers
	for(int l = net->getLayerCount()-1; l >= 0; l--){
		//over all neurons in layer
		for(int n = 0; n < net->getNeuronCount(l); n++){
			//alpha * delta (support value)
			double k = delta[l][n] * alpha;
			//over all weights of neuron
			for(int w = 0; w < (*net)[l][n].weightCount(); w++){
				//updates weight value
				(*net)[l][n][w] += k * output[l][w];
			}
			//updates bias value
			(*net)[l][n].addBias(k);
		}
	}
}

void BpAlgSt::genDeltaArray(){
	delta.clear();
	for(int i = 0; i < net->getLayerCount(); i++){
		delta.append(QList<double>());
		for(int j = 0; j < net->getNeuronCount(i); j++){
			delta[i].append(0.0);
		}
	}
}

}

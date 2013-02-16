#include "LrnEngine.h"
#include <QDebug>

namespace NeuralNetwork{

LrnEngine::LrnEngine() : QObject(){}

void LrnEngine::setAlgorithm(AbstractLrnAlg* algorithm){
	thread = new QThread();
	alg = algorithm;
	alg->moveToThread(thread);
	connect(thread, SIGNAL(started()), alg, SLOT(start()));
	connect(alg, SIGNAL(stoped(int,long,double)), thread, SLOT(quit()));
	connect(thread, SIGNAL(finished()), this, SLOT(delThread()));
}

AbstractLrnAlg* LrnEngine::getAlgorithm(){
	return alg;
}

void LrnEngine::waitTofinish(){
	thread->wait();
}

void LrnEngine::startThread(){
	thread->start();
}

void LrnEngine::stopThread(){
	alg->stop();
}

void LrnEngine::delThread(){
	delete thread;
}

LrnEngine::~LrnEngine(){}

}


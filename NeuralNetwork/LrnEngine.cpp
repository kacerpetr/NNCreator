#include "LrnEngine.h"
#include <QDebug>

namespace NeuralNetwork{

LrnEngine::LrnEngine() : QObject(){}

void LrnEngine::setAlgorithm(AbstractLrnAlg* algorithm){
	Q_ASSERT(algorithm != NULL);
	thread = new QThread(this);
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
	Q_ASSERT(alg != NULL);
	alg->stop();
}

void LrnEngine::delThread(){
	delete thread;
	thread = NULL;
	delete alg;
	alg = NULL;
}

LrnEngine::~LrnEngine(){}

}


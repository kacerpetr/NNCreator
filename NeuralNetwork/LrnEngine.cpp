#include "LrnEngine.h"
#include <QDebug>

namespace NeuralNetwork{

LrnEngine::LrnEngine() : QObject(){
	thread = new QThread(this);
}

void LrnEngine::setAlgorithm(AbstractLrnAlg* algorithm){
	alg = algorithm;
	alg->moveToThread(thread);
	connect(thread, SIGNAL(started()), alg, SLOT(start()));
	connect(alg, SIGNAL(stoped(int,long,double)), thread, SLOT(deleteLater()));
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

LrnEngine::~LrnEngine(){
	delete thread;
}

}


#include "LrnEngine.h"
#include <QDebug>

namespace NeuralNetwork{

/**
 * Creates unconfigured learning engine.
 */
LrnEngine::LrnEngine() : QObject(){}

/**
 * Sets pointer to learning algorithm class.
 */
void LrnEngine::setAlgorithm(AbstractLrnAlg* algorithm){
	Q_ASSERT(algorithm != NULL);
	thread = new QThread(this);
	alg = algorithm;
	alg->moveToThread(thread);
	connect(thread, SIGNAL(started()), alg, SLOT(start()));
    connect(alg, SIGNAL(stoped()), thread, SLOT(quit()));
	connect(thread, SIGNAL(finished()), this, SLOT(delThread()));
}

/**
 * Returns pointer to learning algorithm class.
 */
AbstractLrnAlg* LrnEngine::getAlgorithm(){
	return alg;
}

/**
 * Waits until learning is finished.
 */
void LrnEngine::waitTofinish(){
	thread->wait();
}

/**
 * Starts learning in secondary thread.
 */
void LrnEngine::startThread(){
	thread->start();
}

/**
 * Stops learning in secondary thread.
 */
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

/**
 * Class destructor.
 */
LrnEngine::~LrnEngine(){}

}


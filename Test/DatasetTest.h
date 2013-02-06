#ifndef DATASETTEST_H
#define DATASETTEST_H

#include <QObject>
#include "NeuralNetwork/Dataset.h"
using namespace NeuralNetwork;

/**
 * Contains all application test code.
 */
namespace Test{

/**
 * Contains test code of Dataset class.
 */
class DatasetTest : public QObject{
	Q_OBJECT

	private slots:
		/** First test of dataset class. */
		void test1();
		/** Second test of dataset class. */
		void test2();
};

}

#endif // DATASETTEST_H

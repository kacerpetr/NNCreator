#ifndef DATASETTEST_H
#define DATASETTEST_H

#include <QObject>
#include "NeuralNetwork/Dataset.h"
using namespace NeuralNetwork;

/**
 * Contains all application test code.
 */
namespace Test{

class DatasetTest : public QObject{
	Q_OBJECT

	public:
		explicit DatasetTest(QObject *parent = 0);

	private slots:
		void test1();
		void test2();
		void test3();
		void test4();
};

}

#endif // DATASETTEST_H

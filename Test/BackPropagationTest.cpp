#include "BackPropagationTest.h"
#include "NeuralNetwork/TrainingPattern.h"
#include <QDebug>

namespace NeuralNetwork{

void BackPropagationTest::test(){
	TrainingPattern pt;

	pt.appendPattern();
	pt.appendValue(0, 0.2, 0.6);
	pt.appendValue(0, 0.1, 0.0);

	pt.appendPattern();
	pt.appendValue(1, 1.2, 0.6);
	pt.appendValue(1, 0.1, -0.3);

	pt.appendPattern();
	pt.appendValue(2, 0.5, 0.1);
	pt.appendValue(2, 0.5, 0.1);

	qDebug() << pt.toString();
}

}

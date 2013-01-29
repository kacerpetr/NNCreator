#ifndef DATASETTEST_H
#define DATASETTEST_H

#include <QObject>

namespace Test{

class DatasetTest : public QObject{
	Q_OBJECT

	public:
		explicit DatasetTest(QObject *parent = 0);

	private slots:
		void test1();
		void test2();
		void test3();
};

}

#endif // DATASETTEST_H

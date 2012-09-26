#ifndef UTILTEST_H
#define UTILTEST_H

#include <QObject>

namespace Util{

class UtilTest : public QObject{
	Q_OBJECT

	private slots:
		void arrayTest();
};

}

#endif // TEST_H

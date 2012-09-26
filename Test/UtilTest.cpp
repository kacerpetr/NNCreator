#include "UtilTest.h"
#include <QtTest/QtTest>
#include <QDebug>
#include "Array.h"

namespace Util{

void UtilTest::arrayTest(){
	Array<int> a;
	QVERIFY(a.isEmpty());
	a.append(150);
	QVERIFY(!a.isEmpty());
	QVERIFY(a.length() == 1);
	QVERIFY(a[0] == 150);
	a.append(1501);
	a.append(1502);
	a.append(1503);
	a.append(1504);
	QVERIFY(a.length() == 5);
	QVERIFY(a[3] == 1503);
	a.insert(-10000, 2);
	QVERIFY(a.length() == 6);
	QVERIFY(a[2] == -10000);
	a.remove(0);
	a.remove(0);
	QVERIFY(a.length() == 4);
	QVERIFY(a[0] == -10000);

	Array<int> b = Array<int>(a);
	for(int i = 0; i < b.length(); i++) QVERIFY(a[i] == b[i]);

	Array<int> c;
	for(int i = 0; i < 1000000; i++) c.append(i);
	for(int i = 0; i < 1000000; i++) QVERIFY(c[i] == i);

	Array<int> d;
	for(int i = 0; i < 1000; i++) d.insert(i, 0);
	for(int i = 0; i < 1000; i++) QVERIFY(d[i] == 999-i);
	for(int i = 0; i < 1000; i++) d.remove(0);
	QVERIFY(d.isEmpty());
	QVERIFY(d.length() == 0);
}

}

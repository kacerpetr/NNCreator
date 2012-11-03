#ifndef TESTINGSCENARIOMODEL_H
#define TESTINGSCENARIOMODEL_H

#include <QString>

class TestingScenarioModel{
	public:
		TestingScenarioModel();
		void setName(QString name);
		QString getName() const;

	private:
		QString name;
};

#endif // TESTINGSCENARIOMODEL_H

#ifndef LEARNINGCONFIGMODEL_H
#define LEARNINGCONFIGMODEL_H

#include <QString>

class LearningConfigModel{
	public:
		LearningConfigModel();
		void setName(QString name);
		QString getName() const;

	private:
		QString name;
};

#endif // LEARNINGCONFIGMODEL_H

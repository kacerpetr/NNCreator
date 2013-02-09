#ifndef LEARNINGCONFIGMODEL_H
#define LEARNINGCONFIGMODEL_H

#include <QString>
#include "BaseModel.h"

/**
 * Contains data models and classes related with project.
 */
namespace Project{

/**
 * Learning configuration data model class.
 */
class LearningConfigModel : public QObject, public BaseModel{
	Q_OBJECT

	public:
		LearningConfigModel();
		void save();
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);

	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);
};

}

#endif // LEARNINGCONFIGMODEL_H

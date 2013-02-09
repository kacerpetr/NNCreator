#ifndef DATASETTESTMODEL_H
#define DATASETTESTMODEL_H

#include "BaseModel.h"
#include <QObject>

/**
 * Contains data models and classes related with project.
 */
namespace Project{

/**
 * Model of dataset test screen.
 */
class DatasetTestModel : public QObject, public BaseModel{
	Q_OBJECT

	public:
		DatasetTestModel();
		void save();
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);

	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);

};

}

#endif // DATASETTESTMODEL_H

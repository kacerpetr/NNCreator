#ifndef GRAPHTESTMODEL_H
#define GRAPHTESTMODEL_H

#include "BaseModel.h"

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Model of test of neural network by output graph.
 */
class GraphTestModel : public QObject, public BaseModel{
	Q_OBJECT

	public:
		GraphTestModel();
		void save();
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);

	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);
};

}

#endif // GRAPHTESTMODEL_H

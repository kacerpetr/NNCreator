#ifndef OPENEDLISTITEM_H
#define OPENEDLISTITEM_H

#include <QListWidgetItem>
#include "Project/BaseModel.h"
using namespace ProjectData;

namespace Application{

class OpenedListItem : public QListWidgetItem{
	public:
		OpenedListItem();
		void setModel(BaseModel* model);
		BaseModel* model();

	private:
		BaseModel* mdl;
};

}

#endif // OPENEDLISTITEM_H

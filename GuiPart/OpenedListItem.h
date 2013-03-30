#ifndef OPENEDLISTITEM_H
#define OPENEDLISTITEM_H

#include <QListWidgetItem>
#include "Project/BaseModel.h"
using namespace ProjectData;

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * ListWidget item used for list of opened items.
 */
class OpenedListItem : public QListWidgetItem{
	public:
		OpenedListItem();
		void setModel(BaseModel* model);
		BaseModel* model();

	private:
        /** Model pointer. */
		BaseModel* mdl;
};

}

#endif // OPENEDLISTITEM_H

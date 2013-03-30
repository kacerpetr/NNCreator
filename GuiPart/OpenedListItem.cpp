#include "OpenedListItem.h"

namespace Application{

/**
 * Class constructor.
 */
OpenedListItem::OpenedListItem() : mdl(NULL){}

/**
 * Sets model pointer and item icon.
 */
void OpenedListItem::setModel(BaseModel* model){
	Q_ASSERT(model != NULL);
	mdl = model;

	QString name = mdl->name();
	if(!mdl->isSaved()) name += "*";
	setText(name);

	switch(mdl->type()){
		case DatasetEdit:
			setIcon(QIcon(":datasetIcon32"));
			break;
		case TopologyEdit:
			setIcon(QIcon(":topologyIcon32"));
			break;
		case LearningConfig:
			setIcon(QIcon(":learningIcon32"));
			break;
		case DatasetTest:
			setIcon(QIcon(":datasetTestIcon32"));
			break;
		case GraphTest:
			setIcon(QIcon(":testingIcon32"));
			break;
	}
}

/**
 * Returns stored model pointer.
 */
BaseModel* OpenedListItem::model(){
	return mdl;
}


}

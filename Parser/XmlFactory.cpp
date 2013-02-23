#include "XmlFactory.h"
#include "Project/DatasetEditModel.h"

namespace Parsers{

XmlFactory::XmlFactory(){}

XmlFactory& XmlFactory::getInstance(){
	static XmlFactory instance;
	return instance;
}

Project::Project* XmlFactory::parseProject(QString filename){
	Project::Project* prj = new Project::Project();
	prj->setPath(filename);
	prj->setName("blabla");
	prj->createModel("sdfsd", "sdfsdf", Project::DatasetEdit);
	prj->createModel("jkjj", "sdfsdf", Project::DatasetEdit);
	return prj;
}

BaseModel* XmlFactory::parseModel(QString filename){

}

}

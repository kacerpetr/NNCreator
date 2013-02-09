#include "ProjectParser.h"

namespace Parsers{

ProjectParser::ProjectParser(){}

ProjectParser& ProjectParser::getInstance(){
	static ProjectParser instance;
	return instance;
}

Project::Project* ProjectParser::loadProject(QString path) const{
	Project::Project* prj = new Project::Project();
	prj->setPath(path);
	prj->setName("blabla");
	prj->createModel("sdfsd", "sdfsdf", Project::DatasetEdit);
	prj->createModel("jkjj", "sdfsdf", Project::DatasetEdit);
	return prj;
}

bool ProjectParser::saveProject(QString path, Project::Project* project) const{
	return true;
}

}

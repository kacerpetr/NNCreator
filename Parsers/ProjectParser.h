#ifndef PROJECTPARSER_H
#define PROJECTPARSER_H

#include "Project/Project.h"

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parsers{

class ProjectParser{
	public:
		static ProjectParser& getInstance();
		Project::Project* loadProject(QString path) const;
		bool saveProject(Project::Project* project) const;

	private:
		ProjectParser();
		ProjectParser(ProjectParser const&);
		void operator=(ProjectParser const&);
};

}

#endif // PROJECTPARSER_H

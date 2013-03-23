#ifndef PROJECTPARSER_H
#define PROJECTPARSER_H

#include "Project/Project.h"
#include <QObject>

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

class ProjectParser : public QObject{
    Q_OBJECT

	public:
		static ProjectParser& get();
		ProjectData::Project* load(QString path) const;
		bool save(ProjectData::Project* project) const;

	private:
		ProjectParser();
		ProjectParser(ProjectParser const&);
		void operator=(ProjectParser const&);
};

}

#endif // PROJECTPARSER_H

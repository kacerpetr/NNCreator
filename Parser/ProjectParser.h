#ifndef PROJECTPARSER_H
#define PROJECTPARSER_H

#include "Project/Project.h"
#include <QObject>

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

/**
 * Project parser class.
 */
class ProjectParser : public QObject{
    Q_OBJECT

	public:
		static ProjectParser& get();
		ProjectData::Project* load(QString path) const;
		bool save(ProjectData::Project* project) const;

	private:
        /** Makes imposible to call class constructor by making it private. */
		ProjectParser();
        /** Makes imposible to call copy constructor by making it private. */
		ProjectParser(ProjectParser const&);
        /** Makes imposible to call operator= by making it private. */
		void operator=(ProjectParser const&);
};

}

#endif // PROJECTPARSER_H

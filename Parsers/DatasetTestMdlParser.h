#ifndef DATASETTESTMDLPARSER_H
#define DATASETTESTMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/DatasetTestModel.h"
using namespace Project;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parsers{

class DatasetTestMdlParser{
	public:
		static DatasetTestMdlParser& getInstance();
		DatasetTestModel* loadProject(QString path) const;
		bool saveProject(QString path, DatasetTestModel* project) const;

	private:
		DatasetTestMdlParser();
		DatasetTestMdlParser(DatasetTestMdlParser const&);
		void operator=(DatasetTestMdlParser const&);
};

}

#endif // DATASETTESTMDLPARSER_H

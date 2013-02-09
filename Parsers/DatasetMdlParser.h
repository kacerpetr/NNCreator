#ifndef DATASETMDLPARSER_H
#define DATASETMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/DatasetEditModel.h"
using namespace Project;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parsers{

class DatasetMdlParser{
	public:
		static DatasetMdlParser& getInstance();
		DatasetEditModel* loadProject(QString path) const;
		bool saveProject(QString path, DatasetEditModel* project) const;

	private:
		DatasetMdlParser();
		DatasetMdlParser(DatasetMdlParser const&);
		void operator=(DatasetMdlParser const&);
};

}

#endif // DATASETMDLPARSER_H

#ifndef DATASETMDLPARSER_H
#define DATASETMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/DatasetEditModel.h"
using namespace ProjectData;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parsers{

class DatasetMdlParser{
	public:
		static DatasetMdlParser& get();
		DatasetEditModel* load(QString path) const;
		bool save(DatasetEditModel* project) const;

	private:
		DatasetMdlParser();
		DatasetMdlParser(DatasetMdlParser const&);
		void operator=(DatasetMdlParser const&);
};

}

#endif // DATASETMDLPARSER_H

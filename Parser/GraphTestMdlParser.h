#ifndef GRAPHTESTMDLPARSER_H
#define GRAPHTESTMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/GraphTestModel.h"
using namespace ProjectData;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

class GraphTestMdlParser{
	public:
		static GraphTestMdlParser& get();
		GraphTestModel* load(QString path) const;
		bool save(GraphTestModel* mdl) const;

	private:
		GraphTestMdlParser();
		GraphTestMdlParser(GraphTestMdlParser const&);
		void operator=(GraphTestMdlParser const&);
};

}

#endif // GRAPHTESTMDLPARSER_H
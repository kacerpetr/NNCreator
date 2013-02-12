#ifndef GRAPHTESTMDLPARSER_H
#define GRAPHTESTMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/GraphTestModel.h"
using namespace Project;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parsers{

class GraphTestMdlParser{
	public:
		static GraphTestMdlParser& get();
		GraphTestModel* load(QString path) const;
		bool save(GraphTestModel* project) const;

	private:
		GraphTestMdlParser();
		GraphTestMdlParser(GraphTestMdlParser const&);
		void operator=(GraphTestMdlParser const&);
};

}

#endif // GRAPHTESTMDLPARSER_H

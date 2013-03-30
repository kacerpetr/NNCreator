#ifndef GRAPHTESTMDLPARSER_H
#define GRAPHTESTMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/GraphTestModel.h"
#include <QObject>
using namespace ProjectData;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

/**
 * Graph test model parser class.
 */
class GraphTestMdlParser : public QObject{
    Q_OBJECT

	public:
		static GraphTestMdlParser& get();
		GraphTestModel* load(QString path) const;
		bool save(GraphTestModel* mdl) const;

	private:
        /** Makes imposible to call class constructor by making it private. */
		GraphTestMdlParser();
        /** Makes imposible to call copy constructor by making it private. */
		GraphTestMdlParser(GraphTestMdlParser const&);
        /** Makes imposible to call operator= by making it private. */
		void operator=(GraphTestMdlParser const&);
};

}

#endif // GRAPHTESTMDLPARSER_H

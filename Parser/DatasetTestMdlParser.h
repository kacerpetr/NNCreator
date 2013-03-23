#ifndef DATASETTESTMDLPARSER_H
#define DATASETTESTMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/DatasetTestModel.h"
#include <QObject>
using namespace ProjectData;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

class DatasetTestMdlParser : public QObject{
    Q_OBJECT

	public:
		static DatasetTestMdlParser& get();
		DatasetTestModel* load(QString path) const;
		bool save(DatasetTestModel* mdl) const;

	private:
		DatasetTestMdlParser();
		DatasetTestMdlParser(DatasetTestMdlParser const&);
		void operator=(DatasetTestMdlParser const&);
};

}

#endif // DATASETTESTMDLPARSER_H

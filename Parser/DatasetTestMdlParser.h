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

/**
 * Dataset test model parser class.
 */
class DatasetTestMdlParser : public QObject{
    Q_OBJECT

	public:
		static DatasetTestMdlParser& get();
		DatasetTestModel* load(QString path) const;
		bool save(DatasetTestModel* mdl) const;

	private:
        /** Makes imposible to call class constructor by making it private. */
		DatasetTestMdlParser();
        /** Makes imposible to call copy constructor by making it private. */
		DatasetTestMdlParser(DatasetTestMdlParser const&);
        /** Makes imposible to call operator= by making it private. */
		void operator=(DatasetTestMdlParser const&);
};

}

#endif // DATASETTESTMDLPARSER_H

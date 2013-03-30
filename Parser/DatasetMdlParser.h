#ifndef DATASETMDLPARSER_H
#define DATASETMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/DatasetEditModel.h"
#include <QObject>
using namespace ProjectData;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

/**
 * Dataset model parser class.
 */
class DatasetMdlParser : public QObject{
    Q_OBJECT

	public:
		static DatasetMdlParser& get();
		DatasetEditModel* load(QString path) const;
		bool save(DatasetEditModel* mdl) const;

	private:
        /** Makes imposible to call class constructor by making it private. */
		DatasetMdlParser();
        /** Makes imposible to call copy constructor by making it private. */
		DatasetMdlParser(DatasetMdlParser const&);
        /** Makes imposible to call operator= by making it private. */
		void operator=(DatasetMdlParser const&);
};

}

#endif // DATASETMDLPARSER_H

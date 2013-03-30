#ifndef LRNCONFMDLPARSER_H
#define LRNCONFMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/LearningConfigModel.h"
#include <QObject>
using namespace ProjectData;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

/**
 * Learning config model class.
 */
class LrnConfMdlParser : public QObject{
    Q_OBJECT

	public:
		static LrnConfMdlParser& get();
		LearningConfigModel* load(QString path) const;
		bool save(LearningConfigModel* mdl) const;

	private:
        /** Makes imposible to call class constructor by making it private. */
		LrnConfMdlParser();
        /** Makes imposible to call copy constructor by making it private. */
		LrnConfMdlParser(LrnConfMdlParser const&);
        /** Makes imposible to call operator= by making it private. */
		void operator=(LrnConfMdlParser const&);
};

}

#endif // LRNCONFMDLPARSER_H

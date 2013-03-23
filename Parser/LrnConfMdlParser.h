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

class LrnConfMdlParser : public QObject{
    Q_OBJECT

	public:
		static LrnConfMdlParser& get();
		LearningConfigModel* load(QString path) const;
		bool save(LearningConfigModel* mdl) const;

	private:
		LrnConfMdlParser();
		LrnConfMdlParser(LrnConfMdlParser const&);
		void operator=(LrnConfMdlParser const&);
};

}

#endif // LRNCONFMDLPARSER_H

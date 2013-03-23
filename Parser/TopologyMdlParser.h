#ifndef TOPOLOGYMDLPARSER_H
#define TOPOLOGYMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/TopologyEditModel.h"
#include <QObject>
using namespace ProjectData;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

class TopologyMdlParser : public QObject{
    Q_OBJECT

	public:
		static TopologyMdlParser& get();
		TopologyEditModel* load(QString path) const;
		bool save(TopologyEditModel* mdl) const;

	private:
		TopologyMdlParser();
		TopologyMdlParser(TopologyMdlParser const&);
		void operator=(TopologyMdlParser const&);
};

}

#endif // TOPOLOGYMDLPARSER_H

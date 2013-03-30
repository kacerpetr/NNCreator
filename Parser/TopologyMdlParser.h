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

/**
 * Topology model parser class.
 */
class TopologyMdlParser : public QObject{
    Q_OBJECT

	public:
		static TopologyMdlParser& get();
		TopologyEditModel* load(QString path) const;
		bool save(TopologyEditModel* mdl) const;

	private:
        /** Makes imposible to call class constructor by making it private. */
		TopologyMdlParser();
        /** Makes imposible to call copy constructor by making it private. */
        TopologyMdlParser(TopologyMdlParser const&);
        /** Makes imposible to call operator= by making it private. */
        void operator=(TopologyMdlParser const&);
};

}

#endif // TOPOLOGYMDLPARSER_H

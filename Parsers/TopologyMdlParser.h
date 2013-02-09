#ifndef TOPOLOGYMDLPARSER_H
#define TOPOLOGYMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/TopologyEditModel.h"
using namespace Project;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parsers{

class TopologyMdlParser{
	public:
		static TopologyMdlParser& getInstance();
		TopologyEditModel* loadProject(QString path) const;
		bool saveProject(QString path, TopologyEditModel* project) const;

	private:
		TopologyMdlParser();
		TopologyMdlParser(TopologyMdlParser const&);
		void operator=(TopologyMdlParser const&);
};

}

#endif // TOPOLOGYMDLPARSER_H

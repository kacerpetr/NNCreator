#ifndef XMLFACTORY_H
#define XMLFACTORY_H

#include <QList>
#include "Project/Project.h"
using namespace Project;

namespace Parsers{

class XmlFactory{
	public:
		static XmlFactory& getInstance();
		Project::Project* parseProject(QString filename);
		BaseModel* parseModel(QString filename);

	private:
		XmlFactory();
		XmlFactory(XmlFactory const&);
		void operator=(XmlFactory const&);
};

}

#endif // XMLFACTORY_H

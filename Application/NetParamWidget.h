#ifndef NETPARAMWIDGET_H
#define NETPARAMWIDGET_H

#include <QWidget>
#include "Project/TopologyEditModel.h"
using namespace Project;

namespace Ui {
	class NetParamWidget;
}

namespace Application{

class NetParamWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit NetParamWidget(QWidget *parent = 0);
		~NetParamWidget();
		void setModel(TopologyEditModel* model);
		bool hasModel();

	private slots:
		void randomizeWeights();
		void randomizeBias();

	private:
		TopologyEditModel* mdl;
		Ui::NetParamWidget *ui;
};

}

#endif // NETPARAMWIDGET_H

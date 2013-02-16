#ifndef NETPARAMWIDGET_H
#define NETPARAMWIDGET_H

#include <QWidget>
#include "Project/TopologyEditModel.h"
using namespace ProjectData;

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
		void setBiasSeed(int val);
		void setBiasMin(double val);
		void setBiasMax(double val);
		void setWgSeed(int val);
		void setWgMin(double val);
		void setWgMax(double val);
	private:
		TopologyEditModel* mdl;
		Ui::NetParamWidget *ui;
};

}

#endif // NETPARAMWIDGET_H

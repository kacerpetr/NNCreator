#ifndef NETPARAMWIDGET_H
#define NETPARAMWIDGET_H

#include <QWidget>
#include "Project/TopologyEditModel.h"
using namespace ProjectData;

namespace Ui {
	class NetParamWidget;
}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Network parameter widget class.
 */
class NetParamWidget : public QWidget{
	Q_OBJECT
		
	public:
        NetParamWidget(QWidget *parent = 0);
		~NetParamWidget();
		void setModel(TopologyEditModel* model);
		bool hasModel();		

	private slots:
		void modelChanged(ChangeType type);
		void randomizeWeights();
		void randomizeBias();
        void randomizeSlope();
		void setBiasSeed(int val);
		void setBiasMin(double val);
		void setBiasMax(double val);
		void setWgSeed(int val);
		void setWgMin(double val);
		void setWgMax(double val);
        void setSlopeSeed(int val);
        void setSlopeMin(double val);
        void setSlopeMax(double val);
		void trFcnSelected(int index);

	private:
		void setNetStats();
		void setRandGenParams();
		void setTrFcnBox();

	private:
        /** Net param widget ui pointer. */
        Ui::NetParamWidget *ui;
        /** Topology edit model pointer. */
		TopologyEditModel* mdl;
};

}

#endif // NETPARAMWIDGET_H

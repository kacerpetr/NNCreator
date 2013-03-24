#ifndef OUTPUTGRAPHWIDGET_H
#define OUTPUTGRAPHWIDGET_H

#include <QWidget>
#include "Project/GraphTestModel.h"

using namespace ProjectData;
namespace Ui{class OutputGraphWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The OutputGraphWidget class.
 */
class OutputGraphWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit OutputGraphWidget(QWidget *parent = 0);
		~OutputGraphWidget();
		void setModel(GraphTestModel* model);
		bool hasModel();
		void setPlot();

	private slots:
        void modelChanged(ChangeType type);
		void drawGraph();
		void networkSelected(QString name);
		void outputChanged(int value);
		void closeBtnPressed();

	private:
        void genSelectedLists();

	signals:
		void closePressed(BaseModel*);

	private:
		Ui::OutputGraphWidget *ui;
		GraphTestModel* model;
};

}

#endif // OUTPUTGRAPHWIDGET_H

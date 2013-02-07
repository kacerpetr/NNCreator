#ifndef OUTPUTGRAPHWIDGET_H
#define OUTPUTGRAPHWIDGET_H

#include <QWidget>
#include "Project/GraphTestModel.h"

using namespace Project;
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

	private:
		Ui::OutputGraphWidget *ui;
		GraphTestModel* model;
};

}

#endif // OUTPUTGRAPHWIDGET_H

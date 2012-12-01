#ifndef OUTPUTGRAPHWIDGET_H
#define OUTPUTGRAPHWIDGET_H

#include <QWidget>
#include "Project/GraphTestModel.h"

using namespace Project;

namespace Ui {
	class OutputGraphWidget;
}

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

#endif // OUTPUTGRAPHWIDGET_H

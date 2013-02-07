#ifndef DATASETEDITWIDGET_H
#define DATASETEDITWIDGET_H

#include <QWidget>
#include "Project/DatasetEditModel.h"

using namespace Project;
namespace Ui{class DatasetEditWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The DatasetEditWidget class.
 */
class DatasetEditWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit DatasetEditWidget(QWidget *parent = 0);
		~DatasetEditWidget();
		void setModel(DatasetEditModel* model);
		bool hasModel();

	public slots:
		void showContextMenu();

	private:
		Ui::DatasetEditWidget *ui;
		Project::DatasetEditModel* model;
};

}

#endif // DATASETEDITWIDGET_H

#ifndef DATASETEDITWIDGET_H
#define DATASETEDITWIDGET_H

#include <QWidget>
#include "Project/DatasetEditModel.h"

using namespace ProjectData;
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
		void changePatternCount();
		void changeInputCount();
		void changeOutputCount();

	private slots:
		void closeBtnPressed();

	signals:
		void closePressed(BaseModel*);

	private:
		Ui::DatasetEditWidget *ui;
		ProjectData::DatasetEditModel* model;
};

}

#endif // DATASETEDITWIDGET_H

#ifndef DATASETTESTWIDGET_H
#define DATASETTESTWIDGET_H

#include <QWidget>
#include "Project/DatasetTestModel.h"
#include "Project/Project.h"

using namespace ProjectData;
namespace Ui{class DatasetTestWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The DatasetTestWidget class.
 */
class DatasetTestWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit DatasetTestWidget(QWidget *parent = 0);
		~DatasetTestWidget();
		void setModel(DatasetTestModel* model);
		bool hasModel();

	private slots:
		void modelchanged(ChangeType type);
		void closeBtnPressed();
		void startTest();
		void networkSelected(QString name);
		void datasetSelected(QString name);

	private:
		void genSelectedLists();

	signals:
		void closePressed(BaseModel*);

	private:
		Ui::DatasetTestWidget *ui;
		DatasetTestModel* model;
		DatasetEditModel* emptyModel;
};

}

#endif // DATASETTESTWIDGET_H

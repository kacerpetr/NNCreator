#ifndef DATASETEDITWIDGET_H
#define DATASETEDITWIDGET_H

#include <QMenu>
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

	private slots:
		void closeBtnPressed();
		void showContextMenu();
		void changePatternCount(int value);
		void changeInputCount(int value);
		void changeOutputCount(int value);
		void copyCell();
		void cutCell();
		void pasteCell();
		void deleteCell();

	signals:
		void closePressed(BaseModel*);

	private:
		bool editValOk;
		double editVal;
		Ui::DatasetEditWidget *ui;
		ProjectData::DatasetEditModel* model;
		QMenu* contextMenu;
};

}

#endif // DATASETEDITWIDGET_H

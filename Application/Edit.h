#ifndef EDIT_H
#define EDIT_H

#include <QWidget>
#include "TrainingPatterns.h"
#include "Topology.h"
#include "Learning.h"
#include "Testing.h"
#include "Graphs.h"

namespace Ui{
	class Edit;
}

class Edit : public QWidget{
	Q_OBJECT

	public:
		explicit Edit(QWidget *parent = 0);
		void setWidget(int id);
		void hideAll(void);
		~Edit();

	private:
		Ui::Edit *ui;
		TrainingPatterns* trainingPatterns;
		Topology* topology;
		Learning* learning;
		Testing* testing;
		Graphs* graphs;
};

#endif // EDIT_H

#ifndef GRAPHS_H
#define GRAPHS_H

#include <QWidget>

namespace Ui {
class Graphs;
}

class Graphs : public QWidget
{
		Q_OBJECT
		
	public:
		explicit Graphs(QWidget *parent = 0);
		~Graphs();
		
	private:
		Ui::Graphs *ui;
};

#endif // GRAPHS_H

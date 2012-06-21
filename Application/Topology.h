#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <QWidget>

namespace Ui{
	class Topology;
}

class Topology : public QWidget{
	Q_OBJECT

	public:
		explicit Topology(QWidget *parent = 0);
		~Topology();

	private:
		Ui::Topology *ui;
};

#endif // TOPOLOGY_H

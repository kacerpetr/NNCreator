#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "AbstractLrnAlg.h"
#include "AbstractBpNet.h"
#include "AbstractDataset.h"

namespace NeuralNetwork{

class BpAlgSt : public AbstractLrnAlg{
	public:
		BpAlgSt();
		~BpAlgSt();
		double iterate(unsigned int pattern);
		double alpha;

	private:
		inline double transferFcnD(double x) const;

	private:
		AbstractDataset* data;
		AbstractBpNet* bpNet;
};

}

#endif // BACKPROPAGATION_H

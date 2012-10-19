#ifndef ABSTRACTTRAININGPATTERN_H
#define ABSTRACTTRAININGPATTERN_H

namespace NeuralNetwork{

class AbstractTrainingPattern{
	public:
		virtual void appendPattern() = 0;
		virtual ~AbstractTrainingPattern() = 0;
};

}

#endif // ABSTRACTTRAININGPATTERN_H

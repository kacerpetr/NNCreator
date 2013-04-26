#ifndef LEARNINGCONFIGMODEL_H
#define LEARNINGCONFIGMODEL_H

#include <QString>
#include <QStringList>
#include "BaseModel.h"
#include "NeuralNetwork/BpAlgSt.h"
#include "NeuralNetwork/LrnEngine.h"
#include "TopologyEditModel.h"
#include "GuiPart/Plot1D.h"

namespace Application{
    class Plot1D;
}

using namespace Application;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Learning configuration data model class.
 */
class LearningConfigModel : public BaseModel{
	Q_OBJECT

	public:
		LearningConfigModel();
		~LearningConfigModel();
		void startLearning();
        void stepLearning();
		void stopLearning();
		void setMaxIter(int value);
		void setMaxErr(double value);
		void setMaxTime(int value);
		void setLrnCoef(double value);
		void setUpdateInterval(int value);
		int maxIter();
		double maxErr();
		int maxTime();
		double lrnCoef();
		int updateInterval();
        void fillPlot(QString data);
		Plot1D* plot();
		virtual void save();
        void reinitNetwork();

	public slots:
        void lrnStarted();
        void lrnStoped();
		void lrnUpdate(int iteration, long time, double error);
        void addPlot(QString name);

	signals:
        /** Emitted when learning is started. */
		void started();
        /** Emitted when learning is stoped. */
        void stoped();
        /** Emitted every update interval during learning. */
		void update(int iteration, long time, double error);

	private:
        /** Learning error plot. */
		Plot1D* plt;
        /** Learning engine. */
		LrnEngine eng;
        /** Stop iteration. */
		int maxIterV;
        /** Stop error value. */
		double maxErrV;
        /** Stop time in miliseconds. */
		int maxTimeV;
        /** Learning coeficient value. */
		double lrnCoefV;
        /** Learning algorithm emits update signal each interval of iterations. */
		int updateIntervalV;
        /** Iteration after last learning finished. */
        double prevIter;
};

}

#endif // LEARNINGCONFIGMODEL_H

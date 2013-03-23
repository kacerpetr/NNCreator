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

	public slots:
        void lrnStarted();
        void lrnStoped();
		void lrnUpdate(int iteration, long time, double error);
        void addPlot(QString name);

	signals:
		void started();
        void stoped();
		void update(int iteration, long time, double error);

	private:
		Plot1D* plt;
		LrnEngine eng;
		int maxIterV;
		double maxErrV;
		int maxTimeV;
		double lrnCoefV;
		int updateIntervalV;
        double prevIter;
};

}

#endif // LEARNINGCONFIGMODEL_H

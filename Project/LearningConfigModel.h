#ifndef LEARNINGCONFIGMODEL_H
#define LEARNINGCONFIGMODEL_H

#include <QString>
#include <QStringList>
#include "BaseModel.h"
#include "NeuralNetwork/BpAlgSt.h"
#include "NeuralNetwork/LrnEngine.h"
#include "TopologyEditModel.h"

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

		QString networkName();
		QString datasetName();
		void setNetworkName(QString name);
		void setDatasetName(QString name);

		QStringList networkList();
		QStringList datasetList(QString name);

		TopologyEditModel* topologyEditModel(QString name);

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

		void save();

	public slots:
		void lrnStarted();
		void lrnStoped(int iteration, long time, double error);
		void lrnUpdate(int iteration, long time, double error);

	signals:
		void started();
		void stoped(int iteration, long time, double error);
		void update(int iteration, long time, double error);

	private:
		LrnEngine eng;
		QString trSet;
		QString mlNet;
		int maxIterV;
		double maxErrV;
		int maxTimeV;
		double lrnCoefV;
		int updateIntervalV;
};

}

#endif // LEARNINGCONFIGMODEL_H

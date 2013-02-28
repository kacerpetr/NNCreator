#ifndef LEARNINGCONFIGMODEL_H
#define LEARNINGCONFIGMODEL_H

#include <QString>
#include <QStringList>
#include "BaseModel.h"
#include "Project.h"
#include "NeuralNetwork/BpAlgSt.h"
#include "NeuralNetwork/LrnEngine.h"

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

class Project;

/**
 * Learning configuration data model class.
 */
class LearningConfigModel : public QObject, public BaseModel{
	Q_OBJECT

	public:
		LearningConfigModel();
		~LearningConfigModel();

		void setProject(Project* prj);

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
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);

	public slots:
		void lrnStarted();
		void lrnStoped(int iteration, long time, double error);
		void lrnUpdate(int iteration, long time, double error);

	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);
		void started();
		void stoped(int iteration, long time, double error);
		void update(int iteration, long time, double error);

	private:
		Project* prj;
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

#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#include <QString>
#include <QColor>

/** Project data model types. */
enum ModelType{
	DatasetEdit,    /**< Dataset editor model. */
	TopologyEdit,   /**< Topology editor model. */
	LearningConfig, /**< Learning configuration model. */
	DatasetTest,    /**< Dataset test model. */
	GraphTest       /**< Output graph model. */
};

/** Type of change in model. */
enum ChangeType{
    WeightChange,   /**< Change of weight in neural network. */
    TopologyChange, /**< Change of neural network topology. */
    NetParamChange, /**< Value change in netParamWidget. */
    TrFcnChange,    /**< Change of transfer function. */
    ModelRenamed,   /**< Change in model name. */
    SelectedNetworkRenamed, /**< Used when selected model is renamed. */
    SelectedDatasetRenamed, /**< Used when selected dataset is renamed. */
    SelectedNetworkDeleted, /**< Used when selected model is deleted. */
    SelectedDatasetDeleted  /**< Used when selected dataset is deleted. */
};

/** Neuron transfer function types. */
enum TransferFcn{
    UnarySigmoid = 1, /**< Unary sigmoid function with output between 0 and 1.   */
    BinarySigmoid = 2 /**< Binary sigmoid function with output between -1 and 1. */
};

/** One dimensional point. */
typedef struct{
    double x; /**< X axis position. */
    double o; /**< Point value. */
}Point1D;

/** Two dimensional point. */
typedef struct{
    double x; /**< X axis position. */
    double y; /**< Y axis position. */
    double o; /**< Point value. */
}Point2D;

/** Three dimensional point. */
typedef struct{
    double x; /**< X axis position. */
    double y; /**< Y axis position. */
    double z; /**< Z axis position. */
    double o; /**< Point value. */
}Point3D;

/** Rounds given number to given number of digits. */
double round(double value, int digit);

/** Returns random number between min and max. */
double random(double min, double max);

/** Returns random number based on given seed between min and max. */
double random(int seed, double from, double to);

/** Returns random integer between min and max. */
int random(int from, int to);

/** Returns random number based on given seed between min and max. */
int random(int from, int to, int seed);

/** Returns color from list of colors. */
QColor color(int index);

#endif // GLOBALDEF_H

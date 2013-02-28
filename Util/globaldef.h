#ifndef GLOBALDEF_H
#define GLOBALDEF_H

/** Project data model types. */
enum ModelType{
	DatasetEdit,    /**< Dataset editor model. */
	TopologyEdit,   /**< Topology editor model. */
	LearningConfig, /**< Learning configuration model. */
	DatasetTest,    /**< Dataset test model. */
	GraphTest       /**< Output graph model. */
};

typedef struct{
	double x;
	double o;
}Point1D;

typedef struct{
	double x;
	double y;
	double o;
}Point2D;

typedef struct{
	double x;
	double y;
	double z;
	double o;
}Point3D;

#endif // GLOBALDEF_H

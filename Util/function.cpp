#include "function.h"
#include <sstream>
#include <math.h>
#include <assert.h>
#include <ctime>
#include <cstdlib>

namespace Util{

double stringToDouble(const std::string& str){
	std::istringstream i(str);
	double x;
	if(!(i >> x)) return 0;
	return x;
}

double round(double value, int digit = 1){
	assert(digit >= 1 && digit < 100);

	double shift = pow(10.0, (double)digit);
	value = value * shift;

	double intpart = 0;
	if(modf(value, &intpart) >= 0.5){
		value = value >= 0.0 ? ceil(value):floor(value);
	}else{
		value = value < 0.0 ? ceil(value):floor(value);
	}

	return value / shift;
}

double random(double from, double to){
	static int count = 1;
	count += 1;
	int seed = (int)(1*(sin(count/M_PI))*100);
	srand(seed);
	float rnd = rand()/((double)RAND_MAX);
	return from + rnd*(to - from);
}

double random(int seed, double from, double to){
	srand(seed);
	float rnd = rand()/((double)RAND_MAX);
	return from + rnd*(to - from);
}

int random(int from, int to){
	static int count = 1;
	count += 1;
	int seed = (int)(1*(sin(count/M_PI))*100);
	srand(seed);
	int rnd = rand()/(RAND_MAX);
	return from + rnd*(to - from);
}

}

#include "function.h"
#include <sstream>
#include <math.h>
#include <assert.h>
#include <ctime>
#include <cstdlib>
#include <QList>

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

int random(int from, int to, int seed){
    srand(seed);
    int rnd = rand()/(RAND_MAX);
    return from + rnd*(to - from);
}

QColor color(int index){
    switch(index){
        case 0 : return QColor(255, 0, 0);
        case 1 : return QColor(0, 255, 0);
        case 2 : return QColor(0, 0, 255);
        case 3 : return QColor(255, 255, 0);
        case 4 : return QColor(255, 0, 255);
        case 5 : return QColor(0, 255, 255);
        case 6 : return QColor(128, 128, 128);
        case 7 : return QColor(128, 0, 0);
        case 8 : return QColor(0, 128, 0);
        case 9 : return QColor(0, 0, 128);
        case 10: return QColor(255, 100, 100);
        case 11: return QColor(100, 255, 100);
        case 12: return QColor(100, 100, 255);
        case 13: return QColor(255, 128, 0);
        case 14: return QColor(128, 255, 0);
        case 15: return QColor(0, 255, 128);
        case 16: return QColor(0, 128, 255);
        case 17: return QColor(255, 0, 128);
        case 18: return QColor(128, 0, 255);
        default:
            int r = random(0, 255,-index);
            int g = random(0, 255, index);
            int b = random(0, 255, index*index);
            return QColor(r, g, b);
    }
}

}

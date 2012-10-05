#include "function.h"
#include <sstream>
#include <math.h>
#include <assert.h>

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

}

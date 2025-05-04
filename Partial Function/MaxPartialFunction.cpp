#include "MaxPartialFunction.h"
#include <iostream>

bool MaxPartialFunction::isDefined(int32_t x) const {
	for (size_t i = 0; i < funcs.getSize(); i++) {
		if (!funcs[i]->isDefined(x)) {
			return false;
		}
	}
	return true;
}

int32_t MaxPartialFunction::getValue(int32_t x) const {
	int32_t max = INT_MIN;
	for (size_t i = 0; i < funcs.getSize(); i++) {
		if (funcs[i]->isDefined((x))) {
			max = std::max(max, funcs[i]->getValue(x));
		}	
	}
	return max;
}

int MaxPartialFunction::getMinDefinedPoint() const{
    int minPoint = INT32_MAX;
    for (int i = 0; i < funcs.getSize(); i++) {
        int minFuncPoint = funcs[i]->getMinDefinedPoint();
        if (minFuncPoint < minPoint) {
            minPoint = minFuncPoint;
        }
    }
    return minPoint;
}

int MaxPartialFunction::getMaxDefinedPoint() const{
    int maxPoint = INT32_MIN;
    for (int i = 0; i < funcs.getSize(); i++) {
        int maxFuncPoint = funcs[i]->getMaxDefinedPoint();
        if (maxFuncPoint > maxPoint) {
            maxPoint = maxFuncPoint;
        }
    }
    return maxPoint;
}
#include "MinPartialFunction.h"
#include <iostream>

bool MinPartialFunction::isDefined(int32_t x) const {
	for (size_t i = 0; i < funcs.getSize(); i++) {
		if (!funcs[i]->isDefined(x)) {
			return false;
		}
	}
	return true;
}
int32_t MinPartialFunction::getValue(int32_t x) const {
	int32_t min = INT_MAX;
	for (size_t i = 0; i < funcs.getSize(); i++) {
		if (!funcs[i]->isDefined((x))) {
			throw std::runtime_error("Not all functions are defined");
		}
		min = std::min(min, funcs[i]->getValue(x));
	}
	return min;
}

int MinPartialFunction::getMinDefinedPoint() const {
    int minPoint = INT32_MAX;
    for (int i = 0; i < funcs.getSize(); i++) {
        int minFuncPoint = funcs[i]->getMinDefinedPoint();
        if (minFuncPoint < minPoint) {
            minPoint = minFuncPoint;
        }
    }
    return minPoint;
}

int MinPartialFunction::getMaxDefinedPoint() const {
    int maxPoint = INT32_MIN;
    for (int i = 0; i < funcs.getSize(); i++) {
        int maxFuncPoint = funcs[i]->getMaxDefinedPoint();
        if (maxFuncPoint > maxPoint) {
            maxPoint = maxFuncPoint;
        }
    }
    return maxPoint;
}
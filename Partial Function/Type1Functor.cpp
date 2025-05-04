#include "Type1Functor.h"

FunctionResult Type1Functor::operator() (int32_t x) const {
	for (size_t i = 0;i<arrayOfUndefinedPoints.getSize();i++) {
		if (x == arrayOfUndefinedPoints[i]) {
			return { false, 0 };
		}
	}
	return { true, x };
}

int Type1Functor::getMinDefinedPoint() const {
	int minDefinedPoint = INT32_MAX;
	for (size_t i = 0; i < arrayOfUndefinedPoints.getSize(); i++)
	{
		if (arrayOfUndefinedPoints[i] < minDefinedPoint) {
			minDefinedPoint = arrayOfUndefinedPoints[i];
		}
	}
	return minDefinedPoint;
}
int Type1Functor::getMaxDefinedPoint() const {
	int maxDefinedPoint = INT32_MIN;
	for (size_t i = 0; i < arrayOfUndefinedPoints.getSize(); i++)
	{
		if (arrayOfUndefinedPoints[i] > maxDefinedPoint) {
			maxDefinedPoint = arrayOfUndefinedPoints[i];
		}
	}
	return maxDefinedPoint;
}

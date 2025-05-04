#include "Type2Functor.h"

FunctionResult Type2Functor::operator() (int32_t x) const {
	for (size_t i = 0;i<arrayOfOnes.getSize();i++) {
		if (x == arrayOfOnes[i]) {
			return { true, 1 };
		}
	}
	return { true, 0 };
}

int Type2Functor::getMinDefinedPoint() const {
	int minDefinedPoint = INT32_MAX;
	for (size_t i = 0; i < arrayOfOnes.getSize(); i++)
	{
		if (arrayOfOnes[i] < minDefinedPoint) {
			minDefinedPoint = arrayOfOnes[i];
		}
	}
	return minDefinedPoint;
}
int Type2Functor::getMaxDefinedPoint() const {
	int maxDefinedPoint = INT32_MIN;
	for (size_t i = 0; i < arrayOfOnes.getSize(); i++)
	{
		if (arrayOfOnes[i] > maxDefinedPoint) {
			maxDefinedPoint = arrayOfOnes[i];
		}
	}
	return maxDefinedPoint;
}

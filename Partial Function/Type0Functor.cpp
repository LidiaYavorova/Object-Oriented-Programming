#include "Type0Functor.h"

FunctionResult Type0Functor::operator() (int32_t x) const {
	for (int i = 0; i < args.getSize(); i++) {
		if (x == args[i]) {
			return { true, result[i] };
		}
	}
	return { false, 0 };
}

int Type0Functor::getMinDefinedPoint() const {
	int minDefinedPoint = INT32_MAX;
	for (size_t i = 0; i < args.getSize(); i++)
	{
		if (args[i] < minDefinedPoint) {
			minDefinedPoint = args[i];
		}
	}
	return minDefinedPoint;
}
int Type0Functor::getMaxDefinedPoint() const {
	int maxDefinedPoint = INT32_MIN;
	for (size_t i = 0; i < args.getSize(); i++)
	{
		if (args[i] > maxDefinedPoint) {
			maxDefinedPoint = args[i];
		}
	}
	return maxDefinedPoint;
}

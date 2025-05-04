#pragma once
#include <iostream>
#include "vector.hpp"
#include "FunctionResult.h"

class Type1Functor {
public:
	Type1Functor(const Vector<int32_t>& arrayOfUndefinedPoints) : arrayOfUndefinedPoints(arrayOfUndefinedPoints) {}
	FunctionResult operator() (int32_t x) const;
	int getMinDefinedPoint() const;
	int getMaxDefinedPoint() const;
private:
	Vector<int32_t> arrayOfUndefinedPoints;
};

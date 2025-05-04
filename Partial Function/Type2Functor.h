#pragma once
#include "Vector.hpp"
#include <iostream>
#include "FunctionResult.h"

class Type2Functor {
public:
	Type2Functor(const Vector<int32_t>& arrayOfOnes) : arrayOfOnes(arrayOfOnes) {}
	FunctionResult operator() (int32_t x) const;
	int getMinDefinedPoint() const;
	int getMaxDefinedPoint() const;
private:
	Vector<int32_t> arrayOfOnes;
};

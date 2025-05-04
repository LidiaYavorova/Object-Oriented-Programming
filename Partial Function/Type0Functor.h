#pragma once
#include "Vector.hpp"
#include "FunctionResult.h"
#include <iostream>

class Type0Functor {
public:
	Type0Functor(const Vector<int32_t>& args, const Vector<int32_t>& result) : args(args), result(result) {}
	FunctionResult operator() (int32_t x) const;
	int getMinDefinedPoint() const;
	int getMaxDefinedPoint() const;

private:
	Vector<int32_t> args;
	Vector<int32_t> result;
};
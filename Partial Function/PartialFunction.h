#pragma once
#include <iostream>
#include "FunctionResult.h"

class PartialFunction {
public:
	virtual ~PartialFunction() = default;
	virtual bool isDefined(int32_t x) const = 0;
	virtual int32_t getValue(int32_t x) const = 0;
	virtual int getMinDefinedPoint() const = 0;
	virtual int getMaxDefinedPoint() const = 0;

	FunctionResult operator()(int32_t x) const {
		const bool defined = isDefined(x);
		if (!defined) {
			return FunctionResult();
		}
		return FunctionResult(true, getValue(x));
	}
};

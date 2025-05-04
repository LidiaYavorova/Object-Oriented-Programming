#pragma once
#include "PartialFunction.h"

template <typename Func>
class PartialFunctionCriteria : public PartialFunction {
public:
	PartialFunctionCriteria(Func&& func) : func(std::move(func)) {}
	virtual bool isDefined(int32_t x) const override {
		return func(x).defined();
	}

	virtual int32_t getValue(int32_t x) const override {
		return func(x).getValue();
	}

	virtual int getMinDefinedPoint() const override {
		return func.getMinDefinedPoint();
	}

	virtual int getMaxDefinedPoint() const override {
		return func.getMaxDefinedPoint();
	}
private:
	Func func;
};
#pragma once
#include "PartialFunction.h"
#include "Vector.hpp"

class MinPartialFunction : public PartialFunction {
public:
	MinPartialFunction(Vector<PartialFunction*>&& funcs) : funcs(std::move(funcs)) {}
	virtual bool isDefined(int32_t x) const override;
	virtual int32_t getValue(int32_t x) const override;
    virtual int getMinDefinedPoint() const override;
	virtual int getMaxDefinedPoint() const override;

private:
	Vector<PartialFunction*> funcs;
};


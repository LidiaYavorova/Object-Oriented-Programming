#pragma once
#include <iostream>

class FunctionResult {
public:
	FunctionResult() : isDefined(false), value(0) {}
	FunctionResult(bool defined, int32_t value) : isDefined(defined), value(value) {}
	bool defined() const;
	int32_t getValue() const;
private:
	bool isDefined;
	int32_t value;
};


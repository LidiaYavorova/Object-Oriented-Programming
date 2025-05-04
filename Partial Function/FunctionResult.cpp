#include "FunctionResult.h"

bool FunctionResult::defined() const {
	return isDefined;
}

int32_t FunctionResult::getValue() const {
	return value;
}

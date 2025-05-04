#include "2.h"
#include <fstream>
int16_t ModifiableIntegerFunction::operator()(int16_t input) const { 
	return f(input); 
}


ModifiableIntegerFunction::ModifiableIntegerFunction() {
	result = new int16_t[SIZE];
	isExcluded = new bool[SIZE];
	for (size_t i = 0; i < SIZE; i++)
	{
		result[i] = 0;
		isExcluded[i] = 0;
	}
}

void ModifiableIntegerFunction::free() {
	delete[] result;
	result = nullptr;
	delete[] isExcluded;
	isExcluded = nullptr;
}

void ModifiableIntegerFunction::copyFrom(const ModifiableIntegerFunction& other) {
	result = new int16_t[SIZE];
	isExcluded = new bool[SIZE];
	for (size_t i = 0; i < SIZE; i++)
	{
		result[i] = other.result[i];
		isExcluded[i] = other.isExcluded[i];
	}
}

ModifiableIntegerFunction::ModifiableIntegerFunction(const ModifiableIntegerFunction& other) {
	copyFrom(other);
}

ModifiableIntegerFunction& ModifiableIntegerFunction::operator=(const ModifiableIntegerFunction& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

ModifiableIntegerFunction::~ModifiableIntegerFunction() {
	free();
}

ModifiableIntegerFunction::ModifiableIntegerFunction(int16_t(*func)(int16_t)) {
	result = new int16_t[SIZE];
	isExcluded = new bool[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		
		result[i] = func(i-offsetIndex);
		isExcluded[i] = 0;	

	}
}

void ModifiableIntegerFunction::setSpecificValue(int16_t input, int16_t output) {
	uint16_t index = input + offsetIndex;
	result[index] = output;
}

void ModifiableIntegerFunction::exclusionOfPoint(int16_t input) {
	uint16_t index = input + offsetIndex;
	isExcluded[index] = 1;
	
}

int16_t ModifiableIntegerFunction::f(int16_t input) const{
	uint16_t index = input + offsetIndex;
	if (isExcluded[index] == 1) {
		throw std::invalid_argument("Excluded point");
	}
	else {
		return result[index];
	}
}


ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	ModifiableIntegerFunction add;
	for (size_t i = 0; i < SIZE; i++)
	{
		add.result[i] = lhs.result[i] + rhs.result[i];
		add.isExcluded[i] = lhs.isExcluded[i] || rhs.isExcluded[i];
	}
	return add;
}


ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	ModifiableIntegerFunction add;
	for (size_t i = 0; i < SIZE; i++)
	{
		add.result[i] = lhs.result[i] - rhs.result[i];
		add.isExcluded[i] = lhs.isExcluded[i] || rhs.isExcluded[i];
	}
	return add;
}


bool operator>(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	for (size_t i = 0; i < SIZE; i++)
	{
		if ( lhs.isExcluded[i] || lhs.result[i] <= rhs.result[i]) {
			return false;
		}
	}
	return true;
}

bool operator<(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	for (size_t i = 0; i < SIZE; i++)
	{
		
		if (rhs.isExcluded[i] ||  lhs.result[i] >= rhs.result[i] ) {
			return false;
		}
	}
	return true;
}

bool operator>=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	return !(lhs < rhs);
}
bool operator<=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	return !(lhs > rhs);
}


bool operator==(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	int constant = lhs.result[0] - rhs.result[0];;
	for (size_t i = 0; i < SIZE; i++)
	{
		if (lhs.isExcluded[i] == rhs.isExcluded[i]) {
			if (lhs.result[i] - rhs.result[i] != constant) {
				return false;
			}
		}
		else {
			return false;
		}
		
	}
	return true;
}

ModifiableIntegerFunction operator*(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs) {
	ModifiableIntegerFunction composition;
	for (size_t i = 0; i < SIZE; i++)
	{	
		composition.result[i] = lhs.result[(uint16_t)rhs.result[i]+offsetIndex];
		composition.isExcluded[i] = rhs.isExcluded[i] || lhs.isExcluded[rhs.result[i]+offsetIndex];
	}
	return composition;
}

ModifiableIntegerFunction operator^(const ModifiableIntegerFunction& lhs, int k) {
	ModifiableIntegerFunction newFunction;
	if (k == -1) {
		for (size_t i = 0; i < SIZE; i++)
		{
		     newFunction.isExcluded[i] = true;
		}
		for (int i = 0; i < SIZE; i++)
		{
			if (!lhs.isExcluded[i]) {
				newFunction.isExcluded[(uint16_t)(lhs.result[i] + offsetIndex)] = false;
				newFunction.result[(uint16_t)(lhs.result[i] + offsetIndex)] = i - offsetIndex;
			}
		}
	}
	else if (k < -1) {
		throw std::logic_error("Logic error");
	}
	else {
		newFunction = lhs;
		for (size_t i = 0; i < k-1; i++)
		{
			newFunction = newFunction * lhs;
		}
	}
	
	return newFunction;
 }

bool ModifiableIntegerFunction::isSurjection() const {

	for (int y = INT16_MIN; y <= INT16_MAX; ++y) {
		bool found = false;
		for (int x = 0; x <= SIZE; ++x) {
			if (f(y) == result[x]) {
				found = true;
				break;
			}
		}
		if (!found) {
			return false;
		}
	}
	return true;

}

bool ModifiableIntegerFunction::isInjection() const {
	for (int x1 = INT16_MIN; x1 <= INT16_MAX; ++x1) {
		for (int x2 = INT16_MIN; x2 <= INT16_MAX; ++x2) {
			if (f(x1) == f(x2)) {
				return false;
			}
		}
	}
	return true;
}

bool ModifiableIntegerFunction::isBijection() const {
	return this->isInjection() && this->isSurjection();
}

void ModifiableIntegerFunction::writeToFile(std::ofstream& ofs) const {	
	ofs.write((const char*)result, sizeof(int16_t) * SIZE);
	ofs.write((const char*)isExcluded, sizeof(bool) * SIZE);

}

void ModifiableIntegerFunction::writeToFile(const char* fileName) const {
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "Unable to open the file" << std::endl;
		return;
	}
	writeToFile(ofs);
}

void ModifiableIntegerFunction::readFromFile(std::ifstream& ifs) {
	result = new int16_t[SIZE];
	isExcluded = new bool[SIZE];
	ifs.read((char*)result, sizeof(int16_t) * SIZE);
	ifs.read((char*)isExcluded, sizeof(bool) * SIZE);
}

void ModifiableIntegerFunction::readFromFile(const char* fileName) {
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "Unable to open the file" << std::endl;
		return;
	}
	readFromFile(ifs);
}

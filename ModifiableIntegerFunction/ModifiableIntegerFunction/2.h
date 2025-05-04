#pragma once
#include <iostream>

constexpr int SIZE = INT16_MAX-INT16_MIN+1;
constexpr int offsetIndex = INT16_MAX+1;

class ModifiableIntegerFunction {
private:
	mutable int16_t* result = nullptr;
	bool* isExcluded=nullptr;

	void free();
	void copyFrom(const ModifiableIntegerFunction& other);

public:
	ModifiableIntegerFunction();
	ModifiableIntegerFunction(int16_t(*f)(int16_t));
	ModifiableIntegerFunction(const ModifiableIntegerFunction& other);
	ModifiableIntegerFunction& operator=(const ModifiableIntegerFunction& other);
	~ModifiableIntegerFunction();

	void setSpecificValue(int16_t input, int16_t output);
	void exclusionOfPoint(int16_t input);
	int16_t f(int16_t input) const;
		
	int16_t operator()(int16_t input) const;
	friend ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	//composition of functions
	friend ModifiableIntegerFunction operator*(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);

	friend bool operator>(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator>=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator<=(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	friend bool operator<(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);


	friend ModifiableIntegerFunction operator^(const ModifiableIntegerFunction& lhs,int k);

	//parallel functions
	friend bool operator==(const ModifiableIntegerFunction& lhs, const ModifiableIntegerFunction& rhs);
	
	bool isSurjection() const;
	bool isInjection() const;
	bool isBijection() const;

	void writeToFile(std::ofstream& ofs) const;
	void writeToFile(const char* fileName) const;

	void readFromFile(std::ifstream& ifs);
	void readFromFile(const char* fileName);
	
	
};
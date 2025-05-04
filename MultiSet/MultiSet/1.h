#pragma once
#include <iostream>

class MultiSet {
private:
	uint8_t* buckets = nullptr;
	unsigned n = 0;
	uint8_t k = 0;
	unsigned BUCKETS_SIZE =0;
	unsigned BUCKETS_COUNT = 0;

	unsigned getBucketIndex(unsigned num) const;
	unsigned getBitIndex(unsigned num) const;

	unsigned getBit(unsigned index) const;
	void setBit(unsigned index,unsigned value) const;

	void copyFrom(const MultiSet& other);
	void free();

	void printNumber(unsigned number, unsigned occurrences) const;


public:
	MultiSet() = default;
	MultiSet(unsigned n,uint8_t k);
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	void add(unsigned num);
	unsigned countOccurrences(unsigned num) const;

	void print() const;
	void printInMemoryLook() const;

	void serialize(std::ofstream& ofs) const;
	void serialize(const char* fileName) const;

	void deserialize(std::ifstream& ifs);
	void deserialize(const char* fileName);

	friend MultiSet intersectionOfMultiSets(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet differenceOfMultiSets(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet additionOfMultiSet(const MultiSet& current);
};

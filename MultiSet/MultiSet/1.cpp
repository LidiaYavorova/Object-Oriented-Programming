#include "1.h"
#include <fstream>

namespace {
	int pow(int base, int exponent) {
		int result = 1;

		if (exponent > 0) {
			for (int i = 0; i < exponent; ++i) {
				result *= base;
			}
		}
		return result;
	}
}

unsigned MultiSet::getBit(unsigned index) const {
	unsigned bucketIndex = index / 8;
	unsigned bitIndexInBucket = 7 - (index % 8);
	int mask = 1 << bitIndexInBucket;
	return buckets[bucketIndex] & mask;
}

void MultiSet::setBit(unsigned index, unsigned value) const {
	unsigned bucketIndex = index / 8;
	unsigned bitIndexInBucket = 7 - (index % 8);
	int mask = 1 << bitIndexInBucket;
	if (value == 0) {
		buckets[bucketIndex] &=~mask;
	}
	else if (value == 1) {
		buckets[bucketIndex] |= mask;
	}
	
}

unsigned MultiSet::getBucketIndex(unsigned num) const {
	return (num * k) / 8;
}

unsigned MultiSet::getBitIndex(unsigned num) const {
	return num * k;
}

void MultiSet::copyFrom(const MultiSet& other) {
	n = other.n;
	k = other.k;
	BUCKETS_COUNT = other.BUCKETS_COUNT;
	BUCKETS_SIZE = other.BUCKETS_SIZE;
	buckets = new uint8_t[other.BUCKETS_COUNT];
	for (size_t i = 0; i < other.BUCKETS_COUNT; i++) {
		buckets[i] = other.buckets[i];
	}	
	
}

void MultiSet::free() {
	delete[] buckets;
	buckets = nullptr;

}


MultiSet::MultiSet(unsigned n, uint8_t k) {
	this->n = n;
	this->k = k;
	BUCKETS_SIZE = (8 * sizeof(uint8_t)) / k;
	BUCKETS_COUNT = ((n * k) / 8) + 1;
	this->buckets = new uint8_t[BUCKETS_COUNT]{ 0 };

}

MultiSet::MultiSet(const MultiSet& other) {
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

MultiSet::~MultiSet() {
	free();
}

void MultiSet::add(unsigned num) {
	if (countOccurrences(num) == (pow(2,k) - 1)) {
		unsigned bitIndex = this->getBitIndex(num);
		for (size_t i = bitIndex + k - 1; i >= bitIndex; i--)
		{

			if (getBit(i) == 0) {
				setBit(i, 1);
				return;
			}
			else {
				setBit(i, 0);
			}
		}
	}
	else {
		std::cout << "Cannot add this number. You have reached the max occurrences." << std::endl;
	}

}

unsigned MultiSet::countOccurrences(unsigned num) const {
	unsigned bitIndex = this->getBitIndex(num);
	unsigned occcurrences = 0;
	int counter = 0;
	for (int i = bitIndex + k - 1; i >= (int)bitIndex; i--)
	{
		if (getBit(i) != 0) {
			occcurrences += 1* pow(2, counter);
		}
		counter++;
	}
	return occcurrences;
}
void MultiSet::printNumber(unsigned number, unsigned occurrences) const {
	for (size_t i = 0; i < occurrences; i++)
	{
		std::cout << number << " ";
	}
}

void MultiSet::print() const {
	for (unsigned i = 0; i <= n; i++)
	{
		printNumber(i, countOccurrences(i));
	}
	std::cout << std::endl;
}

void MultiSet::printInMemoryLook() const {
	for (unsigned i = 0; i <= (n+1)*k; i++)
	{
		if (getBit(i) == 0) {
			std::cout << 0;
		}
		else {
			std::cout << 1;
		}
		std::cout << " ";
	}
	std::cout << std::endl;
}

void MultiSet::serialize(const char* fileName) const {
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "Unable to open the file";
		return;
	}
	serialize(ofs);
}

void MultiSet::serialize(std::ofstream& ofs) const {
	ofs.write((const char*)&n, sizeof(unsigned));
	ofs.write((const char*)&k, sizeof(uint8_t));
	ofs.write((const char*)buckets, sizeof(uint8_t) * BUCKETS_COUNT);
}

void MultiSet::deserialize(const char* fileName) {
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "Unable to open the file";
		return;
	}
	deserialize(ifs);
}
void MultiSet::deserialize(std::ifstream& ifs) {
	ifs.read((char*)&n, sizeof(unsigned));
	ifs.read((char*)&k, sizeof(uint8_t));
	BUCKETS_SIZE = (8 * sizeof(uint8_t)) / k;
	BUCKETS_COUNT = ((n * k) / 8) + 1;
	this->buckets = new uint8_t[BUCKETS_COUNT];
	ifs.read((char*)buckets, sizeof(uint8_t) * BUCKETS_COUNT);
}

MultiSet intersectionOfMultiSets(const MultiSet& lhs, const MultiSet& rhs) {
	MultiSet result(std::min(lhs.n, rhs.n), std::min(lhs.k, rhs.k));
	for (size_t i = 0; i < result.n; i++)
	{
		int occurrences = std::min(lhs.countOccurrences(i), rhs.countOccurrences(i));
		for (size_t j = 0; j < occurrences; j++)
		{
			result.add(i);
		}
	}
	return result;
}

MultiSet differenceOfMultiSets(const MultiSet& lhs, const MultiSet& rhs) {
	MultiSet result(lhs.n, lhs.k);
	for (size_t i = 0; i <= lhs.n; i++)
	{
		int occurrences = lhs.countOccurrences(i) - rhs.countOccurrences(i);
		occurrences = std::max(0, occurrences);
		for (size_t j = 0; j < occurrences; j++)
		{
			result.add(i);
		}
	}
	return result;
}

MultiSet additionOfMultiSet(const MultiSet& current) {
	MultiSet result(current.n, current.k);
	unsigned p = 0;
	unsigned newP = 0;
	for (unsigned i = 0; i <=current.n; i++)
	{
		p = current.countOccurrences(i);
		newP = (pow(2,current.k) - 1) - p;
		for (unsigned j = 1; j <= newP; j++)
		{
			result.add(i);
		}
		
	}
	return result;
}
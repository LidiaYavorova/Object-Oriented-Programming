#include <iostream>
#include <fstream>
#include "PartialFunction.h"
#include "PartialFunctionCriteria.hpp"
#include "Vector.hpp"
#include "Type0Functor.h"
#include "Type1Functor.h"
#include "Type2Functor.h"
#include "MaxPartialFunction.h"
#include "MinPartialFunction.h"

void safeReadInt(std::ifstream& ifs, int16_t& n) {
	std::streamsize start = ifs.tellg();
	ifs.read((char*)&n, sizeof(n));
	if (start != int(ifs.tellg()) - sizeof(n)) {
		throw std::overflow_error("N or T is invalid.");
	}
}

void safeReadArray(std::istream& ifs, Vector<int32_t>& array, size_t size) {
	std::streamsize start = ifs.tellg();
	ifs.read((char*)array.getData(), sizeof(int32_t) * size);
	if (start != int(ifs.tellg()) - size * sizeof(int32_t)) {
		throw std::length_error("Array is invalid");
	}
}
static PartialFunction* loadPartialFunction(std::ifstream& stream);

static PartialFunction* loadPartialFunction(const char* path) {
	std::ifstream in;
	in.open(path, std::ios::binary);
	if (!in.is_open()) {
		throw std::invalid_argument("Could not read file");
	}
	PartialFunction* func = loadPartialFunction(in);
	in.close();
	return func;
}
static PartialFunction* loadPartialFunction(std::ifstream& stream) {
	int16_t n = 0;
	int16_t t = 0;
	safeReadInt(stream, n);
	if (n > 32) {
		throw std::domain_error("N should be equal to or less than 32.");
	}
	safeReadInt(stream, t);
	if (t == 0) {
		Vector<int32_t> args;
		Vector<int32_t> results;
		args.resize(n);
		results.resize(n);
		safeReadArray(stream, args, n);
		safeReadArray(stream, results, n);

		return new PartialFunctionCriteria<Type0Functor>(Type0Functor(args, results));
	}
	if (t == 1) {
		Vector<int32_t> undefs;
		undefs.resize(n);
		safeReadArray(stream, undefs, n);
		return new PartialFunctionCriteria<Type1Functor>(Type1Functor(undefs));
	}
	if (t == 2) {
		Vector<int32_t> ones;
		ones.resize(n);
		safeReadArray(stream, ones, n);
		return new PartialFunctionCriteria<Type2Functor>(Type2Functor(ones));
	}
	if (t == 3) {
		Vector<PartialFunction*> funcs;
		for (int i = 0; i < n; i++) {
			Vector<char> buf;
			char c = ' ';
			while (stream.read(&c, 1) && c != '\0') {
				buf.push_back(c);
			}
			buf.push_back('\0');
			funcs.push_back(loadPartialFunction(buf.getData()));
		}
		return new MaxPartialFunction(std::move(funcs));
	}
	if (t == 4) {
		Vector<PartialFunction*> funcs;
		for (int i = 0; i < n; i++) {
			Vector<char> buf;
			char c = ' ';
			while (stream.read(&c, 1) && c != '\0') {
				buf.push_back(c);
			}
			buf.push_back('\0');
			funcs.push_back(loadPartialFunction(buf.getData()));
		}
		return new MinPartialFunction(std::move(funcs));
	}
}

static void writeFiles() {
	{
		std::ofstream fs0;
		fs0.open("func.dat", std::ios::binary | std::ios::out);
		int16_t n = 3;
		int16_t t = 3;
		fs0.write((char*)&n, sizeof(n));
		fs0.write((char*)&t, sizeof(t));
		fs0.write("first.dat", sizeof("first.dat"));
		fs0.write("second.dat", sizeof("second.dat"));
		fs0.write("third.dat", sizeof("third.dat"));
		fs0.close();
	}

	{
		std::ofstream fs1;
		fs1.open("first.dat", std::ios::binary);
		int16_t n = 7, t = 0;
		fs1.write((char*)&n, sizeof(n));
		fs1.write((char*)&t, sizeof(t));
		for (int i : { 0, 1, 2, 3, 5, 6, 7 }) {
			fs1.write((char*)&i, sizeof(i));
		}
		for (int i : { 0, 3, 3, 3, 4, 4, 0 }) {
			fs1.write((char*)&i, sizeof(i));
		}
		fs1.close();
	}

	{
		std::ofstream fs2;
		fs2.open("second.dat", std::ios::binary);
		int16_t n = 2, t = 1;
		fs2.write((char*)&n, sizeof(n));
		fs2.write((char*)&t, sizeof(t));
		int a = 3, b = 5;
		fs2.write((char*)&a, sizeof(a));
		fs2.write((char*)&b, sizeof(b));
		fs2.close();
	}

	{
		std::ofstream fs3;
		fs3.open("third.dat", std::ios::binary);
		int16_t n = 4, t = 2;
		fs3.write((char*)&n, sizeof(n));
		fs3.write((char*)&t, sizeof(t));
		for (int32_t i : { 0, 5, 6, 7 }) {
			fs3.write((char*)&i, sizeof(int32_t));
		}
		fs3.close();
	}
}

int main()
{
	writeFiles();
	
	try {
		const PartialFunction* func = loadPartialFunction("func.dat");
		std::cout << "Enter for 1 if you want output in interval or 2 if you sequential output." << std::endl;
		int command = 0;
		std::cin >> command;
		if (command == 1) {
			int a, b;
			std::cout << "Enter start and end of the interval: ";
			std::cin >> a >> b;
			for (int i = a; i <= b; i++) {
				const FunctionResult fr = (*func)(i);
				if (fr.defined()) {
					std::cout <<"f("<< i << ") = " << fr.getValue() << std::endl;
				}
			}
		}
		else if (command == 2) {
			for (int32_t i = func->getMinDefinedPoint(); i <= func->getMaxDefinedPoint(); i++)
			{
				const FunctionResult fr = (*func)(i);
				if (fr.defined()) {
					std::cout << "Press Enter to generate the next result...";
					std::cin.ignore();
					std::cout << "f(" << i << ") = " << fr.getValue() << std::endl;
				}
			}
		}
	
		delete func;
	}
	catch (const std::length_error& exc) {
		std::cout << "Array of values is invalid length." << std::endl;
		return -1;
	}
	catch (const std::overflow_error& exc) {
		std::cout << "N/T is invalid." << std::endl;
		return -1;
	}
	catch (const std::domain_error& exc) {
		std::cout << "N is out of bound." << std::endl;
		return -1;
	}
	catch (const std::runtime_error& exc) {
		std::cout << "Not all functions are defined." << std::endl;
		return -1;
	}
	catch (...) {
		std::cout << "Unknown error." << std::endl;
		return -1;
	}
	std::cout << std::endl;
	return 0;
}


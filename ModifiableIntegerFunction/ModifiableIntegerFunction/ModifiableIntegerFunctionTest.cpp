#include <iostream>
#include "2.h"

int16_t add1(int16_t input) {
	return 1+ input;
}
int16_t nothing(int16_t input) {
	return input;
}
int16_t multiplyBy2(int16_t input) {
	return 2 * input;
}
int16_t multiplyBy4(int16_t input) {
	return 4 * input;
}

#define expected(func, exp) \
do { \
const int16_t res = func; \
if (res!=exp) std::cout << #func << " failed. " << res << " != " << exp << std::endl; \
} while (0)

#define expected_throw(func, exp) \
do { \
try { \
func; \
std::cout << #func << " did not throw!" << std::endl; \
} \
catch (std::exception) { } \
} while (0)

int16_t add2(int16_t input) {
	return 2 + input;
}

int16_t mul2(int16_t input) {
	return 2 * input;
}

int16_t id(int16_t input) {
	return input;
}

int16_t x2(int16_t input) {
	return input * input;
}

int main()
{
	//testvai s min i max-greshen izhod s tqh
	//greshno exclude point
	//greshno * 
	//greshno ^
	//ModifiableIntegerFunction m1(add1);
	//ModifiableIntegerFunction m2(multiplyBy2);
	//ModifiableIntegerFunction m3(multiplyBy4);
	//ModifiableIntegerFunction m4 = m3 - m3;
	//m1.exclusionOfPoint(6);
	//std::cout << std::boolalpha << (m1 < m3);
	const ModifiableIntegerFunction func(add1);
	//assert(func == func);
	//assert(!(func < func) && !(func > func));
	//assert(func(func(50)) == 52);
	//expected(func(50), 51);
	//expected(func(-50), -49);
	//const ModifiableIntegerFunction funcCube = func * func * func;
	//assert(funcCube == func ^ 3);
	//expected(funcCube(50), 53);
	//expected(funcCube(-100), -97);
	//const ModifiableIntegerFunction invFunc = func ^ -1;
	//expected(invFunc(-100), -101);
	//expected(invFunc(0), -1);
	//expected(invFunc(100), 99);
	//const ModifiableIntegerFunction func2(add2);
	//assert(func2(-offsetIndex) == func(-offsetIndex) + 1);
	//// assert(func < func2); dkgjdopghnji[wtnpjhbn[jg;ldjgh[pqwenmtgpodfgjh;'sdjfg'
	//const ModifiableIntegerFunction funcMul(mul2);
	//expected(funcMul(50), 100);
	//expected_throw((funcMul ^ -1)(99), 45);
	//expected((funcMul ^ -1)(100), 50);
	//const ModifiableIntegerFunction idFunc(id);
	//idFunc.draw(0, 0, "Salatka");
	//func2.draw(0, 0, "f(x)=x+2");
	//(func ^ -1).draw(0, 0, "f(x)^1, f(x)=x+1");
	//const ModifiableIntegerFunction x2Func(x2);
	//x2Func.draw(-10, -2, "f(x)=x^2");


}


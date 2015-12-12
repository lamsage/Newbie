#include <iostream>
using namespace std;
#define __STL_TEMPLATE_NULL template<>
template <class key> struct hash {
	void operator()() {cout<< "hase<T>" <<endl; }
};

__STL_TEMPLATE_NULL struct hash<char> {
	void operator()() {cout<< "hase<char>" <<endl; }
};

__STL_TEMPLATE_NULL struct hash<unsigned char> {
	void operator()() {cout<< "hase<unsigned char>" <<endl; }
};

int main() {
	hash<long> t1;
	hash<char> t2;
	hash<unsigned char> t3;

	t1();
	t2();
	t3();
}

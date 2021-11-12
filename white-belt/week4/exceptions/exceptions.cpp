#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

void EnsureEqual(const string &left, const string &right) {
	if (left != right) {
		stringstream ss(left + " != " + right);
		throw runtime_error(ss.str());
	}
}


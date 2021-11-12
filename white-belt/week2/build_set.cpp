#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;


set<string> BuildMapValuesSet(const map<int, string>& m) {
	set<string> result;
	for (auto [key, value] : m) {
		result.insert(value);
	}
	return result;
}


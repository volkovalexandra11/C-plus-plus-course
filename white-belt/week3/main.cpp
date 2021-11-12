#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include "Person.h"
#include "ReversibleString.h"
#include "Incognizable.h"

using namespace std;

vector<int> InputIntVector(int n) {
	vector<int> result(n);

	for (auto &x: result) {
		cin >> x;
	}
	return result;
}

vector<string> InputStringVector(int n) {
	vector<string> result(n);

	for (auto &x: result) {
		cin >> x;
	}
	return result;
}

void PrintIntVector(const vector<int> &v) {
	for (auto &x: v) {
		cout << x << " ";
	}
}


void PrintStringVector(const vector<string> &v) {
	for (auto &x: v) {
		cout << x << " ";
	}
}

//task1
void SortByAbs() {
	int n;
	cin >> n;

	auto v = InputIntVector(n);

	sort(v.begin(), v.end(), [](int i, int j) { return abs(i) < abs(j); });

	PrintIntVector(v);
}


//task2
string tolower(const string& s) {
	string new_s = s;
	for (auto &c: new_s) {
		c = tolower(c);
	}
	return new_s;
}

bool cmp (string& s, string& t) {
	auto s1 = tolower(s);
	auto t1 = tolower(t);
	return s1 < t1;
}

void SortByLowerCase() {
	int n;
	cin >> n;
	auto v = InputStringVector(n);

	sort(v.begin(), v.end(), cmp);

	PrintStringVector(v);
}

int main() {
	Incognizable a;
	Incognizable b = {};
	Incognizable c = {0};
	Incognizable d = {0, 1};
	return 0;
}

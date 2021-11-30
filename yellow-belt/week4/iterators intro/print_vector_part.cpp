#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void PrintVectorReversed(vector<int>::iterator begin, vector<int>::iterator end) {
	auto it = end;
	while (it != begin) {
		it--;
		cout << *it << " ";
	}
}

void PrintVectorPart(const vector<int> &numbers) {
	auto bound = find_if(
			numbers.begin(),
			numbers.end(),
			[](int num) { return num < 0; }
			);
	auto it = numbers.end();
	while (it != bound) {
		it--;
		cout << *it << " ";
	}
}

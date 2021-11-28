#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void PrintVectorPart(const vector<int> &numbers) {
	auto bound = find_if(
			numbers.begin(),
			numbers.end(),
			[](int num) { return num < 0; }
	);

	auto it = bound;
	while (it != numbers.begin()) {
		it--;
		cout << *it << " ";
	}
}
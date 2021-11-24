#include "sum_reverse_sort.h"

#include <string>
#include <algorithm>

using namespace std;

int Sum(int a, int b) {
	return a + b;
}

string Reverse(string s) {
	string res;
	for (int i = s.size() - 1; i >= 0; i--) {
		res.push_back(s[i]);
	}

	return res;
}

void Sort(vector<int> &nums) {
	sort(nums.begin(), nums.end());
}
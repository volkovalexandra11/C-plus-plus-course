#include <algorithm>
#include <vector>

using namespace std;

void Reverse(vector<int> &number) {
	reverse(number.begin(), number.end());
}

vector<int> Reversed(const vector<int> &v) {
	auto reversed = v;
	reverse(reversed.begin(), reversed.end());
	return reversed;
}

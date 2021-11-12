#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;


//average temperature task
double GetAverage(const vector<int> &v) {
	int64_t sum = 0;
	for (const auto &x: v) {
		sum += x;
	}

	return sum / static_cast<int>(v.size());
}

void PrintVector(const vector<int> &v) {
	cout << v.size() << endl;
	for (const auto &x: v) {
		cout << x << " ";
	}
}

void SolveAvgTemperature() {
	int n;
	cin >> n;
	vector<int> temps(n);

	for (auto &x: temps) {
		cin >> x;
	}

	double avg = GetAverage(temps);
	vector<int> greater;
	for (int i = 0; i < n; i++) {
		int x = temps[i];
		if (x > avg) {
			greater.push_back(i);
		}
	}

	PrintVector(greater);
}

int main() {
	SolveAvgTemperature();
}

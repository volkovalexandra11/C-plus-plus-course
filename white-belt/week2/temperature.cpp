#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

double Average(const vector<double> &v) {
	if (v.size() == 0)
		return 0;

	double sum = 0;
	for (auto el: v)
		sum += el;

	return sum / v.size();
}

void PrintVector(const vector<double> &v) {
	for (auto el: v) {
		cout << el << " ";
	}
}

void GetDaysWithHighTemp() {
	int days_count;
	cin >> days_count;
	vector<double> temps(days_count), result;
	for (double &day: temps)
		cin >> day;

	int avg = Average(temps);

	for (int i = 0; i < temps.size(); i++) {
		if (temps[i] > avg)
			result.push_back(i);
	}

	cout << result.size() << endl;
	PrintVector(result);
}
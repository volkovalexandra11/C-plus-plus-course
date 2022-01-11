#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

int solve_athletes_task() {
	const int MAX_ATHLETES_COUNT = 100'000;
	int q;
	cin >> q;
	list<int> numbers;
	vector<list<int>::iterator> athlete_pos(MAX_ATHLETES_COUNT + 1, numbers.end());
	for (int i = 0; i < q; ++i) {
		int men_num, next_num;
		cin >> men_num >> next_num;
		athlete_pos[men_num] = numbers.insert(athlete_pos[next_num], men_num);
	}

	for (const int& x: numbers) {
		cout << x << '\n';
	}

	return 0;
}

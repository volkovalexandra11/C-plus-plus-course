#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

class RouteManager {
public:
	void AddRoute(int start, int finish) {
		reachable_lists_[start].insert(finish); //O(log n)
		reachable_lists_[finish].insert(start); //O(log n)
	} // O(log n)

	int FindNearestFinish(int start, int finish) const {
		int result = abs(start - finish);
		if (reachable_lists_.count(start) < 1) {
			return result;
		}
		const set<int>& reachable_stations = reachable_lists_.at(start); //O(log m)
		const auto finish_lower = reachable_stations.lower_bound(finish); //O(log n)
		if (finish_lower != reachable_stations.end()) {
			result = min(result, abs(finish - *finish_lower));
		}
		if (finish_lower != reachable_stations.begin()) {
			result = min(result, abs(finish - *prev(finish_lower)));
		}
		return result;
	} //O(log n + log m)
private:
	map<int, set<int>> reachable_lists_;
};


int main3() {
	RouteManager routes;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int start, finish;
		cin >> start >> finish;
		if (query_type == "ADD") {
			routes.AddRoute(start, finish);
		} else if (query_type == "GO") {
			cout << routes.FindNearestFinish(start, finish) << "\n";
		}
	}

	return 0;
}
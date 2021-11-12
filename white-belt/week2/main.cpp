#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

int Factorial(int x) {
	if (x <= 0)
		return 1;

	int fact = 1;
	for (int i = 1; i <= x; i++) {
		fact *= i;
	}
	return fact;
}

bool IsPalindrom(string s) {
	int n = s.size();
	for (int i = 0; i < n; i++) {
		if (s[i] != s[n - i - 1])
			return false;
	}

	return true;
}

vector<string> PalindromFilter(vector<string> strings, int minLength) {
	vector<string> result;

	for (auto s: strings) {
		if (IsPalindrom(s) && s.size() >= minLength) {
			result.push_back(s);
		}
	}

	return result;
}

void UpdateIfGreater(int a, int &b) {
	if (a > b)
		b = a;
}

void MoveStrings(vector<string> &source, vector<string> &destination) {
	for (auto s: source)
		destination.push_back(s);
	source.clear();
}

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

void PrintVector(const vector<string> &v) {
	for (auto el: v) {
		cout << el << " ";
	}
//	cout << endl;
}

void PrintVectorFormat(const vector<string> &v, const string &remove) {
	for (auto el: v) {
		if (el != remove)
			cout << el << " ";
	}
	cout << endl;
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


int GetWorryCount(const vector<bool> &queue) {
	int count = 0;
	for (auto person: queue) {
		if (person) count++;
	}

	return count;
}

void ProcessQueue() {
	int query_count;
	cin >> query_count;
	string query_type;
	vector<bool> queue;

	for (int i = 0; i < query_count; i++) {
		cin >> query_type;
		if (query_type == "WORRY_COUNT") {
			cout << GetWorryCount(queue) << endl;
		} else if (query_type == "WORRY") {
			int ind;
			cin >> ind;
			queue[ind] = true;
		} else if (query_type == "QUIET") {
			int ind;
			cin >> ind;
			queue[ind] = false;
		} else if (query_type == "COME") {
			int count;
			cin >> count;
			if (count > 0) {
				for (int i = 0; i < count; i++) {
					queue.push_back(false);
				}
			} else {
				queue.erase(queue.end() + count, queue.end());
			}
		}
	}
}

void GetTimetable() {
	map<int, vector<string>> timetable;
	for (int i = 1; i <= 31; i++) {
		timetable[i] = vector<string>();
	}

	vector<int> daysCount = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int curr = 0;
	int query_count;
	cin >> query_count;

	for (int i = 0; i < query_count; i++) {
		string query;
		cin >> query;
		if (query == "NEXT") {
			if (daysCount[curr] < daysCount[curr + 1]) {}
			else {
				int last = timetable.rbegin()->first;
				int diff = -(daysCount[curr + 1] - daysCount[curr]);
				for (int j = last - diff + 1; j <= last; j++) {
					for (auto d: timetable[j]) {
						timetable[last - diff].push_back(d);
					}
					timetable[j].clear();
				}
			}
			curr++;
			if (curr > 11) curr = 0;
		}
		if (query == "DUMP") {
			int day;
			cin >> day;
			PrintVector(timetable[day]);
		}
		if (query == "ADD") {
			int day;
			string name;
			cin >> day >> name;
			timetable[day].push_back(name);
		}
	}
}

map<char, int> BuildCharMap(const string &word) {
	map<char, int> result;
	for (const auto &s: word) {
		result[s]++;
	}
	return result;
}

void ProcessAnagrams() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string first, second;
		cin >> first >> second;

		if (BuildCharMap(first) == BuildCharMap(second)) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
}

void PrintMap(const map<string, string> &map) {
	if (map.empty()) {
		cout << "There are no countries in the world" << endl;
		return;
	}
	for (auto[key, value]: map) {
		cout << key << "/" << value << " ";
	}
	cout << endl;
}

void ProcessCountries() {
	map<string, string> capitals;
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		string query;
		cin >> query;

		if (query == "CHANGE_CAPITAL") {
			string country, new_capital;
			cin >> country >> new_capital;
			if (!capitals.count(country)) {
				cout << "Introduce new country " << country << " with capital " << new_capital << endl;
			} else if (capitals[country] == new_capital) {
				cout << "Country " << country << " hasn't changed its capital" << endl;
			} else {
				cout << "Country " << country << " has changed its capital from " << capitals[country] << " to "
					 << new_capital << endl;
			}

			capitals[country] = new_capital;
		}

		if (query == "RENAME") {
			string old_country_name, new_country_name;
			cin >> old_country_name >> new_country_name;
//			capitals[new_country_name] = capitals[old_country_name];

			if (old_country_name == new_country_name || !capitals.count(old_country_name) ||
				capitals.count(new_country_name)) {
				cout << "Incorrect rename, skip" << endl;
			} else {
				cout << "Country " << old_country_name << " with capital " << capitals[old_country_name]
					 << " has been renamed to " << new_country_name << endl;
				capitals[new_country_name] = capitals[old_country_name];
				capitals.erase(old_country_name);
			}
		}
		if (query == "ABOUT") {
			string country;
			cin >> country;
			if (capitals.count(country)) {
				cout << "Country " << country << " has capital " << capitals[country] << endl;
			} else {
				cout << "Country " << country << " doesn't exist" << endl;
			}

		}
		if (query == "DUMP") {
			PrintMap(capitals);
		}
	}
}

void ProcessStop(map<string, vector<string>> &stops_to_buses, const string &stop) {
	if (stops_to_buses.count(stop)) {
		PrintVector(stops_to_buses[stop]);
	} else {
		cout << "No stop" << endl;
	}
}

void ProcessBusStops() {
	map<string, vector<string>> buses_to_stops;
	map<string, vector<string>> stops_to_buses;

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		string query;
		cin >> query;

		if (query == "NEW_BUS") {
			string bus_name;
			int stops_count;

			cin >> bus_name >> stops_count;

			for (int j = 0; j < stops_count; j++) {
				string stop;
				cin >> stop;
				buses_to_stops[bus_name].push_back(stop);
				stops_to_buses[stop].push_back(bus_name);
			}
		}

		if (query == "BUSES_FOR_STOP") {
			string stop;
			cin >> stop;
//			if (stops_to_buses.count(stop)) {
//				PrintVector(stops_to_buses[stop]);
//			} else {
//				cout << "No stop";
//			}
			ProcessStop(stops_to_buses, stop);
		}

		if (query == "STOPS_FOR_BUS") {
			string bus_name;
			cin >> bus_name;
			if (!buses_to_stops.count(bus_name)) {
				cout << "No bus" << endl;
			} else {
				auto stops = buses_to_stops[bus_name];
				for (auto stop: stops) {
					auto buses = stops_to_buses[stop];
					if (buses.size() == 1 && buses[0] == bus_name) {
						cout << "Stop " << stop << ": no interchange" << endl;
					} else {
						cout << "Stop " << stop << ": ";
						PrintVectorFormat(buses, bus_name);
					}
				}
			}
		}
		if (query == "ALL_BUSES") {
			if (buses_to_stops.empty()) {
				cout << "No buses" << endl;
			} else {
				int i = 0;
				for (auto[bus, stops]: buses_to_stops) {
					cout << "Bus " << bus << ": ";
					PrintVector(stops);
				}
			}
		}
	}
}

void ProcessBuses() {
	int n;
	cin >> n;
	int cur = 1;
	map<vector<string>, int> busNums;

	for (int i = 0; i < n; i++) {
		int count;
		cin >> count;
		vector<string> stops(count);
		for (auto &stop: stops) {
			cin >> stop;
		}

		if (busNums.count(stops)) {
			cout << "Already exists for " << busNums[stops] << endl;
		} else {
			cout << "New bus " << cur << endl;
			busNums[stops] = cur;
			cur++;
		}
	}
}

void GetUniqueStrings() {
	int n = 0;
	cin >> n;
	set<string> strings;

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		strings.insert(s);
	}

	cout << strings.size();
}

void ProcessSyn() {
	int n;
	cin >> n;
	map<string, set<string>> synonyms;

	for (int i = 0; i < n; i++) {
		string query;
		cin >> query;

		if (query == "ADD") {
			string word1, word2;
			cin >> word1 >> word2;

			synonyms[word1].insert(word2);
			synonyms[word2].insert(word1);
		}

		if (query == "CHECK") {
			string word1, word2;
			cin >> word1 >> word2;

			if (synonyms[word1].count(word2) || synonyms[word2].count(word1)) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
		}

		if (query == "COUNT") {
			string word;
			cin >> word;

			cout << synonyms[word].size() << endl;
		}
	}
}

void ProcessBuses2() {
	int n;
	cin >> n;
	int cur = 1;
	map<set<string>, int> busNums;

	for (int i = 0; i < n; i++) {
		int count;
		cin >> count;
		set<string> stops;
		for (int j = 0; j < count; j++) {
			string stop;
			cin >> stop;
			stops.insert(stop);
		}

		if (busNums.count(stops)) {
			cout << "Already exists for " << busNums[stops] << endl;
		} else {
			cout << "New bus " << cur << endl;
			busNums[stops] = cur;
			cur++;
		}
	}
}

int main() {
	ProcessBuses2();
}

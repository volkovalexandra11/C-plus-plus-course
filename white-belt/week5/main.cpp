#include <set>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>

using namespace std;

class Date {
public:

	Date() : year(0), month(0), day(0) {}

	explicit Date(const string &dateStr) {
		stringstream ss(dateStr);
		set<char> delimiters = {' ', '\n', '\t'};
		auto pos_year = TryReadInt(ss);
		CheckNextSymbol(ss, delimiters);
		auto pos_month = TryReadInt(ss);
		CheckNextSymbol(ss, delimiters);
		auto day = TryReadInt(ss);
		if (!ss.eof())
			throw runtime_error("Wrong date format: " + dateStr);
		if (!InRange(1, 12, pos_month))
			throw runtime_error("Month value is invalid: " + to_string(pos_month));
		if (!InRange(1, 31, day))
			throw runtime_error("Day value is invalid: " + to_string(day));
		this->year = pos_year;
		this->month = pos_month;
		this->day = day;
	}

	string ToString() const {
		string year_str = to_string(year);
		while (year_str.length() < 4) {
			year_str = "0" + year_str;
		}
		string str = year_str + "-" + FormatTwo(month) + "-" + FormatTwo(day);
		return str;
	}

	int GetYear() const {
		return year;
	}

	int GetMonth() const {
		return month;
	}

	int GetDay() const {
		return day;
	}

private:
	int year{};
	int month{};
	int day{};

	static string FormatTwo(int val) {
		if (to_string(val).length() == 1) {
			return "0" + to_string(val);
		}
		return to_string(val);
	}

	static void CheckNextSymbol(stringstream &ss, const set<char> &delimiters) {
		if (ss.peek() != '-')
			throw runtime_error("Wrong date format: " + ss.str());
		ss.ignore(1);
		if (delimiters.find(ss.peek()) != delimiters.end()) {
			throw runtime_error("Wrong date format: " + ss.str());
		}
	}

	static int TryReadInt(stringstream &ss) {
		int val;
		if (!(ss >> val))
			throw runtime_error("Wrong date format: " + ss.str());
	}

	static bool InRange(int left, int right, int val) {
		return !(val < left || val > right);
	}
};

bool operator<(const Date &lhs, const Date &rhs) {
	if (lhs.GetYear() < rhs.GetYear()) return true;
	if (lhs.GetYear() == rhs.GetYear()) {
		if (lhs.GetMonth() < rhs.GetMonth()) return true;
		if (lhs.GetMonth() == rhs.GetMonth()) {
			return lhs.GetDay() < rhs.GetDay();
		}
	}
	return false;
}

class DataBase {
public:
	void Add(const Date &date, const string &event) {
		db[date].insert(event);
	}

	string Delete(const Date &date, const string &event) {
		if (db.find(date) != db.end() && db[date].find(event) != db[date].end()) {
			db[date].erase(event);
			return "Deleted successfully";
		}
		return "Event not found";
	}

	string Delete(const Date &date) {
		if (db.find(date) == db.end() || db[date].empty()) {
			return "Deleted 0 events";
		}

		auto n = db[date].size();
		db.erase(date);
		return "Deleted " + to_string(n) + " events";
	}

	set<string> Find(const Date &date) const {
		set<string> events;
		if (db.find(date) != db.end())
			return db.at(date);
		else return events;
	}

	set<string> GetFormattedStrings() const {
		set<string> strings;
		for (auto[date, events]: db) {
			for (const auto &event: events) {
				string str = date.ToString() + " " + event;
				strings.insert(str);
			}
		}
		return strings;
	}

private:
	map<Date, set<string>> db;
};


void PrintSet(const set<string> &set) {
	for (const auto &str: set) {
		cout << str << endl;
	}
}


int main() {
	DataBase db;
	string commandStr;
	set<string> known_commands = {"Add", "Print", "Find", "Del"};

	while (getline(cin, commandStr)) {
		stringstream ss(commandStr);
		string command;
		string dateAsString, event;
		ss >> command;
		ss >> dateAsString;
		ss >> event;

		if (command.length() == 0)
			continue;

		if (known_commands.find(command) == known_commands.end()) {
			cout << "Unknown command: " << command;
			return 0;
		}

		Date date;
		if (command != "Print") {
			try {
				date = Date(dateAsString);
			} catch (runtime_error &error) {
				cout << error.what();
				return 0;
			}
		}

		if (command == "Add") {
			db.Add(date, event);
			continue;
		}

		if (command == "Del") {
			if (!event.empty()) {
				cout << db.Delete(date, event) << endl;
			} else {
				cout << db.Delete(date) << endl;
			}
			continue;
		}

		if (command == "Find") {
			PrintSet(db.Find(date));
			continue;
		}

		if (command == "Print") {
			PrintSet(db.GetFormattedStrings());
		}
	}

	return 0;
}

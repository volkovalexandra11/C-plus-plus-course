//#include <set>
//#include <map>
//#include <string>
//#include <iostream>
//#include <sstream>
//#include <exception>
//
//using namespace std;
//
//class Date {
//public:
//
//	Date() : year(0), month(0), day(0) {}
//
//	explicit Date(const string& dateStr) {
//		stringstream ss(dateStr);
//		if (ss >> this->year)
//			throw runtime_error("Wrong date format:" + dateStr);
//
//		if (ss.peek() != '-')
//			throw runtime_error("Wrong date format:" + dateStr);
//		ss.ignore(1);
//		if (!(ss >> this->month))
//			throw runtime_error("Wrong date format:" + dateStr);
//		if (month <= 0 || month > 12)
//			throw runtime_error("Month value is invalid: " + to_string(month));
//		if (ss.peek() != '-')
//			throw runtime_error("Wrong date format: " + dateStr);
//		ss.ignore(1);
//		if (!(ss >> this->day))
//			throw runtime_error("Wrong date format:" + dateStr);
//		if (day <= 0 || day > 31)
//			throw runtime_error("Day value is invalid: " + to_string(day));
//		if (!ss.eof())
//			throw runtime_error("Wrong date format:" + dateStr);
//	}
//
//	string ToString() const {
//		string str = to_string(year) + "-" + FormatTwo(month) + "-" + to_string(day);
//		return str;
//	}
//
//	int GetYear() const {
//		return year;
//	}
//
//	int GetMonth() const {
//		return month;
//	}
//
//	int GetDay() const {
//		return day;
//	}
//
//private:
//	int year{};
//	int month{};
//	int day{};
//
//	static string FormatTwo(int val) {
//		if (to_string(val).length() == 1) {
//			return "0" + to_string(val);
//		}
//		return to_string(val);
//	}
//};
//
//bool operator<(const Date &lhs, const Date &rhs)  {
//	if (lhs.GetYear() < rhs.GetYear()) return true;
//	if (lhs.GetYear() == rhs.GetYear()) {
//		if (lhs.GetMonth() < rhs.GetMonth()) return true;
//		if (lhs.GetMonth() == rhs.GetMonth()) {
//			return lhs.GetDay() < rhs.GetDay();
//		}
//	}
//	return false;
//}
//
//class DataBase {
//public:
//	void Add(const Date &date, const string &event) {
//		db[date].insert(event);
//	}
//
//	string Delete(const Date &date, const string &event) {
//		if (db.find(date) != db.end() && db[date].find(event) != db[date].end()) {
//			return "Deleted successfully";
//		}
//		return "Event not found";
//	}
//
//	string Delete(const Date &date) {
//		if (db.find(date) == db.end() || db[date].empty()) {
//			return "Deleted 0 events";
//		}
//
//		auto n = db[date].size();
//		db.erase(date);
//		return "Deleted " + to_string(n) + " events";
//	}
//
//	set<string> Find(const Date &date) {
//		return db[date];
//	}
//
//	set<string> GetFormattedStrings() {
//		set<string> strings;
//		for (auto[date, events]: db) {
//			for (const auto &event: events) {
//				string str = date.ToString() + " " + event;
//				strings.insert(str);
//			}
//		}
//		return strings;
//	}
//
//private:
//	map<Date, set<std::string>> db;
//};



//void PrintSet(const set<string> &set) {
//	for (const auto &str: set) {
//		cout << str << endl;
//	}
//}
//
//
//int main() {
//	DataBase db;
//	string command;
//
//	while (cin >> command) {
//		if (command.empty())
//			continue;
//		if (command == "Add") {
//			string dateAsString, event;
//			Date date;
//			cin >> dateAsString;
//			cin >> event;
//			try {
//				date = Date(dateAsString);
//			} catch (runtime_error &error) {
//				cout << error.what();
//				return 0;
//			}
//			db.Add(date, event);
//		}
//
//		if (command == "Delete") {
//			string dateAsString, event;
//			Date date;
//			cin >> dateAsString;
//			try {
//				date = Date(dateAsString);
//			} catch (runtime_error &error) {
//				cout << error.what();
//				return 0;
//			}
//			if (cin >> event) {
//				cout << db.Delete(date, event) << endl;
//			} else {
//				cout << db.Delete(date) << endl;
//			}
//		}
//
//		if (command == "Find") {
//			string dateAsString;
//			Date date;
//			cin >> dateAsString;
//			try {
//				date = Date(dateAsString);
//			} catch (runtime_error &error) {
//				cout << error.what();
//				return 0;
//			}
//			PrintSet(db.Find(date));
//		} else {
//			PrintSet(db.GetFormattedStrings());
//		}
//	}
//
//	return 0;
//}


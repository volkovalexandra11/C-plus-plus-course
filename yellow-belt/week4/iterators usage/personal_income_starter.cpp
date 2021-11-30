//#include <iostream>
//#include <string>
//#include <vector>
//#include <numeric>
//#include <sstream>
//#include <chrono>
//#include <iomanip>
//
//using namespace std;
//
//pair<string, string> SplitTwoStrict(const string &s, const string &delimiter) {
//	const auto pos = s.find(delimiter);
//	if (pos == std::string::npos) {
//		return {s, ""};
//	} else {
//		return {s.substr(0, pos), s.substr(pos + delimiter.length())};
//	}
//}
//
//pair<string, string> SplitTwo(const string &s, const string &delimiter) {
//	const auto[lhs, rhs] = SplitTwoStrict(s, delimiter);
//	return {lhs, rhs};
//}
//
//string ReadToken(string &s, const string &delimiter = " ") {
//	const auto[lhs, rhs] = SplitTwo(s, delimiter);
//	s = rhs;
//	return lhs;
//}
//
//int ConvertToInt(const string &str) {
//	size_t pos;
//	const int result = stoi(string(str), &pos);
//	if (pos != str.length()) {
//		stringstream error;
//		error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
//		throw invalid_argument(error.str());
//	}
//	return result;
//}
//
//class Date {
//public:
//	static Date ParseFromString(string str) {
//		const int year = ConvertToInt(ReadToken(str, "-"));
//		const int month = ConvertToInt(ReadToken(str, "-"));
//		const int day = ConvertToInt(str);
//		return {year, month, day};
//	}
//
//	time_t ToTimestamp() const {
//		tm t{};
//		t.tm_sec = 0;
//		t.tm_min = 0;
//		t.tm_hour = 0;
//		t.tm_mday = day_;
//		t.tm_mon = month_ - 1;
//		t.tm_year = year_ - 1900;
//		t.tm_isdst = 0;
//		return mktime(&t);
//	}
//
//	static int ComputeDaysDiff(const Date &date_to, const Date &date_from) {
//		const time_t timestamp_to = date_to.ToTimestamp();
//		const time_t timestamp_from = date_from.ToTimestamp();
//		static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
//		return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
//	}
//
//private:
//	int year_;
//	int month_;
//	int day_;
//
//	Date(int year, int month, int day)
//			: year_(year), month_(month), day_(day) {}
//};
//
//static const Date START_DATE = Date::ParseFromString("2000-01-01");
//static const Date END_DATE = Date::ParseFromString("2100-01-01");
//static const size_t DAY_COUNT = Date::ComputeDaysDiff(END_DATE, START_DATE);
//
//void SolveIncome() {
//	vector<double> moneyByDay(DAY_COUNT, 0.0);
//	int query_count;
//	cin >> query_count;
//
//	for (int i = 0; i < query_count; i++) {
//		string q_type, date_from, date_to;
//
//		cin >> q_type >> date_from >> date_to;
//
//		int fromBegin = Date::ComputeDaysDiff(
//				Date::ParseFromString(date_from),
//				START_DATE);
//		int fromEnd = Date::ComputeDaysDiff(
//				Date::ParseFromString(date_to),
//				START_DATE);
//
//		if (q_type == "Earn") {
//			double sum;
//			cin >> sum;
//			int days_count = Date::ComputeDaysDiff(
//					Date::ParseFromString(date_to),
//					Date::ParseFromString(date_from)
//			);
//			sum /= (days_count + 1);
//			for (auto j = fromBegin; j < fromEnd + 1; j++) {
//				moneyByDay[j] += sum;
//			}
//		} else {
//			cout << setprecision(25);
//			cout << accumulate(moneyByDay.begin() + fromBegin,
//							   moneyByDay.begin() + fromEnd + 1,
//							   0.0);
//			cout << endl;
//		}
//	}
//}

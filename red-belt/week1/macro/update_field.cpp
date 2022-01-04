//#include "airline_ticket.h"
//#include "test_runner.h"
//#include <ostream>
//#include <string>
//
//using namespace std;
//
//ostream& operator<<(ostream& os, const Date& d) {
//	os << d.year << " " << d.month << " " << d.day << " ";
//	return os;
//}
//
//ostream& operator<<(ostream& os, const Time& time) {
//	os << time.hours << " " << time.minutes << " ";
//	return os;
//}
//
//bool operator<(const Date& l, const Date& r) {
//	if (l.year < r.year)
//		return true;
//	if (l.year == r.year && l.month < r.month)
//		return true;
//	if (l.year == r.year && l.month == r.month && l.day < r.day)
//		return true;
//	return false;
//}
//
//bool operator<(const Time& l, const Time& r) {
//	if (l.hours < r.hours)
//		return true;
//	if (l.hours == r.hours && l.minutes < r.minutes)
//		return true;
//	return false;
//}
//
//bool operator==(const Date& l, const Date& r) {
//	return l.year == r.year && l.day == r.day && l.month == r.month;
//}
//
//bool operator==(const Time& l, const Time& r) {
//	return l.hours == r.hours && l.minutes == r.minutes;
//}
//
//istream& operator>>(istream& is, Date& d) {
//	string tmp;
//	getline(is, tmp, '-');
//	d.year = stoi(tmp);
//	getline(is, tmp, '-');
//	d.month = stoi(tmp);
//	getline(is, tmp);
//	d.day = stoi(tmp);
//	return is;
//}
//
//istream& operator>>(istream& is, Time& time) {
//	string tmp;
//	getline(is, tmp, ':');
//	time.hours = stoi(tmp);
//	getline(is, tmp);
//	time.minutes = stoi(tmp);
//	return is;
//}
//
//#define UPDATE_FIELD(ticket, field, values) { \
//	const auto it = (values).find(#field);    \
//	if (it != (values).end()) {               \
//		istringstream is(it->second);         \
//		is >> (ticket).field;				  \
//    }                                         \
//}
//
//void TestUpdate() {
//	AirlineTicket t;
//	t.price = 0;
//
//	const map<string, string> updates1 = {
//			{"departure_date", "2018-2-28"},
//			{"departure_time", "17:40"},
//	};
//	UPDATE_FIELD(t, departure_date, updates1);
//	UPDATE_FIELD(t, departure_time, updates1);
//	UPDATE_FIELD(t, price, updates1);
//
//	ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
//	ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
//	ASSERT_EQUAL(t.price, 0);
//
//	const map<string, string> updates2 = {
//			{"price", "12550"},
//			{"arrival_time", "20:33"},
//	};
//	UPDATE_FIELD(t, departure_date, updates2);
//	UPDATE_FIELD(t, departure_time, updates2);
//	UPDATE_FIELD(t, arrival_time, updates2);
//	UPDATE_FIELD(t, price, updates2);
//
//	ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
//	ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
//	ASSERT_EQUAL(t.price, 12550);
//	ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
//}
//
//int main4() {
//	TestRunner tr;
//	RUN_TEST(tr, TestUpdate);
//	return 0;
//}
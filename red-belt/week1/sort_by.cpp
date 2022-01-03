#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, const Date& d) {
	os << d.year << " " << d.month << " " << d.day << " ";
	return os;
}

ostream& operator<<(ostream& os, const Time& time) {
	os << time.hours << " " << time.minutes << " ";
	return os;
}

bool operator<(const Date& l, const Date& r) {
	if (l.year < r.year)
		return true;
	if (l.year == r.year && l.month < r.month)
		return true;
	if (l.year == r.year && l.month == r.month && l.day < r.day)
		return true;
	return false;
}

bool operator<(const Time& l, const Time& r) {
	if (l.hours < r.hours)
		return true;
	if (l.hours == r.hours && l.minutes < r.minutes)
		return true;
	return false;
}

bool operator==(const Date& l, const Date& r) {
	return l.year == r.year && l.day == r.day && l.month == r.month;
}

bool operator==(const Time& l, const Time& r) {
	return l.hours == r.hours && l.minutes == r.minutes;
}

#define SORT_BY(field) [](AirlineTicket& l, AirlineTicket& r) { return l.field < r.field; }

void TestSortBy() {
	vector<AirlineTicket> tixs = {
			{"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20, 0},  1200},
			{"AER", "VKO", "Utair",     {2018, 3, 5},  {14, 15}, {2018, 3, 5},  {16, 30}, 1700},
			{"AER", "SVO", "Aeroflot",  {2018, 3, 5},  {18, 30}, {2018, 3, 5},  {20, 30}, 2300},
			{"PMI", "DME", "Iberia",    {2018, 2, 8},  {23, 00}, {2018, 2, 9},  {3,  30}, 9000},
			{"CDG", "SVO", "AirFrance", {2018, 3, 1},  {13, 00}, {2018, 3, 1},  {17, 30}, 8000},
			{"CDG", "SVO", "AirFrance", {2018, 4, 1},  {13, 00}, {2018, 3, 1},  {17, 30}, 8000},
	};

	sort(begin(tixs), end(tixs), SORT_BY(price));
	ASSERT_EQUAL(tixs.front().price, 1200);
	ASSERT_EQUAL(tixs.back().price, 9000);

	sort(begin(tixs), end(tixs), SORT_BY(from));
	ASSERT_EQUAL(tixs.front().from, "AER");
	ASSERT_EQUAL(tixs.back().from, "VKO");

	sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
	ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
	ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));

	sort(begin(tixs), end(tixs), SORT_BY(departure_time));
	ASSERT_EQUAL(tixs.front().departure_time, (Time{13, 00}));
	ASSERT_EQUAL(tixs.back().departure_time, (Time{23, 00}));
}

int main3() {
	TestRunner tr;
	RUN_TEST(tr, TestSortBy);
	return 0;
}
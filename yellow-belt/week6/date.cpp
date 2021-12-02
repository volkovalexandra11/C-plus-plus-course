#include "date.h"

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

Date::Date() {}

Date ParseDate(istringstream& is) {
	int year, month, day;
	if (!(is >> year &&
		  is.get() == '-' &&
		  isspace(is.peek()) &&
		  is >> month &&
		  is.get() == '-' &&
		  isspace(is.peek()) &&
		  is >> day)) {
		is.setstate(ios_base::failbit);
		return {};
	}
	return {year, month, day};
}

bool operator<(const Date& left, const Date& right) {
	if (left.GetYear() < right.GetYear()) return true;
	if (left.GetMonth() < right.GetYear()) return true;
	if (left.GetDay() < right.GetDay()) return true;
	return false;
}

ostream& operator<<(ostream& os, const Date& date) {
	os << date.GetYear() <<'-' << date.GetMonth() << '-' << date.GetDay();
	return os;
}


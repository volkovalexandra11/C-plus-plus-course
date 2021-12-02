#pragma once

#include <sstream>
#include <iostream>

using namespace std;
#ifndef WEEK6_DATE_H
#define WEEK6_DATE_H


class Date {
public:
	Date();

	Date(int year, int month, int day);

	int GetYear() const;

	int GetMonth() const;

	int GetDay() const;

private:
	int year, month, day;
};

Date ParseDate(istringstream& is);

ostream& operator<<(ostream& os, const Date& date);

bool operator<(const Date& left, const Date& right);

#endif //WEEK6_DATE_H

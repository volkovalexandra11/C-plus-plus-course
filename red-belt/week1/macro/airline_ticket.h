#ifndef WEEK1_AIRLINE_TICKET_H
#define WEEK1_AIRLINE_TICKET_H

#pragma once

#include <string>
using namespace std;

struct Date {
	int year, month, day;
};

struct Time {
	int hours, minutes;
};

struct AirlineTicket {
	string from;
	string to;
	string airline;
	Date departure_date;
	Time departure_time;
	Date arrival_date;
	Time arrival_time;
	int price;
};

#endif //WEEK1_AIRLINE_TICKET_H

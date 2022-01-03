#pragma once

#include "date.h"

#include <map>
#include <string>
#include <vector>
#include <set>
#include <utility>

using namespace std;

#ifndef WEEK6_DATABASE_H
#define WEEK6_DATABASE_H

struct Event {
	string eventName;
	int order;
};


class Database {
public:
	void Add(Date date, const string& event);
	void Print(ostream& os);

	template<typename TPredicate>
	int RemoveIf(TPredicate predicate);

	template<typename TPredicate>
	vector<pair<Date, set<Event>>> FindIf(TPredicate predicate);

	string Last(Date date);

private:
	map<Date, set<Event>> events;
	int curOrder = 0;
};

ostream& operator<<(ostream& os, pair<Date, set<Event>> p);

bool operator<(const Event& l, const Event& r);


#endif //WEEK6_DATABASE_H

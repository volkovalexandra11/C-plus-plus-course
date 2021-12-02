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


class Database {
public:
	void Add(Date date, const string& event);
	void Print(ostream& os);

	template<typename TPredicate>
	int RemoveIf(TPredicate predicate);

	template<typename TPredicate>
	vector<pair<Date, set<string>>> FindIf(TPredicate predicate);
private:
	map<Date, set<string>> events;
};

ostream& operator<<(ostream& os, pair<Date, set<string>> p);


#endif //WEEK6_DATABASE_H

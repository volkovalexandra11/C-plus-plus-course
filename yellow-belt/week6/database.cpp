#include "database.h"

#include <algorithm>
#include <iterator>

void Database::Add(Date date, const string& event) {
	events[date].insert(event);
}

void Database::Print(ostream& os) {
	for (const auto& p: events) {
		os << p;
	}
}

template<typename TPredicate>
int Database::RemoveIf(TPredicate predicate) {

}

template<typename TPredicate>
vector<pair<Date, set<string>>> Database::FindIf(TPredicate predicate) {
	vector<pair<Date, set<string>>> found;
	auto insert_iter = back_inserter(found);
	for (auto [date, events_date] : events) {
		copy_if(events_date.begin(),  events_date.end(), insert_iter, predicate);
	}
	return found;
}


ostream& operator<<(ostream& os, pair<Date, set<string>> p) {
	for (const auto& str: p.second) {
		os << p.first << ' ' << str << endl;
	}
	return os;
}

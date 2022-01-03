#include "database.h"

#include <algorithm>
#include <iterator>
#include <experimental/map>

void Database::Add(Date date, const string& event) {
	events[date].insert({event, ++curOrder});
}

void Database::Print(ostream& os) {
	for (const auto& p: events) {
		os << p;
	}
}

template<typename TPredicate>
int Database::RemoveIf(TPredicate predicate) {
	int deletedCount = 0;
	for (auto it = events.begin(); it != events.end();) {
		if (predicate(*it)) {
			events.erase(it);
			deletedCount++;
		}
		it++;
	}
	return deletedCount;
}

template<typename TPredicate>
vector<pair<Date, set<Event>>> Database::FindIf(TPredicate predicate) {
	vector<pair<Date, set<Event>>> found;
	auto insert_iter = back_inserter(found);
	for (auto[date, events_date]: events) {
		copy_if(events_date.begin(), events_date.end(), insert_iter, predicate);
	}
	return found;
}

string Database::Last(Date date) {
	auto first_greater_date = events.upper_bound(date);
	if (first_greater_date == events.begin()) {
		return "No entries";
	}
	const Date last_date = (--first_greater_date)->first;

}


ostream& operator<<(ostream& os, const pair<Date, set<Event>>& p) {
	for (const auto& e: p.second) {
		os << p.first << ' ' << e.eventName << endl;
	}
	return os;
}

bool operator<(const Event& l, const Event& r) {
	return l.order > r.order;
}

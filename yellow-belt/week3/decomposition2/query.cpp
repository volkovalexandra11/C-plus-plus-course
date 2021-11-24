#include "query.h"

istream &operator>>(istream &is, Query &q) {
	string operation_code;
	cin >> operation_code;

	if (operation_code == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count;
		is >> stop_count;
		q.stops.resize(stop_count);
		for (string &stop: q.stops) {
			is >> stop;
		}
	}

	if (operation_code == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}

	if (operation_code == "STOPS_FOR_BUS") {
		is >> q.bus;
		q.type = QueryType::StopsForBus;
	}

	if (operation_code == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}

	return is;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
	for (const auto &x: v) {
		os << x << " ";
	}
	return os;
}



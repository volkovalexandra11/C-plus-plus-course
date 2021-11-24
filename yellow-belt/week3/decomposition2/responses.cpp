#include "responses.h"

#include <iostream>

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
	for (const auto &x: v) {
		os << x << " ";
	}
	return os;
}

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
	if (r.buses.empty()) {
		os << "No stop";
	} else {
		os << r.buses;
	}
	return os;
}

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
	if (r.stops.empty()) {
		os << "No bus";
	} else {
		auto count = r.stops.size();
		int i = 0;
		for (const auto &busToStopR: r.stops) {
			os << "Stop " << busToStopR.stop << ": ";
			i++;
			if (busToStopR.buses.size() == 1) {
				os << "no interchange";
			} else {
				for (const string &other_bus: busToStopR.buses) {
					if (r.bus != other_bus) {
						os << other_bus << " ";
					}
				}
			}
			if (i != count)
				os << endl;
		}
	}
	return os;
}

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
	if (r.buses_to_stops.empty()) {
		os << "No buses";
	} else {
		auto count = r.buses_to_stops.size();
		int i = 0;
		for (const auto &bus_item: r.buses_to_stops) {
			os << "Bus " << bus_item.first << ": ";
			for (const auto &busToStopR: bus_item.second) {
				os << busToStopR.stop << " ";
			}
			i++;
			if (i != count)
				os << endl;
		}
	}
	return os;
}


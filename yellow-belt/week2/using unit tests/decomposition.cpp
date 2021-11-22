#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
	for (const auto &x: v) {
		os << x << " ";
	}
	return os;
}


enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

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

struct BusesForStopResponse {
	string stop;
	vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
	if (r.buses.empty()) {
		os << "No stop";
	} else {
		os << r.buses;
	}
	return os;
}

struct StopsForBusResponse {
	string bus;
	vector<BusesForStopResponse> stops;
};

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

struct AllBusesResponse {
	map<string, vector<BusesForStopResponse>> buses_to_stops;
};

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

class BusManager {
public:
	void AddBus(const string &bus, const vector<string> &stops) {
		for (const auto &stop: stops) {
			stops_to_buses[stop].push_back(bus);
		}
		buses_to_stops[bus] = stops;
	}

	BusesForStopResponse GetBusesForStop(const string &stop) const {
		BusesForStopResponse r;
		r.stop = stop;
		if (stops_to_buses.find(stop) == stops_to_buses.end()) {
			return r;
		}
		r.buses = stops_to_buses.at(stop);
		return r;
	}

	StopsForBusResponse GetStopsForBus(const string &bus) const {
		StopsForBusResponse r;
		r.bus = bus;
		if (buses_to_stops.find(bus) == buses_to_stops.end())
			return r;
		vector<BusesForStopResponse> v;
		for (auto &stop: buses_to_stops.at(bus)) {
			BusesForStopResponse busesForStopResponse;
			busesForStopResponse.stop = stop;
			if (stops_to_buses.find(stop) != stops_to_buses.end())
				busesForStopResponse.buses = stops_to_buses.at(stop);
			v.push_back(busesForStopResponse);
		}
		r.stops = v;
		return r;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse r;
		for (auto&[bus, stops_for_bus]: buses_to_stops) {
			for (auto &stop: stops_for_bus) {
				BusesForStopResponse busesForStopResponse;
				busesForStopResponse.stop = stop;
				if (buses_to_stops.find(bus) != buses_to_stops.end())
					busesForStopResponse.buses = buses_to_stops.at(bus);
				r.buses_to_stops[bus].push_back(busesForStopResponse);
			}
		}
		return r;
	}

private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};

int main8() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				cout << bm.GetBusesForStop(q.stop) << endl;
				break;
			case QueryType::StopsForBus:
				cout << bm.GetStopsForBus(q.bus) << endl;
				break;
			case QueryType::AllBuses:
				cout << bm.GetAllBuses() << endl;
				break;
		}
	}

	return 0;
}
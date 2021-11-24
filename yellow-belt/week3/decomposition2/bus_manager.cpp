#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
	for (const auto &stop: stops) {
		stops_to_buses[stop].push_back(bus);
	}
	buses_to_stops[bus] = stops;
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
	BusesForStopResponse r;
	r.stop = stop;
	if (stops_to_buses.find(stop) == stops_to_buses.end()) {
		return r;
	}
	r.buses = stops_to_buses.at(stop);
	return r;
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
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
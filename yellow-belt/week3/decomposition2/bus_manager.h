#pragma once

#include <string>
#include <vector>
#include <string>
#include <map>
#include <iostream>


#include "responses.h"

using namespace std;

#ifndef WEEK3_BUS_MANAGER_H
#define WEEK3_BUS_MANAGER_H


class BusManager {
public:
	void AddBus(const string &bus, const vector<string> &stops);
	BusesForStopResponse GetBusesForStop(const string &stop) const;
	StopsForBusResponse GetStopsForBus(const string &bus) const;
	AllBusesResponse GetAllBuses() const;

private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};


#endif //WEEK3_BUS_MANAGER_H

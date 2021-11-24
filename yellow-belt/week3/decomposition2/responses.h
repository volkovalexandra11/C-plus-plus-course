#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


struct BusesForStopResponse {
	string stop;
	vector<string> buses;
};

struct StopsForBusResponse {
	string bus;
	vector<BusesForStopResponse> stops;
};

struct AllBusesResponse {
	map<string, vector<BusesForStopResponse>> buses_to_stops;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);
ostream &operator<<(ostream &os, const StopsForBusResponse &r);
ostream &operator<<(ostream &os, const AllBusesResponse &r);

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

auto make_tuple_from_region(const Region &region) {
	return make_tuple(region.std_name, region.parent_std_name, region.names, region.population);
}

bool operator<(const Region &lhs, const Region &rhs) {
	auto left = make_tuple_from_region(lhs);
	auto right = make_tuple_from_region(rhs);
	return left < right;
}

int FindMaxRepetitionCount(const vector<Region> &regions) {
	if (regions.empty()) return 0;
	map<Region, int> repetitions;
	int maximum = 0;
	for (const Region& reg: regions) {
		maximum = max(maximum, ++repetitions[reg]);
	}
	return maximum;
}


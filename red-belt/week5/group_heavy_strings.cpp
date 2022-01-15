#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

template <typename String>
using Group = vector<String>;

template <typename String>
using Char = typename String::value_type;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	map<set<Char<String>>, vector<String>> groups;

	for (auto& str : strings) {
		set<Char<String>> letters;
		String string1;

		for (auto& ch : str) {
			string1.push_back(move(ch));
			letters.insert(string1.back());
		}

		groups[move(letters)].push_back(move(string1));
	}

	vector<Group<String>> res;
	res.reserve(groups.size());
	for (auto& [letters, group] : groups) {
		res.push_back(move(group));
	}
	return res;
}


void TestGroupingABC() {
	vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));  // РџРѕСЂСЏРґРѕРє РіСЂСѓРїРї РЅРµ РёРјРµРµС‚ Р·РЅР°С‡РµРЅРёСЏ
	ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
	ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
	vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));  // РџРѕСЂСЏРґРѕРє РіСЂСѓРїРї РЅРµ РёРјРµРµС‚ Р·РЅР°С‡РµРЅРёСЏ
	ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
	ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
	ASSERT_EQUAL(groups[2], vector<string>({"port"}));
	ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main2() {
	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);
	return 0;
}